#ifndef SMART_PTR_HPP
#define SMART_PTR_HPP



namespace my_stl
{


template<typename T>
class shared_ptr
{
    public:
        shared_ptr():data(nullptr),count(0){}
        shared_ptr(T* pointer):data(pointer){count = new int(1);}
        shared_ptr(shared_ptr& copy):data(copy.data){
            *copy.count++;
            count = copy.count;
        }
        shared_ptr(shared_ptr&&)=delete;
        shared_ptr& operator=(shared_ptr& copy)
        {
            data = copy.data;
            *copy.count++;
            count = copy.count;
            return *this;
        }

        shared_ptr& operator=(shared_ptr&&)=delete;
        ~shared_ptr()
        {
            if(*count == 1)
            {
                delete data;
                delete count;
            }
            else
            {
                *count--;
            }
        }

    private:
        T* data;
        int* count;
};

template<typename T>
class shared_ptr<T[]>
{
    public:
        shared_ptr():data(nullptr),count(0){}
        shared_ptr(T* pointer):data(pointer){count = new int(1);}
        shared_ptr(shared_ptr& copy):data(copy.data){
            *copy.count++;
            count = copy.count;
        }
        shared_ptr(shared_ptr&&)=delete;
        shared_ptr& operator=(shared_ptr& copy)
        {
            data = copy.data;
            *copy.count++;
            count = copy.count;
            return *this;
        }

        shared_ptr& operator=(shared_ptr&&)=delete;
        ~shared_ptr()
        {
            if(*count == 1)
            {
                delete[] data;
                delete count;
            }
            else
            {
                *count--;
            }
        }

    private:
        T* data;
        int* count;
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
        T* data_ptr = nullptr;
};



}
    







#endif