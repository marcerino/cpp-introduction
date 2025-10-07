#pragma once
#include <cstdint>

class Birthday 
{ 
private: 
    uint16_t year;
    uint16_t month; // member initializer: here to `0` (explicit) 
    uint16_t day; // member initializer: also 0, but implicit 
public: 
    uint16_t get_day() const; 
    uint16_t get_month() const; 
    uint16_t get_year() const; 


    void set_day(uint16_t const d); // lazy 😉 
    void set_month(uint16_t const m); 
    void set_year(uint16_t const y);

    // Default constructor 
    Birthday();

    // Copy constructor 
    Birthday(Birthday const & c);

    //copyassignment constructor
    Birthday & operator=(Birthday const & rhs);

    // Move constructor 
    Birthday(Birthday &&); 

    // Custom constructor 
    Birthday(uint16_t const y, uint16_t const m, uint16_t const d);
    // Destructor 
    ~Birthday();
};

bool operator==(Birthday const & lhs, Birthday const & rhs);
bool operator!=(Birthday const & lhs, Birthday const & rhs);