/*
File:       JGen.cpp
Author:     Keegan MacDonald
Created:    2025.04.04
Purpose:    Implement the main entry point of the JGen program
*/

#include <Jabberwock/Jabberwock.h>

#include <iostream>
#include <fstream>
#include <bitset>

// Default set of typable characters for random seed generation
std::string DEFAULTCHARS = "abcdefghijklmnopqrstuvwxyz`1234567890-=[]\\;',./"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ~!@#$%^&*()_+{}|:\"<>?";

/*
Generate binary data using the Jabberwock PRNG
Parameter: Jabberwock& jabberwock - The seeded instance of the Jabberwock PRNG
Parameter: size_t outCount - The number of bytes to generate
Parameter: const std::string& outFileName - The file path to output bytes to
*/
void GenBin(Jabberwock& jabberwock, size_t outCount,
    const std::string& outFileName) {
    // Open the output file if necessary
    std::ofstream outFile;
    if (!outFileName.empty()) {
        outFile.open(outFileName, std::ios::binary);
        if (!outFile.good()) {
            std::cout << "Invalid output file" << std::endl;
            return;
        }
    }
    // Initialize memory
    bool progress[10];
    for (size_t i = 0; i < 10; i++) {
        progress[i] = false;
    }
    // Generate bytes
    std::cout << "Generating" << std::endl;
    for (size_t i = 0; i < outCount; i++) {
        uint8_t outByte = jabberwock.getByte();
        if (!outFileName.empty()) {
            outFile.write((const char*)(&outByte), 1);
            for (size_t j = 0; j < 10; j++) {
                if ((float)j / 10.0f < (float)i / (float)outCount
                    && !progress[j]) {
                    std::cout << (j * 10) << "%, ";
                    std::cout.flush();
                    progress[j] = true;
                }
            }
        } else {
            std::cout << std::bitset<8>(outByte);
            std::cout.flush();
        }
    }
    std::cout << std::endl << "Done" << std::endl;
    // Close the output file if necessary
    if (!outFileName.empty()) {
        outFile.close();
    }
}

/*
Generate text data using the Jabberwock PRNG
Parameter: Jabberwock& jabberwock - The seeded instance of the Jabberwock PRNG
Parameter: size_t outCount - The number of characters to generate
Parameter: const std::string& outFileName - The file path to output characters
to
*/
void GenText(Jabberwock& jabberwock, size_t outCount,
    const std::string& outFileName) {
    // Get the set of allowed characters
    std::cout << "Allowed characters (default all): ";
    std::string allowedChars = "";
    if (!std::getline(std::cin, allowedChars)) {
        std::cout << "Invalid input" << std::endl;
        return;
    }
    if (allowedChars.empty()) {
        std::cout << "Using default set of all typable characters" << std::endl;
        allowedChars = DEFAULTCHARS;
    }
    for (size_t i = 0; i < allowedChars.length(); i++) {
        for (size_t j = 0; j < allowedChars.length(); j++) {
            if (allowedChars[i] == allowedChars[j] && i != j) {
                std::cout << "Invalid allowed character set" << std::endl;
                return;
            }
        }
    }
    // Open the output file if necessary
    std::ofstream outFile;
    if (!outFileName.empty()) {
        outFile.open(outFileName);
        if (!outFile.good()) {
            std::cout << "Invalid output file" << std::endl;
            return;
        }
    }
    // Initialize memory
    bool progress[10];
    for (size_t i = 0; i < 10; i++) {
        progress[i] = false;
    }
    // Generate text characters
    std::cout << "Generating" << std::endl;
    for (size_t i = 0; i < outCount; i++) {
        uint32_t selector = 0x00000000;
        for (size_t j = 0; j < 4; j++) {
            selector <<= 8;
            selector |= jabberwock.getByte();
        }
        char outChar = allowedChars[selector % allowedChars.length()];
        if (!outFileName.empty()) {
            outFile << outChar;
            for (size_t j = 0; j < 10; j++) {
                if ((float)j / 10.0f < (float)i / (float)outCount
                    && !progress[j]) {
                    std::cout << (j * 10) << "%, ";
                    std::cout.flush();
                    progress[j] = true;
                }
            }
        } else {
            std::cout << outChar;
            std::cout.flush();
        }
    }
    std::cout << std::endl << "Done" << std::endl;
    // Close the output file if necessary
    if (!outFileName.empty()) {
        outFile.close();
    }
}

