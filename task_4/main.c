#include "parse_line.h"


// Будет использован getopt_long(), так как присутствуют опции с --
int main(int argc, char **argv) {
    parse_line(argc, argv);
    return 0;
}