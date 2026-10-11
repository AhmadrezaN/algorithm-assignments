Here is a short summary of questions and solutions

## KMP
#### Problem Description
After returning to the Shire, Pippin and Mary open a restaurant called "Second Breakfast". They run into a naming conflict because Pippin dislikes it whenever one of his menu item names appears as a substring within Mary's menu item names. To maintain peace and blessing in their business, Mary decides to replace a minimum number of characters in her item name ($S$) with `#` so that Pippin's item name ($T$) no longer appears as a substring anywhere in $S$.
* **Time Limit:** 1 second
* **Memory Limit:** 256 MB
* **Constraints:** $0 < \vert{}S\vert{}, \vert{}T\vert{} \le 10^6$

#### Approach
This problem is solved efficiently using the **Knuth-Morris-Pratt (KMP) Algorithm** combined with interval processing:
1. **Pattern Matching (KMP):** The prefix function (`P` array) is computed for string $T$. Then, KMP pattern matching is run between $S$ and $T$ to identify all starting and ending indices where $T$ occurs as a substring within $S$.
2. **Interval Overlap Analysis:** The occurrences are stored as coordinate intervals `{start, end}`. A greedy check iterates through the intervals to detect overlapping matches.
3. **Character Replacement Counting:** By subtracting overlapping conflicts from the total number of occurrences, the algorithm computes the minimum number of character alterations required to eliminate all occurrences of $T$ from $S$.

#### Complexity Analysis
* **Time Complexity:** $O(\vert{}S\vert{} + \vert{}T\vert{})$ since computing the KMP prefix function takes $O(\vert{}T\vert{})$ and scanning string $S$ takes $O(\vert{}S\vert{})$, followed by a linear scan over the matched intervals.
* **Space Complexity:** $O(\vert{}T\vert{} + \vert{}S\vert{})$ auxiliary space for storing the prefix table, the match interval list, and input string buffers.

#### C++ Solution Highlights
```cpp
// KMP Pattern Matching to find occurrences of T in S
int q = 0, count = 0;
for (int i = 0; i < n; i++) {
    while (q > 0 && T[q] != S[i]) {
        q = P[q - 1];
    }
    if (T[q] == S[i]) {
        q++;
    }
    if (q == m) {
        count++;
        Ans.push_back({i - m + 1, i});
        q = P[q - 1];
    }
}

```
## Substrings
#### Problem Description
Given a string of lowercase English letters and a binary character classification string of length 26 (where `1` indicates an honest letter and `0` indicates a dishonest letter), write a program to find the number of **unique intimate substrings**. An intimate substring is defined as a contiguous substring where the number of dishonest characters is less than $k$.
* **Time Limit:** 2 seconds
* **Memory Limit:** 512 MB
* **Constraints:** Length of string $S \le 1500$

#### Approach
This problem is solved using substring enumeration with precomputed dishonesty cost tracking:
1. **Character Honesty Mapping:** Each character in string $S$ is evaluated using the provided binary mapping array (`T`) to determine if it incurs a cost (dishonest character assigned value `1`) or is honest (assigned value `0`).
2. **Cost Matrix Precomputation:** A 2D cost table (`Cost[i][j]`) is populated to store the cumulative number of dishonest characters for any substring ranging from index $i$ to $j$.
3. **Unique Substring Counting:** Iterating over all possible substring lengths ($l$) and start indices ($i$), substrings with a total dishonesty cost $\le k$ are extracted and tracked using an `unordered_set` (`dictionary`) to filter out duplicates and count unique intimate substrings efficiently.

#### Complexity Analysis
* **Time Complexity:** $O(n^2 \cdot l)$ where $n$ is the string length ($n \le 1500$), driven by substring extractions and hash set lookups.
* **Space Complexity:** $O(n^2)$ auxiliary space to store the 2D cost matrix and hash set dictionary elements.

#### C++ Solution Highlights
```cpp
int count = 0;
std::unordered_set<std::string> dictionary;
for (int l = 1; l <= n; l++) {
    for (int i = 0; i + l <= n; i++) {
        if (Cost[i][i + l - 1] > k) continue;
        std::string sub = S.substr(i, l);
        if (dictionary.find(sub) == dictionary.end()) {
            dictionary.insert(sub);
            count++;
        }
    }
    dictionary.clear();
}

```
