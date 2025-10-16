r-value ist ein Objekt dass keinen Namen hat (nicht an einen Namen gebunden)
```c++
size_t s1c = size_t{1};  

size_t & s3a = i1;  
// size_t & s3b = i2; 
//size_t & s3c = size_t{1}; 

size_t const & s4a = i1;
size_t const & s4b = i2;
size_t const & s4c = size_t{1}; // funkioniert, da kann ein temporäres objekt an eine reference zu const binden. Die Referenz verlängert die lebens zeit des objekts bis ende der ref sehr häufig anwendbar
```
If we copy, we don't care about const-ness. We can only bind non-const-ref to non-const-objects & cannot bind to a temporary value, but const & apparently can!

```c++
void print(std::string const & s) 
{
std::cout << s: 
} 

std::string s1{"foo"};
std::string const s2{"bar"};
print(s1); // pass by ref 
print(s2); // pass by ref 
print("bax"); // <- temporary
```
The const & binds to the temporary and extends its lifetime to match its own lifetime. This feature of const & allows us to write interfaces that handle references and values. 

Q: Why can't non-const & do this?
A: void print(std::string & s) would suggest that the function's purpose is to permanently change an outside parameter. Since the temporary does not exist outside of the function, this would not make sense.
____
```c++
public: 
	MyVector() = default;
	 MyVector(MyVector const & rhs) 
	 { 
	 operator=(rhs); 
	 } 
	 MyVector & operator=(MyVector const & rhs) 
	 { size = rhs.size; // copy size 
	 delete[] data; data = new T[size]; // deallocate and reallocate 
	 for (size_t i = 0; i < size; ++i) 
		 data[i] = rhs.data[i]; // copy every element return *this; }
 
```
Sollten wir ein Temporäres objekt in den Vektor geben, dann müssen wir nicht dieses Kopieren sondern können die Daten in unser Objekt  rein **Mooven**!

or temporaries, we would like to just transfer ownership instead of reallocating:

```c++
MyVector & operator=(MyVector && rhs) 
{ 
size = rhs.size; // copy size 
delete[] data; data = rhs.data; // point to rhs' data 
rhs.data = nullptr; // prevent rhs from deleting return *this; 
return *this;
}
```

`&&` bedeutet in typen `r-value reference`

This looks correct, but we have two problems:
- we still need the old assignment operator for copying from references 
- we can't take rhs by something that is const, because we are changing it

Übersicht welche ausdrücke stimmen:
![[Pasted image 20251009103502.png]]

Overloading:
```c++
void foo(size_t i) {} // (1) 
void foo(size_t const i) {} // (2) 
void foo(size_t & i) {} // (3) 
void foo(size_t const & i) {} // (4) 
void foo(size_t && i) {} // (5)
```
(1) and (2) can never be declared together.
- (1) is ambiguous with (3), (4), (5) 
- (2) is ambiguous with (3), (4), (5)
Typically either:
	(1) or (2) or (3) or (4) or (4)+(5) 
	(3)+(4)+(5) possible, but unus


![[Pasted image 20251009104157.png]]

## MyVector – Summary move construction/assignment
The Move-constructor and the move-assignment operator allow us to avoid unnecessary copies, because they are chosen automatically by overload resolution over the copy-constructor / copy-assignment operator when the source is a temporary. By default they move-assign/move-construct all members. If you provide you own copy-constructor / copy-assignment operator, move-* will never be declared implicitly, you should also define or explicitly =default them.

## Explicitly moving
```c++
std::move() // Move macht value zu einem r value 
std::vector v0{1, 2, 3, 5}; 
std::vector v1{v0}; // v1 is copy of v0 
std::vector v2{std::move(v0)}; // contents of v0 moved into v2
```

- It is possible to "mark something as being a temporary" using std::move. 
- Note that std::move does not actually move something by itself, it merely casts its argument to && so that other functions (e.g. the move constructor) are chosen and can then "steal" the contents. 
- Attention: this leaves the moved-from object in "valid, but unspecified state" → you cannot use them afterwards, potential for errors!

```c++
void foo(MyVector<size_t> && s) { /*…*/ } 

void bar(MyVector<size_t> && s) 
{ 
s[0] = 42; 
foo(std::move(s)); 
} 
bar(MyVector<size_t>{7})
```
innerhalb hat bar einen namen, (verliert r -value eigenschaft) hiermit kann die r - value eigenschaft wiederher eschtellt werden.

## Use-cases for && outside of construction/assignment?
```c++
MyVector<size_t> foo(MyVector<size_t> const & s) 
{ 
	MyVector<size_t> ret_value{s}; 
	ret_value[0] = 42; return ret_value; 
} 
MyVector<size_t> foo(MyVector<size_t> && s) 
{ 
	MyVector<size_t> ret_value{std::move(s)}; // avoid copy ret_
	value[0] = 42; 
	return ret_value; 
}
```


Q: Do you need to do that for all functions that copy input? 

```c++
MyVector<size_t> foo(MyVector<size_t> ret_value) // copy or move by constructor 
{ 
	ret_value[0] = 42; 
	return ret_value;
}
```
A: If you need to copy the input, take it by value and trust the constructors!

Q: What about the return value, should we move it out?
A: No, copies of the return value are avoided automatically¹.

### std::swap
std::swap ist move implementiert, dann ist swap auch möglich

