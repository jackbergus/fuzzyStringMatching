//
// Created by giacomo on 11/12/18.
//

#ifndef INCONSISTENCY_CSV_ISTREAM_H
#define INCONSISTENCY_CSV_ISTREAM_H


#include <istream>
#include <sstream>

template <typename T> struct is_signed_int { enum { val = false }; };
template <> struct is_signed_int<short> { enum { val = true}; };
template <> struct is_signed_int<int> { enum { val = true}; };
template <> struct is_signed_int<long> { enum { val = true}; };
template <> struct is_signed_int<long long> { enum { val = true}; };

template <typename T> struct is_unsigned_int { enum { val = false }; };
template <> struct is_unsigned_int<unsigned short> { enum { val = true}; };
template <> struct is_unsigned_int<unsigned int> { enum { val = true}; };
template <> struct is_unsigned_int<unsigned long> { enum { val = true}; };
template <> struct is_unsigned_int<unsigned long long> { enum { val = true}; };

template <typename T> struct is_int {
    enum { val = (is_signed_int<T>::val || is_unsigned_int<T>::val) };
};

struct csv_istream {
    std::istream &is_;
    csv_istream();
    csv_istream (std::istream &is);
    void scan_ws () const;
    void scan (std::string *s = 0) const;
    template <typename T, bool> struct set_value {
        void operator () (std::string in, T &v) const {
            std::istringstream(in) >> v;
        }
    };
    template <typename T> struct set_value<T, true> {
        template <bool SIGNED> void convert (std::string in, T &v) const {
            if (SIGNED) v = ::strtoll(in.c_str(), 0, 0);
            else v = ::strtoull(in.c_str(), 0, 0);
        }
        void operator () (std::string in, T &v) const {
            convert<is_signed_int<T>::val>(in, v);
        }
    };
    template <typename T> const csv_istream & operator >> (T &v) const;
    const csv_istream & operator >> (std::string &v) const;
    template <typename T>
    const csv_istream & operator >> (T &(*manip)(T &)) const;
    operator bool () const;
};


#endif //INCONSISTENCY_CSV_ISTREAM_H
