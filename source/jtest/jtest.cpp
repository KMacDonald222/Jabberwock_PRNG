/*
File:       jtest.cpp
Author:     Keegan MacDonald
Created:    2025.03.28
Purpose:    Implement the main entry point to the jtest program
*/

#include <jabberwock/jabberwock.h>

#include <iostream>
#include <bitset>

/*
The main entry point of the jtest program
Returns: int - The exit code of the program
*/
int main() {
    // Test the main Jabberwock PRNG class
    jabberwock jprng;
    jprng.seed("Hello World!");
    for (size_t i = 0; i < 128; i++) {
        std::cout << std::bitset<8>(jprng.get_byte());
        std::cout.flush();
    }
    std::cout << std::endl;
    jprng.clear();
    return EXIT_SUCCESS;
}