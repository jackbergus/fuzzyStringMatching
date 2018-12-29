//
// Created by giacomo on 10/12/18.
//

#include "ICEWSPlace.h"

void ICEWSPlace::load(SplitStringIterator &it) {
    city = *it; it++;
    district = *it; it++;
    province = *it; it++;
    country = *it; it++;
    latitude = std::stold(*it); it++;
    longitude = std::stold(*it); it++;
}

std::ostream &operator<<(std::ostream &os, const ICEWSPlace &place) {
    if (!place.city.empty())
        os << "city: " << place.city;
    else if (!place.district.empty())
        os << "district: " << place.district;
    else if (!place.province.empty())
        os << "province: " << place.province;
    else if (!place.country.empty())
        os << "country: " << place.country;
    os << " with lat,long=<" << place.latitude << "," << place.longitude << ">";
    return os;
}
