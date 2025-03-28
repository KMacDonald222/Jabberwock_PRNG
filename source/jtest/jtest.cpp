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
    // Get the hexadecimal and binary digests of a string
    std::string input = "Hello World!";
    std::string hex_digest = SHA_hex(input);
    std::vector<bool> bin_digest = SHA_bin(input);
    // Print results
    std::cout << "Input string: \"" << input << "\"" << std::endl;
    std::cout << "Hexadecimal digest: \"" << hex_digest << "\"" << std::endl;
    std::cout << "Binary digest: ";
    for (size_t i = 0; i < bin_digest.size(); i++) {
        std::cout << (int)bin_digest[i];
    }
    std::cout << std::endl;
    return EXIT_SUCCESS;
}