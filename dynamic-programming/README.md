Here is a short summary of the questions and solutions.
---

## Jump
#### Problem Description
A frog starts on the first stone out of $n$ stones of varying heights and wants to reach the last ($n$-th) stone with the minimum possible total energy. From any stone $i$, the frog can jump to any of the next stones from $i+1$ up to $i+k$, where $k$ is a given constant. The energy consumed by a jump from stone $i$ to stone $j$ is equal to the absolute difference in their heights, $\vert{}height(i) - height(j)\vert{}$.
* **Time Limit:** 2 seconds
* **Memory Limit:** 1024 MB
* **Constraints:** $2 \le n \le 10^{5}$, $1 \le k \le 100$, $1 \le h_{i} \le 10^{4}$

### Approach
The problem is solved using **Dynamic Programming** to build up the minimum energy required to reach each stone:
1. **State Definition:** Let `array[i]` represent the minimum energy required to reach stone $i$ from the starting stone.
2. **Base Case:** The energy to reach the first stone (index 0) is $0$.
3. **Transition Relation:** For each subsequent stone $i$, the minimum energy is calculated by evaluating all possible previous jumping options within the range $[i-k, i-1]$:
$$\text{array}[i] = \min_{1 \le j \le k, i-j \ge 0} (\text{array}[i-j] + \vert{}\text{list}[i] - \text{list}[i-j]\vert{})$$

#### Complexity Analysis
* **Time Complexity:** $O(n \cdot k)$ since for each of the $n$ stones, we look back at up to $k$ previous stones.
* **Space Complexity:** $O(n)$ auxiliary space to store the heights list and the DP array.

#### C++ Solution Highlights

```cpp
int *array = new int[n];
array[0] = 0;
array[1] = abs(list[1] - list[0]);

for (int i = 2; i < n; i++) {
    int min = max;
    for (int j = 1; j <= k; j++) {
        if (i >= j) {
            int jump = array[i - j] + abs(list[i] - list[i - j]);
            if (jump < min) {
                min = jump;
            }
        }
    }
    array[i] = min;
}

```
## Unfair Lottery
#### Problem Description
You are organizing a lottery with $n$ participants, where each participant $i$ starts with a certain number of chances $a_i$ (ranging from $1$ to $3$). In each round, a die with faces $1$ through $n$ is rolled. If the selected participant still has remaining chances, one chance is decremented. The goal is to calculate the **expected number of rounds** required until all participants run out of all their chances ($a_i = 0$ for all $i$), accurate up to 9 decimal places.
* **Time Limit:** 2 seconds
* **Memory Limit:** 1024 MB
* **Constraints:** $n \le 300$, $1 \le a_i \le 3$

#### Approach
This problem is solved using **Dynamic Programming on Expected Values (Markov Chain / Expectation DP)**:
1. **State Space Compression:** Since each $a_i \in \{1, 2, 3\}$, the state can be represented by the counts of participants having 3, 2, and 1 chances left ($a_3, a_2, a_1$), because the exact identities of participants don't affect the transition probabilities—only how many have a specific number of chances remaining.
2. **Transition Relations:** Using the linearity of expectation and backward/forward transitions, the expected time to reach a state from previous states is computed iteratively. When a roll lands on a participant with 0 chances (probability $\frac{a_0}{n}$), another roll is forced, giving a recursive relation for the expected value.
3. **Multi-Dimensional Flattening:** The 3D state counts are mapped into a 1D array using a custom index function (`getIndex`) to fit within memory constraints.

#### Complexity Analysis
* **Time Complexity:** $O(n^3)$ due to the nested loops tracking the distribution of counts for $a_3$, $a_2$, and $a_1$, which efficiently bound the state space since total counts sum to $n$.
* **Space Complexity:** $O(n^3)$ auxiliary space to store the DP transition matrix (`Matrix` array).

#### C++ Solution Highlights

