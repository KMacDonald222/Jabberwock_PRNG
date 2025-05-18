/*
File:       AbstractNode.cpp
Author:     Keegan MacDonald
Created:    2025.03.28
Purpose:    Implement AbstractNode class functions declared in Nodes.h
*/

#include "Nodes.h"
#include "Utilities.h"

// Implement AbstractNode class functions

AbstractNode::~AbstractNode() {
    clear();
}

void AbstractNode::seed(const std::string& seed, size_t level) {
    // Seed each child node with a permuted version of the seed string and one
    // less than the current level count
    std::string permutedSeed = seed;
    for (size_t i = 0; i < m_children.size(); i++) {
        permutedSeed = PermuteString(permutedSeed);
        m_children[i]->seed(permutedSeed, level - 1);
    }
}

void AbstractNode::clear() {
    // Clear each child node and delete it from memory
    for (size_t i = 0; i < m_children.size(); i++) {
        m_children[i]->clear();
        delete m_children[i];
        m_children[i] = nullptr;
    }
    m_children.clear();
}