# Fenwick tree

First we're discussing about the problem of doing operations over arrays, then we'll explain how Fenwick Tree can be used to solve that kind of problem.

### The problem

Given an array `arr`, where `arr[i]` is the i'th element of the array, 1-indexed, we're interested in doing two kind of operations over that array:

**1. Updating elements**

<u>Point update</u><br>

Add a value (it can be a negative value) to `arr[i]`, for a given `i`.

<u>Range update</u><br>

Add a value (it can be a negative value) to every element in the range `[i, j]` for given `i <= j`.

**2. Querying elements**

<u>Point query</u><br>

Get the value of `arr[i]`, for a given `i`.

<u>Range query</u><br>

Get the sum of values for every element in the range `[i, j]` for given `i <= j`. That is: `arr[i] + arr[i + 1] + ... + arr[j]`

### Solving the problems

| Update / Query        | Point update | Range update  |
| ------------- |:-------------:| -----:|
| Point query| Just use a simple static array<br>Complexity: `(O(1), O(1))`| It will be discussed below, since it's non obvious Fenwick application <br>Complexity: `(O(lg n), O(lg n))`|
| Range query | Classical Fenwick operations, no modifications to the original data-structure<br>Complexity: `(O(lg n), O(lg n))` | Non-trivial solution using Fenwick, but it's a classical problem solved by `segment tree + lazy propagation` <br>Complexity: `(O(lg n), O(lg n))`|


### The case of range update + point queries on arrays

**Problem statement**

Given an array `arr`, `|arr| = n`, and `Q` queries of two types:
1. Get the value of `arr[i]`, `i` is given
2. Add the number `val` to every element in the range `[i, j]`. `val, i, j` are given and `i <= j`.

**Solution**

We're going to use two static arrays:

1. `arr[N]`, the initial given array of maximal size `N`. That array will not be modified any time in the algorithm, it's only purpose it's to save the original values of the given array.
2. `ft[N]`, the static array used to maintain the fenwick data-structure.

<u> Dealing with the point queries </u><br><br>

The answer is simply `arr[i] + query(i)`, where `query(i)` means the point query in the classical fenwick data-structure.

<u> Dealing with the range updates </u><br><br>

This is the tricky case. Initially all values on the array `ft[]` are set to zero, independently of the given `arr[]`.


**Example**

Suppose our goal is to add `3` to every element in the range `[2, 4]`:

<u>Initially queries on the fenwick</u><br>

| Index / Query result | 1 | 2 | 3 | 4 | 5 |
| -- |:--:| --:| --:| --:| --:|
| query(index)| 0 | 0 | 0 | 0 | 0 |

<u>After query(2, 3) </u><br>

| Index / Query result | 1 | 2 | 3 | 4 | 5 |
| -- |:--:| --:| --:| --:| --:|
| query(index)| 0 | 3 | 3 | 3 | 3 |

<u>After query(5, -3) </u><br>

| Index / Query result | 1 | 2 | 3 | 4 | 5 |
| -- |:--:| --:| --:| --:| --:|
| query(index)| 0 | 3 | 3 | 3 | 0 |

Note that we automatically added `3` to every element in the range `[2, 4]` in that data-structure, but that does not take in consideration the inital `arr`. To deal with that we can just sum to the result of `query(i)` the value of `arr(i)` once we're dealing with the problem queries.


**Real problem example**

Problem link: http://codeforces.com/problemset/problem/295/A

Solution link: [code](range-update_pointquery_codeforces-example.cpp)
