#include <vector>
#include <iostream>
#include <bits/stdc++.h>
#include <cstdint>

using namespace std;

// Overload << for vector DIESER CODE DIENT DER pRINT VON VEKTOREN, UND IST AUS DEM INTERNET KOPIERT <3
template <typename S>
ostream& operator<<(ostream& os, const vector<S>& vector) {
  
    // Printing all the elements using <<
    for (auto i : vector) 
        os << i << " ";
    return os;
}

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


//Task I
template <typename TLambda> 
std::vector<size_t> filter(std::vector<size_t> const & input, TLambda const & l) {
    std::vector<size_t> outputvector{};
    for ( size_t  t: input)
        if (l(t) == true){
            outputvector.push_back(t);
        } 
    return outputvector;
}



void task1(){
    auto iseven  = [] (auto const & elem) {return (elem %2 == 0);}; 
    auto isodd  = [] (auto const & elem) {return elem %2 == 1;}; 
    auto iszero = [](auto const & elem){return elem !=0;};

        std::vector<size_t> const inputvec{0,1,2};

        auto output = filter(inputvec, iseven);
        std::cout << "Input/Output " << inputvec <<" / " << output << "\n";  
        output = filter(inputvec, isodd);
        std::cout << "Input/Output " << inputvec <<" / " << output << "\n";  
        output = filter(inputvec, iszero);
        std::cout << "Input/Output " << inputvec <<" / " << output << "\n";  
    }

//Task II
enum class GENDER{
    FEMALE, MALE,DIVERSE,UNDETEMINED
};

std::string genderstringis (GENDER const gen)
{
    switch (gen)
    {
        case GENDER::FEMALE: return "Female";
        case GENDER::MALE:   return "MANN";
        case GENDER::DIVERSE: return "What are you, a Cop?";
    
    default: return "A SECRET FITHT";
    }
}

GENDER getgenderfromstring(std::string input){
    if (input == "MANN"  || input == "1") {return GENDER::MALE;}
    else if (input == "Female"  || input == "0") {return GENDER::FEMALE;}
    else if (input == "Divers"  || input == "2") {return GENDER::DIVERSE;}
    else {return GENDER::UNDETEMINED;}
}


struct Person{
    std::string name{};
    uint16_t age{};
    GENDER geschlecht{};

    void print(){
        std::cout << "Name: " << name << " Alter: " << age << " Agenda: " << genderstringis(geschlecht) << "\n";
    }
    std::string print(string){
        return "Name: " +name + " Alter: " + std::to_string(age) +" Agenda: " + genderstringis(geschlecht) + "\n" ;
    }

    Person & operator<(Person const & c) 
    {
         re += c.re; 
         im += c.im; 
         return *this;
    }

};

ostream& operator<<(ostream& os, const vector<Person> vector) {
  
    // Printing all the elements using <<
    for (auto i : vector) 
        os << i.print("a")<< " ";
    return os;
}

void task2(){
    Person p1 = {"Julia", 23, GENDER::FEMALE};
    p1.print();
}

//Task III
void task3(){
    std::vector<Person> personenvec{};
    std::string inname{};
    uint16_t inalter{};
    std::string ingenderstr{};
    GENDER ingender{};

    bool exit = false;
    while (exit == false){
        std::cout << "Bitte gebe die daten der Person ein [Name, Alter, Gender] ";
        std::cin >> inname >> inalter >> ingenderstr;
        ingender = getgenderfromstring(ingenderstr);
        personenvec.push_back(Person{inname,inalter,ingender});

        exit = !exitfrage();
    }

    std::cout << personenvec;
}

//Task IV
void task4(){}


//MaintaskFunktions



int main(){
    task1();
    task2();
    task3();
//    task1();


}