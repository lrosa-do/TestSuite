#include <iostream>
#include "TestSuite.hpp"



int testFunction() {
    return 42;
}

float floatTestFunction() {
    return 3.14f;
}

bool boolTestFunction() {
    return true;
}

void leftTimeFunction() 
{

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void rightTimeFunction() 
{

    std::this_thread::sleep_for(std::chrono::milliseconds(50));
}


int main()
{

   TestSuite suite;

    // Adicionando testes de exemplo
    suite.addTest("Integer Test", testFunction, 42);
    suite.addTest("Float Test", floatTestFunction, 3.14f);
    suite.addTest("Boolean Test", boolTestFunction, true);
    suite.addTest("Time Test", leftTimeFunction, rightTimeFunction);


    suite.runTestsAsync();


    return 0;

}