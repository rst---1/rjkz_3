#!/bin/bash

# полный путь до скрипта
ABSOLUTE_FILENAME=`readlink -e "$0"`
# каталог в котором лежит скрипт
DIRECTORY=`dirname "$ABSOLUTE_FILENAME"`

stringEnd=".gpl"
stringS1="$DIRECTORY/$1$stringEnd"
stringS2="$DIRECTORY/$2$stringEnd"

if [ "$3" = "1" ]
then
	gnuplot << EOF
	set term png enhanced size 1600,1200
	set style line 1 lt 2 lw 3 lc rgb 'red'
	set style line 2 lt 2 lw 3 lc rgb 'blue'
	set style line 3 lt 2 lw 2 lc rgb 'blue'
	set style line 4 lt 2 lw 4 lc rgb 'red'
	set output "$DIRECTORY/png/$1.png"
	set size 1.0, 1.0				#соотношение сторон общего графика
	set origin 0.0, 0.0				#изменит начало координат графика. x и y даны в "экранных" координатах.

	set multiplot					#вход в режим multiplot
		#  plot №1
		set size 1.0,0.8
		set origin 0.0,0.2
		set xlabel " Y" font "Helvetica,18"
		set bmargin 4
		set ylabel "Tau_z_x" font "Helvetica,18" offset 3
		set key top right
		set grid
		plot "$stringS1" u 9:10 title "$1", "$stringS2" u 9:10 title "$2"

		#  plot №2
		set size 0.9,0.24
		set origin 0.072,0.0
		unset key
		unset xlabel
		unset ylabel
		unset title
		set border 0
		unset xtics
		unset ytics
		set parametric
		set trange [0:2*pi]
		fx(t) = 0.36*cos(t)			#функции для рисовки окружностей
		fy(t) = 0.36*sin(t)
		f_verti(t) = t / (2*pi) * 1.0 - 0.5
		f_horiz(t) = t / (2*pi) * 6.77 - 3.38
		plot fx(t), fy(t) ls 3,    0.84+fx(t), fy(t) ls 3,    -0.84+fx(t), fy(t) ls 3,    1.68+fx(t), fy(t) ls 3,\
    -1.68+fx(t), fy(t) ls 3,    2.52+fx(t), fy(t) ls 3,    -2.52+fx(t), fy(t) ls 3,    f_horiz(t), -0.5 ls 3,\
    f_horiz(t), 0.5 ls 3,    -3.38, f_verti(t) ls 3,    3.38, f_verti(t) ls 3,    f_horiz(t), -$4 ls 4
	unset multiplot
#==============================================================
EOF
elif [ "$3" = "2" ]
then
	gnuplot << EOF
	set term png enhanced size 1600,1200
	set style line 1 lt 2 lw 3 lc rgb 'red'
	set style line 2 lt 2 lw 3 lc rgb 'blue'
	set style line 3 lt 2 lw 2 lc rgb 'blue'
	set style line 4 lt 2 lw 4 lc rgb 'red'
	set output "$DIRECTORY/png/$1.png"
	set size 1.0, 1.0				#соотношение сторон общего графика
	set origin 0.0, 0.0				#изменит начало координат графика. x и y даны в "экранных" координатах.

	set multiplot					#вход в режим multiplot
		#  plot №1
		set size 1.0,0.8
		set origin 0.0,0.2
		set xlabel " X" font "Helvetica,18"
		set bmargin 4
		set ylabel "Tau_z_x" font "Helvetica,18" offset 3
		set key top right
		set grid
		plot "$stringS1" u 8:10 title "$1", "$stringS2" u 8:10 title "$2"	

		#  plot №2
		set size 0.9,0.24
		set origin 0.072,0.0
		unset key
		unset xlabel
		unset ylabel
		unset title
		set border 0
		unset xtics
		unset ytics
		set parametric
		set trange [0:2*pi]
		fx(t) = 0.36*cos(t)
		fy(t) = 0.36*sin(t)
		f_verti(t) = t / (2*pi) * 1.0 - 0.5
		f_horiz(t) = t / (2*pi) * 6.77 - 3.38
		plot fx(t), fy(t) ls 3,    0.84+fx(t), fy(t) ls 3,    -0.84+fx(t), fy(t) ls 3,    1.68+fx(t), fy(t) ls 3,\
    -1.68+fx(t), fy(t) ls 3,    2.52+fx(t), fy(t) ls 3,    -2.52+fx(t), fy(t) ls 3,    f_horiz(t), -0.5 ls 3,\
    f_horiz(t), 0.5 ls 3,    -3.38, f_verti(t) ls 3,    3.38, f_verti(t) ls 3,    -$4, f_verti(t) ls 4
	unset multiplot
