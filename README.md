*This project has been created as part of the 42 curriculum by <login1>.*

# push_swap

## Description

**push_swap** is an algorithmic project from the 42 curriculum focused on data structures, algorithmic complexity, and sorting optimization.

The primary goal of the project is to sort a given stack of unique integers in ascending order using only two stacks (**Stack A** and **Stack B**) and a strictly limited set of 11 stack operations. The program must output the shortest possible sequence of instructions to `stdout` that results in a fully sorted **Stack A** and an empty **Stack B**.

Key features of this implementation include:
* **Coordinate Compression (Indexing):** Normalizing arbitrary signed integers into sequential ranks from `0` to `n - 1`.
* **Disorder Metric Calculation:** Measuring the initial inversion ratio of the input stack prior to sorting.
* **Four Sorting Strategies:** Supporting Simple $O(n^2)$, Medium $O(n\sqrt{n})$, Complex $O(n \log n)$, and an **Adaptive** mode that automatically selects the optimal algorithm based on the measured disorder.
* **Benchmarking Mode (`--bench`):** Tracking total operations and per-instruction counts, outputting a formatted statistical report to `stderr`.

---

## Allowed Operations

| Operation | Description |
| :--- | :--- |
| `sa` | **Swap A:** Swap the first 2 elements at the top of stack `a`. |
| `sb` | **Swap B:** Swap the first 2 elements at the top of stack `b`. |
| `ss` | **Swap Both:** Execute `sa` and `sb` simultaneously. |
| `pa` | **Push A:** Take the top element from `b` and put it at the top of `a`. |
| `pb` | **Push B:** Take the top element from `a` and put it at the top of `b`. |
| `ra` | **Rotate A:** Shift up all elements of stack `a` by 1 (the first element becomes the last). |
| `rb` | **Rotate B:** Shift up all elements of stack `b` by 1 (the first element becomes the last). |
| `rr` | **Rotate Both:** Execute `ra` and `rb` simultaneously. |
| `rra` | **Reverse Rotate A:** Shift down all elements of stack `a` by 1 (the last element becomes the first). |
| `rrb` | **Reverse Rotate B:** Shift down all elements of stack `b` by 1 (the last element becomes the first). |
| `rrr` | **Reverse Rotate Both:** Execute `rra` and `rrb` simultaneously. |

---

## Instructions

### 1. Compilation & Installation

Clone the repository and compile the project using the provided `Makefile`. The code is compiled with `-Wall -Wextra -Werror` flags and strictly adheres to the 42 **Norminette** standard.

    # Compile the push_swap executable
    make

    # Remove object files (.o)
    make clean

    # Remove object files and the binary executable
    make fclean

    # Recompile the entire project from scratch
    make re

### 2. Execution & Usage Examples

Run the program by passing a sequence of unique integers either as separate command-line arguments or as a single space-separated string:

    # Standard execution (runs --adaptive mode by default)
    ./push_swap 42 -5 19 0 8

    # Passing arguments as a single quoted string
    ./push_swap "42 -5 19 0 8"

#### Strategy Selection Flags:

    # Force Simple O(n^2) selection sort strategy
    ./push_swap --simple 5 2 9 1 3

    # Force Medium O(n * sqrt(n)) chunk-based strategy
    ./push_swap --medium 5 2 9 1 3

    # Force Complex O(n log n) bitwise Radix sort strategy
    ./push_swap --complex 5 2 9 1 3

    # Explicitly run Adaptive strategy (default)
    ./push_swap --adaptive 5 2 9 1 3

#### Benchmarking Mode:

Add the `--bench` flag to output detailed complexity and operation statistics to `stderr` while keeping `stdout` clean for piping into `checker`:

    ./push_swap --bench 4 3 2 1

Example output on `stderr`:

    [bench] disorder:   100.00%
    [bench] strategy:   Adaptive / O(n log n)
    [bench] total_ops:  14
    [bench] sa:   1  sb:   0  ss:   0  pa:   4  pb:   4
    [bench] ra:   3  rb:   0  rr:   0  rra:  2  rrb:  0  rrr:   0