```cpp
int getIndex(int n, int a3, int a2, int a1) {
    return n * n * a3 + n * a2 + a1;
}

// Inside main loop over state distributions:
Matrix[getIndex(N, a3, a2, a1)] = (double)(n) / (n - a0);
if (a3 > 0) {
    Matrix[getIndex(N, a3, a2, a1)] += (((double)a3 / (n - a0)) * Matrix[getIndex(N, a3 - 1, a2 + 1, a1)]);
}
// Similar transitions for a2 and a1...

```
## Chance Game
#### Problem Description
You are completing a multi-stage game with $n$ levels. The probability of passing the $i$-th level is represented by $x_i$ percent. The rules for progression are:
* If you pass level $i$, you stop for the day and resume from level $i+1$ the next day.
* If you fail at level $i$, you stop for the day and must restart from level 1 the next day.
The goal is to calculate the expected number of days required to finish the entire game, outputting the result modulo $998244353$ as modular inverse form $p \cdot q^* \pmod N$.
* **Time Limit:** 2 seconds
* **Memory Limit:** 256 MB
* **Constraints:** $1 \le n \le 2 \cdot 10^{5}$, $1 \le x_{i} \le 100$

#### Approach
This problem uses a mathematical expectation recurrence relation that can be evaluated linearly using an iterative approach:
1. **Expectation Formulation:** By defining the recurrence relation for the expected number of days to clear up to stage $i$, the expected value can be expressed as a fraction $\frac{p}{q}$.
2. **Modular Arithmetic & Inverse:** Since the output requires a modulo of $998244353$, modular inverse via Fermat's Little Theorem ($q^{N-2} \pmod N$) is computed using binary exponentiation (`mod` function).
3. **Linear Accumulation:** The solution updates the numerator $p$ and denominator $q$ dynamically in a single pass over the probabilities array.

#### Complexity Analysis
* **Time Complexity:** $O(n \log N)$ due to the modular exponentiation function calculated alongside a single linear pass of $n$ elements.
* **Space Complexity:** $O(n)$ auxiliary space to store the level probabilities.

#### C++ Solution Highlights

```cpp
long long mod(long long a, int b, int N) {
    long long r = 1;
    while (b > 0) {
        if (b % 2 == 1) r = (r * a) % N;
        a = (a * a) % N;
        b /= 2;
    }
    return r;
}

// Inside main:
for (int i = 0; i < n; i++) {
    p = (q + p) % N;
    p = (p * 100) % N;
    q = (q * list[i]) % N;
}
long long I = mod(q, N - 2, N);
long long J = (I * p) % N;

```
## Normal Array
#### Problem Description
An array of numbers of length $k$ ($1 \le b_1 \le b_2 \le \dots \le b_k \le n$) is called a **good array** (or normal array) if each element is divisible by its preceding element ($b_{i+1}$ is divisible by $b_i$). Given $n$ and $k$, find the total number of such good arrays of length $k$, modulo $10^9 + 7$.
* **Time Limit:** 1 second
* **Memory Limit:** 256 MB
* **Constraints:** $1 \le n, k \le 2000$

#### Approach
The problem is solved using a **Dynamic Programming (DP)** approach:
1. **State Definition:** Let `matrix[i][j]` represent the number of valid good array sequences of length $j$ ending with the number $i$.
2. **Initialization (`MatrixInitializer`):** For arrays of length 1 ($j=1$), the number of ways to pick multiples or numbers up to $n$ is initialized. Specifically, for a given element $i$, we count how many multiples or choices fit up to $n$.
3. **Transition (`FillMatrix`):** For lengths from $2$ to $k$, we build up the counts using harmonic divisor/multiple steps: for each element $i$, we accumulate counts from its multiples or sub-multiples as dictated by the divisibility constraint, applying modulo $10^9 + 7$ at each step.

#### Complexity Analysis
* **Time Complexity:** $O(n k \log n)$ due to the nested loops looping through elements up to $n$ and stepping through their multiples (harmonic series sum bounded by $n \log n$), repeated for length $k$.
* **Space Complexity:** $O(n \cdot k)$ auxiliary space to store the 2D DP matrix mapped onto a 1D array.

#### C++ Solution Highlights

