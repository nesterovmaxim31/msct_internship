#pragma once

#include <math.h>
#include <string.h>

#include "parse_core.h"


int **generate_truth_table();

int* get_expression_values(obj_t* current_obj, int** truth_table);

void output_answer(int* variable_values, int** truth_table);
void handle_expression(obj_t* expr);