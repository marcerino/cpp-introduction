#include <iostream>
bool exitfrage ()
{
    bool exit = false;
    char antwort{};
    bool result{};

    while (exit == false){
    
        std::cout << "Enter another person? [y/n]: ";
        std::cin >> antwort;
    
        if (antwort == 'y')
        {
            exit = true;
            result = true;
        } 
        else if (antwort == 'n') 
        {
            exit = true;
            result = false;
        }

    }
    return result;
}

int main(){
    bool test = exitfrage();
    std::cout << test;
}