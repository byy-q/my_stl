#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <cstddef>
#include <istream>
#include <ostream>
namespace my_stl
{

    class input_iterator_tag{};
    class forward_iterator_tag : public my_stl::input_iterator_tag{};
    class bidirectional_iterator_tag : public my_stl::forward_iterator_tag {};
    using bidirection_iterator_tag = my_stl::bidirectional_iterator_tag;
    class random_access_iterator_tag : public my_stl::bidirectional_iterator_tag{};
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

    template<typename Iterator>
    class reverse_iterator
    {
    public:
        using iterator_type = Iterator;
        using traits_type = my_stl::iterator_traits<Iterator>;
        using value_type = typename traits_type::value_type;
        using difference_type = typename traits_type::difference_type;
        using pointer = typename traits_type::pointer;
        using reference = typename traits_type::reference;
        using iterator_category = typename traits_type::iterator_category;

        reverse_iterator() : current() {}
        explicit reverse_iterator(Iterator iterator) : current(iterator) {}

        template<typename OtherIterator>
        reverse_iterator(const reverse_iterator<OtherIterator>& other)
            : current(other.base()) {}

        Iterator base() const { return current; }

        reference operator*() const
        {
            Iterator previous = current;
            return *--previous;
        }

        pointer operator->() const { return &(operator*()); }
        reverse_iterator& operator++() { --current; return *this; }
        reverse_iterator operator++(int)
        {
            reverse_iterator previous(*this);
            --current;
            return previous;
        }
        reverse_iterator& operator--() { ++current; return *this; }
        reverse_iterator operator--(int)
        {
            reverse_iterator previous(*this);
            ++current;
            return previous;
        }
        reverse_iterator operator+(difference_type offset) const
        { return reverse_iterator(current - offset); }
        reverse_iterator& operator+=(difference_type offset)
        { current -= offset; return *this; }
        reverse_iterator operator-(difference_type offset) const
        { return reverse_iterator(current + offset); }
        reverse_iterator& operator-=(difference_type offset)
        { current += offset; return *this; }
        reference operator[](difference_type offset) const
        { return *(*this + offset); }

    private:
        Iterator current;
    };

    template<typename Iterator1, typename Iterator2>
    bool operator==(const reverse_iterator<Iterator1>& lhs,
                    const reverse_iterator<Iterator2>& rhs)
    { return lhs.base() == rhs.base(); }

    template<typename Iterator1, typename Iterator2>
    bool operator!=(const reverse_iterator<Iterator1>& lhs,
                    const reverse_iterator<Iterator2>& rhs)
    { return !(lhs == rhs); }

    template<typename Iterator1, typename Iterator2>
    bool operator<(const reverse_iterator<Iterator1>& lhs,
                   const reverse_iterator<Iterator2>& rhs)
    { return rhs.base() < lhs.base(); }

    template<typename Iterator1, typename Iterator2>
    bool operator>(const reverse_iterator<Iterator1>& lhs,
                   const reverse_iterator<Iterator2>& rhs)
    { return rhs < lhs; }

    template<typename Iterator1, typename Iterator2>
    bool operator<=(const reverse_iterator<Iterator1>& lhs,
                    const reverse_iterator<Iterator2>& rhs)
    { return !(rhs < lhs); }

    template<typename Iterator1, typename Iterator2>
    bool operator>=(const reverse_iterator<Iterator1>& lhs,
                    const reverse_iterator<Iterator2>& rhs)
    { return !(lhs < rhs); }

    template<typename Iterator1, typename Iterator2>
    typename iterator_traits<Iterator1>::difference_type
    operator-(const reverse_iterator<Iterator1>& lhs,
              const reverse_iterator<Iterator2>& rhs)
    { return rhs.base() - lhs.base(); }

    template<typename Iterator>
    reverse_iterator<Iterator> operator+(
        typename reverse_iterator<Iterator>::difference_type offset,
        const reverse_iterator<Iterator>& iterator)
    { return iterator + offset; }

    template<typename T, typename CharT = char,
             typename Traits = std::char_traits<CharT>,
             typename Distance = std::ptrdiff_t>
    class istream_iterator
    {
    public:
        using value_type = T;
        using difference_type = Distance;
        using pointer = const T*;
        using reference = const T&;
        using iterator_category = my_stl::input_iterator_tag;

        istream_iterator() : stream(nullptr), value(), at_end(true) {}
        explicit istream_iterator(std::basic_istream<CharT, Traits>& input)
            : stream(&input), value(), at_end(false)
        { read(); }

