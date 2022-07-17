# _algobase_: Algorithms and data structures templates
This is a repository with implementations of many algorithms and data structures in C++.
It was written for using in competitive programming as templates to save time and do not get distracted by writing a theoretical algorithms.

## List of contents
Repository includes C++ files which contains implementation of following algorithms and data structures:

### `templates.cpp`
- *gcd* - GCD and LCM finding
- *sparse table* - sparse table structure

### `graphs.cpp`
- *graph* - template for graphs (used below)
- *multi edges* - function to remove multi edges from graph
- *topological sort* - toplogical sort of graph or part of it
- *bridges* - selection of bridges in graph
- *edge biconnected components* - coloring and condensation of graph by edge biconnected components
- *strongly connected components* - coloring and condensation of graph by strongly connected components
- *2-SAT* - structure for solving 2-SAT problem
- *level ancestor* - structures for level ancestor problem with binary search and binary ups
- *LCA* - structures for dynamic LCA and LCA with binary ups, segment tree and sparse table
- *tree path queries* - structure for answering queries on paths in trees using binary ups and LCA

### `strings.cpp`
- *trie* - trie structure for strings
- *number trie* - trie structure for integers
- *hash* - structure for polynomial hashing

### `trees.cpp`
- *treap* - treap and implicit treap structures
- *fenwick tree* - Fenwick tree structure and it's version with range operations
- *2D fenwick tree* - 2-dimensional Fenwick tree structure and it's version with range operations
- *segment tree* - segment tree with sum and update queries on range