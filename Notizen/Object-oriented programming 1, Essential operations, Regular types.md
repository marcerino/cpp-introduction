# Essential operations and Regular types

- Essential operations, conventional operations Essential: 
1. construct: create an object, possibly initialise 
2. assignment: change the state of existing object 
3. destruct: free the resources of an object 

Conventional: 
1. compare: (in-)equality, less-than... 
2. swap: exchange contents of two objects (covered later)
## Constructors
Sometimes you may want to protect your member variables so that they are only accessible to member functions. 
You can use the private and public keywords to denote this difference. A class is a struct whose members are private by default.

- A constructor is a special member function with the name of the type and no return type. 
- Called when attempting to create a new object of a given type. 
- Here the constructor enables us to initialise the object's members on creation. 
- There is a convenience syntax (initializer list) for initialising members.
```c++
class Complex 
{ 
private: 
double re{}; 
double im{}; 

public: 
Complex(double const _re, double const _im) : 
re{_re}, im{_im} //<-initializer list 
{ 
} // other member functions... 

}; // now this works again: Complex c{1, 3.4};
```


Constructors - struct vs class 
- Both class and struct are "class types", you can do everything with both, by definition the only difference is that members are private by default in classes and public by default in structs. 
- BUT there is a very strong convention to 
	1. use class instead of struct when you have class invariants (this usually implies custom constructors)
	2. use class if you want to hide implementation details, e.g. an internal data structure, which the user shall not have access to 
A class invariant is a restriction on the state of objects of your class, e.g. 
- "The float member .f may only hold positive values" 
- "If the value of member .a changes, member .b needs to be updated" 
This usually means: Explicitly declare all constructors/destructors in classes and none in structs
## Invarianten
```c++
#include <cassert> // provides the assert() macro/function 

class Birthday 
{ 
private: 
uint16_t month{0}; // member initializer: here to `0` (explicit) 
uint16_t day{}; // member initializer: also 0, but implicit 

public: Birthday(uint16_t const m, uint16_t const d) 
{set_month(m); set_day(d); } 

uint16_t get_day() const { return day; } 
uint16_t get_month() const { return month; } 

void set_day(uint16_t const d) { assert(d <= 31); day = d; } // lazy 😉 
void set_month(uint16_t const m) { assert(m <= 12); month = m; } 
};
```

There are different ways to enforce invariants: 

- `assert()` from `<cassert>` causes program to abort; error only in DEBUG mode!
- throwing exceptions (more on this next week); always cause error, but can be caught by program. 
- silently restore correct state on invalid input (e.g. convert values), never errors.


## Constructor Types
![[Pasted image 20251007111054.png]]
Möglichkeit default const:
```c++
// Default constructor 
Birthday() = default; 

// Copy constructor 
Birthday(Birthday const &) = default; 
// Move constructor 
Birthday(Birthday &&) = default; 

// Custom constructor 
Birthday(uint16_t const m, uint16_t const d) { set_month(m); set_day(d); } // more custom constructors 

// Destructor 
~Birthday() = default;
```

- Member initialisers are executed by all constructors unless the c'tor initializes the member explicitly 
- A typical reason for a class not being default-constructible is one of it's data members not being default-constructible, e.g. data members of reference type are not! 
- Mark it as = default and rely on member initialisers if the default constructor enforces no invariant. The defaulted default constructor(!) calls the default constructors of base-classes and members. 
- Mark it as = delete only if your class absolutely cannot be created without some parameters.

Attention: 
- For class types with user-provided constructors Birthday d0; and Birthday d1{}; behave the same, both call the default constructor. 
- But for built-in types like float and class types without user-provided constructors, {} leads to initialisation while omitting it leads to no initialisation.
→ It's good practice to always write {}.
### Constructors - copy constructor

Essential operations - Summary

No: call it struct no user-provided constructors, destructor or assignment operators (assumed to be defaulted) "Rule-of-none" / "Rule-of-0" everything public no virtual functions e.g. plain data storage also called "aggregate types"

Yes: call it class always explicitly provide 1. default constructor 2. copy constructor 3. move constructor 4. copy assignment operator 5. move assignment operator 6. destructor "Rule-of-6" can be = default or = delete or user- define
```c++
Birthday(Birthday const & rhs) 
{ set_day(rhs.get_day()); set_month(rhs.get_month()); }
```
### Constructors - copy assignment
- Assignment is closely related to Construction.
- We expect that if a new object can be constructed as the copy of another one, we should also be able to make an existing object the copy of another one.
- With very few exceptions, copy assign and copy construct should leave the object in the same state!
- In fact, one is usually implemented as using the other.
- Can be marked = default or = delete, too. 
- There is also move assignment (more on this later).
```c++
Birthday & operator=(Birthday const & rhs)
 { month = rhs.month; day = rhs.day; return *this; }
```

