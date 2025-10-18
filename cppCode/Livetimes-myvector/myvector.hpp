#pragma once
#include <memory>


template <typename T> class MyVector 
{
private: 
    size_t vecsize{};
    std::unique_ptr<T[]> data{}; 
public: 
    //constuctors

    MyVector() = default; 
    ~MyVector() = default; // can now be defaulted 
    MyVector(size_t const s) : vecsize{s}, data{new T[s]{}} {}
    MyVector(MyVector const & rhs)
    { 
        operator=(rhs);
    } 
    MyVector & operator=(MyVector const & rhs) 
    { 
    if (this != &rhs) 
        { //check self assignment 
            vecsize = rhs.vecsize; // copy size 
            data.reset(new T[size]); // deallocate and reallocate 
            for (size_t i = 0; i < size; ++i) 
                data[i] = rhs.data[i]; // copy every element 
        } 
        return *this; 
    }

    //member functions
    size_t size() const
    {
        return vecsize;
    }
    T operator[size_t]; 

    void rezise();
    void push_back(T) const;
};