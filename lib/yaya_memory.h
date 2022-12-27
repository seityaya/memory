//Author                 : Seityagiya Terlekchi
//Contacts               : seityaya@ukr.net
//Creation Date          : 2022.12
//License Link           : https://spdx.org/licenses/LGPL-2.1-or-later.html
//SPDX-License-Identifier: LGPL-2.1-or-later
//Copyright © 2022-2022 Seityagiya Terlekchi. All rights reserved.

#ifndef YAYA_MEMORY_H
#define YAYA_MEMORY_H

#include "stdint.h"
#include "stdbool.h"
#include "stdlib.h"

#ifndef USE_MEMORY_STATS
#define USE_MEMORY_STATS 1
#endif

#if USE_MEMORY_STATS
#define mem_new(S, N, O, s) yaya_memory_new((S), (void**)(N), (void*)(O), (s))
#define mem_del(S, N)       yaya_memory_del((S), (void**)(N))
#else
#define mem_new(N, O, s) memory_new(NULL, (void**)(N), (void*)(O), (s))
#define mem_del(N)       memory_del(NULL, (void**)(N))
#endif

#define mem_size(P)      memory_size((void*)(P))

typedef struct mem_stats_t {
    size_t memory_request;    //запросил
    size_t memory_produce;    //выдали
    size_t memory_release;    //освободили
    intmax_t memory_call_new; //фактически выдано
    intmax_t memory_call_res; //фактически перераспределено
    intmax_t memory_call_del; //фактически удалено
}mem_stats_t;

typedef struct mem_info_t {
    size_t memory_request;
    size_t memory_produce;
    int8_t memory_ptr[];
}mem_info_t;

#if USE_MEMORY_STATS
bool memory_stats_init(mem_stats_t **mem_stats);
bool memory_stats_free(mem_stats_t **mem_stats);
bool memory_stats_print(mem_stats_t *mem_stats);
#else
#define memory_stats_init(A) true
#define memory_stats_free(A) true
#define memory_stats_print(A) true
#endif

bool   memory_new(mem_stats_t *mem_stats, void **ptr, void *old_ptr, const size_t new_size_len);
bool   memory_del(mem_stats_t *mem_stats, void **ptr);
size_t memory_size(void *ptr);
bool  memory_dump_(void *ptr, size_t len, uint catbyte, uint column, bool ascii);

#define memory_dump(a) memory_dump_( a, 0, 1, 16, 0)
#endif // YAYA_MEMORY_H