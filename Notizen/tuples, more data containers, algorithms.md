# STD - The Standard library
All of it is just plain c++ code (up to 99%)  ist gespeichert als einfacher header files und importierbar via  `#include <headername>`.
und Funktionen Objekte Klassen etc. aus der std müssen mit der std:: prefixt werden.
umgehen kann man dies mit `using namespacestd;` 
___
**`using namespacestd;` nur in .cpp files nicht in header files**
___
Template typen könnne deduced werden aber nicht.
Achte bitte immer auf die Komplexität einer ausführung , und Objekte.
# Tupel
Tupel sind ein Idealer Datentyp um mehrere Werte/Daten/Obekte auch von **unterschiedlichen** typen zu koppeln. Dies wird genutz um mehrere Datentypen zurück zu geben.
Definition:
```cpp
std::tuple{a,b} // mit konstrucktor
// oder als typ
std::tuple<typ 1,typ 2, typ 3>
```

## Tupel access:
You can access tuple elements via:
1. std::get\<NUMBER>() 
2. std::get\<TYPE>() (only if the types are unique!) 
3. "structured bindings", i.e. declaring a set of variables of auto type (or auto & or auto const &...) and assigning the tuple.

```c++
std::tuple<std::string, std::string> cosmonaut{"Sigmund", "Jaehn"}; 

// via get
 std::cout << "First name: " << std::get<0>(cosmonaut) << ' ' << "Last name: " << std::get<1>(cosmonaut) << '\n'; 
// via structured bindings 
auto & [ f, l ] = cosmonaut; // std::string & f = std::get<0>(cosmonaut)… 
std::cout << f << ' ' << l << '\n';
```
## Tupel creation
Creating tuples from existing variables copies the values and discards `const`
```c++
size_t const i = 7; 
std::string s{"foo"}; 

std::tuple tup0{i, s}; // == std::tuple<size_t, std::string>
```

To make a tuple of references you would need to specify that or use the **`std::tie()`** Funktion:
```c++
std::tuple<size_t const &, std::string &> tup1{i, s};

auto tup2 = std::tie(i, s); // == std::tuple<size_t const &, // std::string &>
```

# Sequenz containers
## Overview
- std::array Fast access, but fixed number of elements 
- std::vector Fast access, efficient insertion/deletion only at end 
- std::basic_string Like std::vector, but optimised for character types 
- std::deque Efficient insertion/deletion at beginning and end 
- std::list Efficient insertion/deletion also in the middle, no [] 
- std::forward_list Efficient insertion/deletion also in the middle, no []
## Iterator
Iterator sind objekte die das momentane element haben und zu nächsten element springen, wen gelesen (im for loop)?
```cpp
T my_cont{1, 2, 3, 4, 5}; 
for (auto const & elem : my_cont) // "range-based" 
	std::cout << elem << ' '; 

for (size_t i = 0; i < my_cont.size(); ++i) // via [] 
	std::cout << my_cont[i] << ' '; 

for (auto it = my_cont.begin(); it != my_cont.end(); ++it) // via iterator 
	std::cout << *it << ' ';
```
- The second loop is much more flexible than the first, e.g. you could increment twice, to get every second element; or you could decrement the counter again, based on a condition. 
- But `operator[]` it is not available for all containers, `std::forward_list` doesn't even have `.size()` 😱
```c++
for (auto it = my_cont.begin(); it != my_cont.end(); ++it) // via iterator 
	std::cout << *it << ' ';
```
### Iterator Functions
- All STL containers return an iterator pointing to the first element when calling .begin(). 
- This iterator can be incremented (++) to move to the next element, or dereferenced (\*) to **retrieve the actual element** (both in O(1)!). 
- It can also be compared against the special "end-iterator" retrieved by calling .end(); **this points behind the last element**.
- Most iterators offer more functions, like decrement (--) or +=. 
- Iterators are leight-weight objects, they are cheap to copy! 
- All STL containers can be looped over via iterators or "range-based", but not all via random access (`[]`).
## Sequence containers
![[Pasted image 20251005223656.png]]
# Associative containers
## Overview
- std::set / std::unordered_set collection of unique 
- keys std::multiset / std::unordered_multiset collection of keys 
- std::map std::unordered_map collection of key-value pairs; keys unique 
- std::multimap std::unordered_multimap collection of key-value pair

- Ordered associative containers are sorted by key, operations are in O(log(n)). 
- Unordered associative container are not sorted, operations are in O(1). 
- Maps are the most popular associative containers. ("dictionaries" in other languages)
## std::map
```c++
// key value 
std::map<std::string, size_t> 
name_salary{}; // key value 
name_salary["Horst"] = 7000; // [] creates element if not found 
name_salary["Angela"] = 5439; 
name_salary["Horst"] = 3999; // overwrites previous value 
for (auto const & [name, freq] : name_salary) 
	std::cout << name << " is paid " << freq << " bitcoin!\n";
```

- The element type of the map is a pair so we can use "structured bindings" to decompose the pair into individual variables.
- The first line printed will be "Angela...", because elements are sorted 
- Each \[] takes O(log(n)), ordered map usually implemented as tree.
## std::unordered_map
```c++
// key value 
std::unordered_map<std::string, size_t> name_salary{}; // key value
name_salary["Horst"] = 7000; // [] creates element if not found 
name_salary["Angela"] = 5439; name_salary["Horst"] = 3999; // overwrites previous value 
for (auto const & [name, freq] : name_salary) 
	std::cout << name << " is paid " << freq << " bitcoin!\n";
```
- The element type of the map is a pair so we can use "structured bindings" to decompose the pair into individual variables. 
- It is undefined which element is printed first!
- Each \[] takes O(1); unordered map usually implemented as hash table.
# Algorithms
Many functions (and usually) function templates can be found in the \<algorithm> header that work on sequences, e.g. Ordered Description

- std::sort Sort the range of items 
- std::count Count the times an item apears in range 
- std::find Find first item that matches 
- std::reverse reverse the items in a range 
- std::unique remove subsequent(!) duplicates

All of these take two iterators to denote the range of elements they work on, e.g.

```c++
template <typename TIterator> 
std::sort(TIterator b, TIterator e); 

template <typename TIterator, typename TLambda> 
std::sort(TIterator b, TIterator e, TLambda const & l); 

std::vector<size_t> vec{1, 5, 4, 9}; 
std::sort(vec.begin(), vec.end()); // vec == { 1, 4, 5, 9} 
std::sort(vec.begin() + 1, vec.end(), [] (size_t const l, size_t const r) 
{ return l > r;}); // vec == { 1, 9, 5, 4}
```