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
    std::string inFileName = "";
    if (!std::getline(std::cin, inFileName)) {
        std::cout << "Invalid input" << std::endl;
        return EXIT_FAILURE;
    }
    std::ifstream inFile(inFileName, std::ios::binary);
    if (!inFile.good()) {
        std::cout << "Invalid input file" << std::endl;
        return EXIT_FAILURE;
    }
    // Get the output file name
    std::cout << "Output file name: ";
    std::string outFileName = "";
    if (!std::getline(std::cin, outFileName)) {
        std::cout << "Invalid input" << std::endl;
        return EXIT_FAILURE;
    }
    std::ofstream outFile(outFileName, std::ios::binary);
    if (!outFile.good()) {
        std::cout << "Invalid output file" << std::endl;
        inFile.close();
        return EXIT_FAILURE;
    }
    // Seed an instance of the Jabberwock PRNG
    std::cout << "Seed: ";
    std::string seed = "";
    if (!std::getline(std::cin, seed)) {
        std::cout << "Invalid input" << std::endl;
        inFile.close();
        outFile.close();
        return EXIT_FAILURE;
    }
    Jabberwock jabberwock;
    jabberwock.seed(seed);
    // Get the size of the input file
    inFile.seekg(0, std::ios::end);
    size_t inFileSize = inFile.tellg();
    inFile.seekg(0, std::ios::beg);
    inFileSize -= inFile.tellg();
    std::cout << "Converting " << inFileSize << "B" << std::endl;
    // Convert the input file and write to the output file
    for (size_t i = 0; i < inFileSize; i++) {
        uint8_t inByte = 0x00;
        inFile.read((char*)(&inByte), 1);
        uint8_t outByte = inByte ^ jabberwock.getByte();
        outFile.write((const char*)(&outByte), 1);
    }
    // Close files and clear memory
    inFile.close();
    outFile.close();
    jabberwock.clear();
    for (size_t i = 0; i < seed.length(); i++) {
        seed[i] = '\0';
    }
    seed.clear();
    return EXIT_SUCCESS;
}