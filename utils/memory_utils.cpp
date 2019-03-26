//
// Created by giacomo on 31/12/18.
//

#include "memory_utils.h"
#include <sys/sysinfo.h>

unsigned long get_ram_avail_bytes() {
    struct sysinfo myinfo{};
    unsigned long total_bytes;
    sysinfo(&myinfo);
    return myinfo.mem_unit * myinfo.totalram;
}
