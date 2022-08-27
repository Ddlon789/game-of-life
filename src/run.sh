#!/bin/bash
echo "enter c-file without .c"
gcc "$1.c" -Wall -Werror -Wextra -o $1
