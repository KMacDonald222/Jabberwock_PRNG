/*
File:       Jabberwock.cpp
Author:     Keegan MacDonald
Created:    2025.03.31
Purpose:    Implement Jabberwock class functions declared in Jabberwock.h
*/

#include "Jabberwock.h"

// Implement Jabberwock class functions

Jabberwock::~Jabberwock() {
    clear();
}

void Jabberwock::seed(const std::string& seed) {
    m_root.seed(seed, 3);
}

uint8_t Jabberwock::getByte() {
    return m_root.getByte();
}

void Jabberwock::clear() {
    m_root.clear();
}