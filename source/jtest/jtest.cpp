/*
File:       jtest.cpp
Author:     Keegan MacDonald
Created:    2025.03.28
Purpose:    Implement the main entry point to the jtest program
*/

#include <jabberwock/utilities.h>

#include <iostream>

/*
The main entry point of the jtest program
Returns: int - The exit code of the program
*/
int main() {
    // Permute a string
    std::string input = "Hello World!";
    std::string permuted = permute_string(input);
    // Print results
    std::cout << "permute_string(\"" << input << "\") = \"" << permuted << "\""
        << std::endl;
    return EXIT_SUCCESS;
}