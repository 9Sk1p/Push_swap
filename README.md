# push_swap

`push_swap` is a 42 algorithm project. It receives a collection of unique
integers, represents them in stack `A`, and prints a sequence of allowed
operations that leaves `A` sorted in ascending order and stack `B` empty.

The program writes sorting operations to `stdout`. Errors and optional
benchmark information are written to `stderr`.

## Contents

- [Requirements](#requirements)
- [Build](#build)
- [Usage](#usage)
- [Options](#options)
- [Allowed operations](#allowed-operations)
- [Input validation](#input-validation)
- [How the implementation works](#how-the-implementation-works)
- [Sorting strategies](#sorting-strategies)
- [Benchmark mode](#benchmark-mode)
- [Verification and testing](#verification-and-testing)
- [Project structure](#project-structure)
- [Complexity](#complexity)
- [Cleanup](#cleanup)
- [Scope](#scope)

## Requirements

The project uses:

- `cc`;
- `make`;
- the C standard library functions allowed by the 42 subject;
- the local `libft` stored in [`libft/`](./libft).

The top-level Makefile compiles with:

```text
-Wall -Wextra -Werror
```

No external runtime dependency is required.

## Build

From the repository root:

```bash
make
```

This builds `libft/libft.a`, compiles the project object files, and creates:

```text
./push_swap
```

Useful targets:

```bash
make          # Build the executable
make clean    # Remove project and libft object files
make fclean   # Remove object files, libft.a, and push_swap
make re       # Run fclean and build again
```

The Makefile builds `libft` through `make -C libft` and links the resulting
static library into `push_swap`.

## Usage

The simplest invocation is:

```bash
./push_swap 42 -5 19 0 8
```

Arguments can be separate shell arguments or one quoted, space-separated
argument:

```bash
./push_swap 42 -5 19 0 8
./push_swap "42 -5 19 0 8"
```

For an already sorted input, the program prints nothing and exits successfully:

```bash
./push_swap 1 2 3 4
```

For an unsorted input, every output line is one operation:

```bash
./push_swap 2 1
# sa
```

The output can be redirected or piped:

```bash
./push_swap 4 3 2 1 > operations.txt
```

## Options

### Strategy selectors

Exactly zero or one strategy selector may be used:

```bash
./push_swap --simple 5 2 9 1 3
./push_swap --medium 5 2 9 1 3
./push_swap --complex 5 2 9 1 3
./push_swap --adaptive 5 2 9 1 3
```

If no selector is supplied, `--adaptive` is used.

The selector may appear before or after `--bench`:

```bash
./push_swap --bench --complex 5 2 9 1 3
./push_swap --medium --bench 5 2 9 1 3
```

The following are errors:

```bash
./push_swap --simple --medium 5 2 9 1 3
./push_swap --adaptive --simple 5 2 9 1 3
./push_swap --unknown 5 2 9 1 3
./push_swap --simple
```

Each error prints `Error` followed by a newline to `stderr` and exits with a
non-zero status.

### `--bench`

`--bench` enables benchmark output without changing the operation stream:

```bash
./push_swap --bench 4 3 2 1 >operations.txt 2>benchmark.txt
```

The contents of `operations.txt` are suitable for a checker. The contents of
`benchmark.txt` contain disorder, the selected strategy, the total number of
operations, and a count for each operation.

`--bench` may be specified once and combined with one strategy selector:

```bash
./push_swap --bench --simple 5 2 9 1 3
./push_swap --complex --bench 5 2 9 1 3
```

## Allowed operations

The algorithms use only these 11 operations:

| Operation | Effect |
| --- | --- |
| `sa` | Swap the top two elements of `A`. |
| `sb` | Swap the top two elements of `B`. |
| `ss` | Apply `sa` and `sb`. |
| `pa` | Push the top of `B` onto `A`. |
| `pb` | Push the top of `A` onto `B`. |
| `ra` | Move the top of `A` to its bottom. |
| `rb` | Move the top of `B` to its bottom. |
| `rr` | Apply `ra` and `rb`. |
| `rra` | Move the bottom of `A` to its top. |
| `rrb` | Move the bottom of `B` to its top. |
| `rrr` | Apply `rra` and `rrb`. |

Operations on a stack with fewer than two elements do nothing. Push operations
on an empty source stack also do nothing internally, although the sorting
algorithms avoid emitting unnecessary pushes.

## Input validation

The parser accepts:

- positive and negative decimal integers;
- an optional leading `+` or `-`;
- `INT_MIN` (`-2147483648`);
- `INT_MAX` (`2147483647`);
- multiple arguments;
- one or more space-separated arguments in a quoted shell argument;
- mixed forms, for example `./push_swap "3 -1" 8`.

The parser rejects:

- duplicate values;
- values outside the signed 32-bit integer range;
- non-decimal tokens;
- a sign without digits;
- empty or whitespace-only numeric arguments;
- unknown options;
- repeated `--bench`;
- more than one strategy selector;
- a selector without any numbers.

Examples:

```bash
./push_swap 2147483647 -2147483648 0
./push_swap "3 -1 2" 8

./push_swap 1 2 1              # Error
./push_swap 2147483648         # Error
./push_swap -2147483649        # Error
./push_swap "+"                # Error
./push_swap ""                 # Error
./push_swap --unknown 1 2      # Error
```

With no arguments at all, `./push_swap` exits successfully without output.

## How the implementation works

### Stack representation

The project uses a doubly linked list:

```c
typedef struct s_node
{
    int             value;
    int             index;
    struct s_node   *next;
    struct s_node   *prev;
}   t_node;
```

Each stack stores its top, bottom, and current size:

```c
typedef struct s_stack
{
    t_node  *top;
    t_node  *bottom;
    int     size;
}   t_stack;
```

Keeping both end pointers makes swap, push, rotate, and reverse rotate pointer
operations constant time.

### Parsing

`parse_options` scans command-line options and returns the selected strategy
and benchmark state. `parse_args` splits numeric arguments, validates each
token, checks the integer range, detects duplicates, allocates a node, and
appends it to `A`.

### Coordinate compression

`index_stack` assigns each value a rank:

- the smallest value gets index `0`;
- the next value gets index `1`;
- the largest value gets index `n - 1`.

The original values remain in each node. Algorithms compare indexes because
they provide a compact range suitable for chunk boundaries and bit tests.

### Disorder

`calculate_disorder` counts inverted pairs:

```text
inversion = (i, j) where i < j and A[i] > A[j]
```

It returns:

```text
inversions / (n * (n - 1) / 2)
```

The result is `0.0` for an already sorted input and approaches `1.0` for a
reverse-sorted input.

### Operation execution

`exec_op` dispatches an operation to the low-level stack functions and prints
the command to `stdout`. When benchmark mode is enabled, it also increments
the operation counters. Benchmark data is never mixed into the operation
stream.

## Sorting strategies

### Simple

`sort_simple` repeatedly finds the next smallest index in `A`, rotates it to
the top using the shorter direction, and pushes it to `B`. It sorts the
remaining small stack and pushes the extracted elements back to `A`.

This is a straightforward selection-style algorithm. It is useful for small
inputs and low disorder.

### Medium

`sort_medium` uses a square-root-sized chunk window:

1. distribute indexed nodes from `A` to `B`;
2. rotate `B` while distributing low indexes;
3. locate the greatest remaining index in `B`;
4. rotate that node to the top using `rb` or `rrb`;
5. push it back to `A`.

The implementation uses a chunk size derived from `sqrt(n)`. It targets
`O(n sqrt(n))` behavior in the push_swap operation model.

### Complex

`sort_complex` is an LSD binary radix sort over the compressed indexes. For
each bit position:

1. push zero-bit elements from `A` to `B`;
2. rotate one-bit elements in `A`;
3. push all elements from `B` back to `A`;
4. continue with the next bit.

The number of passes is the number of bits needed to represent `n - 1`.
Its target complexity is `O(n log n)` in generated push_swap operations.

### Adaptive

`sort_adaptive` selects a strategy from the measured disorder:

| Disorder | Strategy |
| --- | --- |
| `< 0.20` | Simple |
| `0.20` to `< 0.50` | Medium |
| `>= 0.50` | Complex |

The thresholds are documented and deterministic. They are a strategy policy,
not a claim that the resulting sequence is mathematically minimal.

## Benchmark mode

Example:

```bash
./push_swap --bench --adaptive 4 3 2 1
```

Example `stderr` output:

```text
[bench] disorder: 100.00%
[bench] strategy: Adaptive
[bench] total_ops: <number of emitted operations>
[bench] sa: <count> sb: <count> ss: <count> pa: <count> pb: <count>
[bench] ra: <count> rb: <count> rr: <count> rra: <count> rrb: <count> rrr: <count>
```

The exact counts depend on the input and selected strategy. `total_ops` is the
sum of emitted operations. To keep the streams separate:

```bash
./push_swap --bench --complex 4 3 2 1 \
    >operations.txt \
    2>benchmark.txt
```

## Verification and testing

### Build check

```bash
make re
```

### Check an operation stream

If a checker binary is available locally:

```bash
ARG="4 67 3 87 23"
./push_swap $ARG | ./checker_linux $ARG
```

Expected result is `OK`. The repository does not include the bonus checker.

### Count operations

```bash
ARG="$(shuf -i 0-9999 -n 100)"
./push_swap $ARG | wc -l

ARG="$(shuf -i 0-9999 -n 500)"
./push_swap $ARG | wc -l
```

### Verify benchmark accounting

```bash
./push_swap --bench --complex 5 2 9 1 3 \
    >/tmp/push_swap.operations \
    2>/tmp/push_swap.benchmark

cat /tmp/push_swap.operations
cat /tmp/push_swap.benchmark
```

The number after `total_ops` must equal the number of operation lines:

```bash
wc -l </tmp/push_swap.operations
grep 'total_ops' /tmp/push_swap.benchmark
```

### Edge-case checklist

Run these cases when changing parsing or algorithms:

```bash
./push_swap
./push_swap 1
./push_swap 1 2
./push_swap 2 1
./push_swap 3 1 2
./push_swap 1 2 3
./push_swap "5 4 3 2 1"
./push_swap -2147483648 0 2147483647
./push_swap 1 2 1
./push_swap 2147483648
./push_swap -2147483649
./push_swap ""
./push_swap --bench --simple 3 2 1
./push_swap --simple --medium 3 2 1
```

The valid cases should sort successfully. Invalid cases should print `Error`
to `stderr` and return a non-zero status.

## Project structure

```text
.
├── Makefile
├── README.md
├── includes/
│   └── push_swap.h
├── libft/
└── src/
    ├── main.c
    ├── algorithms/
    │   ├── simple.c
    │   ├── medium.c
    │   ├── complex.c
    │   └── sort_3.c
    ├── operations/
    │   ├── execute.c
    │   ├── index.c
    │   ├── push.c
    │   ├── rotate.c
    │   └── swap.c
    ├── parsing/
    │   ├── parse_args.c
    │   ├── validate.c
    │   └── disorder.c
    └── utils/
        ├── bench.c
        └── free_and_error.c
```

Important responsibilities:

| File | Responsibility |
| --- | --- |
| `main.c` | Initialize stacks, parse options, run the selected strategy, clean up. |
| `parse_args.c` | Split arguments and build stack `A`. |
| `validate.c` | Validate decimal tokens, ranges, and duplicates. |
| `disorder.c` | Parse options, test sortedness, calculate disorder. |
| `execute.c` | Dispatch operations, print them, and count them. |
| `index.c` | Assign compressed indexes. |
| `swap.c` | Implement `sa`/`sb` primitives. |
| `push.c` | Implement `pa`/`pb` primitives. |
| `rotate.c` | Implement rotate and reverse-rotate primitives. |
| `simple.c` | Selection-style strategy. |
| `medium.c` | Chunk strategy and adaptive selection. |
| `complex.c` | Binary radix strategy. |
| `sort_3.c` | Small-stack sorting. |
| `bench.c` | Format benchmark output to `stderr`. |
| `free_and_error.c` | Free allocated memory and report `Error`. |

## Complexity

The expected strategy targets are:

| Component | Target |
| --- | --- |
| Stack operations | `O(1)` pointer updates |
| Indexing | `O(n^2)` time, `O(n)` node storage |
| Disorder calculation | `O(n^2)` time |
| Simple strategy | `O(n^2)` generated-operation target |
| Medium strategy | `O(n sqrt(n))` generated-operation target |
| Complex strategy | `O(n log n)` generated-operation target |

Operation count is the relevant cost model for this project. The strategies
are deterministic, but they do not promise a globally shortest sequence for
every input.

## Cleanup

Remove all generated build files before submitting or switching branches:

```bash
make fclean
```

This removes project object files, libft object files, `libft.a`, and the
`push_swap` executable.

## Scope

The mandatory `push_swap` executable, four strategies, adaptive selection,
input validation, benchmark mode, and build system are included.

The bonus `checker` program is intentionally not included. A local
`checker_linux` or equivalent checker can still be used for external
verification as shown above.
