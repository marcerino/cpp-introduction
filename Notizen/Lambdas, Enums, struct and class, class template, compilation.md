# Casting 
```c++
uint32_t numbl{}
uint32_t numtotal{}

double ratio = numbln/num_total; // liefert nur eine Int
double ratio = static_cast <double> (numbln)/numtotal; //numbln gecastet als double somit doubleint division rückgabe ist double
```
# Lambdas
Angenommen du hast eine Funktion die quadriert und eine die die wurzel Zieht. für alle Elemente in eine Vektor.,  Diese gleichen sich i allem außer der eigentlichen Operationen.

```c++
template <typename TElem, typename TLambda> 
void on_all_elements(std::vector<TElem> & vec, TLambda const & l) 
{ 
	for (TElem & elem : vec) 
		elem = l(elem);
}

int main() 
{ 
	auto square = [] (auto const & elem) { return elem * elem; };
	auto square_root =     [] (auto const & elem) { return std::sqrt(elem); };
	
 std::vector<double> ds{0.2, 1.5, 2}; 
 on_all_elements(ds, square); // ds == { 0.04, 2.25, 4 } 
 on_all_elements(ds, square_root); // ds == { 0.20, 1.50, 2 } }
}
```

lamda Funktionen werden mit \[]  initialisier, das `auto` zeigt **nicht** auf den Rückgabetyp sndern auf labda da jedes Lambda immer ein eigender typ ist.
___
`auto square = [] (auto const & elem) { return elem * elem; };`
- Lambdas are objects and each lambda has a distinct type – that's why we can only save them in a variable with deduced type and why functions need to take them as template parameters. 
- A minimal Lambda that does nothing is \[](){}. 
- \[] introduces a Lambda definition (other things can go into the \[] - capture group, but we won't cover that now). 
- () contains the parameters, just like with ordinary functions except that auto is valid (even before C++20). 
- {} contains the body of the lambda function. 
- The return type of the Lambda is deduced by default.
# Thought behind User-defined types  
- The arithmetic types, possibly modified by const and/or &, as well as arrays thereof are built-in types. 
- They are low-level; efficiently reflect the capabilities of conventional hardware.
- C++ provides various mechanisms of abstraction for the design of higher level applications. You can combine these abstraction mechanisms with the built-in types to create user-defined types. 
- User-defined types are either enumerations or class types
# Enumerations
- Enumerations are simple user-defined types that represent a small set of integer values by giving them names.
- Helps to make code more expressive, making it easier to read and write and prevents errors. 
- Enumerations can be introduced by enum NAME or enum class NAME, the latter is a strongly-typed enumeration. 
- Prefer strongly-typed enums!

Enumeration C++ implement: (strunglytyped)
```c++
enum class Color 
{ 
red, blue, green, yellow 
}; // ; is important! 
Color invertMe(Color const c) 
{ 
	switch (c) 
	{ 
		case Color::red: return Color::green; 
		case Color::green: return Color::red; 
		case Color::blue: return Color::yellow; 
		case Color::yellow: return Color::blue; 
	} 
}
```
Diese Implenetierung bidnet die Namen direkt an die Klasse. die Namen fliegen nicht wie zuvor als i globalen Namespace rum. In C würde red jetzt immer teil der klasse sein und nichtmehr ein type sein können

# Class Types

Structs dienen eher der Datenbündelung und Aggregierung:
```c++
struct Complex { 
	double re{}; 
	double im{}; 
}; // ; is important! 

Complex c{1, 4}; 

std::cout << "real:" << c.re << " imaginary:" << c.im << '\n'; 
Complex c2; // like {0, 0} 
Complex c3{}; // like {0, 0}
```

- The definition on the left introduces the Complex class type for complex numbers. 
- It consists of two member variables, a real part (.re) and an imaginary part (.im). 
- The member variables can be accessed via the dot-operator. 
- Objects of type Complex can be brace-initialised, both with values and default 
- Member variables of built-in type could (and should!) be member-initialised. {} die basis typen der Klasse sind innitialisiert.
___
**Nach einer Klasse muss ein ";" stehen**
___
## Member Funktionen
sind äquivalent zu Methoden

- Customarily those arithmetic operators that change an object, return a reference to the object itself after it was changed. 
- This enables them to be "chained" and used in expressions.
- At this point you don't need to understand what *this does except "reference to self"
```c++
struct Complex {
//...
void add(Complex const & c) 
{ 
re += c.re; 
im += c.im; 
}
}
```

Implementation: mit den eingebauten operatoren.

```c++
struct Complex 
{ 
	double re{}; 
	double im{}; 
	
	Complex & operator+=(Complex const & c) 
		{ 
			re += c.re; 
			im += c.im; 
			return *this;  //de referene itself
		} 
		
}; 

Complex c{1, 4}; Complex c2{2, 5}; Complex c3{1, 1}; 
// not equivalent to without () 
(c += c2) += c3; // c == {4, 10} 
// c2 unchanged
```
Often some operators can be used to simplify the definition of others. 
Be aware of the different return values: 
- arithmetic+assignment: reference to self 
- regular arithmetic: new object 
- comparison: bool 
Member functions that don't change an object should be marked const; otherwise can't be called on objects of const type.

```c++
Complex operator+(Complex const & c)
 { 
 Complex tmp{re, im}; 
 tmp += c; return tmp; 
 }
```
Wird zu:
```c++
Complex operator+(Complex c) const { return (c += *this);}
```
## Protection
Sometimes you may want to protect your member variables so that they are only accessible to member functions. You can use the private and public keywords to denote this difference. A class is a struct whose members are private by default. More on classes in the 2nd week of the course!

Diese Klasse Funktioniert nicht da die constructor funktion
```c++
class Complex 
{ 
private: 
	double re{}; 
	double im{}; 
public: 
	Complex & operator+=(Complex const & c) { 
	re += c.re;
	im += c.im; 
	return *this; 
	} 
}; 
// private members disable easy initial. 
// Complex c{1, 3.4}; 
// and direct access: 
// std::cout << c.re; 
// can't do: private now
```

# Class templates
Es können Templates für klassen ,



# Sperate Kompilierung

Wenn man größere Projekte schreibt können diese in viele verschiedenen dateien aufteilen
es gibt `.cpp` standard dateien und `.hpp` datei. Die .hpp habe keine `main()` funktion.

The more code you write, the less organised your .cpp will get. To increase readability and maintainability of your code, you should split it into multiple files. C++ knows .cpp files and header files (.hpp, sometimes .h). Header files are like .cpp files, but they don't contain a main() function. Header files are included by \#include; headers can include other headers. Including a header literally results in the entire contents of the header being pasted into the current source file! This also means you need to avoid including a header twice (why?). To do that, write \#pragma once into the header file

There are two different "styles" for organising source code: 
1. A single .cpp file and many header files (or in the case of libraries only headers)
2. A .cpp file with main() and pairs of cpp+hpp files where declaration and definition are split: 
	1. declaration in the header 
	2. definition in the cpp 
The second style is more common, but it depends also on the paradigm of programming.

## -- header-only
- simpler build process; entire library shipped as headers 
- necessary for function templates and members of class templates 
- slower build-times, because all headers are parsed every time and the entire project is rebuilt on every small change
```c++
main.cpp
#include "example.hpp" 
int main() { example_func(); }

exmple.hpp
#pragma once
#include <iostream> 
void example_func() { std::cout << "!!!"; }
```
## -- cpp+hpp
- every pair of cpp+hpp is compiled separately (called translation unit) 
- faster builds (only those parts are rebuilt that changed) 
- libraries used by many programs are shared (less memory used) 
- doesn't work for templates

```c++
main.cpp
#include "example.hpp" 
int main() { example_func(); }

example.hpp
#pragma once
void example_func();

example.cpp
#include <iostream> 
#include "example.hpp" 
void example_func() { std::cout << "!!!"; }
```

####
Build-process unix:
First we build an object file for every cpp other than main:
```bash
% g++ -std=c++17 -Wall -Wextra -Werror -pedantic example.cpp -c 
```
(note the -c!) This created example.o.
Finally we build main.cpp and link it with the existing object files:
```bash
% g++ -std=c++17 -Wall -Wextra -Werror -pedantic main.cpp example.o 
```
In larger projects build-systems like CMake, Meson, Gnu-Make, Ninja or a combination thereof handle this for us.
# Aufgaben
## Task 1 - Filtern
## Task 2 - Structs
4\. Teilaufgabe mach ein mapping
## Task 3 - Opertor Implementerung
## Task 4 - Komplexe Zahlen und Seperate Compiling
Why can templates not have their definitions in separate cpp files? Think about / find out!
Weil teoretisch der Typ bereits compiliert in einer Anderen File ist 