        reference operator*() const { return value; }
        pointer operator->() const { return &value; }
        istream_iterator& operator++() { read(); return *this; }
        istream_iterator operator++(int)
        {
            istream_iterator previous(*this);
            read();
            return previous;
        }

        template<typename U, typename C, typename Tr, typename D>
        friend bool operator==(const istream_iterator<U, C, Tr, D>&,
                               const istream_iterator<U, C, Tr, D>&);

    private:
        void read()
        {
            if (stream && (*stream >> value))
                at_end = false;
            else
            {
                stream = nullptr;
                at_end = true;
            }
        }

        std::basic_istream<CharT, Traits>* stream;
        T value;
        bool at_end;
    };

    template<typename T, typename CharT, typename Traits, typename Distance>
    bool operator==(const istream_iterator<T, CharT, Traits, Distance>& lhs,
                    const istream_iterator<T, CharT, Traits, Distance>& rhs)
    {
        return (lhs.at_end && rhs.at_end) ||
               (!lhs.at_end && !rhs.at_end && lhs.stream == rhs.stream);
    }

    template<typename T, typename CharT, typename Traits, typename Distance>
    bool operator!=(const istream_iterator<T, CharT, Traits, Distance>& lhs,
                    const istream_iterator<T, CharT, Traits, Distance>& rhs)
    { return !(lhs == rhs); }

    template<typename T, typename CharT = char, typename Traits = std::char_traits<CharT>>
    class ostream_iterator
    {
    public:
        using iterator_category = my_stl::output_iterator_tag;
        using value_type = void;
        using difference_type = void;
        using pointer = void;
        using reference = void;

        explicit ostream_iterator(std::basic_ostream<CharT, Traits>& output,
                                  const CharT* separator = nullptr)
            : stream(&output), delimiter(separator) {}

        ostream_iterator& operator=(const T& value)
        {
            *stream << value;
            if (delimiter)
                *stream << delimiter;
            return *this;
        }
        ostream_iterator& operator*() { return *this; }
        ostream_iterator& operator++() { return *this; }
        ostream_iterator& operator++(int) { return *this; }

    private:
        std::basic_ostream<CharT, Traits>* stream;
        const CharT* delimiter;
    };

    template<typename Container>
    class insert_iterator
    {
    public:
        using iterator_category = my_stl::output_iterator_tag;
        using value_type = void;
        using difference_type = void;
        using pointer = void;
        using reference = void;

        insert_iterator(Container& target, typename Container::iterator position)
            : container(&target), current(position) {}

        insert_iterator& operator=(const typename Container::value_type& value)
        {
            current = container->insert(current, value);
            ++current;
            return *this;
        }
        insert_iterator& operator*() { return *this; }
        insert_iterator& operator++() { return *this; }
        insert_iterator& operator++(int) { return *this; }

    protected:
        Container* container;
        typename Container::iterator current;
    };

    template<typename Container>
    class back_insert_iterator
    {
    public:
        using iterator_category = my_stl::output_iterator_tag;
        using value_type = void;
        using difference_type = void;
        using pointer = void;
        using reference = void;

        explicit back_insert_iterator(Container& target) : container(&target) {}
        back_insert_iterator& operator=(const typename Container::value_type& value)
        { container->push_back(value); return *this; }
        back_insert_iterator& operator*() { return *this; }
        back_insert_iterator& operator++() { return *this; }
        back_insert_iterator& operator++(int) { return *this; }

    private:
        Container* container;
    };

    template<typename Container>
    class front_insert_iterator
    {
    public:
        using iterator_category = my_stl::output_iterator_tag;
        using value_type = void;
        using difference_type = void;
        using pointer = void;
        using reference = void;

        explicit front_insert_iterator(Container& target) : container(&target) {}
        front_insert_iterator& operator=(const typename Container::value_type& value)
        { container->push_front(value); return *this; }
        front_insert_iterator& operator*() { return *this; }
        front_insert_iterator& operator++() { return *this; }
        front_insert_iterator& operator++(int) { return *this; }

    private:
        Container* container;
    };

    template<typename Container>
    insert_iterator<Container> inserter(
        Container& target, typename Container::iterator position)
    { return insert_iterator<Container>(target, position); }

    template<typename Container>
    back_insert_iterator<Container> back_inserter(Container& target)
    { return back_insert_iterator<Container>(target); }

    template<typename Container>
    front_insert_iterator<Container> front_inserter(Container& target)
    { return front_insert_iterator<Container>(target); }
}
template<typename Iterator>
void my_stl::swap(Iterator __it1,Iterator __it2)
{
    typename my_stl::iterator_traits<Iterator>::value_type temp = *__it1;
    *__it1 = *__it2;
    *__it2 = temp;
}











#endif