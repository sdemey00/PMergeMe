~10h

*This project has been created as part of the 42 curriculum by sdemey.*
# PmergeMe – Merge-Insertion Sort (Ford–Johnson Algorithm)
PmergeMe is an implementation of the Ford–Johnson algorithm, also known as Merge-Insertion Sort.
This algorithm is designed to minimize the number of comparisons required to sort a sequence. It works by:

- Grouping elements into ordered pairs
- Recursively sorting the larger elements
- Inserting the smaller elements using binary search
- Following a special insertion order based on the Jacobsthal sequence

The result is a highly comparison-efficient sorting algorithm.

## How the Algorithm Works
**Step 1 – Pairing Elements**
The input array is grouped into pairs:
```
(a, b)
(c, d)
(e, f)
...
```
Each pair is internally ordered so that:
```
small <= large
```
So we transform:
```
(7, 2) → (2, 7)
(9, 4) → (4, 9)
```
This guarantees that every small element (left) is less than or equal to its paired large.

**Step 2 – Extract and Sort Large Elements**

All the larger elements from each pair are extracted into a new vector:
```
large = [7, 9, 12, ...]
```
If the original array has an odd number of elements, the last element is directly added to large.
Then we recursively sort large using mergeInsertionSort function.
At this point, large is fully sorted.

**Step 3 – Insert Small Elements (Optimized Order)**

Now we insert each small element into the sorted large vector.
Instead of inserting sequentially, we follow an order defined by the Jacobsthal sequence, which reduces the number of comparisons required.
Each insertion:
- Uses binary search (std::lower_bound)
- Is restricted to the range before its paired large element
- Preserves sorted order

This step is the key optimization of the Ford–Johnson algorithm.

## In code

#### Binary Insert
```
void PmergeMe::binaryInsert(std::vector<int> &arr, int value, std::vector<int>::iterator end)
```

**Purpose**

Insert a value into a sorted portion of a vector using binary search.

**How It Works**

Uses std::lower_bound to find the correct insertion position:

```
std::lower_bound(arr.begin(), end, value);
```

Inserts the element at that position:

```
arr.insert(pos, value);
```

**Why the end Iterator?**

It limits the binary search range.
This is crucial because during insertion, only part of the vector is guaranteed to be sorted.

**Complexity**

*Search*: O(log n)
*Insert*: O(n)

#### Jacobsthal Insert

```
void PmergeMe::jacobsthalInsert(std::vector<Pair>& pairs, std::vector<int>& large)
```

**Purpose**

Insert all small values from pairs into the already sorted large vector using an optimized insertion order.

**Detailed Behavior**

- Keep track of how many small elements are inserted.
- Use the Jacobsthal sequence to determine insertion batch sizes.
- Insert elements in reverse order within each batch.

For each pair:

- Find the position of its corresponding large value.
- Insert small before it using binaryInsert.

**Why Reverse Order?**

Reverse iteration ensures:

- Correct placement
- Minimal disturbance of previously inserted elements
- Optimal comparison count

#### Merge-Insertion Sort

```
void PmergeMe::mergeInsertionSort(std::vector<int>& arr)
```

**Purpose**

Main recursive implementation of the Ford–Johnson merge-insertion algorithm.
Step-by-Step Behavior
1. *Base Case*

If the array size is 0 or 1, return immediately.

2. *Create Ordered Pairs*

Loop through the array two elements at a time:

```
if (arr[i] < arr[i + 1])
    pairs.push_back(Pair(arr[i], arr[i + 1]));
else
    pairs.push_back(Pair(arr[i + 1], arr[i]));
```
Each pair guarantees:

```
small <= large
```

3. *Extract Large Elements*

Build a new vector containing only the larger values.
If the original array size is odd, append the last element directly.

4. *Recursive Sort*

Recursively sort the large vector:

```
mergeInsertionSort(large);
```

5. *Insert Small Elements*

This inserts all smaller elements into their correct positions.

```
jacobsthalInsert(pairs, large);
```

6. *Replace Original Array*

Swap the sorted result back:
```
arr.swap(large);
```

## Complexity Analysis

### Comparisons

The Ford–Johnson algorithm minimizes the number of comparisons.
For small input sizes, it achieves the optimal known comparison count.
Worst-case comparisons: ``≈ n log n - 1.44n``
This is better than classic merge sort in terms of comparison count.

### Time Complexity

Overall: ``O(n log n)``

However: Vector insertions cost ``O(n)``

In practice, *std::sort* is usually faster

This implementation is primarily valuable for:

- Academic purposes
- Understanding optimal comparison sorting

### Why This Algorithm Is Special

Most sorting algorithms:

- *Merge Sort* → balanced divide and conquer
- *Insertion Sort* → sequential insertions
- *Quick Sort* → partition-based recursion

*Ford–Johnson* combines:

- Pair grouping
- Recursive sorting
- Binary search insertion
- A mathematically optimized insertion order

This makes it one of the most comparison-efficient sorting algorithms ever designed.


