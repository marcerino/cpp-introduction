# Object lifetime
Disclaimer: 
- As with many topics I sometimes don't tell the whole truth and make sensible reductions. 
- "Lifetime", "Scope" and "Storage duration" are closely related (but distinct) terms. 
- I won't cover the distinctions here, but there are links at the end of this section that do.
- "Lifetime of an object is equal to or is nested within the lifetime of its storage" 
- I henceforth focus on "storage duration"

Storage duration (how)
1. automatic storage duration:
	- allocated at beginning of the enclosing code block and deallocated at end 
2. static storage duration: 
	- allocated when the program begins and deallocated when the program ends; only one instance of the object exists 
3. dynamic storage duration: 
	- allocated "manually" by new and deleted by delete 
4. thread storage duration:
	- allocated when the thread begins and deallocated when the thread ends; one instance per thread

(what)
- automatic storage duration: all local objects, except those declared static, extern or thread_local 
- static storage duration: all objects declared at namespace scope (including global namespace), plus those declared with static or extern 
- dynamic storage duration: those objects allocated "manually" by new 
- thread storage duration: only objects declared thread_local;  thread_local can appear together with static or extern. 

where?
- automatic storage duration: usually allocated on the stack 
- static storage duration: usually has separate memory region 
- dynamic storage duration: usually allocated on the heap 
- thread storage duration: usually has separate memory region

![[Pasted image 20251008104442.png]]

```c++
char c = 'C'; // global variable (implicit static storage // duration; 'static' keyword means something // else here (internal linkage)!)
struct F { 
	static size_t i = 23; // static member variable 
	size_t j = 42; 
};

void foobar() 
{ 
	static size_t i = 0; // static "local" variable 
	std:: cout << i++ << ' ';
} 
```
eine Static variable wird nur 1 mal initialisiert, auch wenn sie out of scope beibt sie bei dem wert sollte 

Static member Variable: ist eine geteilte Ressource über alle Objekte (veränderere ein verändere alle). 
Zugriff ist möglich via `CLASSENNAME::membername;`

There is only one i in the whole program. i is allocated on program start and exists until the end of the program. Each invocation of foobar() prints a larger number. The name "i" is only visible within this function, not globally.

There is only one i in the whole program. i is allocated on program start and exists until the end of the program. If i is also public, it is visible globally under the name F::i. When an object f of type F exists, i is also accessible as f.i (like other members).


## Dynamische storage durarion 
wann allokiert wird, wann desallokiert wird.

- All automatic/static/thread storage is allocated and deallocated without you having to worry about it.
- For dynamic storage duration, allocation and de-allocation can happen during any time of program execution. 
- It can be governed by run-time decisions.
*In C++ the term "dynamic" usually refers to the opposite of "static". In the case of storage duration this is not fully true, because there is more than "static" and "dynamic", but you should remember that "dynamic" almost always refers to things happening at run-time!*

## Stack vs. Heap 
This is not a class about computer architecture, we won't go into details of the memory. But you should remember: 1. Dynamic memory needs to be allocated upon first use (and later deallocated), i.e. dynamic storage might be 'slower'. 2. On the other hand the heap can grow to be the entire system memory, while the stack is often limited to a few MBs, i.e. more dynamic storage is possible. Being able to allocate user defined types on the stack is one reason C and C++ are faster than other languages (e.g. Java allocates all objects on the heap).

# new and delete
Normales array ist statisch auf stack

The dynamic array:
- The obvious correct answer is to use a vector, we know that it can grow. 
- So it must be doing something fundamentally different; it cannot be known at compile-time how many numbers the user will provide. 
- Before we look at what the vector does, we'll look at a simpler example!

```c++
size_t s{}; std::cin >> s; // ask the user for the size 
int64_t * arr = new int64_t[s]{}; // 🧐 

for (size_t j = 0; j < s; ++j) // can't use range-based for loop anymore 
	std::cin >> arr[j]; 
	
for (size_t j = 0; j < s; ++j) 
	std::cout << arr[j] << ' '; // print it back out 

delete[] arr; 
```

