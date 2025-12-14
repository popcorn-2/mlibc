#include <sys/handle.h>
#include <frg/string.hpp>

handle_map_t *handle_map;

unsigned long long get_handle(const char *name) {
	auto handle_data = handle_map;
	while (handle_data->name) {
		frg::string_view view{handle_map->name};
		if (view == name) {
			return handle_data->number;
		}
		handle_data++;
	}
	return (unsigned long long)-1;
}
