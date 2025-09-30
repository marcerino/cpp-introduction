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
rückgabetyp name(parametertyp name, parametertyp name)
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
1. By default make all function parameters const & 
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


# Tasks
## Task 1
Postleitzahl gibt es eine Tabelle

## Task 2


## Task 3