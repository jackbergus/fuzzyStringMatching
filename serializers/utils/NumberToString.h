//
// Created by giacomo on 10/08/17.
//

#ifndef PROJECT_NUMBERTOSTRING_H
#define PROJECT_NUMBERTOSTRING_H

/* http://www.cplusplus.com/articles/D9j2Nwbp/ */

#include <sstream>

template <typename T> std::string NumberToString (T Number ) {
    std::ostringstream ss;
    ss << Number;
    return ss.str();
}

template <typename T> T StringToNumber ( const std::string &Text )  {
    std::istringstream ss(Text);
    T result;
    return ss >> result ? result : 0;
}

#endif //PROJECT_NUMBERTOSTRING_H
