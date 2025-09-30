# Control Flow
## Logik operatoren -
- ! negation
- && logical AND
- || logical OR
## If-Abfrage
syntax: 
```c++
if (condition)
{
Codeblock
}
else if
{
Codeblock
}
else {
}
```
Optimations eigenschaften:
- es ist möglich in die condition eine variable zu definieren, die nur im ifstatement 
- if constexpr ist auch möglich, aber alle knditionen mmüssen vorher zu stehen
## Switch case 

```c++
switch (i)
{
  case 0: 
	std::cout << "ZERO\n"; 
	break; 
	case 1: 
		std::cout << "ONE\n";
		break; 
	case 42: 
	  { 
		  char c = 'C'; 
		  // ... 
		  break; 
		} 
	default: std::cout << "OTHER\n"; 
}
```
instead of many successive if checks, do a single switch statement only works for expressions of integral or enum type each case begins with a case label and ends with a break; if you omit the break; statement, subsequent block will also be executed! if you introduce local variables, you must enclose the block in {}
## Control flow -for loops
```c++

std::vector<uint16_t> vec{1, 22, 333, 4444}; 

// "for e in vec" 
for (uint16_t e : vec)
	 std::cout << e << ' '; 
	 
 // initial state. ; run condition; iteration expr. 
 for (size_t i = 0; i < vec.size(); ++i) 
	 { if (i % 2 == 0) continue; 
	 std::cout << "elem no." << i << " is " << vec[i] << '\n';
	 }
```
To iterate over a range (vector, array...) use the short syntax to exit the innermost loop early, call break; to jump to the next iteration early, call continue;

## Controll Flow -while do while

Similiar to for-loops but used less frequently also support break; and continue; often as while (true) and later if (complex_condition) break;

```c++
while (condition) 
{ // ... } 

while (init; condition) 
{ // ... } 
do { // ... 
} while (condition);
```

# Referenzen
What happens when you initialise (or assign) one variable with another variable of the same type?

**Referenzen sind i c+++ richtig wichtig,**
bei zuweisungen wir immer!! eine Kopie erstellt. 
Bei  großenobjekten ist das sehr Kostspielig desswegen kann man Referenzen erstellen. 

Sometimes we don't want to copy, we just want to introduce a new name, that's what references are for:

```c++
std::string s{"A text much longer than this example"}; 
std::string & t{s}; // ^ reference symbol 

std::cout << t << '\n'; // prints "A text..." 
t = "a shorter text"; 

std::cout << s << '\n'; // prints "a shorter text" 
          // ^ original variable has changed
```

Sobald etwas an der Referenz geändert wird wird das originale Objekt auch geändert.
soll eine referenz ihr Objekt nicht geändert werden kann `const` vor dem `&` getsellt werden.

___
**Wenn man ein objekt in eine Schleife oder Funktions geben möchte muss man Referenzen nutzen, da ansonsten diese Elemente nicht geändert werden können**
___
- by default things are copied in C++ 
- avoid copying anything except arithmetic types
- instead of copying you can create references to existing variables references behave just like the original (same syntax) 
- the referred object has to be set at time of declaration and cannot be changed later on
- const-ness can be "added" via a reference, but not "removed" 
- const, & and const & are part of a variable's type, e.g. int const & i; means i is of type "reference to integer constant"

# Funktionen
syntax:
```c++
rückgabetyp name( const parametertyp referenz nameinfunktion , parametertyp name)
{
Codeblock
}
```
Die **Code signatur** ist rückgabe wert name und eingabe argumente

a function must be declared, before it is first used a function may be declared multiple times, but defined only once (one-definition- rule, ODR (one definiion rule))

___
You can return references, but you will need this rarely outside of member functions (more on this tomorrow); and it can be dangerous!
___
Große Objekte werden beim Return nicht Kopiert (ab neuen C++ Versionen) sondern direkt übergeben
___
Recommendations :
1. By default make all function parameters `const &` 
2. Ask yourself: do I want to change it? 
	1. no 
		1. arithmetic type? → just const 
		2. else → keep const & 
	2. yes 
		1. so that change is visible outside? → just & 
		2. change only inside function? → neither const nor & (copy)
___
# Funktions Überladung

