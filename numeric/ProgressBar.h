//
// Created by giacomo on 11/12/18.
//

#ifndef INCONSISTENCY_PROGRESSBAR_H
#define INCONSISTENCY_PROGRESSBAR_H

#include <iostream>

class ProgressBar {

    long double progress, MAX;
    int barWidth;

public:
    ProgressBar(long double max);
    void update(double step);

    void reset();
};


#endif //INCONSISTENCY_PROGRESSBAR_H
