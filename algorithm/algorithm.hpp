#ifndef SORT_HPP
#define SORT_HPP



template<typename Iterator>
void quick_sort(Iterator begin,Iterator end);

template<typename Iterator>
void insert_sort(Iterator begin,Iterator end);

template<typename Iterator>
void merge_sort(Iterator __begin,Iterator __end);

template<typename Iterator>
void count_sort(Iterator __begin,Iterator __end,typename my_stl::iterator_traits<Iterator>::value_type k);

template<typename Iterator>
void Radix_sort(Iterator begin,Iterator end);
#include "./imple/sort.cpp"

template<typename Iterator>
auto max_subarray(Iterator __begin,Iterator __end,Iterator __first,Iterator __last)
->typename my_stl::iterator_traits<Iterator>::value_type;
#include "./imple/find.cpp"
#endif