//
// Created by giacomo on 31/12/18.
//

#ifndef INCONSISTENCY_MEMORY_UTILS_H
#define INCONSISTENCY_MEMORY_UTILS_H

/**
 * This function provides a real-time result on which is the available RAM memory.
 * This must be used to check whether we can allocate a file in primary memory or not.
 *
 * @return
 */
unsigned long get_ram_avail_bytes();

#endif //INCONSISTENCY_MEMORY_UTILS_H
