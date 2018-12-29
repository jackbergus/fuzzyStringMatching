//
// Created by giacomo on 11/12/18.
//

#include "ProgressBar.h"

ProgressBar::ProgressBar(long double max) : MAX{max}, progress{0.0}, barWidth{70} {}

void ProgressBar::update(double step) {
    int elem = int((progress / MAX) * 10000.0);
    int neu = int((step / MAX) * 10000.0);
    if (step <= MAX && elem != neu) {
        progress = step;
        std::cout << "[";
        int pos = barWidth * (progress / MAX);
        for (int i = 0; i < barWidth; ++i) {
            if (i < pos) std::cout << "=";
            else if (i == pos) std::cout << ">";
            else std::cout << " ";
        }
        std::cout << "] " << (int((progress / MAX) * 10000.0))/100.0 << " %\r";
        std::cout.flush();
        //std::cout << std::endl;
    }
}

void ProgressBar::reset() {
    progress = 0.0;
}
