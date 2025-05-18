/*
File:       Utilities.cpp
Author:     Keegan MacDonald
Created:    2025.03.28
Purpose:    Implement utility module functions found in Utilities.h
*/

#include "Utilities.h"

#include <SHA/SHA512.h>

// Define utilities module variables

// Set of 16 of the 24 permutation of 4 objects
std::vector<std::vector<size_t>> PERMUTATIONS4 = {
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
std::vector<std::vector<size_t>> PERMUTATIONS8 = {
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

std::string SHAHex(const std::string& input) {
    SHA512 sha;
    return sha.hash(input);
}

std::vector<bool> SHABin(const std::string& input) {
    // Initialize memory
    std::string hexChars = "0123456789abcdef";
    std::vector<bool> binDigest;
    // Get the hexadecimal digest to convert to binary
    std::string hexDigest = SHAHex(input);
    // Convert each character of the hexadecimal digest to 4 bits
    for (size_t i = 0; i < hexDigest.length(); i++) {
        // Initialize memory
        char hexChar = hexDigest[i];
        uint8_t bits = 0x00;
        // Find the position of the hex character
        for (; bits < 16; bits++) {
            if (hexChar == hexChars[bits]) {
                break;
            }
        }
        // Convert position to bits
        for (size_t j = 0; j < 4; j++) {
            binDigest.push_back((bool)((bits >> (4 - j - 1)) & 0x01));
        }
    }
    return binDigest;
}

std::string PermuteString(const std::string& input) {
    // Compute the hexadecimal and binary SHA-512 digests of the input
    std::string hexDigest = SHAHex(input);
    std::vector<bool> binDigest = SHABin(input);
    // Pad the input string to the next highest multiple of 8 in length
    std::string padded = input;
    size_t paddingIndex = 0;
    do {
        padded += hexDigest[paddingIndex++];
    } while (padded.length() % 8 != 0);
    // Split the padded string into chunks of 4 characters
    std::vector<std::string> chunks4;
    for (size_t i = 0; i < padded.length(); i += 4) {
        chunks4.push_back(padded.substr(i, 4));
    }
    // Choose a 4-permutation by the binary SHA-512 digest
    uint8_t permutation4Index = 0x00;
    for (size_t i = 0; i < 4; i++) {
        permutation4Index <<= 1;
        permutation4Index |= (((uint8_t)binDigest[504 + i]) & 0x01);
    }
    // Permute each 4-chunk by the 4-permutation choice and concatenate
    std::string permuted4 = "";
    for (size_t i = 0; i < chunks4.size(); i++) {
        std::string chunk4 = chunks4[i];
        for (size_t j = 0; j < 4; j++) {
            permuted4 += chunk4[PERMUTATIONS4[permutation4Index][j] - 1];
        }
    }
    // Split the 4-permuted string into 8 chunks of characters
    size_t chunk8Length = permuted4.length() / 8;
    std::vector<std::string> chunks8;
    for (size_t i = 0; i < permuted4.length(); i += chunk8Length) {
        chunks8.push_back(permuted4.substr(i, chunk8Length));
    }
    // Choose an 8-permutation by the binary SHA-512 digest
    uint8_t permutation8Index = 0x00;
    for (size_t i = 0; i < 4; i++) {
        permutation8Index <<= 1;
        permutation8Index |= (((uint8_t)binDigest[508 + i]) & 0x01);
    }
    // Permute the 8 chunks by the 8-permutation choice and concatenate
    std::string permuted8 = "";
    for (size_t i = 0; i < 8; i++) {
        permuted8 += chunks8[PERMUTATIONS8[permutation8Index][i] - 1];
    }
    return permuted8;
}