- You can have multiple functions with the same name provided 
- they have a different number of parameters; 
- and/or the parameters have different types 
- (a different return type is not sufficient!) 
- This is called function overloading.
- This is very useful when the functions do different things, but...

also square vo double in  ... etc. pp.

aber Mann kann sich zum beispiel

# Funktions-Templates
Templates sind ein weg für einen "Späte-Bindung-Polymorphismus". Der Compiler bekommt gesagt wie ein Code ausgeführt ohne den genauen typen zu wissen.
gebraucht wird ein `Template <typename>`, welche dann als `typ` in der funktion genutzt werden kann.
Beispiel: 
```c++
template <typename U>
const auto Fibonaccilike(U n1, U n2, int32_t c)
{
	U helper{};
	int32_t counter = 0;
	while (counter < c)
	{
		helper = n1;
		n1 = n1+n2;
		n2 = helper;
		counter ++;
	}	
	return n1;
}
int main()
{
	const auto result = Fibonaccilike(3.6,2.4,2);
}
```
`auto` lohnt sich hier, da der `typ` erst von der eingabe abhängt.
Beachte aber, das durch die Eingabe der *Argumente* im quellcode bereits das Ergebnis und somit der typ zur Completime feststeht und ein userinput nicht möglich, da auto bereits bei Compiletime den `typ` wissen muss. 
# Tasks
## Task 1
Postleitzahl gibt es eine Tabelle

## Task 2A
What happens when you return something of const type from a function?

wenn `const func()`, dann inmutable:
wenn `return const foo` oder `const foo; return foo`, resultat ist mutable 

Can constants be initialised from functions that return a non-const type?
ja, const von einer nicht const rückgabe ist möglich.

What happens when you return a reference?
bei:
```cpp

std::string & clash ()
{
std::string A{"A"};
std::string & ref = A;
return ref;
}
```
Eine Ausabe die leer ist
Return einer Referenz auf ein Lokales Objekt ist ein Null pointer oder dangleing reference
Return einer referenz eines vorherexestierenden Objekts verhält sich normal.

Das Example von seite 21:
```c++
double & square() 
{ 
double d{5.3}; 
return d; // 💣 
} 
double & d = square(); // 💥
```
Resultat:
`Referenz auf lokale Variable »d« zurückgegeben -Werror=return-local-addr]`
## Task 2B
What does the program print? Why? How can you "fix" it?
```c++
#include <iostream> 
template <typename T> 
void print(T const i) 
{ 
	std::cout << "Integer!\n"; 
} 
void print(float const i) 
{ 
std::cout << "Floating point!\n";
} 

int main() 
{ 
print(3.3);
}
```
Ausgabe:
```bash
controllflow.cpp: In function »void print(float)«:  
controllflow.cpp:87:24: Fehler: unverwendeter Parameter »i« [-Werror=unused-parameter]  
  87 | void print(float const i)  
     |            ~~~~~~~~~~~~^  
controllflow.cpp: In instantiation of »void print(T) [mit T = double]«:  
controllflow.cpp:179:10:   required from here  
 179 |     print(3.3);  
     |     ~~~~~^~~~~  
controllflow.cpp:83:20: Fehler: unverwendeter Parameter »i« [-Werror=unused-parameter]  
  83 | void print(T const i)  
     |            ~~~~~~~~^  
cc1plus: Alle Warnungen werden als Fehler behandelt
```
Schritt 1:
entfernen der `i` aus der *Funktionssignatur* da diese nicht gebracht/genutzt  werden.
nun ist die Ausgabe: `Integer!`
Schritt 2:
deklarieren des typs von `3.3` als `float dpd = 3.3; print(dpd)` da `print(3.3)` per default 3.3 als Double interpretiert/kompiliert.
## Task 3

make your function 'constexpr', e.g. constexpr auto fib(...) { ... }. Is it sufficient to capture the return value as const auto fib_value = fib(...); or do you need constexpr here as well? 
Apparently yes, compiler doesnt even complein if i capture it without const, and no matter what neither const nor const expr make it immutable idk y tho.



Compute the 5th canonical fibonacci number at compile time. 
3
Can you also compute the 100th number at compile time?
nei, selbst beim nutzen vo long long übersteigt die Nummer die range des Datentypen und der Compiler wirft eine range overflow.