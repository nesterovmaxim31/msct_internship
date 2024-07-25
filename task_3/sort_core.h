#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "compare_func.h"


void sort_file(const char* source_file, const char* target_file, const char* proposed_sort_method);