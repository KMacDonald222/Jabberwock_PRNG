/*
File:       jtest.cpp
Author:     Keegan MacDonald
Created:    2025.03.28
Purpose:    Implement the main entry point to the jtest program
*/

#include <jabberwock/jabberwock.h>

#include <iostream>
#include <fstream>
#include <chrono>

// Define jtest module variables

// Set of printable characters for generating seed values
std::string CHARS = "abcdefghijklmnopqrstuvwxyz`1234567890-=[]\\;',./"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ~!@#$%^&*()_+{}|:\"<>?";

/*
The main entry point of the jtest program
Returns: int - The exit code of the program
*/
int main() {
    // Seed the built-in PRNG for seed generation
    srand((unsigned int)time(0));
    // Get the number of data files to generate
    std::cout << "Output file count: ";
    std::string out_file_count_str = "";
    if (!std::getline(std::cin, out_file_count_str)) {
        std::cout << "Invalid input" << std::endl;
        return EXIT_FAILURE;
    }
    size_t out_file_count = (size_t)std::atoi(out_file_count_str.c_str());
    if (out_file_count < 1) {
        std::cout << "Invalid output file count" << std::endl;
        return EXIT_FAILURE;
    }
    // Get the size of data files to generate
    std::cout << "Output file size: ";
    std::string out_file_size_str = "";
    if (!std::getline(std::cin, out_file_size_str)) {
        std::cout << "Invalid input" << std::endl;
        return EXIT_FAILURE;
    }
    size_t out_file_size = (size_t)std::atoi(out_file_size_str.c_str());
    if (out_file_size < 1) {
        std::cout << "Invalid output file size" << std::endl;
        return EXIT_FAILURE;
    }
    std::cout << std::endl;
    // Initialize timing memory
    std::vector<size_t> gen_times;
    // Generate the output files
    for (size_t i = 0; i < out_file_count; i++) {
        // Print the output file name
        std::string out_file_name = "data/" + std::to_string(i + 1) + ".bin";
        std::cout << "Generating data file \"" << out_file_name << "\""
            << std::endl;
        // Open the output file
        std::ofstream out_file(out_file_name, std::ios::binary);
        if (!out_file.good()) {
            std::cout << "Bad output file \"" << out_file_name << "\""
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
        jabberwock prng;
        prng.seed(seed);
        bool progress[10];
        for (size_t j = 0; j < 10; j++) {
            progress[j] = false;
        }
        // Start clock for measuring generation time
        std::chrono::steady_clock::time_point start
            = std::chrono::steady_clock::now();
        // Generate output data
        std::cout << "Generating..." << std::endl;
        for (size_t j = 0; j < out_file_size; j++) {
            uint8_t out_byte = prng.get_byte();
            out_file.write((const char*)(&out_byte), 1);
            for (size_t k = 0; k < 10; k++) {
                if (((float)j / (float)out_file_size > (float)k / 10.0f)
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
        gen_times.push_back(elapsed);
        std::cout << std::endl << "Done in " << elapsed << "s" << std::endl
            << std::endl;
        // Clear the Jabberwock PRNG and close this output file
        prng.clear();
        out_file.close();
    }
    // Compute the average generation time
    size_t avg_gen_time = 0;
    for (size_t i = 0; i < gen_times.size(); i++) {
        avg_gen_time += gen_times[i];
    }
    avg_gen_time /= gen_times.size();
    std::cout << "Average generation time: " << avg_gen_time << "s"
        << std::endl;
    return EXIT_SUCCESS;
}