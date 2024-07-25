#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int change_get_current_status(int status);

void sigint_hnd();