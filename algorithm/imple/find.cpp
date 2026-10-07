#include "../../iterator/iterator.hpp"

template<typename Iterator>
auto max_subarray(Iterator __begin,Iterator __end,Iterator __first,Iterator __last)
->typename my_stl::iterator_traits<Iterator>::value_type
{
    typename my_stl::iterator_traits<Iterator>::value_type sum = 0;
    typename my_stl::iterator_traits<Iterator>::difference_type distance = __end - __begin;
    if(distance < 2)
    {
        __first == __begin,__last = __end;
        return *begin;
    }
    Iterator middle = __begin + distance / 2;

    Iterator __left_first,__left_last,__right_first,__right_last;
    typename my_stl::iterator_traits<Iterator>::value_type __left_sum,__right_sum,midlle_sum = *middle;

    __left_sum = max_subarray(__begin,middle,__left_first,__left_last);
    __right_sum = max_subarray(middle+1,__end,__right_first,__right_last);

    typename my_stl::iterator_traits<Iterator>::value_type middle_right_sum = 0,midlle_right_max_sum = 0;
    Iterator current = middle+1,bound = middle;
    while(current != __end)
    {
        middle_right_sum += *current;
        if(middle_right_sum > midlle_right_max_sum)
        {    
            midlle_right_max_sum = middle_right_sum;
            bound = current;
        }    
    }

    typename my_stl::iterator_traits<Iterator>::value_type middle_left_sum = 0,middle_left_max_sum = *middle;
    current = middle;
    Iterator l_bound = middle;
    while(current != (__begin - 1))
    {
        middle_left_sum += *current;
        if(middle_left_sum > middle_left_max_sum)
        {
            l_bound = current;
            middle_left_max_sum = middle_left_sum;
        }
    }
    typename my_stl::iterator_traits<Iterator>::value_type middle_sum = middle_left_max_sum + midlle_right_max_sum;
    if(middle_sum > __left_sum && middle_sum > __right_sum)
    {   
        __first = l_bound,__last = bound;
        return midlle_sum;
    }   
    else if(__left_sum > middle_sum && __left_sum > __right_sum)
    {
        __first = __left_first,__last = __left_last;
        return __left_sum;
    }
    else
    {
        __first = __right_first,__last = __right_last;
        return __right_sum;
    }
}