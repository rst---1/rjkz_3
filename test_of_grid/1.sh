#!/bin/bash

# полный путь до скрипта
ABSOLUTE_FILENAME=`readlink -e "$0"`
# каталог в котором лежит скрипт
DIRECTORY=`dirname "$ABSOLUTE_FILENAME"`


#"$DIRECTORY/converter_gpl_to_csv.py" "1layer 1_to_1_boxgrid.gpl" 
#"$DIRECTORY/converter_gpl_to_csv.py" "FU_z.gpl" 
cd "$DIRECTORY/Sections"
rm *.gpl
rm *.csv
cd "$DIRECTORY/Sections/png"
rm *.png
cd "$DIRECTORY/Sections/errors"
rm *.png

