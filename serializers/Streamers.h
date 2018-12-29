//
// Created by giacomo on 11/12/18.
//

#ifndef INCONSISTENCY_STREAMERS_H
#define INCONSISTENCY_STREAMERS_H

#include <vector>
#include <string>
#include <ostream>
#include <fstream>
#include "commons/structure.h"

std::ostream &operator<<(std::ostream &os, const std::vector<LONG_NUMERIC> &vec);
std::ostream &operator<<(std::ostream &os, const std::vector<double> &vec);
std::ostream &operator<<(std::ostream &os, const std::vector<std::string> &vec);

#endif //INCONSISTENCY_STREAMERS_H
