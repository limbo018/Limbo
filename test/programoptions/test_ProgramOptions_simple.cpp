/**
 * @file   test_ProgramOptions_simple.cpp
 * @author Yibo Lin
 * @date   Wed Jul 15 21:44:22 2015
 */

#include <iostream>
#include <string>
#include <vector>
#include <limbo/programoptions/ProgramOptions.h>

/**
 * @brief 
 * @param argc 
 * @param argv
 * @return
 */
int main(int argc, char** argv)
{
    bool help = false;
    int i = 0;
    double fp = 0;
    std::vector<int> vInteger;

    typedef limbo::programoptions::ProgramOptions po_type;
    using limbo::programoptions::Value;
    po_type desc ("My options");
    // add user-defined options
    desc.add_option(Value<bool>("-help", &help, "print help message").toggle(true).default_value(false).toggle_value(true).help(true)) // specify help option 
        .add_option(Value<int>("-i", &i, "an integer").default_value(100, "1.0.0"))
        .add_option(Value<double>("-f", &fp, "a floating point").required(true)) // the floating point option is a required option, so user must provide it 
        .add_option(Value<std::vector<int> >("-vi", &vInteger, "vector of integers"))
        ;

    try 
    {
        bool flag = desc.parse(argc, argv);
        if (flag) 
            std::cout << "parsing succeeded\n";
    }
    catch (std::exception& e)
    {
        std::cout << "parsing failed\n";
        std::cout << e.what() << "\n";
    }

    // print help message 
    if (help)
    {
        std::cout << desc << "\n";
        return 1; 
    }

    std::cout << "help = " << ((help)? "true" : "false") << std::endl;
    std::cout << "i = " << i << std::endl;
    std::cout << "fp = " << fp << std::endl;
    std::cout << "vInteger = ";
    for (std::vector<int>::const_iterator it = vInteger.begin(); it != vInteger.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    return 0;
}
