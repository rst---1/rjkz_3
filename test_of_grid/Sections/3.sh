#!/bin/bash

# полный путь до скрипта
ABSOLUTE_FILENAME=`readlink -e "$0"`
# каталог в котором лежит скрипт
DIRECTORY=`dirname "$ABSOLUTE_FILENAME"`

number_x=0
number_y=0
while read myline
do
#-----------------------------------------------------Find Slice_x
	if [ "${myline:0:7}" = "Slice_x" ]
	then
		Slice_x_[$number_x]="${myline:8:8}"
		let "number_x += 1"
	fi
#-----------------------------------------------------Find Slice_y
	if [ "${myline:0:7}" = "Slice_y" ]
	then
		Slice_y_[$number_y]="${myline:8:8}"
		let "number_y += 1"
	fi
#-----------------------------------------------------Find Name of files
	if [ "${myline:0:14}" = "CSV_FILENAME_1" ]
	then
		CSV_FILENAME_1="${myline:15:50}"
	fi
#-----------------------------------------------------Find Name of files
	if [ "${myline:0:14}" = "CSV_FILENAME_2" ]
	then
		CSV_FILENAME_2="${myline:15:50}"
	fi
#-----------------------------------------------------
done < "$DIRECTORY/0SETTINGS.txt"
echo "number_x = "$number_x
echo "number_y = "$number_y
echo "CSV_FILENAME_1 = "$CSV_FILENAME_1
echo "CSV_FILENAME_2 = "$CSV_FILENAME_2

#=========================================================================================


#координаты сечений функций Tau_zx по x
number=0
while (let "number<number_x")
do
	A_Tau_zx_x_[$number]="$CSV_FILENAME_1 tau_zx x(${Slice_x_[$number]})"
	D_Tau_zx_x_[$number]="$CSV_FILENAME_2 tau_zx x(${Slice_x_[$number]})"
	let "number += 1"
done

#координаты сечений функций Tau_zx по y
number=0
while (let "number<number_y")
do
	A_Tau_zx_y_[$number]="$CSV_FILENAME_1 tau_zx y(${Slice_y_[$number]})"
	D_Tau_zx_y_[$number]="$CSV_FILENAME_2 tau_zx y(${Slice_y_[$number]})"
	let "number += 1"
done

#координаты сечений функций Tau_zy по x
number=0
while (let "number<number_x")
do
	A_Tau_zy_x_[$number]="$CSV_FILENAME_1 tau_zy x(${Slice_x_[$number]})"
	D_Tau_zy_x_[$number]="$CSV_FILENAME_2 tau_zy x(${Slice_x_[$number]})"
	let "number += 1"
done

#координаты сечений функций Tau_zy по y
number=0
while (let "number<number_y")
do
	A_Tau_zy_y_[$number]="$CSV_FILENAME_1 tau_zy y(${Slice_y_[$number]})"
	D_Tau_zy_y_[$number]="$CSV_FILENAME_2 tau_zy y(${Slice_y_[$number]})"
	let "number += 1"
done



#=========================================================================================
#Вызовы скриптов для создания графиков в gnuplot'е
#-------------------------------------------------------------------------
#создание графика, содержащего сечения функции Tau_zx на разных координатах x
#"адрес скрипта" параметр1 параметр2 параметр3
#	параметр1 - передача файла 1 вида "CurveGrid tau_zx x=0.00000000.gpl" - сечение из deal.II
#	параметр2 - передача файла 4 вида "CurveGrid_Analytic tau_zx x(0.0).gpl" - сечение из deal.II
#	параметр3 - параметр, описывающий класс сечения
#			параметр3 = "1" - для tau_zx x
#			параметр3 = "2" - для tau_zx y
#			параметр3 = "3" - для tau_zy x
#			параметр3 = "4" - для tau_zy y
#			параметр4 = передаёт координату по которой строится сечение

number=0
while (let "number<number_x")
do
	"$DIRECTORY/3_.sh" "${A_Tau_zx_x_[$number]}" "${D_Tau_zx_x_[$number]}" "1" ${Slice_x_[$number]}
	let "number += 1"
done

number=0
while (let "number<number_y")
do
	"$DIRECTORY/3_.sh" "${A_Tau_zx_y_[$number]}" "${D_Tau_zx_y_[$number]}" "2" ${Slice_y_[$number]}
	let "number += 1"
done

number=0
while (let "number<number_x")
do
	"$DIRECTORY/3_.sh" "${A_Tau_zy_x_[$number]}" "${D_Tau_zy_x_[$number]}" "3" ${Slice_x_[$number]}
	let "number += 1"
done

number=0
while (let "number<number_y")
do
	"$DIRECTORY/3_.sh" "${A_Tau_zy_y_[$number]}" "${D_Tau_zy_y_[$number]}" "4" ${Slice_y_[$number]}
	let "number += 1"
done


