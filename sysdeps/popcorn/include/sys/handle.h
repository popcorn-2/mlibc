#ifndef _POPCORN_HANDLE_MAP_H
#define _POPCORN_HANDLE_MAP_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
	const char *name;
	unsigned long long number;
} handle_map_t;

extern handle_map_t *handle_map;

unsigned long long get_handle(const char *name);

#ifdef __cplusplus
}
#endif

#endif