/*
Generate integer data using the Jabberwock PRNG
Parameter: Jabberwock& jabberwock - The seeded instance of the Jabberwock PRNG
Parameter: size_t outCount - The number of integers to generate
Parameter: const std::string& outFileName - The file path to output integer to
*/
void GenInts(Jabberwock& jabberwock, size_t outCount,
    const std::string& outFileName) {
    // Get the minimum value
    std::cout << "Minimum: ";
    std::string minimumStr = "";
    if (!std::getline(std::cin, minimumStr)) {
        std::cout << "Invalid input" << std::endl;
        return;
    }
    int minimum = std::atoi(minimumStr.c_str());
    // Get the maximum value
    std::cout << "Maximum: ";
    std::string maximumStr = "";
    if (!std::getline(std::cin, maximumStr)) {
        std::cout << "Invalid input" << std::endl;
        return;
    }
    int maximum = std::atoi(maximumStr.c_str());
    if (maximum <= minimum) {
        std::cout << "Invalid maximum" << std::endl;
        return;
    }
    // Open the output file if necessary
    std::ofstream outFile;
    if (!outFileName.empty()) {
        outFile.open(outFileName);
        if (!outFile.good()) {
            std::cout << "Invalid output file" << std::endl;
            return;
        }
    }
    // Initialize memory
    bool progress[10];
    for (size_t i = 0; i < 10; i++) {
        progress[i] = false;
    }
    int range = maximum - minimum + 1;
    // Generate the appropriate number of integers
    std::cout << "Generating" << std::endl;
    for (size_t i = 0; i < outCount; i++) {
        uint32_t selector = 0x00000000;
        for (size_t j = 0; j < 4; j++) {
            selector <<= 8;
            selector |= jabberwock.getByte();
        }
        int outInt = minimum + (selector % range);
        if (!outFileName.empty()) {
            outFile << outInt << ", ";
            for (size_t j = 0; j < 10; j++) {
                if ((float)j / 10.0f < (float)i / (float)outCount
                    && !progress[j]) {
                    std::cout << (j * 10) << "%, ";
                    std::cout.flush();
                    progress[j] = true;
                }
            }
        } else {
            std::cout << outInt << ", ";
            std::cout.flush();
        }
    }
    std::cout << std::endl << "Done" << std::endl;
    // Close the output file if necessary
    if (!outFileName.empty()) {
        outFile.close();
    }
}

/*
Generate float data using the Jabberwock PRNG
Parameter: Jabberwock& jabberwock - The seeded instance of the Jabberwock PRNG
Parameter: size_t outCount - The number of floats to generate
Parameter: const std::string& outFileName - The file path to output floats to
*/
void GenFloats(Jabberwock& jabberwock, size_t outCount,
    const std::string& outFileName) {
    // Get the minimum value
    std::cout << "Minimum: ";
    std::string minimumStr = "";
    if (!std::getline(std::cin, minimumStr)) {
        std::cout << "Invalid input" << std::endl;
        return;
    }
    float minimum = std::atof(minimumStr.c_str());
    // Get the maximum value
    std::cout << "Maximum: ";
    std::string maximumStr = "";
    if (!std::getline(std::cin, maximumStr)) {
        std::cout << "Invalid input" << std::endl;
        return;
    }
    float maximum = std::atof(maximumStr.c_str());
    if (maximum <= minimum) {
        std::cout << "Invalid maximum" << std::endl;
        return;
    }
    // Open the output file if necessary
    std::ofstream outFile;
    if (!outFileName.empty()) {
        outFile.open(outFileName);
        if (!outFile.good()) {
            std::cout << "Invalid output file" << std::endl;
            return;
        }
    }
    // Initialize memory
    bool progress[10];
    for (size_t i = 0; i < 10; i++) {
        progress[i] = false;
    }
    float range = maximum - minimum + 1;
    // Generate the appropriate number of floats
    std::cout << "Generating" << std::endl;
    for (size_t i = 0; i < outCount; i++) {
        uint32_t selector = 0x00000000;
        for (size_t j = 0; j < 4; j++) {
            selector <<= 8;
            selector |= jabberwock.getByte();
        }
        float distance = (float)selector / (float)0xFFFFFFFF;
        float outFloat = minimum + (distance * range);
        if (!outFileName.empty()) {
            outFile << outFloat << ", ";
            for (size_t j = 0; j < 10; j++) {
                if ((float)j / 10.0f < (float)i / (float)outCount
                    && !progress[j]) {
                    std::cout << (j * 10) << "%, ";
                    std::cout.flush();
                    progress[j] = true;
                }
            }
        } else {
            std::cout << outFloat << ", ";
            std::cout.flush();
        }
    }
    std::cout << std::endl << "Done" << std::endl;
    // Close the output file if necessary
    if (!outFileName.empty()) {
        outFile.close();
    }
}

