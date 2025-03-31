/*
File:       abstract_node.cpp
Author:     Keegan MacDonald
Created:    2025.03.28
Purpose:    Implement abstract_node class functions declared in nodes.h
*/

#include "nodes.h"
#include "utilities.h"

// Implement abstract_node class functions

abstract_node::~abstract_node() {
    clear();
}

void abstract_node::seed(const std::string& seed, size_t level) {
    // Seed each child node with a permuted version of the seed string and one
    // less than the current level count
    std::string permuted_seed = seed;
    for (size_t i = 0; i < m_children.size(); i++) {
        permuted_seed = permute_string(permuted_seed);
        m_children[i]->seed(permuted_seed, level - 1);
    }
}

void abstract_node::clear() {
    // Clear each child node and delete it from memory
    for (size_t i = 0; i < m_children.size(); i++) {
        m_children[i]->clear();
        delete m_children[i];
        m_children[i] = nullptr;
    }
    m_children.clear();
}