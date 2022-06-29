// https://github.com/farberbrodsky/tracklloc

#include <stddef.h>
#include <stdbool.h>

#include "tracklloc.h"

#ifndef TRACKLLOC_H
#define TRACKLLOC_H

struct malloc_tracking_t {
      void *ptr;
};
static const size_t S = sizeof(struct malloc_tracking_t);

static struct malloc_tracking_t *malloc_tracking = NULL;
static size_t malloc_tracking_length = 0;

void* _TRACK_malloc(size_t size) {
    malloc_tracking = realloc(malloc_tracking, S * (malloc_tracking_length + 1));
    void *result = malloc(size);

    malloc_tracking[malloc_tracking_length++].ptr = result;
    return result;
}

void* _TRACK_calloc(size_t count, size_t size) {
    malloc_tracking = realloc(malloc_tracking, S * (malloc_tracking_length + 1));
    void *result = calloc(count, size);

    malloc_tracking[malloc_tracking_length++].ptr = result;
    return result;
}

bool _TRACK_allocated(void* ptr) {
    bool res = false;

    for (size_t i = 0; i < malloc_tracking_length; ++i) {
            if (malloc_tracking[i].ptr == ptr) {
                res = true;
                break;
            }
    }
    return res;
}

void _TRACK_free(void *ptr) {
    // find the index for it
    for (size_t i = 0; i < malloc_tracking_length; ++i) {
        if (malloc_tracking[i].ptr == ptr) {
            free(ptr);
            // remove this from the malloc_tracking
            --malloc_tracking_length;

            for (size_t j = i; j < malloc_tracking_length; ++j) {
                malloc_tracking[j] = malloc_tracking[j + 1];
            }

            malloc_tracking = realloc(malloc_tracking, S * malloc_tracking_length);
            return;
        }
    }
    // double freed!
    fprintf(stderr, "\033[91mfreeing memory that wasn't malloc'd/double freeing: %p\033[0m\n", ptr);
    free(ptr);
}

void _TRACK_log_unfreed() {
    // print unfreed memory
    for (size_t i = 0; i < malloc_tracking_length; ++i) {
        fprintf(stderr, "\033[91munfreed memory: %p033[0m\n", malloc_tracking[i].ptr);
    }
}

#endif