#### Verification and Move Counting:

    # Validate output using the official 42 checker
    ARG="4 67 3 87 23"; ./push_swap $ARG \vert{} ./checker_linux$ARG

    # Count the number of operations for 100 random integers
    ARG=$(shuf -i 0-9999 -n 100); ./push_swap$ARG | wc -l

    # Count the number of operations for 500 random integers
    ARG=$(shuf -i 0-9999 -n 500); ./push_swap$ARG | wc -l

---

## Detailed Explanation and Justification of Algorithms

### 1. Data Structure Choice: Doubly Linked List
Instead of static arrays (which require $O(n)$ memory shifts whenever an element is pushed or rotated), this project uses a **doubly linked list** (`t_node`) managed by a stack header structure (`t_stack`):
* **`t_node`** stores `value` (original integer), `index` (normalized rank in `[0, n - 1]`), and pointers `next` and `prev`.
* **`t_stack`** stores pointers to both the `top` and `bottom` nodes along with the current `size`.
* **Justification:** Maintaining direct pointers to both ends of the list allows all 11 stack operations (`swap`, `push`, `rotate`, and `rev_rotate`) to execute in strict **$O(1)$ constant time** via pointer rewiring without traversing the list.

### 2. Pre-processing: Coordinate Compression (Indexing)
Before sorting begins, `index_stack` assigns each node an `index` from `0` to `n - 1` equal to the number of elements in the stack that are strictly smaller than its value.
* **Justification:** Indexing transforms arbitrary signed integers (including negative numbers and `INT_MIN` / `INT_MAX` extremes) into a contiguous range `[0, n - 1]`. This simplifies range comparisons in Chunk Sort and enables direct binary bit inspection in Radix Sort.

### 3. Base Cases (`size <= 3`)
* **2 Elements:** Executes a single `sa` if the top element is greater than the bottom element.
* **3 Elements (`sort_three`):** Guarantees sorting in **at most 2 operations**. In step 1, the maximum value among the three nodes is rotated to `bottom` (`ra` if the maximum is at `top`, or `rra` if it is in the middle). In step 2, if the top two elements remain out of order, a single `sa` swaps them into place.

### 4. Simple Strategy — $O(n^2)$: Minimum Extraction (Selection Sort)
* **Mechanism:** The algorithm repeatedly searches **Stack A** for the node with the smallest remaining `index` (`target = 0, 1, 2...`), calculates its current position to determine the shortest rotation direction (`ra` if located in the upper half `pos <= size / 2`, or `rra` if located in the lower half), brings it to the top, and pushes it to **Stack B** (`pb`). Once only 3 elements remain in **Stack A**, `sort_three` orders them, and all elements in **Stack B** are pushed back to **Stack A** (`pa`).
* **Justification:** Scanning the stack takes $O(n)$ and rotating takes at most $n / 2$ operations per element, yielding $O(n^2)$ overall complexity. For small inputs or nearly sorted stacks (`disorder < 0.20`), it avoids bucket partitioning overhead and achieves very low operation counts.

### 5. Medium Strategy — $O(n\sqrt{n})$: Chunk-Based Sort (K-Sort)
* **Mechanism:**
  1. **Phase 1 (Distribution from A to B):** A sliding window of width `chunk_size` $\approx \sqrt{n}$ (`15` for $n \le 100$, `30` for $n = 500$) and a counter `i` are maintained. If `a->top->index <= i`, the element is pushed to **Stack B** (`pb`) and rotated to the bottom (`rb`), incrementing `i`. Else if `a->top->index <= i + chunk_size`, the element is pushed to the top of **Stack B** (`pb`), incrementing `i`. Otherwise, **Stack A** is rotated (`ra`). This arranges **Stack B** into a K-shaped distribution where smaller indices cluster near the middle and larger indices sit near the top and bottom edges.
  2. **Phase 2 (Reconstruction from B to A):** The algorithm repeatedly locates the maximum remaining index (`b->size - 1`) in **Stack B**, rotates it to the top via the shortest path (`rb` or `rrb`), and pushes it back to **Stack A** (`pa`).