```c++
new int64_t[s]
```
- reserviert einen speicherblock der größe (s mal int64_t) und 
- gibt die adresse auf das erste elment wieder
`int64_t * arr` ist ein **pointer** des names arr
Pointer ermöglichen auch `[]` zugriff
```c++
new int64_t // allocate space for one int64_t 
new int64_t{42} // ... and initialise it with '42' 

new int64_t[n] // allocate space for array of size n 
new int64_t[n]{} // ... and initialise values to 0 
int64_t * i = new int64_t{42}; // pointer to int64_t 
int64_t * j = new int64_t[42]{}; // pointer to first element of int64_t[42]

delete i; // deallocates single variable 
delete[] j; // deallocates array
```
___
**Never forget to delete something allocated with new!**
___
# Raw pointers

## Working with pointers
```c++
int64_t i = 42; 
int64_t j = 23; 
int64_t * i_p = nullptr; // can be initialised to point nowhere 

i_p = &i; // change where you point to 
   // ^ The "reference" symbol is the "address-of" operator here 

*i_p = 7; // change value of the pointee 
// * as unary prefix operator is "contents-of" operator 
// also called "dereferencing" or "indirection" 
int64_t * i_p2 = new int64_t{7}; i_p2 = i_p; // what happens here?
```
`&variablenname` liefert den pointer zu variablenname 
\*pointer dereferenziert den pointer also schreibt nicht den pointer neu, sondern den bereich wo der operator hin zeigt.
```c++
int64_t * arr = new int64_t[7]{}; // "holding pointer" 
arr[0] = 42; // assign to 0th value 
std::cout << arr[0]; // prints 0th elem ("42") 

int64_t * it = arr; // create second pointer to begin 
*it = 23; // assign through pointer 

std::cout << *it; // also prints 0th elem ("23") 
++it; // incrementing pointer moves to next 

std::cout << *it; // prints 1st element ("0") 
it += 3; // moves to 4th... 

delete[] arr;
```
Working with (raw) pointers summary:

- can represent single values or arrays
- hold new values (implied ownership) or existing values (similar to references) 
- but ownership "not implemented" → need to delete / delete[] yourself! 
- 
- pointer types are regular types and pointers are objects – in contrast to references. 
- assignment/comparison/… relate to stored address, not pointee! 
- use "address-of" operator & on any object to get address. 
- use "contents-of" operator * on pointer to access the pointee. 
- instead of writing (\*my_obj).foobar(), you can also write my_obj->foobar() (two letters shorter 🤓)
- this is a pointer to current object, *this returns a reference to current object.


Pitfalls of (raw) pointers:
Using (raw) pointers is a frequent source of bugs, e.g.: 
- Memory leaks (forgetting to delete)
- Double delete (deleting something twice) 
- Use-after-free (using an object after it was deleted) 

Pointers are a legacy from C and many uses of pointers can be easily replaced with references in C++. 
For those cases where one needs pointers, C++ has invented smart pointers that help avoid some of the typical problems.

# Smart pointers
`std::unique_ptr<T> / std::unique_ptr<T[]>`:
- cannot be copied 
- deletes its pointee when its own lifetime ends 
- for "unique" access to some resource 

`std::shared_ptr<T> / std::shared_ptr<T[]>`:
- can be copied; copies "know" about each other 
- when lifetime of last copy ends, it deletes its pointee 
- for "shared" access to some resource

## Resource Acquisition is initialisation (RAII) 
An idiom that describes tying resource management to the lifetime of an object:
- resource acquisition (memory allocation) during construction
- resource release (memory deallocation) upon destruction 

Using smart pointers we can tie the lifetime and management of a heap-allocated object – the pointee – to the lifetime of a stack-allocated (and automatically managed) object, the pointer. 

This makes it easier to reason about resource management and is safer in many situations.

# Tasks Tag 6