#include <cassert> // provides the assert() macro/function 
#include <cstdint>
#include <tuple> 
#include "birthday.hpp"

uint16_t Birthday::get_day() const { return day; }
uint16_t Birthday::get_month() const { return month; }
uint16_t Birthday::get_year() const { return year; }

void Birthday::set_day(uint16_t const d) { assert(d <= 31); day = d; }
void Birthday::set_month(uint16_t const m) { assert(m <= 12); month = m; }
void Birthday::set_year(uint16_t const y) { assert(y <= 6000); year = y; }

Birthday::Birthday() : year(0), month(0), day(0) {}

Birthday::Birthday(Birthday const & c)
    : year(c.get_year()), month(c.get_month()), day(c.get_day()) {}

Birthday & Birthday::operator=(Birthday const & rhs) {
    year = rhs.year;
    month = rhs.month;
    day = rhs.day;
    return *this;
}

Birthday::Birthday(Birthday &&) = default;

Birthday::Birthday(uint16_t const y, uint16_t const m, uint16_t const d) {
    set_year(y);
    set_month(m);
    set_day(d);
}

Birthday::~Birthday() = default;

bool operator==(Birthday const & lhs, Birthday const & rhs) {
    return std::tuple{lhs.get_year(), lhs.get_month(), lhs.get_day()} ==  std::tuple{rhs.get_year(), rhs.get_month(), rhs.get_day()};
}

bool operator!=(Birthday const & lhs, Birthday const & rhs) {
    return !(lhs == rhs);
}