## Summary
There are rvalue references denoted by && that only bind to temporary objects. We can use these to define move-constructors and move-assignment operators that are then preferred overloads for temporaries. These can be used to "steal" dynamically allocated memory instead of copying which is more efficient (memory on the stack is always copied!) rvalue references are rarely used outside of move-construction/assignment. If you copy the argument-to-a-function inside that function, just take the input by value. If you "pass on" a temporary, you need to explicitly std::move it.

# Forwarding

value references:
```c++
MyVector<int> && v = /*…*/ void 
foobar(MyVector<int> && v) { /*…*/ }
```
forwarding references:
```c++
auto && v = /*…*/ 
template <typename T> 
void foobar(T && v) { /*…*/ }
```

![[Pasted image 20251009110320.png]]

```c++
template <typename TRange> 
void foo(TRange && rng) // can be `&`, `&&`, `const &` 
{ 
	for (auto && elem : rng) // can be `&`, `&&`, `const &` 
	{ 
		std::cout << elem; 
	} 
}
```
- Forwarding references are useful in generic code, because you can express logic independent of whether you are working with references or values (and independent of const-ness); use when you would otherwise use const &, but where you want to change the values.
- In the above example, rng could be a container (type of elem has &) or a "generator" (type of elem has &&).

## Perfect forwarding
```c++
template <typename TRange> 
void foo(TRange && rng) { /*…*/ } 

template <typename TRange> 
void bar(TRange && rng) 
{ 
	/*…*/ 
	foo(std::forward<TRange>(rng)); 
}
```

- As with rvalue references, objects bound to forwarding references loose their "temporary-ness".
- To preserve it you cannot std::move them, because the function template handles both: temporaries and references. 
- Instead you can std::forward them which preserves the original type independent of context.

## Summary
- && as part of template parameters or in combination with auto is not an rvalue reference, but a forwarding reference. 
- Forwarding references can act as rvalue references and as regular references (single &) depending on context. 
- Inconsistent, but makes writing generic code easier. 
- Whenever you would std::move something bound to an rvalue reference, you should std::forward it if bound to a forwarding reference.
- Appears quite frequently in generic code.
# Inheritance and virtual functions

We distinguish two roles of inheritance: 
- Interface inheritance: An object of a derived class can be used wherever an object of the base class is required. 
- Implementation inheritance: A base class provides functions or data that simplifies the definition of a derived class.
![[Pasted image 20251009111222.png]]

```c++
void printArea(Shape const & s) 
{ 
	std::cout << s.area() << '\n'; 
} 
Square sq{}; sq.width = 4; printArea(sq); 
Circle ci{}; ci.radius = 4; printArea(ci);
```
output:
```bash
nan 
nan
```

Verbesserung:
```c++
struct Shape { 
virtual double area() const { return NAN; } // returns not-a-number 
virtual double perimeter() const { return NAN; } // returns not-a-number 
};

struct Square : Shape 
{ 
double width{}; 
double area() const override 
{ return width*width; } 
double perimeter() const override 
{ return 4*width; } 
};

```

ein virtual initialisiert einen v-table. Jedes abgeleitetes Objekt trägt einen hidden Pointer der auf einen eintrag in dem v table zeigt.

## Virtual functions Summary
- The virtual keyword tells the compiler that Shape might be a Shape or a derivate (derived class).
- When calling a member function that is marked virtual in the base class 
1. the compiler performs a look-up at run-time to see if the object you are referring to, is in fact a derivate 
2. if yes, checks if that class overrides that function 
3. if yes, calls the derivate's function instead of its own 
- The override keyword in derivates is optional (it will "override" without it), but highly recommended! 
- The final keyword may be used instead of or additionally to override to state that (further-)derived classes may not override this function anymore.

Interface inheritance

- Interface inheritance virtual function lookup works as expected on references and pointers, you can directly assign objects/new values of derived type to references/pointers of the base type. 
- But when you implicitly convert to an object of the base type, slicing happens: you simply get an object of the base type and any state of the derivate is not represented in the new object. 
- This means if you want to store a collection of possibly different related types in e.g. a vector, you need to store pointers (you cannot store references in a std::vector):

```c++
std::vector<std::unique_ptr<Shape>> vec{}; 
vec.push_back(std::make_unique<Circle>()); printArea(*vec[0]); // prints `0` because object was default-initialised
```

## Abstract base classes
```c++
struct ShapeInterface { 
virtual double area() const = 0; // this function is "pure" virtual 
virtual double perimeter() const = 0; // this function is "pure" virtual 
};
```
Sobald eine  memberfunlktion ein `virtual ....  = 0` hat, ist es eine abtrakte klasse.

- Abstract base classes virtual functions that are declared with = 0 are pure virtual functions, they never have a definition.
- A class (type) with at least one pure virtual function is an abstract class (type).
- You cannot create objects of abstract types, but you can inherit from them and declare references or pointers to them.
- You should separate interface inheritance from implementation inheritance, because this makes reasoning about inheritance much easier; one is the formal description of the properties of the type, the other is some helper to reduce code- duplication. 
- Interfaces should be declared as abstract classes to highlight that they cannot be used on their own. 
- This also prevents some slicing errors.


## Interface abstractclasses Inheriatance Summary
- Virtual functions facilitate specialisation similar to inheritance in other languages like Java. 
- In C++ functions need to be explicitly marked as virtual for this to work.
- If you override a virtual function in a derived class, additionally mark it as override. 
- With virtual functions, use class (not struct) and follow rule-of-six! 
- Make sure to declare your destructor as virtual so that correct clean-up happens. 
- Separate interface inheritance from implementation inheritance, make interface classes abstract by marking all member functions as pure virtual (= 0).
