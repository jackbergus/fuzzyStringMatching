//
// Created by giacomo on 11/12/18.
//

#include "Streamers.h"
#include <sstream>
#include <iterator>

inline bool not_digit(char ch) {
    return '0' <= ch && ch <= '9';
}

std::ostream &operator<<(std::ostream &os, const std::vector<LONG_NUMERIC> &vec) {
    std::ostringstream oss;
    if (!vec.empty()) {
        // Convert all but the last element to avoid a trailing ","
        std::copy(vec.begin(), vec.end()-1,
                  std::ostream_iterator<LONG_NUMERIC>(oss, ", "));

        // Now add the last element with no delimiter
        oss << vec.back();
    }
    os << "{" << oss.str() << "}";
    return os;
}

std::ostream &operator<<(std::ostream &os, const std::vector<double> &vec) {
    std::ostringstream oss;
    if (!vec.empty()) {
        // Convert all but the last element to avoid a trailing ","
        std::copy(vec.begin(), vec.end()-1,
                  std::ostream_iterator<double>(oss, ", "));

        // Now add the last element with no delimiter
        oss << vec.back();
    }
    os << "{" << oss.str() << "}";
    return os;
}

std::ostream &operator<<(std::ostream &os, const std::vector<std::string> &vec) {
    std::ostringstream oss;
    if (!vec.empty()) {
        // Convert all but the last element to avoid a trailing ","
        for (auto it = vec.begin(); it != vec.end()-1; it++) {
            oss << *it << ", ";
        }

        // Now add the last element with no delimiter
        oss << vec.back();
    }
    os << "{" << oss.str() << "}";
    return os;
}