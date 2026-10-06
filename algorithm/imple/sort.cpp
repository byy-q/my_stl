
#include "../../iterator/iterator.hpp"

template<typename Iterator>
Iterator partition(Iterator begin,Iterator end)
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
    Iterator boundary = partition(beigin,end);
    quick_sort(begin,boundary-1);
    quick_sort(boundary+1,end);
}