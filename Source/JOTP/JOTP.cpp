/*
File:       JOTP.cpp
Author:     Keegan MacDonald
Created:    2025.04.10
Purpose:    Implement the main entry point of the JOTP program
*/

#include <Jabberwock/Jabberwock.h>

#include <iostream>
#include <fstream>

/*
The main entry point of the JOTP program
Returns: int - The exit code of the program
*/
int main() {
    // Get the input file name
    std::cout << "Input file name: ";
    std::string in_file_name = "";
    if (!std::getline(std::cin, in_file_name)) {
        std::cout << "Invalid input" << std::endl;
        return EXIT_FAILURE;
    }
    std::ifstream in_file(in_file_name, std::ios::binary);
    if (!in_file.good()) {
        std::cout << "Invalid input file" << std::endl;
        return EXIT_FAILURE;
    }
    // Get the output file name
    std::cout << "Output file name: ";
    std::string out_file_name = "";
    if (!std::getline(std::cin, out_file_name)) {
        std::cout << "Invalid input" << std::endl;
        return EXIT_FAILURE;
    }
    std::ofstream out_file(out_file_name, std::ios::binary);
    if (!out_file.good()) {
        std::cout << "Invalid output file" << std::endl;
        in_file.close();
        return EXIT_FAILURE;
    }
    // Seed an instance of the Jabberwock PRNG
    std::cout << "Seed: ";
    std::string seed = "";
    if (!std::getline(std::cin, seed)) {
        std::cout << "Invalid input" << std::endl;
        in_file.close();
        out_file.close();
        return EXIT_FAILURE;
    }
    Jabberwock jabberwock;
    jabberwock.seed(seed);
    // Get the size of the input file
    in_file.seekg(0, std::ios::end);
    size_t in_file_size = in_file.tellg();
    in_file.seekg(0, std::ios::beg);
    in_file_size -= in_file.tellg();
    std::cout << "Converting " << in_file_size << "B" << std::endl;
    // Convert the input file and write to the output file
    for (size_t i = 0; i < in_file_size; i++) {
        uint8_t in_byte = 0x00;
        in_file.read((char*)(&in_byte), 1);
        uint8_t out_byte = in_byte ^ jabberwock.get_byte();
        out_file.write((const char*)(&out_byte), 1);
    }
    // Close files and clear memory
    in_file.close();
    out_file.close();
    jabberwock.clear();
    for (size_t i = 0; i < seed.length(); i++) {
        seed[i] = '\0';
    }
    seed.clear();
    return EXIT_SUCCESS;
}