* **Justification:** Partitioning into $\approx \sqrt{n}$ chunks keeps candidate elements close to the top or bottom of **Stack B**, reducing the average rotation cost during reconstruction to $O(\sqrt{n})$ per element and $O(n\sqrt{n})$ in total. Empirically, this strategy averages **~600 moves for 100 numbers** and **~5000 moves for 500 numbers**, outperforming pure Radix Sort on standard evaluation sizes.

### 6. Complex Strategy — $O(n \log n)$: LSD Bitwise Radix Sort
* **Mechanism:** Operates on the binary representation of each node's `index` from the Least Significant Bit (bit `0`) to the Most Significant Bit (`max_bits`). For each bit position `i`, all $n$ elements currently in **Stack A** are inspected:
  * If the $i$-th bit of `a->top->index` is `0`, the node is pushed to **Stack B** (`pb`).
  * If the $i$-th bit is `1`, the node is rotated in **Stack A** (`ra`).
  * After all $n$ elements have been processed for bit `i`, all nodes in **Stack B** are returned to **Stack A** (`pa`), preserving their relative order for the next bit pass.
* **Justification:** For $n$ elements, the maximum index is $n - 1$, requiring $\lceil \log_2(n) \rceil$ bit passes (7 passes for $n = 100$, 9 passes for $n = 500$). Because each pass executes at most $2n$ operations, the total complexity is strictly bounded by $O(n \log n)$ regardless of initial disorder.

### 7. Adaptive Strategy & Disorder Metric
Before executing any stack operations, the program computes the **disorder metric** as the ratio of inverted pairs to the total number of element pairs:
$$\text{disorder} = \frac{\text{mistakes}}{\frac{n(n - 1)}{2}}$$
where a mistake is any pair of positions $(i, j)$ with $i < j$ such that $a[i] > a[j]$.
* **`disorder < 0.20`:** Selects the **Simple $O(n^2)$** strategy to efficiently resolve low-entropy stacks.
* **`0.20 <= disorder < 0.50`:** Selects the **Medium $O(n\sqrt{n})$** chunk strategy for balanced partitioning and extraction.
* **`disorder >= 0.50`:** Selects the **Complex $O(n \log n)$** strategy to guarantee logarithmic scaling on highly disordered inputs.

---

## Resources

### Classic References & Documentation
* **Donald E. Knuth** — *The Art of Computer Programming, Volume 3: Sorting and Searching* (inversion theory, Selection Sort, and Radix Sort fundamentals).
* **Thomas H. Cormen et al.** — *Introduction to Algorithms (CLRS)* (asymptotic analysis, doubly linked lists, and comparison vs. non-comparison sorting).
* **Push_Swap Visualizer:** [o-reo/push_swap_visualizer](https://github.com/o-reo/push_swap_visualizer) (used for visual debugging of stack operations and K-Sort distributions).
* **GeeksforGeeks:** Articles on [Radix Sort](https://www.geeksforgeeks.org/radix-sort/) and [Counting Inversions in an Array](https://www.geeksforgeeks.org/inversion-count-in-array-using-merge-sort/).

### AI Usage Disclosure
In compliance with the 42 curriculum guidelines, Artificial Intelligence (Google Gemini) was used as a study partner and assistant for the following tasks:
* **Data Structure Architecture:** Understanding pointer manipulation (`next` and `prev` links) in doubly linked lists compared to arrays.
* **Norminette Compliance:** Refactoring the command dispatcher (`exec_op` and `exec_rotate`) and sorting helper functions to satisfy the 25-line-per-function and single-statement-per-line rules.
* **Algorithm Verification:** Reviewing the mathematical logic for coordinate compression (`index_stack`), K-Sort chunk window sizing ($O(n\sqrt{n})$), and bitwise LSD Radix Sort ($O(n \log n)$).
* **Documentation:** Structuring and formatting this `README.md` file according to the project specification.
