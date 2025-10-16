#include <iostream>
#include "birthday.hpp"
#include<type_traits>
#include "birthtime.hpp"


void print(Birthday const & b){
    std::cout << b.get_year() << "-" << b.get_month() << "-"<< b.get_day() << "\n";
}

//tasks
void task1()
{
    
    std::cout << (Birthtime() == Birthtime(0,0,0,0,0)) << " " << (Birthday() == Birthtime(0,0,0,1,0)) << " " << (Birthtime() == Birthtime(0,0,0,0,0)) << " " <<(1==1) <<"\n";
    std::cout << std::is_copy_constructible<Birthtime>::value << "Moove \n";
    print(Birthtime(1,4,5,6,7));
    std::cout << std::is_copy_constructible<Birthtime>::value << "Moove \n";

}




int main(){task1();}