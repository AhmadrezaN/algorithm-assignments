Here is a short summary of questions and solutions.

## Competition
#### Problem Description
A two-player game is played starting with a value $x = 0$. Over $n$ turns, a predetermined sequence of turns given by a string $X$ dictates whether Player 0 ('0') or Player 1 ('1') gets a turn. In step $i$, the active player can either choose to apply an XOR operation with a pre-defined array value $Y[i]$ ($x \leftarrow x \oplus Y[i]$) or do nothing. Player 0 wins if $x = 0$ at the end of the game, while Player 1 wins if $x \neq 0$. Assuming both players play optimally, determine the winner.
* **Time Limit:** 2 seconds
* **Memory Limit:** 1024 MB
* **Constraints:** $1 \le n \le 200$, $1 \le y_i \le 10^{18}$

#### Approach
Although framed as a game theory problem, the optimal strategy can be evaluated sequentially using a **Greedy-like deterministic check** or state tracing:
1. **State Tracking:** The code iterates through each turn based on the turn string $X$ and updates the running variable $x$ using bitwise XOR operations conditional on player strategies.
2. **Greedy State Resolution:** At each step, choices are evaluated to see whether maintaining or toggling the bitwise accumulation forces $x$ to settle at $0$ or non-zero, matching the respective player's optimal objective.

#### Complexity Analysis
* **Time Complexity:** $O(n)$ as it performs a single linear pass over the sequence of length $n$
* **Space Complexity:** $O(n)$ auxiliary space to store the array $Y$ and string $X$.

#### C++ Solution Highlights
```cpp
for (int i = 0; i < n; i++) {
    if (X[i] == '0') {
        if (x == Y[i] || x == 0) {
            x = 0;
        } else {
            x ^= Y[i];
        }
    } else {
        if (x == 0 && Y[i] == 0) {
            x = 0;
        } else {
            x ^= Y[i];
        }
    }
}
if (x == 0) std::cout << "0";
else std::cout << "1";

```
## Numbers Party
#### Problem Description
Given an array of $N$ integers, find the number of ways to divide the array into 3 contiguous subsegments (covering all elements) such that the sum of elements in each of the 3 subsegments is equal.
* **Time Limit:** 1 second
* **Memory Limit:** 256 MB
* **Constraints:** $1 \le N \le 5 \cdot 10^{5}$, $0 \le \vert{}a_{i}\vert{} \le 10^{9}$

#### Approach
The solution uses an efficient **Linear Scan with Prefix Sum tracking** (a greedy/two-pass counting technique):
1. **Total Sum Validation:** First, compute the total sum of the array. If the total sum is not divisible by 3, it's impossible to split it into three equal parts, so the answer is 0.
2. **Non-Zero Total Sum Case:** If the sum is non-zero (let target $S = \text{Sum}/3$), we do a single pass to accumulate prefix sums. We keep track of how many valid first split points (where prefix sum equals $S$) have been seen so far. Every time the prefix sum hits $2S$, we add the count of previous valid first split points to our total answer.
3. **Special Zero Sum Case:** If the total sum is 0, we count how many prefix sums equal 0 and use combinatorics (combinations of choosing 2 split points from the valid zero-sum prefix positions) to find the total combinations.

#### Complexity Analysis
* **Time Complexity:** $O(N)$ because it requires a single linear traversal of the array.
* **Space Complexity:** $O(N)$ auxiliary space to store the input array elements.

#### C++ Solution Highlights
```cpp
long long SubSum = 0;
long long answer = 0;
if (Sum != 0) {
    Sum /= 3;
    long long first = 0;
    for (int i = 0; i < n; i++) {
        SubSum += list[i];
        if (SubSum == Sum) first++;
        if (SubSum == 2 * Sum) answer += first;
    }
} else {
    long ZeroCount = 0;
    for (int i = 0; i < n; i++) {
        SubSum += list[i];
        if (SubSum == 0) ZeroCount++;
    }
    answer = (ZeroCount - 1) * (ZeroCount - 2) / 2;
}

```
## Card Game
#### Problem Description
You are given $n$ cards, each containing a letter of the English alphabet, represented as a string of length $n$. You are allowed to choose exactly $k$ cards. For each chosen card, you score points equal to the number of cards among your chosen selection that share the exact same letter. The goal is to design an algorithm to find the maximum possible score you can obtain.
* **Time Limit:** 1 second
* **Memory Limit:** 256 MB
* **Constraints:** $1 \le k \le n \le 10^{5}$

#### Approach
This problem is efficiently solved using a **Greedy Strategy**:
1. **Frequency Counting:** Count the occurrences of each unique character present in the string.
2. **Sorting by Frequency:** Sort the unique characters based on their frequencies in ascending order using a custom quicksort implementation.
3. **Greedy Selection:** To maximize the score (since score scales quadratically as count squared: $count^2$), we greedily pick the characters with the largest frequencies first until we reach the total count limit of $k$.

#### Complexity Analysis
* **Time Complexity:** $O(n \log n)$ due to sorting the unique character counts (where the number of unique characters is bounded by the alphabet size, or up to $n$ in general cases).
* **Space Complexity:** $O(n)$ auxiliary space to store the structures representing distinct characters and their counts.

