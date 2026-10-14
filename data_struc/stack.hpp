#ifndef STACK_HPP
#define STACK_HPP

#include <deque>
#include <utility>
namespace my_stl
{


//in STL,stack usual be a container adapter
//it require some basic operation offered by lower container
template<typename T, typename Container = std::deque<T>>
class stack
{
    public:

        stack() = default;

        explicit stack(const Container& underlying) : container(underlying) {}
        explicit stack(Container&& underlying) : container(std::move(underlying)) {}


        using value_type = T;
        using container_type = Container;
        using size_type = typename Container::size_type;
        using reference = typename Container::reference;
        using const_reference = typename Container::const_reference;

        bool empty() const { return container.empty(); }
        size_type size() const { return container.size(); }

        reference top() { return container.back(); }
        const_reference top() const { return container.back(); }

        void push(const T& value) { container.push_back(value); }
        void push(T&& value) { container.push_back(std::move(value)); }

        template<typename... Args>
        void emplace(Args&&... args)
        { container.emplace_back(std::forward<Args>(args)...); }

        void pop() { container.pop_back(); }

    protected:
        Container container;
};
















}
#endif
