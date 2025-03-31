/*
File:       LFSR_node.cpp
Author:     Keegan MacDonald
Created:    2025.03.28
Purpose:    Implement LFSR_node class functions declared in nodes.h
*/

#include "nodes.h"
#include "utilities.h"

// Define LFSR_node module variables

// Set of 16 preset width and tap position configurations for LFSRs
std::vector<std::vector<size_t>> LFSR_CONFIGS = {
    { 4096, 4095, 4081, 4069, },
    { 2048, 2035, 2034, 2029, },
    { 777, 776, 767, 761, },
    { 667, 664, 660, 649, },
    { 666, 664, 659, 656, },
    { 665, 661, 659, 654, },
    { 589, 586, 585, 579, },
    { 512, 510, 507, 504, },
    { 444, 435, 432, 431, },
    { 333, 331, 329, 325, },
    { 303, 297, 291, 290, },
    { 256, 254, 251, 246, },
    { 222, 220, 217, 214, },
    { 128, 127, 126, 121, },
    { 111, 109, 107, 104, },
    { 64, 63, 61, 60, },
};

// Implement LFSR_node class functions

LFSR_node::~LFSR_node() {
    clear();
}

void LFSR_node::seed(const std::string& seed, size_t) {
    // Compute seed SHA-512 digest
    std::vector<bool> bin_digest = SHA_bin(seed);
    // Choose a configuration choice by the seed's SHA-512 digest
    uint8_t config_index = 0x00;
    for (size_t i = 0; i < 4; i++) {
        config_index <<= 1;
        config_index |= (int)bin_digest[508 + i];
    }
    // Get the LFSR buffer width
    size_t width = LFSR_CONFIGS[config_index][0];
    // Initialize state buffer
    m_state.resize(width);
    for (size_t i = 0; i < width; i++) {
        m_state[i] = bin_digest[i % bin_digest.size()];
    }
    // Initialize tap position buffer
    m_taps.resize(width);
    for (size_t i = 0; i < width; i++) {
        m_taps[i] = false;
    }
    for (size_t i = 0; i < 4; i++) {
        size_t tap_position = LFSR_CONFIGS[config_index][i];
        m_taps[width - tap_position] = true;
    }
}

uint8_t LFSR_node::get_byte() {
    // Get LFSR buffer width
    size_t width = m_state.size();
    // Generate 8 output bits
    uint8_t out_byte = 0x00;
    for (size_t i = 0; i < 8; i++) {
        // Get output bit
        uint8_t out_bit = (uint8_t)m_state[width - 1];
        out_byte <<= 1;
        out_byte |= out_bit;
        // Shift the state buffer
        for (int j = width - 1; j > 0; j--) {
            m_state[j] = m_state[j - 1];
        }
        m_state[0] = false;
        if (out_bit == 0x01) {
            // Apply XOR taps
            for (size_t j = 0; j < width; j++) {
                m_state[j] = m_state[j] ^ m_taps[j];
            }
        }
    }
    return out_byte;
}

void LFSR_node::clear() {
    // Overwrite the state and tap position buffers
    size_t width = m_state.size();
    for (size_t i = 0; i < width; i++) {
        m_state[i] = false;
        m_taps[i] = false;
    }
    // Clear memory
    m_state.clear();
    m_taps.clear();
}