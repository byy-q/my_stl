
#include "../../iterator/iterator.hpp"

template<typename Iterator>
static Iterator partition(Iterator begin,Iterator end)
{
    using value_type = typename my_stl::iterator_traits<Iterator>::value_type;
    Iterator i = begin-1;
    value_type x = *(end-1);
    Iterator j = begin;
    while(j != end)
    {
        if(j < x)
        {
            i++;
            my_stl::swap(i,j);
        }
        j++;
    }
    return i+1;
}

template <typename Iterator>
void quick_sort(Iterator begin,Iterator end)
{
    if(end - begin == 1)
        return;
    Iterator boundary = partition(begin,end);
    quick_sort(begin,boundary);
    quick_sort(boundary+1,end);
}

template<typename Iterator>
void insert_sort(Iterator begin,Iterator end)
{
    Iterator sorted_bound = begin;
    Iterator insert_item = begin + 1;
    while(insert_item != end)
    {
        Iterator compare = sorted_bound;
        while(compare > insert_item && compare != begin)
        {
            compare--;
        }
        if(compare != begin)
        {
            typename my_stl::iterator_traits<Iterator>::value_type temp = *insert_item;
            Iterator backward = insert_item;
            while(backward != compare)
            {
                *backward = *(--backward);
            }
            *backward = temp;
        }
    }
}


template<typename Iterator>
void merge_sort(Iterator __begin,Iterator __end)
{
    typename my_stl::iterator_traits<Iterator>::difference_type distance = __end - __begin;
    if (distance < 32 )
        insert_sort(__begin,__end);
    Iterator middle = __begin + distance/2;
    merge_sort(__begin,middle);
    merge_sort(middle,__end);
}

