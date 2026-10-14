# tiny STL

A small STL-inspired C++ project for learning and experimenting with containers,
algorithms, and iterators. The project targets C++11 and is still under active
development; some components are incomplete.

## Contents

- Iterator tags and `iterator_traits`
- Stream iterators: `istream_iterator` and `ostream_iterator`
- Insertion iterators: `insert_iterator`, `back_insert_iterator`, and
  `front_insert_iterator`
- `reverse_iterator`
- Basic algorithm and data-structure implementations, currently in progress

## Iterator Example

Insertion iterators let standard algorithms write into containers without
preallocating space:

```cpp
#include "iterator/iterator.hpp"
#include <algorithm>
#include <vector>

std::vector<int> source{1, 2, 3};
std::vector<int> destination;

std::copy(source.begin(), source.end(), my_stl::back_inserter(destination));
```

Use `my_stl::front_inserter(container)` for containers that support
`push_front`, or `my_stl::inserter(container, position)` to insert at a position.
