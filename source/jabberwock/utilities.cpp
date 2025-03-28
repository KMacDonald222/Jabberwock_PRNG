/*
File:       utilities.cpp
Author:     Keegan MacDonald
Created:    2025.03.28
Purpose:    Implement utility module functions found in utilities.h
*/

#include "utilities.h"

#include <SHA/SHA512.h>

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