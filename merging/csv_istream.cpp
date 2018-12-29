//
// Created by giacomo on 11/12/18.
//

#include "csv_istream.h"

std::istringstream e{};

csv_istream::csv_istream() : is_(e) {}

csv_istream::csv_istream(std::istream &is) : is_(is) {}

void csv_istream::scan_ws() const {
    while (is_.good()) {
        int c = is_.peek();
        if (c != ' ' && c != '\t') break;
        is_.get();
    }
}

void csv_istream::scan(std::string *s) const {
    std::string ws;
    int c = is_.get();
    if (is_.good()) {
        do {
            if (c == ',' || c == '\n') break;
            if (s) {
                ws += c;
                if (c != ' ' && c != '\t') {
                    *s += ws;
                    ws.clear();
                }
            }
            c = is_.get();
        } while (is_.good());
        if (is_.eof()) is_.clear();
    }
}

const csv_istream &csv_istream::operator>>(std::string &v) const {
    v.clear();
    scan_ws();
    if (is_.peek() != '"') scan(&v);
    else {
        std::string tmp;
        is_.get();
        std::getline(is_, tmp, '"');
        while (is_.peek() == '"') {
            v += tmp;
            v += is_.get();
            std::getline(is_, tmp, '"');
        }
        v += tmp;
        scan();
    }
    return *this;
}

template<typename T>
const csv_istream &csv_istream::operator>>(T &(*manip)(T &)) const {
    is_ >> manip;
    return *this;
}

csv_istream::operator bool() const { return !is_.fail(); }

template<typename T>
const csv_istream &csv_istream::operator>>(T &v) const {
    std::string tmp;
    scan(&tmp);
    set_value<T, is_int<T>::val>()(tmp, v);
    return *this;
}
