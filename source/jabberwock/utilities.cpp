/*
File:       utilities.cpp
Author:     Keegan MacDonald
Created:    2025.03.28
Purpose:    Implement utility module functions found in utilities.h
*/

#include "utilities.h"

#include <SHA/SHA512.h>

// Define utilities module variables

// Set of 16 of the 24 permutation of 4 objects
std::vector<std::vector<size_t>> PERMUTATIONS_4 = {
    { 1, 2, 4, 3, },
    { 1, 3, 2, 4, },
    { 1, 3, 4, 2, },
    { 1, 4, 3, 2, },
    { 2, 1, 3, 4, },
    { 2, 3, 1, 4, },
    { 2, 3, 4, 1, },
    { 2, 4, 1, 3, },
    { 3, 1, 4, 2, },
    { 3, 2, 4, 1, },
    { 3, 4, 1, 2, },
    { 3, 4, 2, 1, },
    { 4, 1, 2, 3, },
    { 4, 2, 1, 3, },
    { 4, 3, 1, 2, },
    { 4, 3, 2, 1, },
};

// Set of 16 of the 40320 permutations of 8 objects
std::vector<std::vector<size_t>> PERMUTATIONS_8 = {
    { 1, 8, 3, 6, 2, 4, 5, 7, },
    { 1, 4, 7, 3, 2, 6, 8, 5, },
    { 2, 3, 6, 5, 4, 1, 8, 7, },
    { 2, 5, 4, 8, 1, 7, 3, 6, },
    { 3, 1, 5, 2, 8, 6, 7, 4, },
    { 3, 6, 8, 5, 2, 7, 4, 1, },
    { 4, 7, 2, 8, 6, 5, 3, 1, },
    { 4, 2, 7, 1, 5, 6, 3, 8, },
    { 5, 6, 2, 3, 1, 8, 7, 4, },
    { 5, 8, 3, 4, 1, 2, 6, 7, },
    { 6, 2, 7, 5, 4, 3, 8, 1, },
    { 6, 7, 5, 1, 2, 4, 8, 3, },
    { 7, 1, 6, 2, 4, 8, 5, 3, },
    { 7, 4, 6, 5, 1, 2, 3, 8, },
    { 8, 3, 4, 6, 2, 5, 7, 1, },
    { 8, 5, 4, 2, 1, 7, 3, 6, },
};

// Implement utilities module functions

std::string SHA_hex(const std::string& input) {
    SHA512 sha;
    return sha.hash(input);
}

std::vector<bool> SHA_bin(const std::string& input) {
    // Initialize memory
    std::string hex_chars = "0123456789abcdef";
    std::vector<bool> bin_digest;
    // Get the hexadecimal digest to convert to binary
    std::string hex_digest = SHA_hex(input);
    // Convert each character of the hexadecimal digest to 4 bits
    for (size_t i = 0; i < hex_digest.length(); i++) {
        // Initialize memory
        char hex_char = hex_digest[i];
        uint8_t bits = 0x00;
        // Find the position of the hex character
        for (; bits < 16; bits++) {
            if (hex_char == hex_chars[bits]) {
                break;
            }
        }
        // Convert position to bits
        for (size_t j = 0; j < 4; j++) {
            bin_digest.push_back((bool)((bits >> (4 - j - 1)) & 0x01));
        }
    }
    return bin_digest;
}

std::string permute_string(const std::string& input) {
    // Compute the hexadecimal and binary SHA-512 digests of the input
    std::string hex_digest = SHA_hex(input);
    std::vector<bool> bin_digest = SHA_bin(input);
    // Pad the input string to the next highest multiple of 8 in length
    std::string padded = input;
    size_t padding_index = 0;
    do {
        padded += hex_digest[padding_index++];
    } while (padded.length() % 8 != 0);
    // Split the padded string into chunks of 4 characters
    std::vector<std::string> chunks_4;
    for (size_t i = 0; i < padded.length(); i += 4) {
        chunks_4.push_back(padded.substr(i, 4));
    }
    // Choose a 4-permutation by the binary SHA-512 digest
    uint8_t permutation_4_index = 0x00;
    for (size_t i = 0; i < 4; i++) {
        permutation_4_index <<= 1;
        permutation_4_index |= (((uint8_t)bin_digest[504 + i]) & 0x01);
    }
    // Permute each 4-chunk by the 4-permutation choice and concatenate
    std::string permuted_4 = "";
    for (size_t i = 0; i < chunks_4.size(); i++) {
        std::string chunk_4 = chunks_4[i];
        for (size_t j = 0; j < 4; j++) {
            permuted_4 += chunk_4[PERMUTATIONS_4[permutation_4_index][j] - 1];
        }
    }
    // Split the 4-permuted string into 8 chunks of characters
    size_t chunk_8_length = permuted_4.length() / 8;
    std::vector<std::string> chunks_8;
    for (size_t i = 0; i < permuted_4.length(); i += chunk_8_length) {
        chunks_8.push_back(permuted_4.substr(i, chunk_8_length));
    }
    // Choose an 8-permutation by the binary SHA-512 digest
    uint8_t permutation_8_index = 0x00;
    for (size_t i = 0; i < 4; i++) {
        permutation_8_index <<= 1;
        permutation_8_index |= (((uint8_t)bin_digest[508 + i]) & 0x01);
    }
    // Permute the 8 chunks by the 8-permutation choice and concatenate
    std::string permuted_8 = "";
    for (size_t i = 0; i < 8; i++) {
        permuted_8 += chunks_8[PERMUTATIONS_8[permutation_8_index][i] - 1];
    }
    return permuted_8;
}