## Conventional operations - comparison (C++<=17)
 Conventional operations - comparison (C++<=17)
- Comparison should be implemented as a free function (or a friend), not a member. You can't make 1 == X{} work with a member function - it has to be a free function
- Comparison is strongly related to assignment and by convention you should make sure that a = b results in a == b. (This might sound trivial, but it isn't always, e.g. if a and b have different types).
- Always try to define == and !=, if possible also <, <=, > and >=.
- Cannot be = default, must be user- implemented, but can be made easier with std::tuple and std::tie; re-use one operator to implement another.
(C++20 or later):

```c++
class Birthday { /**/ }; 

bool operator==(Birthday const & lhs, Birthday const & rhs) 
{ 
return std::tuple{lhs.get_month(), lhs.get_day()} == std::tuple{rhs.get_month(), rhs.get_day()}; }

```
comparison operators can be defaulted 
- <=> (spaceship operator) can be defaulted and allows 3-way comparison (returning -1,0,1 for less,equal,greater) 
- this will implicitly define \==, <, etc. 
- rules on what type is returned by <=> are a bit complicated... 
- 1 == X{} works with a member function bool X::operator\==(int); since comparisons are symmetric in C++20 or later

Try to make all of your types regular, it makes reasoning about them much easier.
Regular type: copyable movable default-constructible (in-)equality-comparable

# Simple inheritance
We distinguish two roles of inheritance: 
- Interface inheritance: An object of a derived class can be used wherever an object of the base class is required.
- Implementation inheritance: A base class provides functions or data that simplifies the definition of a derived class.

```c++
#include <cassert> // provides the assert() macro/function 

class Birthday 
{ 
private: uint16_t month{}; uint16_t day{}; 
public: 
Birthday() = default; 
Birthday(uint16_t const m, uint16_t const d) 
{ set_month(m); set_day(d); } 
uint16_t get_day() const { return day; } 
uint16_t get_month() const { return month; } 

void set_day(uint16_t const d) { assert(d <= 31); day = d; } // lazy 😉 
void set_month(uint16_t const m) { assert(m <= 12); month = m; }
};

class ExactBirthday : public Birthday 
{ 
private: 
	uint16_t hour{}; 
public: 
	ExactBirthday() = default; 
	ExactBirthday(ExactBirthday const &) = default; 
	ExactBirthday(ExactBirthday &&) = default; 
	ExactBirthday & operator=(ExactBirthday const &) = default;
	ExactBirthday & operator=(ExactBirthday &&) = default;
	~ExactBirthday() = default; 
	
	// either: 
	ExactBirthday(uint16_t const m, uint16_t const d, uint16_t const h) { set_month(m); set_day(d); set_hour(h); } 
	
	// or: 
	
	ExactBirthday(uint16_t const m, uint16_t const d, uint16_t const h) 
	: Birthday(m, d) 
	{set_hour(h); }
	
	uint16_t get_hour() const { return hour; } 
	void set_hour(uint16_t const h) { assert(h <= 23); hour = h; } };
```

class ExactBirthday is derivate of the base class Birthday Members of Birthday are accessible: public members: by everything protected members: by self and derivate classes private members: only by self Members not directly accessible can be changed indirectly through members that are

```c++
ExactBirthday & operator=(ExactBirthday const & rhs) { Birthday::operator=(rhs); hour = rhs.hour; return *this; }

//oder 
ExactBirthday & operator=(ExactBirthday const & rhs) = default
```
___
**Custom Constructoren werdne nie geerbt.**
___

Derived types are implicitly convertible to their base types so bool operator \==(Birthday const & lhs, Birthday const & rhs) is called which evaluates to true. Exercise: what happens when you compare two ExactBirthday objects?


- Class types can inherit other class types to re-use code and to be used in similar situations (more on the latter in two days).
- The type of inheritance is almost always public.
- Whether or not members of the base type can be accessed by the derived type depends on their access protection. 
- Constructors and assignment operators are not inherited by default. 
- Derived types are implicitly convertible to base types, but not the other way around.

# Aufgaben

Can you compare objects of type Birthtime with Birthdate? What are the semantics?
Yes, you can Compare, it will check the most recent Origin and their common members

Write a free function void print(Birthdate & d) that streams out the date in "YYYY-MM- DD" notation. What happens when you print a Birthtime with this function? Does conversion take place?

It cuts all of its experience 