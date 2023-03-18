/**
 * Utils
 *
 * @file: utils.h
 * @date: 18.03.2023
 */

#ifndef IPKCPC_UTILS_H
#define IPKCPC_UTILS_H

#include <algorithm>
#include <cctype>
#include <locale>

/**
 * Trim string from start (in place)
 * @param s String to trim
 */
void ltrim(std::string &s);

/**
 * Trim string from end (in place)
 * @param s String to trim
 */
void rtrim(std::string &s);

/**
 * Trim string from both ends (in place)
 * @param s String to trim
 */
void trim(std::string &s);

/**
 * Trim string from start (copying)
 * @param s String to trim
 * @return Trimmed string
 */
std::string ltrim_copy(std::string s);

/**
 * Trim string from end (copying)
 * @param s String to trim
 * @return Trimmed string
 */
std::string rtrim_copy(std::string s);

/**
 * Trim string from both ends (copying)
 * @param s String to trim
 * @return Trimmed string
 */
std::string trim_copy(std::string s);

#endif// IPKCPC_UTILS_H