```cpp
void FillMatrix(unsigned long long Matrix[], int N, int K) {
    for (int j = 2; j < K; j++) {
        for (int i = 1; i < N; i++) {
            for (int l = i; l < N; l += i) {
                Matrix[MatrixIndex(i, j, K)] += Matrix[MatrixIndex(l, j - 1, K)];
                Matrix[MatrixIndex(i, j, K)] %= 1000000007;
            }
        }
    }
}

```
## Far Vertices
#### Problem Description
Write a program to count the number of distinct connected simple undirected graphs with $N$ vertices where the length of the shortest path between vertex 1 and vertex $N$ is strictly greater than the shortest path between vertex 1 and any other vertex. Two graphs are considered distinct if and only if there exists a pair of vertices with an edge in one graph and no edge in the other. The answer must be computed modulo $X$.
* **Time Limit:** 4 seconds
* **Memory Limit:** 1024 MB
* **Constraints:** $3 \le N \le 500$, $10^8 \le X \le 10^9$

#### Approach
This problem uses an advanced **Dynamic Programming with Combinatorics** approach:
1. **Combinatorial Precomputations:** Precomputes powers of two (`POWER2`), binomial coefficients/combinations (`C`), and match distributions (`Match`) using modular arithmetic.
2. **Component & Layer Transitions:** The DP state tracks layer-by-layer configurations across the structural boundaries of the graph based on distance constraints from vertex 1 to vertex $N$.
3. **Modular Aggregation:** Accumulates valid configurations dynamically, outputting the final total modulo $mod$.

#### Complexity Analysis
* **Time Complexity:** $O(N^3)$ due to nested iterations computing combinatorial matrices and state transitions up to $N$.
* **Space Complexity:** $O(N^2)$ auxiliary space to store the combination tables, match matrices, power lookups, and DP state grid.

#### C++ Solution Highlights
```cpp
POWER2(power2, n * n, mod);
C(nCk, n, mod);
Match(match, power2, n, mod);

auto *DP = new long long[(n - 2) * (n - 2)];
DP[Midx(1, 1, n)] = 1;

for (int h = 1; h <= n - 2; h++) {
    for (int l = 1; l <= n - 2; l++) {
        // State transition calculations for valid graph layers...
    }
}

```
## LCS
#### Problem Description
Gandalf, Aragorn, and Pippin are planning a battle strategy using respective string maps $G$ (Gandalf), $A$ (Aragorn), and $P$ (Pippin). Due to a falling out between Gandalf and Pippin, Gandalf wants to find the longest common subsequence (LCS) between his map $G$ and Aragorn's map $A$ such that Pippin's map $P$ does **not** appear as a contiguous substring within the resulting sequence. If multiple valid answers exist, any of them is acceptable; if no valid common subsequence exists, output `0`.
* **Time Limit:** 1 second
* **Memory Limit:** 256 MB
* **Constraints:** $1 \le \vert{}G\vert{}, \vert{}A\vert{}, \vert{}P\vert{} \le 100$

#### Approach & Methodology
This problem is solved using a dynamic programming approach combined with backtracking and string post-processing:
1. **LCS Table Construction:** Standard Dynamic Programming is used to compute the Longest Common Subsequence matrix (`C`) and the backtracking path direction matrix (`B`) for strings $G$ and $A$.
2. **Path Reconstruction (Backtracking):** Using a stack-based traversal over the choice matrix, valid candidate LCS strings are extracted.
3. **Substring Exclusion Filter:** The candidate LCS strings are checked for the presence of Pippin's map $P$ as a contiguous substring. If $P$ is found as a substring, characters are iteratively sanitized/erased until $P$ no longer appears, yielding the final valid sequence.

#### Complexity Analysis
* **Time Complexity:** $O(\vert{}G\vert{} \cdot \vert{}A\vert{} + \text{exp})$ where the LCS table generation takes $O(\vert{}G\vert{} \cdot \vert{}A\vert{})$ time, with backtracking exploring potential path combinations.
* **Space Complexity:** $O(\vert{}G\vert{} \cdot \vert{}A\vert{})$ auxiliary space to store the LCS table `C` and backtracking tracker `B`.

#### C++ Solution Highlights

```cpp
// Standard LCS computation between G and A
for (int i = 1; i <= glen; i++) {
    for (int j = 1; j <= alen; j++) {
        if (G[i-1] == A[j-1]) {
            C[i][j] = C[i-1][j-1] + 1;
            B[i][j] = 3;
        } else if (C[i-1][j] > C[i][j-1]) {
            C[i][j] = C[i-1][j];
            B[i][j] = 1;
        } else {
            C[i][j] = C[i][j-1];
            B[i][j] = 2;
        }
    }
}

```