#### C++ Solution Highlights
```cpp
quicksort(list, 0, len - 1);

int K = k;
int idx = len - 1;
int Sum = 0;
while (K > 0) {
    if (K > list[idx].count) {
        K -= list[idx].count;
        Sum += (list[idx].count * list[idx].count);
        idx--;
    } else {
        Sum += (K * K);
        break;
    }
}

```
## Beautiful String
#### Problem Description
A string of English letters is considered **beautiful** if no two adjacent characters are identical. Given a string, the goal is to transform it into a beautiful string using the **minimum possible number of modifications**. If multiple valid answers exist, any correct one can be output.
* **Time Limit:** 2 seconds
* **Memory Limit:** 256 MB
* **Constraints:** $1 \le \vert{}s\vert{} \le 2 \cdot 10^{5}$

#### Approach
This problem is efficiently resolved using a **Greedy Strategy**:
1. **Linear Scan:** Traverse the string from left to right checking for adjacent duplicate characters (`str[i] == str[i-1]`).
2. **Local Choice:** Whenever a duplicate is found at index `i`, greedily replace it with a character from the allowed set (`a`, `b`, or `c`) that does not match its preceding character (`str[i-1]`) and does not conflict with its succeeding character (`str[i+1]`).
3. **Immediate Correction:** By ensuring the chosen replacement avoids both neighbors, local conflicts are resolved instantly in a single pass without cascading issues.

#### Complexity Analysis
* **Time Complexity:** $O(n)$ because it performs a single linear pass over the string of length $n$, checking a fixed constant number of characters ($3$ alphabet options) for each replacement.
* **Space Complexity:** $O(1)$ auxiliary space if modifying the string in-place, or $O(n)$ to store the input string.

#### C++ Solution Highlights

```cpp
for (int i = 1; i < len; i++) {
    if (str[i] == str[i-1]) {
        for (int j = 0; j < 3; j++) {
            if (str[i] != L[j] && str[i+1] != L[j]) {
                str[i] = L[j];
                break;
            }
        }
    }
}
std::cout << str;

```
## Great Binary
#### Problem Description
Given two natural numbers $a$ and $b$, consider all pairs of numbers $x$ and $y$ such that $a \le x \le y \le b$. The objective is to find the maximum possible value of their bitwise XOR operation, $x \oplus y$, for the given range $[a, b]$.
* **Time Limit:** 1 second
* **Memory Limit:** 256 MB
* **Constraints:** $1 \le a \le b \le 10^{18}$

#### Approach
This problem is solved efficiently using a **Greedy Bit Manipulation Strategy**:
1. **Binary Representation:** Extract the binary representation of both numbers $a$ and $b$ bit-by-bit from least significant to most significant bits.
2. **Finding the Highest Divergence:** Iterate from the highest bit downwards to find the most significant position (`I`) where the binary digits of $a$ and $b$ differ.
3. **Greedy Maximization:** To maximize the XOR result $x \oplus y$, we can set the bits up to the divergence point `I` to turn on all bits from that position downwards, yielding $2^{I+1} - 1$ as the maximum possible value.

#### Complexity Analysis
* **Time Complexity:** $O(\log b)$ since we only iterate over the number of bits required to represent $b$ (which is bounded by $\log_2(10^{18}) \approx 60$ iterations).
* **Space Complexity:** $O(1)$ auxiliary space (using fixed-size arrays of size 512 to store binary digits).

#### C++ Solution Highlights
```cpp
long long Max = 1;
int I = -1;
for (long i = jdx - 1; i >= 0; i--) {
    if (binA[i] != binB[i]) {
        I = i;
        break;
    }
}
for (int i = 0; i <= I; i++) {
    Max <<= 1;
}
std::cout << Max - 1;

```
## Bamqom
#### Problem Description
You are given an array of length $n$, $A = [a_1, a_2, \dots, a_n]$. An array $B$ is called **beautiful** if the greatest common divisor (GCD) of all its elements is strictly greater than 1 ($\gcd(b_1, b_2, \dots, b_n) > 1$). In one operation, you can choose an index $i$, replace $a_i$ and $a_{i+1}$ with $a_i - a_{i+1}$ and $a_i + a_{i+1}$ respectively. Find the minimum number of operations required to make the array beautiful, and output `YES` or `NO`.
* **Time Limit:** 1 second
* **Memory Limit:** 256 MB
* **Constraints:** $1 \le n \le 10^{5}$, $1 \le a_{i} \le 10^{9}$

#### Approach
This problem is solved using a **Greedy Number Theory Strategy** based on parity and GCD transformations:
1. **Initial GCD Check:** First, calculate the overall GCD of the entire array. If the GCD is already greater than 1, zero operations are needed.
2. **Parity Analysis & Transformations:** If the overall GCD is 1, we can make adjacent elements even using specific operation patterns. The code tracks parities of elements (`isEven`) and greedily applies operations to adjacent odd/even pairs to transform them into even numbers, minimizing the total cost.

#### Complexity Analysis
* **Time Complexity:** $O(n \log(\max(A)))$ for computing the initial GCD across elements, followed by linear scans of size $n$ to adjust parities.
* **Space Complexity:** $O(n)$ auxiliary space to store the input array and parity tracker flags.

#### C++ Solution Highlights
```cpp
long g = gcd(list[0], list[1]);
for (int i = 2; i < n; i++) {
    g = gcd(g, list[i]);
}

if (g > 1) {
    std::cout << "YES" << std::endl << 0;
} else {
    // Greedy parity adjustments and operation counting
    // ...
    std::cout << "YES\n" << count;
}

```
