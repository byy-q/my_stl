#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <cstddef>
namespace my_stl
{

    class input_iterator_tag{};
    class forward_iterator_tag : public my_stl::input_iterator_tag{};
    class bidirection_iterator_tag : public my_stl::forward_iterator_tag {};
    class random_access_iterator_tag : public my_stl::bidirection_iterator_tag{};
    class output_iterator_tag {};


    template<typename Iterator>
    void swap(Iterator __it1,Iterator __it2);
    template<typename Iterator>
    struct iterator_traits
    {
        using value_type = typename Iterator::value_type;
        using difference_type = typename Iterator::difference_type;
        using pointer = typename Iterator::pointer;
        using reference = typename Iterator::reference;
        using iterator_category = typename Iterator ::iterator_category;
    };

    template<typename T>
    struct iterator_traits<T*>
    {
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;
        using iterator_category = my_stl::random_access_iterator_tag;
    };

    template<typename T>
    struct iterator_traits<const T*>
    {
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;
        using iterator_category = my_stl::random_access_iterator_tag;
    };
}
template<typename Iterator>
void my_stl::swap(Iterator __it1,Iterator __it2)
{
    typename my_stl::iterator_traits<Iterator>::value_type temp = *__it1;
    *__it1 = *__it2;
    *__it2 = temp;
}











#endif