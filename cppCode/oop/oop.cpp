#include <iostream>
#include "birthday.hpp"
#include<type_traits>

//tasks
void task1()
{
    std::cout << (Birthday() == Birthday(0,0,0)) << (1==1) <<"\n";
    std::cout << std::is_move_constructible<Birthday>::value << "Moove \n";
}




int main(){task1();}