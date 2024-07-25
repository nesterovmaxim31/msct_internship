#pragma once

#include <stdlib.h>
#include <string.h>

#include "secondary_functions.h"

void sort_array(long* source_array, long* supporting_array, size_t size_of_array);
void comparator(long* source_array, long* supporting_array, size_t last_index, size_t left_index, size_t right_index);