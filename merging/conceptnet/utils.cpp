//
// Created by giacomo on 17/10/18.
//

#include <string>
#include <algorithm>
#include <regex>
#include "utils.h"


std::regex spaceRegex("\\s");
std::string slash{"/"};

/**
 * Provides the expected representation for the string in Concepts
 *
 * @param x
 * @return
 */
std::string rectify(std::string& x) {
    std::string s{x};
    std::regex_replace (s, spaceRegex, "_");
    std::replace( s.begin(), s.end(), '-', '_');
    return s;
}

/**
 * This function allows to traverse a string and get the i-th substring separated by a given delimiter
 * without the need of actually splitting the string. In this way we perform at most a linear scan
 * of the string and we save primary memory space.
 *
 * @param s             String to be tokenized according to the delimiter
 * @param delimiter     Delimiter separating the tokens
 * @param ith           Selecting the i-th token that is separated from the delimiter
 * @return              Returns the token if it has been found, or an empty string otherwise. Important:
 *                      the semantic assumes that the to-be-splitted string shall never contain empty tokens
 */
std::string splitOnce(std::string& s, std::string& delimiter, int ith) {
    size_t next = 0, pos = 0, prev = 0, count = 0, c = 0;
    size_t len = delimiter.length();
    while ((next = s.find(delimiter, pos)) != std::string::npos && count < ith) {
        count++;
        prev = pos;
        pos = s.find(delimiter, next+len);
    }
    c = (s.find(delimiter, pos+1));
    bool finalIsNotEnd = c != std::string::npos;
    bool begIsNotEnd = pos != std::string::npos;
    std::string toret = next == s.length() ? "" :
           s.substr((begIsNotEnd ? pos+1 : prev+len),(finalIsNotEnd && begIsNotEnd ? c-pos-1 : s.length()));
    return toret;
}

std::string unrectify(std::string& x) {
    std::string s{x};
    if (s.rfind("/c/", 0) == 0) {
        std::string split = splitOnce(x, slash, 2);
        return unrectify(split);
    } else {
        std::replace( s.begin(), s.end(), '_', ' ');
        return s;
    }
}

std::string extract_basic_id(std::string &generic_id) {
    long pos = strpos((char*)generic_id.c_str(), (char*)slash.c_str(),4);
    if (pos >=  0) {
        return generic_id.substr(0, pos);
    } else {
        return generic_id;
    }
}
