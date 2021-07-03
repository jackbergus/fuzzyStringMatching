/*
 * utils.cpp
 * This file is part of fuzzyStringMatching
 *
 * Copyright (C) 2018 - Giacomo Bergami
 *
 * fuzzyStringMatching is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * fuzzyStringMatching is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with fuzzyStringMatching. If not, see <http://www.gnu.org/licenses/>.
 */
//
// Created by giacomo on 17/10/18.
//
//
// Created by giacomo on 26/08/19.
//

#include <locale>
#include <algorithm>
#include <codecvt>
#include "utils/stringuitls.h"

int strnmcmp(char *value, size_t len1, char *other, size_t len2) {
    int lim = len1 < len2 ? len1 : len2;
    for (int k = 0; k < lim; k++) {
        char c1 = value[k];
        char c2 = other[k];
        if (c1 != c2) {
            return c1 - c2;
        }
    }
    return len1 - len2;
}

auto& t = std::use_facet<std::ctype<wchar_t>>(std::locale());
std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converterX;

wchar_t lowcase(wchar_t ch) {
    return t.tolower( ch );
}

std::string utf8_tolower(const std::string &src) {
    std::wstring wsTmp(src.begin(), src.end());
    std::wstring result;
    std::transform( src.begin(), src.end(), std::back_inserter( result ), lowcase );
    return converterX.to_bytes(result);
}



#include <string>
#include <algorithm>
#include <regex>


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
