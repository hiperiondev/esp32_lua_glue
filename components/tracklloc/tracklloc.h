// https://github.com/farberbrodsky/tracklloc

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void* _TRACK_malloc(size_t size);
void* _TRACK_calloc(size_t count, size_t size);
void _TRACK_free(void *ptr);
bool _TRACK_allocated(void* ptr);
void _TRACK_log_unfreed();
