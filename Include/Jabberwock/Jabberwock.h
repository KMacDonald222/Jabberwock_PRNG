/*
File:       Jabberwock.h
Author:     Keegan MacDonald
Created:    2025.03.31
Purpose:    Declare the main class of the Jabberwock PRNG library
*/

#ifndef JLIB_JABBERWOCK_H
#define JLIB_JABBERWOCK_H

#include "Nodes.h"

// The main wrapper class of the Jabberwock PRNG library
class Jabberwock {
public:
    /*
    Destructor for Jabberwock PRNG
    */
    ~Jabberwock();
    /*
    Initialize the Jabberwock PRNG tree memory
    Parameter: const std::string& seed - The PRNG seed
    */
    void seed(const std::string&);
    /*
    Get a pseudorandom byte from the Jabberwock PRNG tree
    Returns: uint8_t - A pseudorandom byte
    */
    uint8_t getByte();
    /*
    Free the Jabberwock PRNG's memory
    */
    void clear();

private:
    // The root node of the Jabberwock PRNG tree
    XORNode m_root;
};

#endif