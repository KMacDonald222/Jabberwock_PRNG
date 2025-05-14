/*
File:       Abstract_Node.cpp
Author:     Keegan MacDonald
Created:    2025.03.28
Purpose:    Implement Abstract_Node class functions declared in Nodes.h
*/

#include "Nodes.h"
#include "Utilities.h"

// Implement Abstract_Node class functions

Abstract_Node::~Abstract_Node() {
    clear();
}

void Abstract_Node::seed(const std::string& seed, size_t level) {
    // Seed each child node with a permuted version of the seed string and one
    // less than the current level count
    std::string permuted_seed = seed;
    for (size_t i = 0; i < m_children.size(); i++) {
        permuted_seed = Permute_String(permuted_seed);
        m_children[i]->seed(permuted_seed, level - 1);
    }
}

void Abstract_Node::clear() {
    // Clear each child node and delete it from memory
    for (size_t i = 0; i < m_children.size(); i++) {
        m_children[i]->clear();
        delete m_children[i];
        m_children[i] = nullptr;
    }
    m_children.clear();
}