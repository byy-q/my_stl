
#include "../../iterator/iterator.hpp"
#include <type_traits>
#include <vector>

template<typename Iterator>
static Iterator partition(Iterator begin,Iterator end)
{
    using value_type = typename my_stl::iterator_traits<Iterator>::value_type;
    if(begin == end)
        return begin;
    value_type x = *(end - 1);
    Iterator i = begin;
    for(Iterator j = begin; j != end - 1; ++j)
    {
        if(*j < x)
        {
            my_stl::swap(i,j);
            ++i;
        }
    }
    my_stl::swap(i, end - 1);
    return i;
}
/** 
 * @details:The performance of quick_sort depends on the bound number we select in partition
 * if the number was the largest or smallest in the input,it performance like insertion sort algorithm
 * it performance best with time complexity of (nlgn) when the bound number has midlle size of the input
 * actually ,as long as the seperate ratio be constant number ,even 99;1,the time complexity sill be the O(nlgn)
 * 

*/
template <typename Iterator>
void quick_sort(Iterator begin,Iterator end)
{
    if(end - begin <= 1)
        return;
    Iterator boundary = partition(begin,end);
    quick_sort(begin,boundary);
    quick_sort(boundary + 1,end);
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

template<typename Iterator>
void count_sort(Iterator begin,Iterator end,typename my_stl::iterator_traits<Iterator>::value_type k)
{
    using value_type = typename my_stl::iterator_traits<Iterator>::value_type;
    static_assert(std::is_integral<value_type>::value, "count_sort requires integral values");
    typename my_stl::iterator_traits<Iterator>::difference_type distance = end - begin;
    if(distance < 2)
        return;

    std::vector<size_t> counts(static_cast<size_t>(k) + 1, 0);
    for(Iterator current = begin; current != end; ++current)
    {
        size_t index = static_cast<size_t>(*current);
        ++counts[index];
    }
    for(size_t i = 1; i < counts.size(); ++i)
        counts[i] += counts[i - 1];

    std::vector<value_type> output(static_cast<size_t>(distance));
    for(Iterator current = end - 1; current >= begin; --current)
    {
        size_t index = static_cast<size_t>(*current);
        --counts[index];
        output[counts[index]] = *current;
    }
    for(size_t i = 0; i < output.size(); ++i)
        *(begin + static_cast<typename my_stl::iterator_traits<Iterator>::difference_type>(i)) = output[i];
}


template<typename Iterator>
void Radix_sort(Iterator begin,Iterator end)
{
    using value_type = typename my_stl::iterator_traits<Iterator>::value_type;
    static_assert(std::is_integral<value_type>::value, "Radix_sort requires integral values");

    typename my_stl::iterator_traits<Iterator>::difference_type distance = end - begin;
    if(distance < 2)
        return;

    auto radix_sort_unsigned = [](std::vector<unsigned long long>& data)
    {
        if(data.size() < 2)
            return;

        std::vector<unsigned long long> output(data.size());
        for(size_t shift = 0; shift < sizeof(unsigned long long) * 8; shift += 8)
        {
            //一次循环对数据的每一字节做一次计数排序
            std::vector<size_t> count(256, 0);//每一个字节可能的取值为0-255
            for(const auto& value : data)
                ++count[(value >> shift) & 0xFFu];
            for(size_t i = 1; i < count.size(); ++i)
                count[i] += count[i - 1];
            for(auto it = data.rbegin(); it != data.rend(); ++it)
            {
                size_t index = ((*it >> shift) & 0xFFu);
                --count[index];
                output[count[index]] = *it;
            }
            data.swap(output);
        }
    };

    if(std::is_signed<value_type>::value)
    {//有符号数
        std::vector<value_type> negatives;
        std::vector<value_type> positives;
        for(Iterator it = begin; it != end; ++it)
        {
            if(*it < value_type(0))
                negatives.push_back(*it);
            else
                positives.push_back(*it);
        }

        std::vector<unsigned long long> positive_keys;
        positive_keys.reserve(positives.size());
        for(const auto& value : positives)
            positive_keys.push_back(static_cast<unsigned long long>(value));
        radix_sort_unsigned(positive_keys);

        std::vector<unsigned long long> negative_keys;
        negative_keys.reserve(negatives.size());
        for(const auto& value : negatives)
        {
            unsigned long long magnitude = static_cast<unsigned long long>(value - std::numeric_limits<value_type>::lowest());
            negative_keys.push_back(magnitude);
        }
        radix_sort_unsigned(negative_keys);

        std::vector<value_type> sorted_values;
        sorted_values.reserve(static_cast<size_t>(distance));
        for(auto it = negative_keys.begin(); it != negative_keys.end(); ++it)
            sorted_values.push_back(std::numeric_limits<value_type>::lowest() + static_cast<value_type>(*it));
        for(const auto& key : positive_keys)
            sorted_values.push_back(static_cast<value_type>(key));

        for(size_t i = 0; i < sorted_values.size(); ++i)
            *(begin + static_cast<typename my_stl::iterator_traits<Iterator>::difference_type>(i)) = sorted_values[i];
        return;
    }
//无符号数
    std::vector<unsigned long long> keys;
    keys.reserve(static_cast<size_t>(distance));
    for(Iterator it = begin; it != end; ++it)
        keys.push_back(static_cast<unsigned long long>(*it));
    radix_sort_unsigned(keys);

    for(size_t i = 0; i < keys.size(); ++i)
        *(begin + static_cast<typename my_stl::iterator_traits<Iterator>::difference_type>(i)) = static_cast<value_type>(keys[i]);
}


