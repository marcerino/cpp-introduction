oHerr Chris Bielow, Herr Sando Andreotti
___
A6 SR 031 Vorlesung | Lab T9 K036 | Test Fr 13-14 |
___
# Über C++
- C++ ist ein erweitete C Sprache (erweitert um Klassen) 
- C++ ist für **Performance** ausgelegt, 
- C++ hat Klassen
- erlaubt generische Programierung (Typ nicht festgelegt ) - Achten sie auf Templates
- erlaubt funktionale Programmierung

- Ist seit den 80er verwendbar
- kommen jeweils neue Konzepte dazu
- C++ ist eine **Compilierte** Sprache
	- Programmm muss vorher Compiliert werden bevor 
	- C++ ist nicht Portabel
	- erlaubt optimierung
	- fehler Passieren vor dem Ausführen 
- Bestet aus der Kernsprache und die Standardlibary
	- Sachen wie arrays müssen explizit Gestatet werden
- Statisch typisiert
	- Der typ einetr Variable muss standardmäßig a sein.
# Variables, Constness, I/O, STL (vector, string, ...)
Was braucht man?
- compiler
- editor
- debugger (optional)
IDEs entfernen Lerneffekt, in dem C++ Kurs eher one :)

## Hello World
``` cpp
#include <iostream> 
int main() // I am a code comment! 
{ 
	std::cout << "Hello, World!\n"; 
}
```

*//* ist ein Kommentar
*main()* am main() startet an der main Funktion. Diese ist nur 1 
funktionen haben rückgabe typen 
Syntax: (rückgabetyp) (name) (eingabe)
rückgabetyp von main ist int, wird 0 zurückgegeben, dann kein error, sonst ein fehler erschienen.
alle Codeblöcke sind in geschweiften Kalmmern "{}" getrennt

input output ist nicht standardt mäßig nicht da, desswegen muss man den header *iostream* implementieren.
<< ist ein Operator, der den Text in den output zieht.
; beendet Ausdruck
## Variablen
declaration: mache einen namen bekannt
definition: definiert den 

- A type defines a set of possible values and a set of operations (for an object). 
- An object is some memory that holds a value of some type.
- A value is a set of bits interpreted according to a type.
- A variable is a named object

Declaration 
``` c++
int i; // i is a variable of integral type, e.g. 1, 77, -3 
std::string s; // s is a variable of string type
```
 Initialisation 
``` c++
int i; // value of i is undefined, printing it can kill kittens 🙀 
// C++ Mantra: Only pay for what you use. 
int j = 7; // j is initialised to 7 
int k{3}; // k is initialised to 3 
int l{}; // l is default-initialised to 0
```
  Rule-of-thumb: Always initialise your variables! If unsure, with {}.
Lierber Initialisieren, statt zu deklarieren, denn sonst kommt es zu abstürzen wenn diese gebraucht werden. 

Assignment 
``` c++
int i{}; // i is initialised to 0 
i = 7; // i is assigned the value 7 
//Beware: 
int i = 42; // this is initialisation! 
i = 23; // this is assignment
```
Assignment & Initialisierung sind Grundverschieden. Rule of Tumb Initialisierung geibt auch den typ an.
### Vektoren 
```c++
vector<int> vec_a{10,20}; // fills the vector with the arguments
```
Vektoren sind Templates welche einen typ bekommen sollen (hier int)
Sie sind vergleichbar mit einer Liste / Array aus python.

### Keyword: auto

Der Kompiler kannn typen automatisch Abgleichen und interpretieren 
``` c++
auto i = 7; // i is of type int 
auto d{3.3}; // d is of type double 
auto x = foobar(); // x is of whatever typ
auto& x_ref = x; // a reference to 'x'
```
Aber dies ist immer noch  statisch typisiert.
Schlechte Praxis, für einfache Typen da der Code weniger lesbar ist, (es ibt aber Situationen wo dies der einzige Weg ist (Templates)) 

