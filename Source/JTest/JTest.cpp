/*
File:       JTest.cpp
Author:     Keegan MacDonald
Created:    2025.03.28
Purpose:    Implement the main entry point to the JTest program
*/

#include <Jabberwock/Jabberwock.h>

#include <iostream>
#include <fstream>
#include <chrono>

// Define JTest module variables

// Set of printable characters for generating seed values
std::string CHARS = "abcdefghijklmnopqrstuvwxyz`1234567890-=[]\\;',./"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ~!@#$%^&*()_+{}|:\"<>?";

/*
The main entry point of the JTest program
Returns: int - The exit code of the program
*/
int main() {
    // Seed the built-in PRNG for seed generation
    srand((unsigned int)time(0));
    // Get the number of data files to generate
    std::cout << "Output file count: ";
    std::string outFileCountStr = "";
    if (!std::getline(std::cin, outFileCountStr)) {
        std::cout << "Invalid input" << std::endl;
        return EXIT_FAILURE;
    }
    size_t outFileCount = (size_t)std::atoi(outFileCountStr.c_str());
    if (outFileCount < 1) {
        std::cout << "Invalid output file count" << std::endl;
        return EXIT_FAILURE;
    }
    // Get the size of data files to generate
    std::cout << "Output file size: ";
    std::string outFileSizeStr = "";
    if (!std::getline(std::cin, outFileSizeStr)) {
        std::cout << "Invalid input" << std::endl;
        return EXIT_FAILURE;
    }
    size_t outFileSize = (size_t)std::atoi(outFileSizeStr.c_str());
    if (outFileSize < 1) {
        std::cout << "Invalid output file size" << std::endl;
        return EXIT_FAILURE;
    }
    std::cout << std::endl;
    // Initialize timing memory
    std::vector<size_t> genTimes;
    // Generate the output files
    for (size_t i = 0; i < outFileCount; i++) {
        // Print the output file name
        std::string outFileName = "data/" + std::to_string(i + 1) + ".bin";
        std::cout << "Generating data file \"" << outFileName << "\""
            << std::endl;
        // Open the output file
        std::ofstream outFile(outFileName, std::ios::binary);
        if (!outFile.good()) {
            std::cout << "Bad output file \"" << outFileName << "\""
                << std::endl;
            return EXIT_FAILURE;
        }
        // Generate a random seed value
        std::string seed = "";
        for (size_t i = 0; i < 16; i++) {
            seed += CHARS[rand() % CHARS.length()];
        }
        std::cout << "Using seed \"" << seed << "\"" << std::endl;
        // Seed the Jabberwock PRNG and initialize memory
        Jabberwock jabberwock;
        jabberwock.seed(seed);
        bool progress[10];
        for (size_t j = 0; j < 10; j++) {
            progress[j] = false;
        }
        // Start clock for measuring generation time
        std::chrono::steady_clock::time_point start
            = std::chrono::steady_clock::now();
        // Generate output data
        std::cout << "Generating..." << std::endl;
        for (size_t j = 0; j < outFileSize; j++) {
            uint8_t outByte = jabberwock.getByte();
            outFile.write((const char*)(&outByte), 1);
            for (size_t k = 0; k < 10; k++) {
                if (((float)j / (float)outFileSize > (float)k / 10.0f)
                    && !progress[k]) {
                    std::cout << (k * 10) << "%, ";
                    std::cout.flush();
                    progress[k] = true;
                }
            }
        }
        // Compute generation time
        std::chrono::steady_clock::time_point end
            = std::chrono::steady_clock::now();
        size_t elapsed = std::chrono::duration_cast<std::chrono::seconds>
            (end - start).count();
        genTimes.push_back(elapsed);
        std::cout << std::endl << "Done in " << elapsed << "s" << std::endl
            << std::endl;
        // Clear the Jabberwock PRNG and close this output file
        jabberwock.clear();
        outFile.close();
    }
    // Compute the average generation time
    size_t avgGenTime = 0;
    for (size_t i = 0; i < genTimes.size(); i++) {
        avgGenTime += genTimes[i];
    }
    avgGenTime /= genTimes.size();
    std::cout << "Average generation time: " << avgGenTime << "s"
        << std::endl;
    return EXIT_SUCCESS;
}