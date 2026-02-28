# Month 2 — The Round Lot Puzzle

**Difficulty:** Medium  
**Tags:** Combinatorics, Modular Arithmetic, Market Microstructure, Subset Sum  
**Setter:** Tilak Jain  
**Date:** February 16, 2026  
**Top Solver:** TBD

---

## Problem

You are a market maker who only trades in round lots (multiples of 100 shares).

Throughout the trading day, you receive N orders, each for a random number of shares. You can combine *any subset* of these orders, and if their total is divisible by 100, you can execute them as one round lot trade.

**Task:** Count how many different non-empty subsets of orders sum to a multiple of 100.

### Input Format

- First line: integer `N`
- Second line: `N` space-separated integers representing order sizes

### Output Format

Single integer: count of non-empty subsets whose sum is divisible by 100.

### Constraints

- `1 ≤ N ≤ 20`
- `1 ≤ order[i] ≤ 1000`
- Time limit: 2 seconds
- Memory limit: 256 MB

---

## Examples

### Example 1
```
Input:
4
100 200 50 50

Output:
7
```

**Explanation:**

Valid subsets:

| Subset | Sum |
|--------|-----|
| `{100}` | 100 |
| `{200}` | 200 |
| `{100, 200}` | 300 |
| `{50, 50}` | 100 |
| `{100, 50, 50}` | 200 |
| `{200, 50, 50}` | 300 |
| `{100, 200, 50, 50}` | 400 |

Total: 7 valid subsets ✓

### Example 2
```
Input:
3
33 67 100

Output:
3
```

Valid subsets: `{100}`, `{33, 67}`, `{33, 67, 100}`.

### Example 3
```
Input:
5
25 25 25 25 100

Output:
3
```

Valid subsets: `{100}`, `{25, 25, 25, 25}`, `{25, 25, 25, 25, 100}`.

**Modular insight:** For `k` copies of 25 to sum to a multiple of 100, we need `k × 25 ≡ 0 (mod 100)`, which requires `k ≡ 0 (mod 4)`. Only `k=0` (empty) or `k=4` (all four) satisfy this.

### Example 4
```
Input:
6
150 250 300 50 75 25

Output:
15
```

**Key insight:** Work mod 100. Residues are: `150→50`, `250→50`, `300→0`, `50→50`, `75→75`, `25→25`. The element with residue 0 (300) is valid alone, and adding it to any already-valid subset keeps it valid.

---

## Editorial

### Approach

The key observation is that divisibility by 100 only depends on the sum mod 100 — so we can reduce every order to `order[i] % 100` upfront. From there, the approach is straightforward bitmask enumeration.

With N ≤ 20, we have at most `2^20 ≈ 1,048,576` subsets. For each non-empty subset, we accumulate the sum and check if it's divisible by 100. This gives roughly `2^20 × 20 ≈ 20 million` operations — well within the 2-second time limit.
```
count = 0
for each non-empty subset S (via bitmask):
    s = sum of order[i] for i in S
    if s % 100 == 0:
        count++
```

### Key Lemmas

**1. Modular Reduction**  
Only the residue mod 100 matters:
```
(a + b) % 100 == 0  ⟺  (a%100 + b%100) % 100 == 0
```
Reduce inputs first to keep sums small.

**2. Bitmask Subset Enumeration**  
Every integer `mask` from `1` to `2^N - 1` uniquely represents a non-empty subset. Bit `j` is set iff element `j` is included.

**3. Empty Set**  
`mask = 0` represents the empty subset — excluded since the problem asks for non-empty subsets only.

### Step-by-Step Walkthrough (orders = [100, 200, 50, 50])

**Step 1 — Reduce mod 100**
```
[100, 200, 50, 50]  →  [0, 0, 50, 50]
```

**Step 2 — Enumerate all 2⁴ - 1 = 15 non-empty subsets**

Only subsets where the residue sum ≡ 0 (mod 100) are counted.

**Step 3 — Count valid subsets**
```
Answer = 7
```

### Complexity

| | |
|---|---|
| **Time** | `O(2^N × N)` |
| **Space** | `O(N)` |

Feasible for N ≤ 20.

### Key Pitfalls

- **Don't forget mod reduction:** Working on raw values still gives correct results (since we check `% 100` at the end), but reducing first keeps intermediate sums smaller.
- **Non-empty subsets only:** Start `mask` from `1`, not `0`.
- **Duplicate elements are distinct:** `{50, 50}` at indices 2 and 3 are two separate orders — treat them as distinct elements.

---

## Solution Code

See [`solution.cpp`](./solution.cpp).
