/*
File:       utilities.h
Author:     Keegan MacDonald
Created:    2025.03.28
Purpose:    Declare utility functions to be used by the libjabberwock project
*/

#ifndef JLIB_UTILITIES_H
#define JLIB_UTILITIES_H

#include <string>
#include <vector>

/*
Get the SHA-512 digest of a string and represent it in hexadecimal
Parameter: const std::string& input - The input string to the SHA-512 function
Returns: std::string - The hexadecimal representation of the SHA-512 digest of
the input string
*/
extern std::string SHA_hex(const std::string&);
/*
Get the SHA-512 digest of a string and represent it in binary
Parameter: const std::string& input - The input string to the SHA-512 function
Returns: std::string - The binary representation of the SHA-512 digest of the
input string
*/
extern std::vector<bool> SHA_bin(const std::string&);

#endif