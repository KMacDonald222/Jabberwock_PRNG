/*
File:       jtest.cpp
Author:     Keegan MacDonald
Created:    2025.03.28
Purpose:    Implement the main entry point to the jtest program
*/

#include <jabberwock/nodes.h>

#include <iostream>
#include <bitset>

/*
The main entry point of the jtest program
Returns: int - The exit code of the program
*/
int main() {
    // Test the LFSR node type
    LFSR_node node;
    node.seed("Hello World!", 0);
    for (size_t i = 0; i < 4; i++) {
        std::cout << std::bitset<8>(node.get_byte()) << std::endl;
    }
    node.clear();
    return EXIT_SUCCESS;
}