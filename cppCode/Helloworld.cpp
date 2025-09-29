#include <iostream> 
#include <climits>
#include <string> 
#include <cstdint>
#include <cmath>
#include <iomanip>
#include <string> 

void helloworld() {
	std::cout << "Hello, World!\n"; 
}

void task1(){
    std::cout << "Char:\n" << "Charbytes: " << sizeof(char) << " = " << (sizeof(char)*8) << " bits " << "\n large /small: " << CHAR_MAX << "/" << CHAR_MIN << "\n"; 
    std::cout << "U_Char:\n" << "SCharbytes: " << sizeof(u_char) << " = " << (sizeof(u_char)*8) << " bites " << "\n large /small: " << UCHAR_MAX << "/" << WCHAR_MIN << "\n"; 
    std::cout << "short:\n" << "short bytes: " << sizeof(short) << " = " << (sizeof(short)*8) << " bites " << "\n large /small: " << SHRT_MAX << "/" << SHRT_MIN << "\n"; 
    std::cout << "ushort:\n" << "ushort bytes: " << sizeof(u_short) << " = " << (sizeof(u_short)*8) << " bites " << "\n large /small: " << USHRT_MAX << "/" << "0" << "\n"; 
    std::cout << "int:\n" << "int bytes: " << sizeof(int) << " = " << (sizeof(int)*8) << " bites " << "\n large /small: " << INT_MAX << "/" << INT_MIN << "\n";
    std::cout << "int:\n" << "int bytes: " << sizeof(u_int) << " = " << (sizeof(u_int)*8) << " bites " << "\n large /small: " << UINT_MAX << "/" << "0" << "\n"; 
    std::cout << "long:\n" << "long bytes: " << sizeof(long) << " = " << (sizeof(long)*8) << " bites " << "\n large /small: " << LONG_MAX << "/" << LONG_MIN << "\n"; 
    std::cout << "ULONG:\n" << "Long bytes: " << sizeof(u_long) << " = " << (sizeof(u_long)*8) << " bites " << "\n large /small: " << ULONG_MAX << "/" << "0" << "\n"; 
    std::cout << "long long:\n" << "long long bytes: " << sizeof(long long) << " = " << (sizeof(long long)*8) << " bites " << "\n large /small: " << LONG_LONG_MAX << "/" << LONG_LONG_MIN << "\n"; 
    std::cout << "Ulong long:\n" << "Ulong long bytes: " << "error" << " = " << (sizeof(long long)*8) << " bites " << "\n large /small: " << ULONG_LONG_MAX << "/" << "0" << "\n"; 

    constexpr int a = 21645;
    std::cout << a;

}
void task2() {

    std::string s{"foo"}; 
	std::cout << "Welcome to the " << s << " program!\n"; 
	std::cout << "Enter two floating point numbers followed by [RETURN]\n"; 
 
	double d1{};
	double d2{}; 
    std::cin >> d1 >> d2; 
	std::cout << "The sum is: " << d1 + d2 << '\n'; 
    std::cout << "Round down = " << std::floor(d1+d2) << "\n";
    std::cout << "Round up = " << std::ceil(d1+d2) << "\n"; 
    std::cout << "Squareroot = " << sqrt(d1+d2) << "\n";
    std::cout << std::setprecision(2);
    std::cout << (d1+d2) << "\n";
    std::cout << std::setprecision(5);
    std::cout << (d1+d2) << "\n";
    std::cout << std::scientific;
    std::cout << (d1+d2) << "\n";



}    

void task3(){
    std::cout << "Task 4: One Word one Number";
    // declare an empty string: 
    std::string dd; 
    int index{};
    std::cin >> dd >> index;
    std::cout << dd << " " << index<< "\n";
    std::cout << "The " << index << ". Character of " << dd << " is: " << dd.at(index);  

}

int main() // I am a code comment! 
{
    //helloworld();
    //task1();
    task2();
    //task3();
}