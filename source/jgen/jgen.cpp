/*
File:       jgen.cpp
Author:     Keegan MacDonald
Created:    2025.04.04
Purpose:    Implement the main entry point of the jgen program
*/

#include <jabberwock/jabberwock.h>

#include <iostream>
#include <fstream>
#include <bitset>

// Default set of typable characters for random seed generation
std::string DEFAULT_CHARS = "abcdefghijklmnopqrstuvwxyz`1234567890-=[]\\;',./"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ~!@#$%^&*()_+{}|:\"<>?";

/*
Generate binary data using the Jabberwock PRNG
Parameter: jabberwock& jprng - The seeded instance of the Jabberwock PRNG
Parameter: size_t out_count - The number of bytes to generate
Parameter: const std::string& out_file_name - The file path to output bytes to
*/
void gen_bin(jabberwock& jprng, size_t out_count,
    const std::string& out_file_name) {
    // Open the output file if necessary
    std::ofstream out_file;
    if (!out_file_name.empty()) {
        out_file.open(out_file_name, std::ios::binary);
        if (!out_file.good()) {
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
    for (size_t i = 0; i < out_count; i++) {
        uint8_t out_byte = jprng.get_byte();
        if (!out_file_name.empty()) {
            out_file.write((const char*)(&out_byte), 1);
            for (size_t j = 0; j < 10; j++) {
                if ((float)j / 10.0f < (float)i / (float)out_count
                    && !progress[j]) {
                    std::cout << (j * 10) << "%, ";
                    std::cout.flush();
                    progress[j] = true;
                }
            }
        } else {
            std::cout << std::bitset<8>(out_byte);
            std::cout.flush();
        }
    }
    std::cout << std::endl << "Done" << std::endl;
    // Close the output file if necessary
    if (!out_file_name.empty()) {
        out_file.close();
    }
}

/*
Generate text data using the Jabberwock PRNG
Parameter: jabberwock& jprng - The seeded instance of the Jabberwock PRNG
Parameter: size_t out_count - The number of characters to generate
Parameter: const std::string& out_file_name - The file path to output characters
to
*/
void gen_text(jabberwock& jprng, size_t out_count,
    const std::string& out_file_name) {
    // Get the set of allowed characters
    std::cout << "Allowed characters (default all): ";
    std::string allowed_chars = "";
    if (!std::getline(std::cin, allowed_chars)) {
        std::cout << "Invalid input" << std::endl;
        return;
    }
    if (allowed_chars.empty()) {
        std::cout << "Using default set of all typable characters" << std::endl;
        allowed_chars = DEFAULT_CHARS;
    }
    for (size_t i = 0; i < allowed_chars.length(); i++) {
        for (size_t j = 0; j < allowed_chars.length(); j++) {
            if (allowed_chars[i] == allowed_chars[j] && i != j) {
                std::cout << "Invalid allowed character set" << std::endl;
                return;
            }
        }
    }
    // Open the output file if necessary
    std::ofstream out_file;
    if (!out_file_name.empty()) {
        out_file.open(out_file_name);
        if (!out_file.good()) {
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
    for (size_t i = 0; i < out_count; i++) {
        uint32_t selector = 0x00000000;
        for (size_t j = 0; j < 4; j++) {
            selector <<= 8;
            selector |= jprng.get_byte();
        }
        char out_char = allowed_chars[selector % allowed_chars.length()];
        if (!out_file_name.empty()) {
            out_file << out_char;
            for (size_t j = 0; j < 10; j++) {
                if ((float)j / 10.0f < (float)i / (float)out_count
                    && !progress[j]) {
                    std::cout << (j * 10) << "%, ";
                    std::cout.flush();
                    progress[j] = true;
                }
            }
        } else {
            std::cout << out_char;
            std::cout.flush();
        }
    }
    std::cout << std::endl << "Done" << std::endl;
    // Close the output file if necessary
    if (!out_file_name.empty()) {
        out_file.close();
    }
}

/*
Generate integer data using the Jabberwock PRNG
Parameter: jabberwock& jprng - The seeded instance of the Jabberwock PRNG
Parameter: size_t out_count - The number of integers to generate
Parameter: const std::string& out_file_name - The file path to output integer to
*/
void gen_ints(jabberwock& jprng, size_t out_count,
    const std::string& out_file_name) {
    // Get the minimum value
    std::cout << "Minimum: ";
    std::string minimum_str = "";
    if (!std::getline(std::cin, minimum_str)) {
        std::cout << "Invalid input" << std::endl;
        return;
    }
    int minimum = std::atoi(minimum_str.c_str());
    // Get the maximum value
    std::cout << "Maximum: ";
    std::string maximum_str = "";
    if (!std::getline(std::cin, maximum_str)) {
        std::cout << "Invalid input" << std::endl;
        return;
    }
    int maximum = std::atoi(maximum_str.c_str());
    if (maximum <= minimum) {
        std::cout << "Invalid maximum" << std::endl;
        return;
    }
    // Open the output file if necessary
    std::ofstream out_file;
    if (!out_file_name.empty()) {
        out_file.open(out_file_name);
        if (!out_file.good()) {
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
    for (size_t i = 0; i < out_count; i++) {
        uint32_t selector = 0x00000000;
        for (size_t j = 0; j < 4; j++) {
            selector <<= 8;
            selector |= jprng.get_byte();
        }
        int out_int = minimum + (selector % range);
        if (!out_file_name.empty()) {
            out_file << out_int << ", ";
            for (size_t j = 0; j < 10; j++) {
                if ((float)j / 10.0f < (float)i / (float)out_count
                    && !progress[j]) {
                    std::cout << (j * 10) << "%, ";
                    std::cout.flush();
                    progress[j] = true;
                }
            }
        } else {
            std::cout << out_int << ", ";
            std::cout.flush();
        }
    }
    std::cout << std::endl << "Done" << std::endl;
    // Close the output file if necessary
    if (!out_file_name.empty()) {
        out_file.close();
    }
}

/*
Generate float data using the Jabberwock PRNG
Parameter: jabberwock& jprng - The seeded instance of the Jabberwock PRNG
Parameter: size_t out_count - The number of floats to generate
Parameter: const std::string& out_file_name - The file path to output floats to
*/
void gen_floats(jabberwock& jprng, size_t out_count,
    const std::string& out_file_name) {
    // Get the minimum value
    std::cout << "Minimum: ";
    std::string minimum_str = "";
    if (!std::getline(std::cin, minimum_str)) {
        std::cout << "Invalid input" << std::endl;
        return;
    }
    float minimum = std::atof(minimum_str.c_str());
    // Get the maximum value
    std::cout << "Maximum: ";
    std::string maximum_str = "";
    if (!std::getline(std::cin, maximum_str)) {
        std::cout << "Invalid input" << std::endl;
        return;
    }
    float maximum = std::atof(maximum_str.c_str());
    if (maximum <= minimum) {
        std::cout << "Invalid maximum" << std::endl;
        return;
    }
    // Open the output file if necessary
    std::ofstream out_file;
    if (!out_file_name.empty()) {
        out_file.open(out_file_name);
        if (!out_file.good()) {
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
    for (size_t i = 0; i < out_count; i++) {
        uint32_t selector = 0x00000000;
        for (size_t j = 0; j < 4; j++) {
            selector <<= 8;
            selector |= jprng.get_byte();
        }
        float distance = (float)selector / (float)0xFFFFFFFF;
        float out_float = minimum + (distance * range);
        if (!out_file_name.empty()) {
            out_file << out_float << ", ";
            for (size_t j = 0; j < 10; j++) {
                if ((float)j / 10.0f < (float)i / (float)out_count
                    && !progress[j]) {
                    std::cout << (j * 10) << "%, ";
                    std::cout.flush();
                    progress[j] = true;
                }
            }
        } else {
            std::cout << out_float << ", ";
            std::cout.flush();
        }
    }
    std::cout << std::endl << "Done" << std::endl;
    // Close the output file if necessary
    if (!out_file_name.empty()) {
        out_file.close();
    }
}

/*
The main entry point to the jgen program
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
            seed += DEFAULT_CHARS[rand() % DEFAULT_CHARS.length()];
        }
        std::cout << "Using randomized seed \"" << seed << "\"" << std::endl;
    }
    // Create a Jabberwock PRNG instance
    jabberwock jprng;
    jprng.seed(seed);
    std::cout << "Seeded Jabberwock PRNG" << std::endl;
    // Get the number of output symbols to generate
    std::cout << "Output symbol count (default 1): ";
    std::string out_count_str = "";
    if (!std::getline(std::cin, out_count_str)) {
        std::cout << "Invalid input" << std::endl;
        return EXIT_FAILURE;
    }
    int out_count_int = std::atoi(out_count_str.c_str());
    if (out_count_str.empty()) {
        std::cout << "Using default 1" << std::endl;
        out_count_int = 1;
    }
    if (out_count_int <= 0) {
        std::cout << "Invalid output symbol count" << std::endl;
        return EXIT_FAILURE;
    }
    size_t out_count = (size_t)out_count_int;
    // Get the output file name to write symbols to
    std::cout << "Output file name (default console): ";
    std::string out_file_name = "";
    if (!std::getline(std::cin, out_file_name)) {
        std::cout << "Invalid input" << std::endl;
        return EXIT_FAILURE;
    }
    if (out_file_name.empty()) {
        std::cout << "Using default output to console" << std::endl;
    } else {
        std::ofstream out_file_test(out_file_name);
        if (!out_file_test.good()) {
            std::cout << "Invalid output file" << std::endl;
            return EXIT_FAILURE;
        }
        out_file_test.close();
    }
    // Get the output format mode
    std::cout << "Output format mode choices:" << std::endl << "1. Binary"
        << std::endl << "2. Text" << std::endl << "3. Integers" << std::endl
        << "4. Floats" << std::endl << "Output format mode (default 1): ";
    std::string out_fmt_mode_str = "";
    if (!std::getline(std::cin, out_fmt_mode_str)) {
        std::cout << "Invalid input" << std::endl;
        return EXIT_FAILURE;
    }
    int out_fmt_mode = std::atoi(out_fmt_mode_str.c_str());
    if (out_fmt_mode_str.empty()) {
        std::cout << "Using default binary" << std::endl;
        out_fmt_mode = 1;
    }
    if (out_fmt_mode < 1 || out_fmt_mode > 4) {
        std::cout << "Invalid output format mode" << std::endl;
        return EXIT_FAILURE;
    }
    // Switch into the appropriate mode
    switch (out_fmt_mode) {
        case 1: {
            gen_bin(jprng, out_count, out_file_name);
            break;
        }
        case 2: {
            gen_text(jprng, out_count, out_file_name);
            break;
        }
        case 3: {
            gen_ints(jprng, out_count, out_file_name);
            break;
        }
        case 4: {
            gen_floats(jprng, out_count, out_file_name);
            break;
        }
    }
    // Clear memory
    for (size_t i = 0; i < seed.length(); i++) {
        seed[i] = '\0';
    }
    seed.clear();
    jprng.clear();
    return EXIT_SUCCESS;
}