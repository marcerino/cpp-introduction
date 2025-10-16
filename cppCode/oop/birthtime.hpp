#pragma once
#include "birthday.hpp"

class Birthtime : public Birthday
{ 
private: 
    uint16_t hour;
    uint16_t seconds;
public: 
    uint16_t get_hour() const; 
    uint16_t get_seconds() const; 

    void set_hour(uint16_t const h); // lazy 😉 
    void set_seconds(uint16_t const s); 

    // Default constructor 
    Birthtime();

    // Copy constructor 
    Birthtime(Birthtime const & c);

    //copyassignment constructor
    Birthtime & operator=(Birthtime const & rhs);

    // Move constructor 
    Birthtime(Birthtime &&); 

    // Custom constructor 
    Birthtime(uint16_t const y, uint16_t const m, uint16_t const d, const uint16_t h, const uint16_t s);
    // Destructor 
    ~Birthtime();
};