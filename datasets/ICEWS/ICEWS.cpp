//
// Created by giacomo on 11/12/18.
//

#include "ICEWS.h"

ICEWS::ICEWS(std::string& line) {
    SplitStringIterator it{line, "\t"}, end{};
    id = std::stoul(*it); it++;
    time = *it; it++;
    src.load(true, it);
    event = *it; it++;
    event_type_id = *it; it++;
    intensity = *it; it++;
    dst.load(false, it);
    //Story ID, Sentence Number, Publisher
    it++; it++; it++;
    if (it != end) {
        place.load(it);
    }
}

std::ostream &operator<<(std::ostream &os, const ICEWS &icews) {

    os << "ICEWS\n\t<" << icews.src.name << ">--[label=" << icews.event
       << ", p=1.0]-><" << icews.dst.name << ">\t@[T=" << icews.time << "; PLC=" << icews.place << "]";
    return os;

    os << "id: " << icews.id << " time: " << icews.time << " src: " << icews.src.name << " event: " << icews.event
       << " event_type_id: " << icews.event_type_id << " intensity: " << icews.intensity << " dst: " << icews.dst
       << " place: " << icews.place << " isNegated: " << icews.isNegated;
    return os;
}
