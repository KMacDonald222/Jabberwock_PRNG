/*
File:       Nodes.h
Author:     Keegan MacDonald
Created:    2025.03.28
Purpose:    Declare node type classes for the Jabberwock PRNG tree
*/

#ifndef JLIB_NODES_H
#define JLIB_NODES_H

#include <string>
#include <vector>

// An abstract node in the Jabberwock PRNG tree
class AbstractNode {
public:
    /*
    Abstract node destructor
    */
    virtual ~AbstractNode();
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
    virtual uint8_t getByte() = 0;
    /*
    Free this node's and its childrens' memory
    */
    virtual void clear();

protected:
    // Set of pointers to this node's children in the Jabberwock PRNG tree
    std::vector<AbstractNode*> m_children;
};

// An XOR node in the Jabberwock PRNG tree
class XORNode : public AbstractNode {
public:
    /*
    XOR node destructor
    */
    ~XORNode() override;
    /*
    Initialize this XOR node's and its childrens' memory
    Parameter: const std::string& seed - Seed data to choose child types to
    generate and seed
    Parameter: size_t level - The level of this node in the Jabberwock PRNG tree
    */
    void seed(const std::string&, size_t) override;
    /*
    Get a pseudorandom byte from this XOR node by bitwise XOR of the outputs of
    its children
    Returns: uint8_t - A pseudorandom byte
    */
    uint8_t getByte() override;
};

// An AND node in the Jabberwock PRNG tree
class ANDNode : public AbstractNode {
public:
    /*
    AND node destructor
    */
    ~ANDNode() override;
    /*
    Initialize this AND node's and its childrens' memory
    Parameter: const std::string& seed - Seed data to choose child types to
    generate and seed
    Parameter: size_t level - The level of this node in the Jabberwock PRNG tree
    */
    void seed(const std::string&, size_t) override;
    /*
    Get a pseudorandom byte from this AND node by bitwise AND of the outputs of
    its children
    Returns: uint8_t - A pseudorandom byte
    */
    uint8_t getByte() override;
};

// An OR node in the Jabberwock PRNG tree
class ORNode : public AbstractNode {
public:
    /*
    OR node destructor
    */
    ~ORNode() override;
    /*
    Initialize this OR node's and its childrens' memory
    Parameter: const std::string& seed - Seed data to choose child types to
    generate and seed
    Parameter: size_t level - The level of this node in the Jabberwock PRNG tree
    */
    void seed(const std::string&, size_t) override;
    /*
    Get a pseudorandom byte from this OR node by bitwise OR of the outputs of
    its children
    Returns: uint8_t - A pseudorandom byte
    */
    uint8_t getByte() override;
};

// A Galois LFSR node in the Jabberwock PRNG tree
class LFSRNode : public AbstractNode {
public:
    /*
    LFSR node destructor
    */
    ~LFSRNode() override;
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
    uint8_t getByte() override;
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