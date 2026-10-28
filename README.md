*This project has been created as part of the 42 curriculum by yhubaren, mvdovenk.*

# push_swap

## Description

`push_swap` is a 42 algorithm project about sorting integers with two stacks and
a restricted set of operations. Stack `A` initially contains the input values,
with the first command-line value at the top, and stack `B` is empty.

The program must generate an operation sequence that sorts `A` in ascending
order while leaving `B` empty. The smallest value must be at the top of `A`.
Only the operations listed in [Allowed operations](#allowed-operations) may be
generated.

This project contains four runtime-selectable strategies:

- **Simple**: an `O(n²)` baseline strategy;
- **Medium**: a chunk-based `O(n√n)` strategy;
- **Complex**: an LSD binary radix `O(n log n)` strategy;
- **Adaptive**: selects an internal strategy using the input disorder.

The complexity classes above are expressed in the Push_swap operation model:
the cost is the number of generated Push_swap operations, not the cost of a
classical array sort.

## Instructions

### Requirements

The project is written in C and follows the 42 Norm. It uses the project-local
[`libft/`](./libft) and is built with:

- `cc`;
- `make`;
- `-Wall -Wextra -Werror`.

No package installation is required.

The implementation does not use global variables, handles allocation failures
through the project error path, and frees all allocated stack memory before
exiting.

### Compilation

From the repository root:

```bash
make
```

This builds the local libft, compiles the project, and creates `push_swap`.

Available Makefile targets:

```bash
make          # Build push_swap
make clean    # Remove project and libft object files
make fclean   # Remove objects, libft.a, and push_swap
make re       # Rebuild from scratch
```

The Makefile does not relink unchanged object files.

### Execution

The basic syntax is:

```bash
./push_swap [strategy] [--bench] [integers...]
```

Examples:

```bash
./push_swap 2 1 3 6 5 8
./push_swap "42 -5 19 0 8"
./push_swap --simple 5 4 3 2 1
./push_swap --medium 5 2 9 1 3
./push_swap --complex 5 2 9 1 3
./push_swap --adaptive 5 2 9 1 3
```

The first integer is the top of stack `A`. Numeric arguments may be supplied as
separate arguments, in one quoted space-separated argument, or in a mixture of
both forms.

If no integers are supplied, the program exits successfully without output.
If the input is already sorted, it also emits no operations. Every emitted
operation is printed on its own line to `stdout`, with no additional text.

### Strategy selectors

At most one selector may be supplied:

| Selector | Behavior |
| --- | --- |
| `--simple` | Force the `O(n²)` Simple strategy. |
| `--medium` | Force the `O(n√n)` Medium strategy. |
| `--complex` | Force the `O(n log n)` Complex strategy. |
| `--adaptive` | Force the disorder-based Adaptive strategy. |
| no selector | Use Adaptive by default. |

Selectors work for every valid input size and disorder level. They may be
placed before or after `--bench`:

```bash
./push_swap --bench --complex 4 3 2 1
./push_swap --medium --bench 5 2 9 1 3
```

### Benchmark mode

`--bench` keeps the operation stream on `stdout` and writes benchmark
information to `stderr` after sorting:

```bash
./push_swap --bench --adaptive 4 3 2 1 \
    >operations.txt \
    2>benchmark.txt
```

The benchmark contains:

- the disorder percentage with two decimal places;
- the selected strategy and its theoretical complexity;
- the total number of generated operations;
- the count of every operation type: `sa`, `sb`, `ss`, `pa`, `pb`, `ra`, `rb`,
  `rr`, `rra`, `rrb`, and `rrr`.

The benchmark appears only when `--bench` is present.

## Allowed operations

The program uses two stacks named `A` and `B`. `A` starts with the input and `B`
starts empty.

| Operation | Effect |
| --- | --- |
| `sa` | Swap the top two elements of `A`. |
| `sb` | Swap the top two elements of `B`. |
| `ss` | Apply `sa` and `sb` simultaneously. |
| `pa` | Push the top element of `B` onto `A`. |
| `pb` | Push the top element of `A` onto `B`. |
| `ra` | Rotate `A` upward: its first element becomes its last. |
| `rb` | Rotate `B` upward: its first element becomes its last. |
| `rr` | Apply `ra` and `rb` simultaneously. |
| `rra` | Reverse-rotate `A`: its last element becomes its first. |
| `rrb` | Reverse-rotate `B`: its last element becomes its first. |
| `rrr` | Apply `rra` and `rrb` simultaneously. |

Swap and rotate operations do nothing when their stack has fewer than two
elements. A push operation does nothing when its source stack is empty.

## Input validation and errors

Accepted input consists of unique signed 32-bit decimal integers, including
`INT_MIN` and `INT_MAX`. The parser accepts an optional leading `+` or `-`.

The program rejects:

- duplicate values;
- values outside the signed 32-bit range;
- non-numeric tokens;
- a sign without digits;
- empty or whitespace-only numeric arguments;
- unknown options;
- repeated `--bench`;
- multiple strategy selectors;
- a selector without integer arguments.

For every invalid input, the program writes exactly:

```text
Error
```

followed by a newline to `stderr` and exits with a non-zero status.

Examples:

```bash
./push_swap 1 2 1
./push_swap 2147483648
./push_swap -2147483649
./push_swap --unknown 1 2
./push_swap --simple --medium 3 2 1
```

## Algorithms

### Disorder metric

Disorder is measured before any sorting operation. For every pair of positions
`i < j`, an inversion is counted when `A[i] > A[j]`:

```text
mistakes = number of inversions
total_pairs = n * (n - 1) / 2
disorder = mistakes / total_pairs
```

The result is in the range `[0, 1]`:

- `0` means that `A` is already sorted;
- `1` means reverse order;
- intermediate values represent partially disordered input.

For an input with fewer than two elements, disorder is treated as zero.

### Simple strategy — `O(n²)`

The Simple strategy repeatedly selects the next smallest indexed value, rotates
it to the top using the shorter direction, and moves it to `B`. After the
remaining values are ordered, it restores the extracted values to `A`.

This selection-style approach is easy to reason about and is effective for
small or nearly sorted inputs. Its upper bound in the Push_swap operation model
is `O(n²)` generated operations, with linear stack storage.

### Medium strategy — `O(n√n)`

The Medium strategy divides the compressed index range into
approximately `√n` chunks. It distributes values from `A` to `B`, rotates `B`
to keep the current chunk organized, then returns values from `B` to `A` in
descending index order.

Chunk partitioning limits the amount of rotation required for each range. Its
target upper bound in the Push_swap operation model is `O(n√n)` generated
operations, with linear stack storage.

### Complex strategy — `O(n log n)`

The Complex strategy uses LSD binary radix sorting on compressed indexes. For
each bit position it:

1. pushes zero-bit values from `A` to `B`;
2. rotates one-bit values in `A`;
3. pushes all values from `B` back to `A`;
4. continues with the next bit.

There are `O(log n)` bit passes and `O(n)` work per pass, giving an
`O(n log n)` upper bound in the Push_swap operation model and linear stack
storage.

### Adaptive strategy

Adaptive measures disorder before performing any moves and chooses an internal
strategy deterministically:

| Input and disorder | Internal strategy |
| --- | --- |
| `n <= 3` | Small-stack sorting. |
| `4 <= n <= 5` | Simple. |
| `n > 5`, disorder `< 0.20` | Simple, `O(n²)`. |
| `n > 5`, `0.20 <= disorder < 0.50` | Medium, `O(n√n)`. |
| `n > 5`, disorder `>= 0.50` | Complex, `O(n log n)`. |

The thresholds follow the subject requirements: low disorder uses the Simple
class, medium disorder uses the Medium class, and high disorder uses the
Complex class. The small-input cases use dedicated small-stack handling because
the finite-size operation count is more important than selecting a large-scale
strategy.

The adaptive strategy is a deterministic policy, not an exhaustive search, so
it does not claim a mathematically minimal sequence for every permutation.

## Performance targets

The subject evaluates the number of generated operations with random inputs:

| Input size | Minimum requirement | Good performance | Excellent performance |
| --- | ---: | ---: | ---: |
| 100 numbers | `< 2000` | `< 1500` | `< 700` |
| 500 numbers | `< 12000` | `< 8000` | `< 5500` |

Example checks:

```bash
ARG="$(shuf -i 0-9999 -n 100)"
./push_swap $ARG | wc -l

ARG="$(shuf -i 0-9999 -n 500)"
./push_swap $ARG | wc -l
```

Operation output can be checked with a checker supplied by the evaluation
environment:

```bash
ARG="4 67 3 87 23"
./push_swap --complex $ARG | ./checker_linux $ARG
```

The expected result is `OK`.

## Resources

### References

- The official 42 `push_swap` subject (`en.subject_push_swap.pdf`) — project
  requirements, operation definitions, disorder metric, strategy classes,
  benchmark format, and performance targets.
- [Big O notation — Wikipedia](https://en.wikipedia.org/wiki/Big_O_notation) —
  asymptotic complexity terminology.
- [Inversion (discrete mathematics) — Wikipedia](https://en.wikipedia.org/wiki/Inversion_(discrete_mathematics)) —
  the inversion concept used by the disorder metric.
- [Radix sort — Wikipedia](https://en.wikipedia.org/wiki/Radix_sort) —
  background for the Complex strategy.

### Use of AI

AI was used as a development assistant for repetitive and review-oriented
tasks. In particular, it helped with:

- reviewing README coverage against the official requirements;

All generated suggestions were reviewed, adapted to the repository, and tested
by the project learners. The learners remain responsible for understanding and
defending the complete implementation.

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
    │   ├── sort_3.c
    │   └── strategy.c
    ├── operations/
    │   ├── execute.c
    │   ├── index.c
    │   ├── push.c
    │   ├── rotate.c
    │   └── swap.c
    ├── parsing/
    │   ├── parse_args.c
    │   ├── validate.c
    │   ├── disorder.c
    │   └── options.c
    └── utils/
        ├── bench.c
        └── free_and_error.c
```

## Testing and cleanup

Useful local checks:

```bash
make re
norminette src includes
git diff --check
make fclean
```

The mandatory `push_swap` part is included. The optional bonus `checker`
program is not included in this repository; `checker_linux` in the examples
must be supplied separately.
