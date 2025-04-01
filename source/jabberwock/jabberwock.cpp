/*
File:       jabberwock.cpp
Author:     Keegan MacDonald
Created:    2025.03.31
Purpose:    Implement jabberwock class functions declared in jabberwock.h
*/

#include "jabberwock.h"

// Implement jabberwock class functions

jabberwock::~jabberwock() {
    clear();
}

void jabberwock::seed(const std::string& seed) {
    m_root.seed(seed, 3);
}

uint8_t jabberwock::get_byte() {
    return m_root.get_byte();
}

void jabberwock::clear() {
    m_root.clear();
}