/*
The main entry point to the JGen program
Returns: int - The exit code of the program
*/
int main() {
    // Get the seed value for the Jabberwock PRNG
    srand((unsigned int)time(0));
    std::cout << "Seed (default randomized): ";
    std::string seed = "";
    if (!std::getline(std::cin, seed)) {
        std::cout << "Invalid input" << std::endl;
        return EXIT_FAILURE;
    }
    if (seed.empty()) {
        for (size_t i = 0; i < 16; i++) {
            seed += DEFAULTCHARS[rand() % DEFAULTCHARS.length()];
        }
        std::cout << "Using randomized seed \"" << seed << "\"" << std::endl;
    }
    // Create a Jabberwock PRNG instance
    Jabberwock jabberwock;
    jabberwock.seed(seed);
    std::cout << "Seeded Jabberwock PRNG" << std::endl;
    // Get the number of output symbols to generate
    std::cout << "Output symbol count (default 1): ";
    std::string outCountStr = "";
    if (!std::getline(std::cin, outCountStr)) {
        std::cout << "Invalid input" << std::endl;
        return EXIT_FAILURE;
    }
    int outCountInt = std::atoi(outCountStr.c_str());
    if (outCountStr.empty()) {
        std::cout << "Using default 1" << std::endl;
        outCountInt = 1;
    }
    if (outCountInt <= 0) {
        std::cout << "Invalid output symbol count" << std::endl;
        return EXIT_FAILURE;
    }
    size_t outCount = (size_t)outCountInt;
    // Get the output file name to write symbols to
    std::cout << "Output file name (default console): ";
    std::string outFileName = "";
    if (!std::getline(std::cin, outFileName)) {
        std::cout << "Invalid input" << std::endl;
        return EXIT_FAILURE;
    }
    if (outFileName.empty()) {
        std::cout << "Using default output to console" << std::endl;
    } else {
        std::ofstream outFileTest(outFileName);
        if (!outFileTest.good()) {
            std::cout << "Invalid output file" << std::endl;
            return EXIT_FAILURE;
        }
        outFileTest.close();
    }
    // Get the output format mode
    std::cout << "Output format mode choices:" << std::endl << "1. Binary"
        << std::endl << "2. Text" << std::endl << "3. Integers" << std::endl
        << "4. Floats" << std::endl << "Output format mode (default 1): ";
    std::string outFmtModeStr = "";
    if (!std::getline(std::cin, outFmtModeStr)) {
        std::cout << "Invalid input" << std::endl;
        return EXIT_FAILURE;
    }
    int outFmtMode = std::atoi(outFmtModeStr.c_str());
    if (outFmtModeStr.empty()) {
        std::cout << "Using default binary" << std::endl;
        outFmtMode = 1;
    }
    if (outFmtMode < 1 || outFmtMode > 4) {
        std::cout << "Invalid output format mode" << std::endl;
        return EXIT_FAILURE;
    }
    // Switch into the appropriate mode
    switch (outFmtMode) {
        case 1: {
            GenBin(jabberwock, outCount, outFileName);
            break;
        }
        case 2: {
            GenText(jabberwock, outCount, outFileName);
            break;
        }
        case 3: {
            GenInts(jabberwock, outCount, outFileName);
            break;
        }
        case 4: {
            GenFloats(jabberwock, outCount, outFileName);
            break;
        }
    }
    // Clear memory
    for (size_t i = 0; i < seed.length(); i++) {
        seed[i] = '\0';
    }
    seed.clear();
    jabberwock.clear();
    return EXIT_SUCCESS;
}