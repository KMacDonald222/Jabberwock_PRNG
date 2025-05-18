/*
File:       ANDNode.cpp
Author:     Keegan MacDonald
Created:    2025.03.31
Purpose:    Implement ANDNode class functions declared in Nodes.h
*/

#include "Nodes.h"
#include "Utilities.h"

// Implement ANDNode class functions

ANDNode::~ANDNode() {
    clear();
}

void ANDNode::seed(const std::string& seed, size_t level) {
    // Compute the binary SHA-512 digest of the seed
    std::vector<bool> binDigest = SHABin(seed);
    if (level <= 1) {
        // Generate 2 to 5 LFSR children
        uint8_t LFSRCount = 2 + ((uint8_t)binDigest[510] << 1)
            + ((uint8_t)binDigest[511]);
        for (size_t i = 0; i < LFSRCount; i++) {
            m_children.push_back(new LFSRNode());
        }
    } else {
        // Generate 1 to 2 XOR children
        uint8_t XORCount = 1 + ((uint8_t)binDigest[509]);
        for (size_t i = 0; i < XORCount; i++) {
            m_children.push_back(new XORNode());
        }
        // Generate 0 to 1 AND children
        uint8_t ANDCount = ((uint8_t)binDigest[510]);
        for (size_t i = 0; i < ANDCount; i++) {
            m_children.push_back(new ANDNode());
        }
        // Generate 1 to 2 OR children
        uint8_t ORCount = 1 + ((uint8_t)binDigest[511]);
        for (size_t i = 0; i < ORCount; i++) {
            m_children.push_back(new ORNode());
        }
    }
    // Seed all child nodes
    AbstractNode::seed(seed, level);
}

uint8_t ANDNode::getByte() {
    // Ensure that there is data to AND
    if (m_children.empty()) {
        return 0x00;
    }
    // Compute AND product of all children's output
    uint8_t outByte = m_children[0]->getByte();
    for (size_t i = 1; i < m_children.size(); i++) {
        outByte &= m_children[i]->getByte();
    }
    return outByte;
}