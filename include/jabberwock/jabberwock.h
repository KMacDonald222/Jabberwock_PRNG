/*
File:       jabberwock.h
Author:     Keegan MacDonald
Created:    2025.03.31
Purpose:    Declare the main class of the Jabberwock PRNG library
*/

#ifndef JLIB_JABBERWOCK_H
#define JLIB_JABBERWOCK_H

#include "nodes.h"

// The main wrapper class of the Jabberwock PRNG library
class jabberwock {
public:
    /*
    Destructor for Jabberwock PRNG
    */
    ~jabberwock();
    /*
    Initialize the Jabberwock PRNG tree memory
    Parameter: const std::string& seed - The PRNG seed
    */
    void seed(const std::string&);
    /*
    Get a pseudorandom byte from the Jabberwock PRNG tree
    Returns: uint8_t - A pseudorandom byte
    */
    uint8_t get_byte();
    /*
    Free the Jabberwock PRNG's memory
    */
    void clear();

private:
    // The root node of the Jabberwock PRNG tree
    XOR_node m_root;
};

#endif