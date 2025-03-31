/*
File:       XOR_node.cpp
Author:     Keegan MacDonald
Created:    2025.03.31
Purpose:    Implement XOR_node class functions declared in nodes.h
*/

#include "nodes.h"
#include "utilities.h"

// Implement XOR_node class functions

XOR_node::~XOR_node() {
    clear();
}

void XOR_node::seed(const std::string& seed, size_t level) {
    // Compute the binary SHA-512 digest of the seed
    std::vector<bool> bin_digest = SHA_bin(seed);
    if (level <= 1) {
        // Generate 5 to 8 LFSR children
        uint8_t LFSR_count = 5 + ((uint8_t)bin_digest[510] << 1)
            + ((uint8_t)bin_digest[511]);
        for (size_t i = 0; i < LFSR_count; i++) {
            m_children.push_back(new LFSR_node());
        }
    } else {
        // Generate 3 to 4 XOR children
        uint8_t XOR_count = 3 + ((uint8_t)bin_digest[509]);
        for (size_t i = 0; i < XOR_count; i++) {
            m_children.push_back(new XOR_node());
        }
        // Generate 1 to 2 AND children
        uint8_t AND_count = 1 + ((uint8_t)bin_digest[510]);
        for (size_t i = 0; i < AND_count; i++) {
            m_children.push_back(new AND_node());
        }
        // Generate 1 to 2 OR children
        uint8_t OR_count = 1 + ((uint8_t)bin_digest[511]);
        for (size_t i = 0; i < OR_count; i++) {
            m_children.push_back(new OR_node());
        }
    }
    // Seed all child nodes
    abstract_node::seed(seed, level);
}

uint8_t XOR_node::get_byte() {
    // Ensure that there is data to XOR
    if (m_children.empty()) {
        return 0x00;
    }
    // Compute XOR sum of all children's output
    uint8_t out_byte = m_children[0]->get_byte();
    for (size_t i = 1; i < m_children.size(); i++) {
        out_byte ^= m_children[i]->get_byte();
    }
    return out_byte;
}