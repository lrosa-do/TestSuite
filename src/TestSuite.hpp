#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <functional>
#include <thread>
#include <cstring>

#define COLOR_RED "\033[31m"
#define COLOR_GREEN "\033[32m"
#define COLOR_RESET "\033[0m"
#define COLOR_YELLOW "\033[33m"






const char* happyFaceEmoji = u8"\U0001F603"; // 😃
const char* badFaceEmoji = u8"\U0001F621"; // 😡
const char* loserFaceEmoji = u8"\U0001F62D"; // 😭
const char* winEmoji = u8"\U0001F3C6"; // 🏆 (trophy)
const char* loserEmoji = u8"\U0001F44E"; // 👎 (thumbs down)
const char* pooEmoji = u8"\U0001F4A9"; // 💩 (pile of poo)
const char* rocketEmoji = u8"\U0001F680"; // 🚀 (rocket
const char* negativeCross = u8"\U0000274C"; // ❌ (cross mark)
const char* checkMark = u8"\U00002705"; // ✅ (check mark)






class TestSuite 
{
public:
    TestSuite() = default;
    ~TestSuite() = default;

    void addTest(std::string name, std::function<int()> test, int expected)
    {
        itests.push_back(std::make_tuple(name, test, expected));
    }

    void addTest(std::string name, std::function<float()> test, float expected)
    {
        ftests.push_back(std::make_tuple(name, test, expected));
    }

    void addTest(std::string name, std::function<bool()> test, bool expected)
    {
        btests.push_back(std::make_tuple(name, test, expected));
    }

    void addTest(std::string name, std::function<void()> left, std::function<void()> right)
    {
        timetests.push_back(std::make_tuple(name, left, right));
    }

    void addTest(std::string name, std::function<char*()> test, char* expected)
    {
        stests.push_back(std::make_tuple(name, test, expected));
    }


    void addSpeedTest(std::string name, std::function<void()> test)
    {
        speedTests.push_back(std::make_tuple(name, test));
    }


    void runTests();
    void runTestsAsync();

    void runSpeedTests();
    void runSpeedTestsAsync();

     

    
    



private:
    std::vector<std::tuple<std::string, std::function<int()>, int>> itests;
    std::vector<std::tuple<std::string, std::function<float()>, float>> ftests;
    std::vector<std::tuple<std::string, std::function<bool()>, bool>> btests;
    std::vector<std::tuple<std::string, std::function<char*()>, char*>> stests;
    
    std::vector<std::tuple<std::string, std::function<void()>,std::function<void()>>> timetests;

    std::vector<std::tuple<std::string, std::function<void()>>> speedTests;
    

    std::string passMessage ;
    std::string failMessage;
    std::string separadorMessage = " ";
    std::string spaces = "            ";
    std::string separador = "---------------------";

    int total{0} ;
    double progress{0};
    double testRun{0};
    int countPass{0};

    std::thread testThread;

    void RunIntTests();
    void RunFloatTests();
    void RunBoolTests();
    void RunTimeTests();
    void RunStringTests();


};

void TestSuite::RunIntTests()
{
    for (auto& test : itests)
    {
        std::string name = std::get<0>(test);
        std::function<int()> test_func = std::get<1>(test);
        int expected = std::get<2>(test);

        int int_result = test_func();
        testRun++;
        progress = (testRun / total) * 100;
        std::cout << "** RUN:  " << name << " progress (" << progress<<"%)   " << separador;
        if (int_result == expected)
        {
            countPass++;
            std::cout <<spaces<< COLOR_GREEN << passMessage<< " Expected ["<<expected<<"] got ["<<int_result<<"]" << COLOR_RESET << std::endl;
        }
        else
        {
            std::cout <<spaces<< COLOR_RED <<  failMessage << " Expected ["<<expected<<"] got ["<<int_result<<"]" << COLOR_RESET << std::endl;
        }
       
        
    }
}


void TestSuite::RunStringTests()
{
    for (auto& test : stests)
    {
        std::string name = std::get<0>(test);
        std::function<char*()> test_func = std::get<1>(test);
        char* expected = std::get<2>(test);

        char* string_result = test_func();
        testRun++;
        progress = (testRun / total) * 100;
        std::cout << "** RUN:  " << name << " progress (" << progress<<"%)   " << separador;
        if (std::strcmp(string_result, expected) == 0)
        {
            countPass++;
            std::cout <<spaces<< COLOR_GREEN << passMessage<< " Expected ["<<expected<<"] got ["<<string_result<<"]" << COLOR_RESET << std::endl;
        }
        else
        {
            std::cout <<spaces<< COLOR_RED <<  failMessage << " Expected ["<<expected<<"] got ["<<string_result<<"]" << COLOR_RESET << std::endl;
        }
               
    }
}

void TestSuite::RunFloatTests()
{
    for (auto& test : ftests)
    {
        std::string name = std::get<0>(test);
        std::function<float()> test_func = std::get<1>(test);
        float expected = std::get<2>(test);

        float float_result = test_func();
         testRun++;
       
        progress = (testRun / total) * 100;
          std::cout << "** RUN:  " << name << " progress (" << progress<<"%)   " << separador;
        if (float_result == expected)
        {
            countPass++;
            std::cout <<spaces<< COLOR_GREEN << passMessage<< " Expected ["<<expected<<"] got ["<<float_result<<"]" << COLOR_RESET << std::endl;
        }
        else
        {
            std::cout <<spaces<< COLOR_RED <<  failMessage << " Expected ["<<expected<<"] got ["<<float_result<<"]" << COLOR_RESET << std::endl;
        }
   
    }
}


