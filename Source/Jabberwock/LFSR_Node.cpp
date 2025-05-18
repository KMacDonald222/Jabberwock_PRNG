/*
File:       LFSRNode.cpp
Author:     Keegan MacDonald
Created:    2025.03.28
Purpose:    Implement LFSRNode class functions declared in Nodes.h
*/

#include "Nodes.h"
#include "Utilities.h"

// Define LFSRNode module variables

// Set of 16 preset width and tap position configurations for LFSRs
std::vector<std::vector<size_t>> LFSRCONFIGS = {
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

// Implement LFSRNode class functions

LFSRNode::~LFSRNode() {
    clear();
}

void LFSRNode::seed(const std::string& seed, size_t) {
    // Compute seed SHA-512 digest
    std::vector<bool> binDigest = SHABin(seed);
    // Choose a configuration choice by the seed's SHA-512 digest
    uint8_t configIndex = 0x00;
    for (size_t i = 0; i < 4; i++) {
        configIndex <<= 1;
        configIndex |= (int)binDigest[508 + i];
    }
    // Get the LFSR buffer width
    size_t width = LFSRCONFIGS[configIndex][0];
    // Initialize state buffer
    m_state.resize(width);
    for (size_t i = 0; i < width; i++) {
        m_state[i] = binDigest[i % binDigest.size()];
    }
    // Initialize tap position buffer
    m_taps.resize(width);
    for (size_t i = 0; i < width; i++) {
        m_taps[i] = false;
    }
    for (size_t i = 0; i < 4; i++) {
        size_t tapPosition = LFSRCONFIGS[configIndex][i];
        m_taps[width - tapPosition] = true;
    }
}

uint8_t LFSRNode::getByte() {
    // Get LFSR buffer width
    size_t width = m_state.size();
    // Generate 8 output bits
    uint8_t outByte = 0x00;
    for (size_t i = 0; i < 8; i++) {
        // Get output bit
        uint8_t outBit = (uint8_t)m_state[width - 1];
        outByte <<= 1;
        outByte |= outBit;
        // Shift the state buffer
        for (int j = width - 1; j > 0; j--) {
            m_state[j] = m_state[j - 1];
        }
        m_state[0] = false;
        if (outBit == 0x01) {
            // Apply XOR taps
            for (size_t j = 0; j < width; j++) {
                m_state[j] = m_state[j] ^ m_taps[j];
            }
        }
    }
    return outByte;
}

void LFSRNode::clear() {
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