## Arithmetische Datentypen
Dies sind Typische Typen
- bool
- char 
- short, int, long, loong loong    (sind verschiedenen längen der Zahl)
- unsigned char, unsigned loong loong
- float double = Fließkomma

Dies  sind Typische Operatoren:
- arithmetic operators: +, -, *, /, % 
- arithmetic assignment operators: +=, -=, *=, /=, %= 
- increment/decrement: ++, -- 
- comparison operators: == ==, !=, <, <=, >, >, ==

Die einfachen int, long sind unsiecher da deren größe von OS zu os unterschiedlich ist, desswegen arbeitet mann mit: 
int8_t, int16_t, int32_t, int64_t uint8_t, uint16_t, uint32_t, uint64_t
wenn mit :#include cstdint gearbeitet wird.

## Constanten
- const: meaning roughly "I promise not to change this value" . This is used primarily to specify interfaces, so that data can be passed to functions without fear of it being modified. The compiler enforces the promise made by const. 
- constexpr: meaning roughly "to be evaluated at compile time". This is used primarily to specify constants, to allow placement of data in memory where it is unlikely to be corrupted, and for performance.

## Input Output:
- Use std::cout for normal interaction with the user. 
- Use std::cerr to print error messages. 
- Use std::cin to read user input. std::cout and std::cerr are used with output stream operator <<. std::cin is used with the input stream operator >>. You can "chain" multiple input/output operations by repeatedly invoking the respective stream operator. 
- The input stream implictly "splits input" at whitespaces. 
- You don't need to understand how the stream operators work at this point.

## Arrays, Vectors and Strings

Array sind hier wirklich nur Sequenzielle abfolge von Feldern (wiein scala  also nicht dynamisch)

### Arrays
Dies ist die Alte C Variante nutze dies bitte nicht:
```c++
// declare built-in array of size 3: 
double dd[3]; 

// can be {} initialised: 
double df[3]{3.1, 2.3, 1.1}; 

// access elements also via [] std::cout << df[0]; // prints 3.1 
df[1] = 32.0; // you can also "assign through" [] 
df[77] = 32.0; // memory access violation, no error, kills kittens 
size_t constexpr s = 100; 
double dg[s]; // only works because s is constexpr
```
- arrays are 0-indexed, size is fixed at compile-time 
- accessing elements behind the end is a dangerous problem

Arrays (standard library) :
```cpp
#include <array> 

// declare standard array of size 3: 
std::array<double, 3> dd; 

// can be {} initialised: 
std::array<double, 3> df{3.1, 2.3, 1.1}; // access elements also via [] 
std::cout << df[0]; // prints 3.1 
df[1] = 32.0; // you can also "assign through" [] 
df[77] = 32.0; // memory access violation, no error, kills kittens 
```
- has convenience member functions: .size(), .front(), .begin() ... 
- has "safe" random access function: .at(77) instead of [77] 
- preferable to "C-array" in any kind of serious code-project

### Vektors
- Vectors are "resizable arrays". 
- provide many more member functions

```c++
#include <vector> 

// declare a vector of doubles: 
std::vector<double> dd; 

// can be {} initialised: 
std::vector<double> df{3.1, 2.3, 1.1}; // access elements also via []
std::cout << df[0]; // prints 3.1 
std::cout << df.size(); // prints 3 

df.push_back(0.5); std::cout << df.size(); // prints 4 
std::cout << df.back(); // prints 0.5
```

### Strings
std::string is similar to std::vector\<char> 
- but has some convenience functions and optimisations. 
- It can be printed as a whole! 
- "FOOBAR" is a string literal (the type is const char[7]) 
- 'a' is a character literal (the type is char)


```c++
#include <string> 

// declare an empty string: 
std::string dd; 

// can be {} initialised: 
std::string df{"FOOBAR"}; 

// access elements also via []
std::cout << df[0]; // prints 'F' 
std::cout << df.size(); // prints 6 
df.push_back('a'); std::cout << df.size(); // prints 7 
std::cout << df; // prints "FOOBARa"
```