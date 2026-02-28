# Month 1 — The Probabilistic Sieve

**Difficulty:** Medium  
**Tags:** Number Theory, Probability, Combinatorics, Bitmasks  
**Setter:** Tilak Jain  
**Date:** February 2, 2026  
**Top Solver:** Samarth Gupta (3:40 pm)

---

## Problem

You are given an array `A` of `N` positive integers. You perform the following randomized process:

1. Start with an empty set `S`.
2. For each element `A[i]`, independently add it to `S` with probability `p[i] = φ(A[i]) / A[i]`, where `φ` is Euler's totient function.
3. After selecting elements, compute `G = gcd(S)` (Greatest Common Divisor of all elements in `S`).
4. If `S` is empty, define `G = 0`.

**Task:** Find the expected value of `G` modulo `10^9 + 7`.

> If the expected value is a fraction `p/q` in lowest terms, output `(p × q⁻¹) mod (10^9 + 7)`.

### Input Format

The first line contains `T` (number of test cases).  
For each test case:
- First line: integer `N`
- Second line: `N` space-separated integers `A[1] ... A[N]`

### Output Format

For each test case, output a single integer — the expected value of the GCD modulo `10^9 + 7`.

### Constraints

- `1 ≤ T ≤ 100`
- `1 ≤ N ≤ 20`
- `2 ≤ A[i] ≤ 10^6`

---

## Examples

### Example 1
```
Input:
3
2
2 4
3
6 10 15
1
12

Output:
2
951111124
4
```

**Explanation (Test Case 1, A = [2, 4]):**

- `φ(2) = 1`, so `p[0] = 1/2`
- `φ(4) = 2`, so `p[1] = 2/4 = 1/2`

All 4 outcomes (each with probability 1/4):

| Subset | GCD |
|--------|-----|
| `{}` (empty) | 0 |
| `{2}` | 2 |
| `{4}` | 4 |
| `{2, 4}` | 2 |

`E[G] = (0 + 2 + 4 + 2) / 4 = 2` ✓

---

## Editorial

> *"This problem was born from a simple question: randomness usually destroys structure, but can it create it? By using Euler's totient function as a probability, we see a beautiful symmetry where the expected GCD becomes cleaner than any deterministic subset sum. It is a love letter to the Divisor Sum identity."*  
> — Tilak Jain

### Approach

At first glance, this looks like a combinatorial nightmare. We have `2^N` possible subsets, each with a complex probability attached. With N ≤ 20, brute-force subset enumeration (~1,048,576 subsets) is feasible within the time limit — but the probability factor `φ(x)/x` makes it intimidating.

**Why `φ(n)/n`?** This isn't an arbitrary choice. In number theory, `φ(n)/n` represents the density of integers coprime to `n`. This hints that the totient function's multiplicative properties will simplify the final expectation.

Our goal is `E[G]`. By the definition of expected value:

```
E[G] = Σ  gcd(S) × P(S)
      S⊆A
```

We iterate over every subset `S`, compute its probability `P(S)` and GCD, and accumulate.

### Key Lemmas

**1. Subset Probability**  
Since inclusions are independent:
```
P(S) = ∏ p_i  ×  ∏ (1 - p_j)
      i∈S       j∉S
```

**2. Modular Inverse**  
We cannot divide directly under a prime modulus. Use:
```
a/b ≡ a × b^(MOD-2)  (mod 10^9 + 7)
```
via fast exponentiation.

**3. The Empty Set**  
`gcd({}) = 0` by definition. This contributes `0` to the sum but is the most common source of bugs — make sure the empty subset is handled and doesn't cause a runtime error.

**4. Common Denominator Trick**  
Every subset's denominator is a divisor of `∏ A[i]`. Rather than reducing fractions, keep a running numerator and denominator in modular arithmetic.

### Step-by-Step Walkthrough (A = [2, 4])

**Step 1 — Probability Setup**
```
p_0 = φ(2)/2 = 1/2       1 - p_0 = 1/2
p_1 = φ(4)/4 = 2/4 = 1/2    1 - p_1 = 1/2
```

**Step 2 — Enumerate all 2² = 4 subsets**
```
mask = 00 → {}      P = (1/2)(1/2) = 1/4    gcd = 0
mask = 01 → {2}     P = (1/2)(1/2) = 1/4    gcd = 2
mask = 10 → {4}     P = (1/2)(1/2) = 1/4    gcd = 4
mask = 11 → {2,4}   P = (1/2)(1/2) = 1/4    gcd = 2
```

**Step 3 — Expected value**
```
E[G] = 0×(1/4) + 2×(1/4) + 4×(1/4) + 2×(1/4) = 8/4 = 2
```

### Complexity

| | |
|---|---|
| **Time** | `O(2^N × N)` per test case |
| **Space** | `O(N)` |

Exponential due to subset enumeration, feasible for N ≤ 20. The GCD step adds a factor of `log(max(A))`.

### Key Pitfalls

- **Empty set bug:** `gcd({})` must return 0, not crash or return the first element.
- **No direct division:** Everything must go through modular inverse — you cannot just divide numerator by denominator.
- **Shared denominator:** Every `P(S)` has the same denominator structure (`∏ A[i]`), which simplifies accumulation significantly.

---

## Solution Code

See [`solution.cpp`](./solution.cpp).
