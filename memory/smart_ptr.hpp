#ifndef SMART_PTR_HPP
#define SMART_PTR_HPP



namespace my_stl
{


template<typename T>
class shared_ptr
{
    public:



    private:


};

template<typename T>
class unique_ptr
{
    public:
        unique_ptr() = default;
        explicit unique_ptr(T* ptr ):data_ptr(ptr){}
        ~unique_ptr(){delete data_ptr;}

        unique_ptr(unique_ptr&& move)
        {
            T* temp = move.data_ptr;
            move.data_ptr = nullptr;
            data_ptr = temp;
        }
        unique_ptr(const unique_ptr& ) = delete;

        unique_ptr& operator=(unique_ptr&& move)
        {
            T* temp = move.data_ptr;
            move.data_ptr = nullptr;
            delete data_ptr;
            data_ptr = temp;
            return *this;   
        }
        
        unique_ptr& operator=(const unique_ptr& ) = delete;
        
    private:
        T* data_ptr = nullptr;
};

template<typename T>
class unique_ptr<T[]>
{
    public:
        unique_ptr() = default;
        explicit unique_ptr(T* ptr ):data_ptr(ptr){}
        ~unique_ptr(){delete [] data_ptr;}

        unique_ptr(unique_ptr&& move)
        {
            T* temp = move.data_ptr;
            move.data_ptr = nullptr;
            data_ptr = temp;
        }
        unique_ptr(const unique_ptr& ) = delete;

        unique_ptr& operator=(unique_ptr&& move)
        {
            T* temp = move.data_ptr;
            move.data_ptr = nullptr;
            delete[] data_ptr;
            data_ptr = temp;
            return *this;   
        }
        

    private:
        T* data_ptr;
};



}
    







#endif