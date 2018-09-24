/*
 * compares.h
 * This file is part of graphSampler
 *
 * Copyright (C) 2017 - Giacomo Bergami
 * Created by Giacomo Bergami on 18/08/16.
 *
 * graphSampler is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * graphSampler is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with graphSampler. If not, see <http://www.gnu.org/licenses/>.
 */



#pragma once

#ifdef __cplusplus
extern "C" {
#endif
void compareU_Int(unsigned int left, unsigned int right, int *toret);
void  compareUL_Int(unsigned long, unsigned long, int *);
void pairCompare(std::pair<unsigned long, unsigned long> left, std::pair<unsigned long, unsigned long> right, int *toret);
#ifdef __cplusplus
}
#endif

