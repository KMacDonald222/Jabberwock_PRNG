/*
File:       nodes.h
Author:     Keegan MacDonald
Created:    2025.03.28
Purpose:    Declare node type classes for the Jabberwock PRNG tree
*/

#ifndef JLIB_NODES_H
#define JLIB_NODES_H

#include <string>
#include <vector>

// An abstract node in the Jabberwock PRNG tree
class abstract_node {
public:
    /*
    Abstract node destructor
    */
    virtual ~abstract_node();
    /*
    Seed this node's children
    Parameter: const std::string& seed - Seed data string to permute and pass to
    childrens' seed functions
    Parameter: size_t level - The level of this node in the Jabberwock PRNG tree
    */
    virtual void seed(const std::string&, size_t);
    /*
    Get a pseudorandom byte from this node
    Returns: uint8_t - A pseudorandom byte
    */
    virtual uint8_t get_byte() = 0;
    /*
    Free this node's and its childrens' memory
    */
    virtual void clear();

protected:
    // Set of pointers to this node's children in the Jabberwock PRNG tree
    std::vector<abstract_node*> m_children;
};

// A Galois LFSR node in the Jabberwock PRNG tree
class LFSR_node : public abstract_node {
public:
    /*
    Initialize this LFSR node's memory
    Parameter: const std::string& seed - Seed data to choose LFSR configuration
    and initialize state buffer by
    Parameter: size_t level - Unused parameter
    */
    void seed(const std::string&, size_t) override;
    /*
    Generate a byte of output from this LFSR node
    Returns: uint8_t - A pseudorandom byte
    */
    uint8_t get_byte() override;
    /*
    Overwrite and free this LFSR node's state and tap position buffers
    */
    void clear() override;

private:
    // The LFSR's state buffer
    std::vector<bool> m_state;
    // The LFSR's tap position buffer
    std::vector<bool> m_taps;
};

#endif