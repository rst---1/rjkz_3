#!/bin/bash

# полный путь до скрипта
ABSOLUTE_FILENAME=`readlink -e "$0"`
# каталог в котором лежит скрипт
DIRECTORY=`dirname "$ABSOLUTE_FILENAME"`


"$DIRECTORY/Sections/7.py"
echo "7.py - done========================================="
"$DIRECTORY/Sections/8.sh"
echo "8.sh - done========================================="
"$DIRECTORY/Sections/9_U_z_x.py"
echo "9_U_z_x.py - done==================================="
"$DIRECTORY/Sections/9_U_z_y.py"
echo "9_U_z_x.py - done==================================="
"$DIRECTORY/Sections/10.sh"
echo "10.sh - done========================================"

