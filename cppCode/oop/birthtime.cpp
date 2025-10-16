#include "birthtime.hpp"
#include <cassert> // provides the assert() macro/function 
#include <cstdint>
#include <tuple> 

uint16_t Birthtime::get_hour() const {return  hour; }
uint16_t Birthtime::get_seconds() const {return  seconds; }

void Birthtime::set_hour( uint16_t const h ) {hour = h;}
void Birthtime::set_seconds( uint16_t const s ) {seconds = s;} 


Birthtime::Birthtime() { Birthday(); set_hour(0); set_seconds(0); }

Birthtime::Birthtime(Birthtime const & c) 
    : Birthday(c.get_year(), c.get_month(), c.get_day()) 
    {hour =c.get_hour(); seconds = c.get_seconds();}



Birthtime::Birthtime(Birthtime &&) = default;

Birthtime::Birthtime(uint16_t const y, uint16_t const m, uint16_t const d, uint16_t const h, uint16_t const s) {
    set_year(y);
    set_month(m);
    set_day(d);
    set_hour(h);
    set_seconds(s);
}

Birthtime::~Birthtime() = default;

bool operator==(Birthtime const & lhs, Birthtime const & rhs) {
    return std::tuple{lhs.get_year(), lhs.get_month(), lhs.get_day(), lhs.get_hour(), lhs.get_seconds()} ==  std::tuple{rhs.get_year(), rhs.get_month(), rhs.get_day(),  rhs.get_hour(), rhs.get_seconds()};
}

bool operator!=(Birthtime const & lhs, Birthtime const & rhs) {
    return !(lhs == rhs);
}