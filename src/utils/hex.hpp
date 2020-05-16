#ifndef PMT_UTILS_HEX_H
#define PMT_UTILS_HEX_H

#include <iostream>
#include <vector>

/**
 * Generates the empty byte
 * 
 * @return std::vector<uint64_t> Empty byte 
 */
std::vector<uint64_t> EmptyByte();

/**
 * @brief Is the string having hex prefix, i.e., 0x
 * 
 * @param input string to be examined
 * @return true if the hex prefix is present
 * @return false if the hex prefix does not exists
 */
bool IsHexPrefixed(const std::string& input);

/**
 * @brief Check if the string is hex string? 
 * 
 * @param input String to be examined
 * @return true If the string is hex string
 * @return false if the string is now hex string
 */
bool IsHexString(const std::string& input);

/**
 * @brief Insert Hex prefix to the hexadecimal string
 * 
 * @param input Hexadecimal string to be hex prefixed
 * @return std::string Hex prefixed heaxadecimal string
 */
std::string InsertHexPrefix(const std::string& input);

/**
 * @brief Remove hex prefix if it exists
 * 
 * @param input String from which hex prefix is to be removed
 * @return std::string processed string by removing hex prefix
 */
std::string StripHexPrefix(const std::string& input);

/**
 * @brief Add even padding to the string.
 * This will check if the string is having length even or not. 
 * If it is not even length, it will add 0 paddinf to make it even lenght.
 * 
 * @param input String to be padded with
 * @return std::string String with even padded.
 */
std::string PadToEven(const std::string& input);

/**
 * @brief Convert integer number of hexadecimal representaion 
 * 
 * @param input number to be converted to hex representation
 * @return std::string Hex String having representation of the input string
 */
std::string IntegerToHex(const uint64_t input);

/**
 * @brief Convert a hexadecimal string to human readable integer number
 * 
 * @param input hexadecimal string
 * @return uint64_t Human readable integer
 */
uint64_t HexToInteger(const std::string& input);

/**
 * @brief Convert a string to hexadecimal format
 * 
 * @param input string to be converted to hexadecimal format
 * @param upper flag to indicate whether to convert hex string to uppercase. Default false
 * @return std::string String having hexadecimal representation of the input string
 */
std::string StringToHex(const std::string& input, bool upper=false);

/**
 * @brief Convert a hexadecimal string to human readable string
 * 
 * @param input hexadecimal string
 * @return std::string Human readable string
 */
std::string HexToString(const std::string& input);

/**
 * @brief Safely parse string to integer 
 * 
 * @param input string to be parsed to integer
 * @param base base at which to parse the number, i.e. 2, 3, octal, hex, etc.
 * @return std::uint64_t parsed integer number
 */
std::uint64_t SafeParseInt(const std::string& input, unsigned int base=10);

/**
 * @brief Convert Integer to Bytes
 * 
 * @param input Large integer to be converted to bytes
 * @return std::vector<char> bytes representation of the integer
 */
std::vector<uint64_t> IntegerToBytes(const uint64_t input);

/**
 * @brief Convert bytes to Integer
 * 
 * @param input bytes representation of the number
 * @return uint64_t integer number
 */
uint64_t BytesToInteger(const std::vector<uint64_t>& input);

/**
 * @brief Convert string to bytes 
 * 
 * @param input String to be converted to bytes
 * @return std::vector<char> bytes representation of the string
 */
std::vector<uint64_t> StringToBytes(const std::string& input);

/**
 * @brief Convert bytes to Hex string
 * 
 * @param input Bytes to be converted in hex string
 * @return std::string Hex representation of string
 */
std::string BytesToString(const std::vector<uint64_t>& input);

#endif