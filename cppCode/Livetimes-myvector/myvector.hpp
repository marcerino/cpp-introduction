#pragma once
#include <memory>
#include <iostream>

template <typename T> class MyVector 
{
private: 
    size_t capacity{1};
    size_t vecsize{};
    std::unique_ptr<T[]> data{}; 
    
    void rezise()
    {
        size_t newsize = capacity*2; 
        T * newdata = new T[newsize]{};
        for (size_t i = 0; i < vecsize; ++i) 
            newdata[i] = data[i]; // copy every element 
        data.reset(newdata);
        newdata = nullptr;
        capacity = newsize;
    }

    public: 
    //constuctors

    MyVector() = default; 
    ~MyVector() = default; // can now be defaulted 
    MyVector(size_t const s) : capacity{s}, vecsize{0}, data{new T[s]{}} {}
    MyVector(MyVector const & rhs)
    { 
        operator=(rhs);
    } 

    MyVector & operator=(MyVector const & rhs) 
    { 
        if (this != &rhs) 
        { //check self assignment 
            capacity = rhs.capacity;
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
    T operator[](size_t index) 
    {
        return data[index];
    } 

    void push_back(T elem) 
    {
        if (capacity < vecsize+1)
        {
            rezise();
        }

        data[vecsize] = elem;
        vecsize = vecsize +1;
    }
};