void TestSuite::RunBoolTests()
{
    for (auto& test : btests)
    {
        std::string name = std::get<0>(test);
        std::function<bool()> test_func = std::get<1>(test);
        bool expected = std::get<2>(test);
        bool bool_result = test_func();
         testRun++;

         std::string strResult = bool_result ? "TRUE" : "FALSE";
       
        progress = (testRun / total) * 100;
          std::cout << "** RUN:  " << name << "  progress (" << progress<<"%)   " << separador;
        if (bool_result == expected)
        {
            countPass++;
            std::cout <<spaces<< COLOR_GREEN << passMessage<< " Expected ["<<expected<<"] got ["<<strResult<<"]" << COLOR_RESET << std::endl;
        }
        else
        {
            std::cout <<spaces<< COLOR_RED <<  failMessage << " Expected ["<<expected<<"] got ["<<strResult<<"]" << COLOR_RESET << std::endl;
        }
       
    }
}


void TestSuite::RunTimeTests()
{
    for (auto& test : timetests)
    {
        std::string name = std::get<0>(test);
        std::function<void()> left  = std::get<1>(test);
        std::function<void()> right = std::get<2>(test);

     
        testRun++;
        progress = (testRun / total) * 100;
        std::cout << "** RUN:  " << name << " progress (" << progress<<"%)   " << separador;

        auto start = std::chrono::high_resolution_clock::now();
        left();
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> left_time = end - start;
        double left_miliseconds = std::chrono::duration<double, std::milli>(end - start).count();
       // double seconds = std::chrono::duration<double>(end - start).count();
      //  std::cout << COLOR_YELLOW<<"\nLeft  Time taken: " << seconds << " seconds "<< left_miliseconds << " miliseconds "<<COLOR_RESET << std::endl;

        start = std::chrono::high_resolution_clock::now();
        right();
        end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> right_time = end - start;
        double  right_miliseconds = std::chrono::duration<double, std::milli>(end - start).count();
       // seconds = std::chrono::duration<double>(end - start).count();
       // std::cout << COLOR_YELLOW<<"\nRight Time taken: " << seconds << " seconds "<< right_miliseconds << " miliseconds "<<COLOR_RESET << std::endl;



        double diff = left_time.count() - right_time.count();
        double diff_miliseconds = left_miliseconds - right_miliseconds;

        if (std::abs(diff) < 0.001 && std::abs(diff_miliseconds) < 1) 
        {
            countPass++;
            std::cout << spaces << COLOR_YELLOW << "It's a tie! "<<diff << " seconds  " << happyFaceEmoji<< COLOR_RESET << std::endl;
        }
        else if (diff < 0)
        {
            countPass++;
            std::cout <<spaces<< COLOR_GREEN<<passMessage  << " is faster by " << diff << " seconds  " <<   diff_miliseconds<< " ms"  << COLOR_RESET << std::endl;
        }
        else
        {
            std::cout <<spaces<< COLOR_RED << failMessage << " is slower by " << diff << " seconds  " <<   diff_miliseconds<< " ms"  <<loserFaceEmoji<< COLOR_RESET << std::endl;
        }

     

    }
}

void TestSuite::runTestsAsync()
{
    testThread = std::thread(&TestSuite::runTests, this);
    testThread.join();
}


void TestSuite::runTests()
{


   passMessage = "[OK] " + std::string(checkMark);
   failMessage = "[KO] " + std::string(negativeCross);

    total = itests.size() + ftests.size() + btests.size() + timetests.size();
    progress = 0;
    testRun = 0;
    std::cout <<"\n       "<< rocketEmoji<<"      ------  Running " << total << " tests ------     "<<rocketEmoji << std::endl;




    RunIntTests();
    RunFloatTests();
    RunBoolTests();
    RunStringTests();
    RunTimeTests();

    std::cout<< COLOR_YELLOW << "\n        ***  All tests completed ***"  COLOR_RESET << std::endl;

    if (countPass == total)
    {
        std::cout << COLOR_GREEN <<winEmoji<< "           All tests passed :)          " <<winEmoji<< COLOR_RESET << std::endl;
    } else if (countPass == 0)
    {
        std::cout <<"    "<< COLOR_RED <<pooEmoji<<loserEmoji<< "      All tests failed       "    <<loserEmoji<< pooEmoji<<COLOR_RESET << std::endl;
    }
    else
    {
        std::cout << COLOR_RED <<loserEmoji<< "    Some tests failed "<<countPass<< " passed and  "<< (total-countPass )<< " fail. "    <<loserEmoji<< COLOR_RESET << std::endl;
        
    }

  std::cout << "\n------ ------ ------ ------ -------- ------\n" << std::endl;
}

void TestSuite::runSpeedTests()
{

    total = speedTests.size();
    progress = 0;
    testRun = 0;
    std::cout <<"\n       "<< rocketEmoji<<"      ------  Running " << total << " tests ------     "<<rocketEmoji << std::endl;

    for (auto& test : speedTests)
    {
        std::string name = std::get<0>(test);
        std::function<void()> speedTest = std::get<1>(test);
        testRun++;
        progress = (testRun / total) * 100;
        std::cout << "** RUN:  " << name << " progress (" << progress<<"%)   " << separador;
        auto start = std::chrono::high_resolution_clock::now();
        speedTest();
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> speed_time = end - start;
        double miliseconds = std::chrono::duration<double, std::milli>(end - start).count();
        double seconds = std::chrono::duration<double>(end - start).count();
        std::cout << COLOR_YELLOW<<"Time taken: " << seconds << " seconds "<< miliseconds << " miliseconds "<<COLOR_RESET << std::endl;
    }

    std::cout<< COLOR_YELLOW << "\n        ***  All tests completed ***"  COLOR_RESET << std::endl;



}
void TestSuite::runSpeedTestsAsync()
{

    testThread = std::thread(&TestSuite::runSpeedTests, this);
    testThread.join();
    
}
