#include <vector> 
#include <iostream>
#include <cstdint>
#include <string>

// funktionen von Task I
bool inberlin( int32_t const PLZ)
    {
    // laut https://www.berlinstadtservice.de/xinh/Postleitzahlen_Berlin.html Berlin hat die Postleitzahlen 10115 bis 14199: Imlementierung mit set/map ist auch möglich
        if (10115 < PLZ && PLZ < 14199){
            return true;
        }   
        else 
        {
            return false;
        }
    }

void updatesmallest(const int32_t neuenum, int32_t & smalestPLZ, const std::string & neuername, std::string & altername)
    {
        if (neuenum < smalestPLZ)
        {
            altername = neuername;
            smalestPLZ = neuenum;
        } 
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

// Funktionennvon task II

int foo(){
    int foo = 4;
    return foo;
}

std::string & clash (){
    std::string A{"A"};
    std::string & ref = A;
    return ref; 
}

const std::string & fi (std::string string){
    std::string & ref = string;
    return ref; 
}

const std::string & fum (const std::string & string){
    const std::string & ref = string;
    return ref; 
}

// double & square() 
//{ 
//double d{5.3}; 
//return d; // 💣 
//} 

template <typename T> 
void print(T const) 
{ 
	std::cout << "Integer!\n"; 
} 
void print(float const) 
{ 
std::cout << "Floating point!\n";
} 

// Funktionen von Task III

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

float fibfloat()
{
    float n1{};
    float n2{};
    float helper{};
    const short c = 42;
    short counter = 0;

    std::cout << "Gebe mir 2 Zahlen n1, n2 um die 42 fibunacci like Nummer zu erhalten. Die erste zahl sollte gößer als die 2. sein. Schema: n1 n2 \n";
    std::cin >> n1 >> n2;

    while (counter < c)
    {
        helper = n1;
        n1 = n1+n2;
        n2 = helper;
        counter ++;
    } 

    return n1;
}

constexpr long long canonfib(int64_t c)
{
    long long n1 = 1;
    long long n2 = 0;
    c = c -2;
    long long helper{}; 
    int64_t counter = 0;

    while (counter < c)
    {
        helper = n1;
        n1 = n1+n2;
        n2 = helper;
        counter ++;
    } 

    return n1;
     
}

// beginn der Aufgaben
void task1 (){
    bool weiterepersonen{};
    int32_t PLZ{};  
    bool result{};
    int32_t gesamt{};  
    double lebendinberin{};  
    std::string Name{};
    std::string nameofsmalles{};
    int32_t SmallestPLZ{};

    // Erster loop muss vorgeschoben werden
    std::cout << "Gebe bitte einen Namen und eine PLZ ein: ";
    std::cin >> Name >> PLZ;

    //standard vergleichwerte
    nameofsmalles = Name;
    SmallestPLZ = PLZ;

    //Funktion erster Loop
    result = inberlin(PLZ);
    if (result == true)
    {
        std::cout << Name <<" Lebt in Berlin\n";
        lebendinberin ++;
        gesamt ++;
    } 
    else {
        std::cout << Name << " lebt ausserhalb von Berlin\n";
        gesamt ++;
    }
    weiterepersonen = exitfrage();

    while (weiterepersonen == true)
    {
        std::cout << "Gebe bitte einen Namen und eine PLZ ein: ";
        std::cin >> Name >> PLZ;
        
        updatesmallest(PLZ,SmallestPLZ, Name, nameofsmalles);

        result = inberlin(PLZ);
        if (result == true)
        {
            std::cout << Name <<" Lebt in Berlin\n";
            lebendinberin ++;
            gesamt ++;
        } 
        else {
            std::cout << Name << " lebt ausserhalb von Berlin\n";
            gesamt ++;
        }
        weiterepersonen = exitfrage();
    }
    
    double percberlinlebend = (lebendinberin/gesamt) *100;
    // Print Statistik
    std::cout << "Overall live " << percberlinlebend << "Prozent der Personen in Berlin \n" << "Die kleinste PLZ hat " << nameofsmalles << " mit der " << SmallestPLZ << "\n";


}

void task2(){
    //const int fan = foo();
    //fan =2;
    //std::cout << fan;
    std::string & flash = clash();

    std::cout << flash << "\n";
    std::string A{"A"};
    std::string & ref = A;
    std::cout << ref << "\n";

    std::string B{"B"};
    std::string C{"C"};

    //const std::string & b = fi(B);
    //std::cout << b << "\n";

    const std::string & c = fum(C);
    std::cout << c << "\n";

    //double & d = square(); // 💥
    //std::cout << d << "\n";
    float dreipdrei = 3.3; 
    //print(3.3);
    print(dreipdrei);
    

}

void task3()
{
    const auto result = Fibonaccilike(3.6,2.4,2);
    //result = 2;
    std::cout << "result: " << result << "\n";
    const float floatres = fibfloat();
    std::cout << "fibfloatresult: " << floatres << "\n";

    constexpr long long canonthnum = 5;
    constexpr long long canonres = canonfib(canonthnum);
    std::cout << "canonresult: " << canonres << "\n";

}
int main (){
    //task1();
    //task2();
    task3();
}