#ifndef PMT_UTILS_NIBBLES_H
#define PMT_UTILS_NIBBLES_H

#include <vector>
#include <iostream>

/**
 * @brief Converts a buffer to nibble
 * 
 * @param input key to convert to nibble
 * @return std::vector<uint> Nibble representation of the input
 */
std::vector<uint> StringToNibble(const std::string& input);

/**
 * @brief Converts a string to nibble
 * 
 * @param input key to convert to nibble
 * @return std::vector<uint> Nibble representation of the input
 */
std::vector<uint> BufferToNibble(const std::vector<uint64_t>& input);

/**
 * @brief Converts a nibble to buffer
 * 
 * @param input Nibble to be converted to buffer
 * @return std::vector<uint64_t> Buffer representation of the input
 */
std::vector<uint64_t> NibbleToBuffer(const std::vector<uint>& input);

/**
 * @brief Match the number of inorder matching nibbles of the two given nubbles
 * 
 * @param input_1 First Nibble
 * @param input_2 Second nibble
 * @return int Number of matching nibbles
 */
int MatchingNibbleLength(const std::vector<uint>& input_1, const std::vector<uint>& input_2);

/**
 * @brief Compare two nibble keys
 * 
 * @param input_1 First Nibble
 * @param input_2 Second Nibble
 * @return true if the keys match
 * @return false if keys do not match
 */
bool DoKeysMatch(std::vector<uint>& input_1, std::vector<uint>& input_2);

/**
 * @brief Prepends hex prefix to nibble
 * 
 * @param input Nibble
 * @param terminator flag to indicate whether there is terminator string or not
 * @return std::vector<uint> Hex Prefixed Nibble
 */
std::vector<uint> AddHexPrefix(const std::vector<uint>& input, bool terminator);

/**
 * @brief Removes Hex prefix of Nibble
 * 
 * @param input Nibble with hex prefixed
 * @return std::vector<uint> Nibble without hex prefix
 */
std::vector<uint> RemoveHexPrefix(const std::vector<uint>& input);

/**
 * @brief Checks if hex prefixed path is for terminating leaf node
 * 
 * @param input Nibble
 * @return true if hex prefixed path is for terminating leaf node
 * @return false if hex prefixed path is not for terminating leaf node
 */
bool IsTerminator(const std::vector<uint>& input);

/**
 * @brief Get the Bytes object
 * 
 * @tparam T Vector representing bytes
 * @param input Bytes
 * @return std::string string representation of bytes 
 */
template<typename T>
std::string GetBytes(T input);

/**
 * @brief Slice the vector from start to end
 * 
 * @tparam T Type of vector
 * @param v Vector be sliced
 * @param start Start point
 * @param end End point
 * @return std::vector<T> Sliced vector
 */
template<typename T>
std::vector<T> Slice(const std::vector<T>& v, int start, int end=-1);

/**
 * @brief Checks if the object is an instance of the Template class name
 * 
 * @tparam Base Base class
 * @tparam T Class name whose type the object needs to be checked
 * @return true if the object is instance of T
 * @return false if object is not instance of T
 */
template<typename Base, typename T>
inline bool instanceof(const T*);

#include "generalised.hpp"

#endif