#==============================================================
EOF
elif [ "$3" = "3" ]
then
	gnuplot << EOF
	set term png enhanced size 1600,1200
	set style line 1 lt 2 lw 3 lc rgb 'red'
	set style line 2 lt 2 lw 3 lc rgb 'blue'
	set style line 3 lt 2 lw 2 lc rgb 'blue'
	set style line 4 lt 2 lw 4 lc rgb 'red'
	set output "$DIRECTORY/png/$1.png"
	set size 1.0, 1.0				#соотношение сторон общего графика
	set origin 0.0, 0.0				#изменит начало координат графика. x и y даны в "экранных" координатах.

	set multiplot					#вход в режим multiplot
		#  plot №1
		set size 1.0,0.8
		set origin 0.0,0.2
		set xlabel " Y" font "Helvetica,18"
		set bmargin 4
		set ylabel "Tau_z_y" font "Helvetica,18" offset 3
		set key top right
		set grid
		plot "$stringS1" u 9:10 title "$1", "$stringS2" u 9:10 title "$2"

		#  plot №2
		set size 0.9,0.24
		set origin 0.072,0.0
		unset key
		unset xlabel
		unset ylabel
		unset title
		set border 0
		unset xtics
		unset ytics
		set parametric
		set trange [0:2*pi]
		fx(t) = 0.36*cos(t)
		fy(t) = 0.36*sin(t)
		f_verti(t) = t / (2*pi) * 1.0 - 0.5
		f_horiz(t) = t / (2*pi) * 6.77 - 3.38
		plot fx(t), fy(t) ls 3,    0.84+fx(t), fy(t) ls 3,    -0.84+fx(t), fy(t) ls 3,    1.68+fx(t), fy(t) ls 3,\
    -1.68+fx(t), fy(t) ls 3,    2.52+fx(t), fy(t) ls 3,    -2.52+fx(t), fy(t) ls 3,    f_horiz(t), -0.5 ls 3,\
    f_horiz(t), 0.5 ls 3,    -3.38, f_verti(t) ls 3,    3.38, f_verti(t) ls 3,    f_horiz(t), -$4 ls 4
	unset multiplot	
#==============================================================
EOF
elif [ "$3" = "4" ]
then
	gnuplot << EOF
	set term png enhanced size 1600,1200
	set style line 1 lt 2 lw 3 lc rgb 'red'
	set style line 2 lt 2 lw 3 lc rgb 'blue'
	set style line 3 lt 2 lw 2 lc rgb 'blue'
	set style line 4 lt 2 lw 4 lc rgb 'red'
	set output "$DIRECTORY/png/$1.png"
	set size 1.0, 1.0				#соотношение сторон общего графика
	set origin 0.0, 0.0				#изменит начало координат графика. x и y даны в "экранных" координатах.

	set multiplot					#вход в режим multiplot
		#  plot №1
		set size 1.0,0.8
		set origin 0.0,0.2
		set xlabel " X" font "Helvetica,18"
		set bmargin 4
		set ylabel "Tau_z_y" font "Helvetica,18" offset 3
		set key top right
		set grid
		plot "$stringS1" u 8:10 title "$1", "$stringS2" u 8:10 title "$2"
	
		#  plot №2
		set size 0.9,0.24
		set origin 0.072,0.0
		unset key
		unset xlabel
		unset ylabel
		unset title
		set border 0
		unset xtics
		unset ytics
		set parametric
		set trange [0:2*pi]
		fx(t) = 0.36*cos(t)
		fy(t) = 0.36*sin(t)
		f_verti(t) = t / (2*pi) * 1.0 - 0.5
		f_horiz(t) = t / (2*pi) * 6.77 - 3.38
		plot fx(t), fy(t) ls 3,    0.84+fx(t), fy(t) ls 3,    -0.84+fx(t), fy(t) ls 3,    1.68+fx(t), fy(t) ls 3,\
    -1.68+fx(t), fy(t) ls 3,    2.52+fx(t), fy(t) ls 3,    -2.52+fx(t), fy(t) ls 3,    f_horiz(t), -0.5 ls 3,\
    f_horiz(t), 0.5 ls 3,    -3.38, f_verti(t) ls 3,    3.38, f_verti(t) ls 3,    -$4, f_verti(t) ls 4
	unset multiplot	
#==============================================================
EOF
fi
