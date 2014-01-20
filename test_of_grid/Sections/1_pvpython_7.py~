#!/usr/bin/pvpython
SETTINGS_FILE = "/home/rst/deal.II.8.0/rjkz_3/test_of_grid/Sections/0SETTINGS.txt"
#---------------------------------------------------------
with open (SETTINGS_FILE) as fd:					#open file
	t = fd.read()									#read file
	for line in t.splitlines():						#read each line
		if (line[:30] == "1_pvpython.py_DIRECTORY_OF_OUT"):
			DIRECTORY_OF_OUT = line[31:]
		if (line[:37] == "1_pvpython.py_TOLERANCE_OF_DELAUNAY2D"):
			TOLERANCE_OF_DELAUNAY2D = float(line[38:])
		if (line[:31] == "1_pvpython.py_DIRECTORY_OF_IN_1"):
			DIRECTORY_OF_IN_1 = line[32:]
		if (line[:31] == "1_pvpython.py_DIRECTORY_OF_IN_2"):
			DIRECTORY_OF_IN_2 = line[32:]
#---------------------------------------------------------
#DIRECTORY_OF_OUT = '/home/rst/deal.II.8.0/rjkz_3/test_of_grid/Sections'
#TOLERANCE_OF_DELAUNAY2D = 0.0
#DIRECTORY_OF_IN_1 = "/home/rst/deal.II.8.0/rjkz_3/test_of_grid/1layer 1_to_1_boxgrid.csv"
RADIUS_OF_BIG_SPHERE = 0.375
x_01 = 0.0
y_01 = 0.0
x_02 = 0.0
y_02 = 0.84091
x_03 = 0.0
y_03 = -0.8491
x_04 = 0.0
y_04 = 1.68182
x_05 = 0.0
y_05 = -1.68182
x_06 = 0.0
y_06 = 2.52272
x_07 = 0.0
y_07 = -2.52272


#open file
from paraview.simple import *
reader_6 = CSVReader(FileName = [DIRECTORY_OF_IN_2])

#filter "Table To Points"
TableToPoints_6 = TableToPoints()
TableToPoints_6.XColumn = "Points:0"
TableToPoints_6.YColumn = "Points:1"
TableToPoints_6.ZColumn = "Points:3"
Render()

#filter "Delaunay2D"
SetActiveSource(TableToPoints_6)
Delaunay2D_6 = Delaunay2D()
Delaunay2D_6.Tolerance = TOLERANCE_OF_DELAUNAY2D
#Show()
Render()

#filter "Clip"
ClipFilter_1_1 = Clip()
ClipFilter_1_1.ClipType = "Sphere"
ClipFilter_1_1.ClipType.Center = [ x_01, y_01, 0.2 ]
ClipFilter_1_1.ClipType.Radius = RADIUS_OF_BIG_SPHERE

ClipFilter_1_2 = Clip()
ClipFilter_1_2.ClipType = "Sphere"
ClipFilter_1_2.ClipType.Center = [ x_01, y_01, 0.1 ]
ClipFilter_1_2.ClipType.Radius = RADIUS_OF_BIG_SPHERE

ClipFilter_1_3 = Clip()
ClipFilter_1_3.ClipType = "Sphere"
ClipFilter_1_3.ClipType.Center = [ x_01, y_01, 0.0 ]
ClipFilter_1_3.ClipType.Radius = RADIUS_OF_BIG_SPHERE

ClipFilter_1_4 = Clip()
ClipFilter_1_4.ClipType = "Sphere"
ClipFilter_1_4.ClipType.Center = [ x_01, y_01, -0.1 ]
ClipFilter_1_4.ClipType.Radius = RADIUS_OF_BIG_SPHERE

ClipFilter_1_5 = Clip()
ClipFilter_1_5.ClipType = "Sphere"
ClipFilter_1_5.ClipType.Center = [ x_01, y_01, -0.2 ]
ClipFilter_1_5.ClipType.Radius = RADIUS_OF_BIG_SPHERE

ClipFilter_1_6 = Clip()
ClipFilter_1_6.ClipType = "Sphere"
ClipFilter_1_6.ClipType.Center = [ x_01, y_01, -0.3 ]
ClipFilter_1_6.ClipType.Radius = RADIUS_OF_BIG_SPHERE

ClipFilter_1_7 = Clip()
ClipFilter_1_7.ClipType = "Sphere"
ClipFilter_1_7.ClipType.Center = [ x_01, y_01, -0.4 ]
ClipFilter_1_7.ClipType.Radius = RADIUS_OF_BIG_SPHERE

ClipFilter_1_8 = Clip()
ClipFilter_1_8.ClipType = "Sphere"
ClipFilter_1_8.ClipType.Center = [ x_01, y_01, -0.5 ]
ClipFilter_1_8.ClipType.Radius = RADIUS_OF_BIG_SPHERE
#----------------------------------------------------

#filter "Clip"
ClipFilter_2_1 = Clip()
ClipFilter_2_1.ClipType = "Sphere"
ClipFilter_2_1.ClipType.Center = [ x_02, y_02, 0.2 ]
ClipFilter_2_1.ClipType.Radius = RADIUS_OF_BIG_SPHERE

ClipFilter_2_2 = Clip()
ClipFilter_2_2.ClipType = "Sphere"
ClipFilter_2_2.ClipType.Center = [ x_02, y_02, 0.1 ]
ClipFilter_2_2.ClipType.Radius = RADIUS_OF_BIG_SPHERE

ClipFilter_2_3 = Clip()
ClipFilter_2_3.ClipType = "Sphere"
ClipFilter_2_3.ClipType.Center = [ x_02, y_02, 0.0 ]
ClipFilter_2_3.ClipType.Radius = RADIUS_OF_BIG_SPHERE

ClipFilter_2_4 = Clip()
ClipFilter_2_4.ClipType = "Sphere"
ClipFilter_2_4.ClipType.Center = [ x_02, y_02, -0.1 ]
ClipFilter_2_4.ClipType.Radius = RADIUS_OF_BIG_SPHERE

ClipFilter_2_5 = Clip()
ClipFilter_2_5.ClipType = "Sphere"
ClipFilter_2_5.ClipType.Center = [ x_02, y_02, -0.2 ]
ClipFilter_2_5.ClipType.Radius = RADIUS_OF_BIG_SPHERE

ClipFilter_2_6 = Clip()
ClipFilter_2_6.ClipType = "Sphere"
ClipFilter_2_6.ClipType.Center = [ x_02, y_02, -0.3 ]
ClipFilter_2_6.ClipType.Radius = RADIUS_OF_BIG_SPHERE

ClipFilter_2_7 = Clip()
ClipFilter_2_7.ClipType = "Sphere"
ClipFilter_2_7.ClipType.Center = [ x_02, y_02, -0.4 ]
ClipFilter_2_7.ClipType.Radius = RADIUS_OF_BIG_SPHERE

ClipFilter_2_8 = Clip()
ClipFilter_2_8.ClipType = "Sphere"
ClipFilter_2_8.ClipType.Center = [ x_02, y_02, -0.5 ]
ClipFilter_2_8.ClipType.Radius = RADIUS_OF_BIG_SPHERE

#----------------------------------------------------

#filter "Clip"

ClipFilter_3_1 = Clip()
ClipFilter_3_1.ClipType = "Sphere"
ClipFilter_3_1.ClipType.Center = [ x_03, y_03, 0.2 ]
ClipFilter_3_1.ClipType.Radius = RADIUS_OF_BIG_SPHERE

ClipFilter_3_2 = Clip()
ClipFilter_3_2.ClipType = "Sphere"
ClipFilter_3_2.ClipType.Center = [ x_03, y_03, 0.1 ]
ClipFilter_3_2.ClipType.Radius = RADIUS_OF_BIG_SPHERE

ClipFilter_3_3 = Clip()
ClipFilter_3_3.ClipType = "Sphere"
ClipFilter_3_3.ClipType.Center = [ x_03, y_03, 0.0 ]
ClipFilter_3_3.ClipType.Radius = RADIUS_OF_BIG_SPHERE

ClipFilter_3_4 = Clip()
ClipFilter_3_4.ClipType = "Sphere"
ClipFilter_3_4.ClipType.Center = [ x_03, y_03, -0.1 ]
ClipFilter_3_4.ClipType.Radius = RADIUS_OF_BIG_SPHERE

ClipFilter_3_5 = Clip()
ClipFilter_3_5.ClipType = "Sphere"
ClipFilter_3_5.ClipType.Center = [ x_03, y_03, -0.2 ]
ClipFilter_3_5.ClipType.Radius = RADIUS_OF_BIG_SPHERE

ClipFilter_3_6 = Clip()
ClipFilter_3_6.ClipType = "Sphere"
ClipFilter_3_6.ClipType.Center = [ x_03, y_03, -0.3 ]
ClipFilter_3_6.ClipType.Radius = RADIUS_OF_BIG_SPHERE

ClipFilter_3_7 = Clip()
ClipFilter_3_7.ClipType = "Sphere"
ClipFilter_3_7.ClipType.Center = [ x_03, y_03, -0.4 ]
ClipFilter_3_7.ClipType.Radius = RADIUS_OF_BIG_SPHERE

ClipFilter_3_8 = Clip()
ClipFilter_3_8.ClipType = "Sphere"
ClipFilter_3_8.ClipType.Center = [ x_03, y_03, -0.5 ]
ClipFilter_3_8.ClipType.Radius = RADIUS_OF_BIG_SPHERE

#----------------------------------------------------

#filter "Clip"

ClipFilter_4_1 = Clip()
ClipFilter_4_1.ClipType = "Sphere"
ClipFilter_4_1.ClipType.Center = [ x_04, y_04, 0.2 ]
ClipFilter_4_1.ClipType.Radius = RADIUS_OF_BIG_SPHERE

ClipFilter_4_2 = Clip()
ClipFilter_4_2.ClipType = "Sphere"
ClipFilter_4_2.ClipType.Center = [ x_04, y_04, 0.1 ]
ClipFilter_4_2.ClipType.Radius = RADIUS_OF_BIG_SPHERE

ClipFilter_4_3 = Clip()
ClipFilter_4_3.ClipType = "Sphere"
ClipFilter_4_3.ClipType.Center = [ x_04, y_04, 0.0 ]
ClipFilter_4_3.ClipType.Radius = RADIUS_OF_BIG_SPHERE

ClipFilter_4_4 = Clip()
ClipFilter_4_4.ClipType = "Sphere"
ClipFilter_4_4.ClipType.Center = [ x_04, y_04, -0.1 ]
ClipFilter_4_4.ClipType.Radius = RADIUS_OF_BIG_SPHERE

ClipFilter_4_5 = Clip()
ClipFilter_4_5.ClipType = "Sphere"
ClipFilter_4_5.ClipType.Center = [ x_04, y_04, -0.2 ]
ClipFilter_4_5.ClipType.Radius = RADIUS_OF_BIG_SPHERE

ClipFilter_4_6 = Clip()
ClipFilter_4_6.ClipType = "Sphere"
ClipFilter_4_6.ClipType.Center = [ x_04, y_04, -0.3 ]
ClipFilter_4_6.ClipType.Radius = RADIUS_OF_BIG_SPHERE

ClipFilter_4_7 = Clip()
ClipFilter_4_7.ClipType = "Sphere"
ClipFilter_4_7.ClipType.Center = [ x_04, y_04, -0.4 ]
ClipFilter_4_7.ClipType.Radius = RADIUS_OF_BIG_SPHERE

ClipFilter_4_8 = Clip()
ClipFilter_4_8.ClipType = "Sphere"
ClipFilter_4_8.ClipType.Center = [ x_04, y_04, -0.5 ]
ClipFilter_4_8.ClipType.Radius = RADIUS_OF_BIG_SPHERE

#----------------------------------------------------

#filter "Clip"

ClipFilter_5_1 = Clip()
ClipFilter_5_1.ClipType = "Sphere"
ClipFilter_5_1.ClipType.Center = [ x_05, y_05, 0.2 ]
ClipFilter_5_1.ClipType.Radius = RADIUS_OF_BIG_SPHERE

ClipFilter_5_2 = Clip()
ClipFilter_5_2.ClipType = "Sphere"
ClipFilter_5_2.ClipType.Center = [ x_05, y_05, 0.1 ]
ClipFilter_5_2.ClipType.Radius = RADIUS_OF_BIG_SPHERE

ClipFilter_5_3 = Clip()
ClipFilter_5_3.ClipType = "Sphere"
ClipFilter_5_3.ClipType.Center = [ x_05, y_05, 0.0 ]
ClipFilter_5_3.ClipType.Radius = RADIUS_OF_BIG_SPHERE

ClipFilter_5_4 = Clip()
ClipFilter_5_4.ClipType = "Sphere"
ClipFilter_5_4.ClipType.Center = [ x_05, y_05, -0.1 ]
ClipFilter_5_4.ClipType.Radius = RADIUS_OF_BIG_SPHERE

ClipFilter_5_5 = Clip()
ClipFilter_5_5.ClipType = "Sphere"
ClipFilter_5_5.ClipType.Center = [ x_05, y_05, -0.2 ]
ClipFilter_5_5.ClipType.Radius = RADIUS_OF_BIG_SPHERE

ClipFilter_5_6 = Clip()
ClipFilter_5_6.ClipType = "Sphere"
ClipFilter_5_6.ClipType.Center = [ x_05, y_05, -0.3 ]
ClipFilter_5_6.ClipType.Radius = RADIUS_OF_BIG_SPHERE

ClipFilter_5_7 = Clip()
ClipFilter_5_7.ClipType = "Sphere"
ClipFilter_5_7.ClipType.Center = [ x_05, y_05, -0.4 ]
ClipFilter_5_7.ClipType.Radius = RADIUS_OF_BIG_SPHERE

ClipFilter_5_8 = Clip()
ClipFilter_5_8.ClipType = "Sphere"
ClipFilter_5_8.ClipType.Center = [ x_05, y_05, -0.5 ]
ClipFilter_5_8.ClipType.Radius = RADIUS_OF_BIG_SPHERE

#----------------------------------------------------

#filter "Clip"

ClipFilter_6_1 = Clip()
ClipFilter_6_1.ClipType = "Sphere"
ClipFilter_6_1.ClipType.Center = [ x_06, y_06, 0.2 ]
ClipFilter_6_1.ClipType.Radius = RADIUS_OF_BIG_SPHERE

ClipFilter_6_2 = Clip()
ClipFilter_6_2.ClipType = "Sphere"
ClipFilter_6_2.ClipType.Center = [ x_06, y_06, 0.1 ]
ClipFilter_6_2.ClipType.Radius = RADIUS_OF_BIG_SPHERE

ClipFilter_6_3 = Clip()
ClipFilter_6_3.ClipType = "Sphere"
ClipFilter_6_3.ClipType.Center = [ x_06, y_06, 0.0 ]
ClipFilter_6_3.ClipType.Radius = RADIUS_OF_BIG_SPHERE

ClipFilter_6_4 = Clip()
ClipFilter_6_4.ClipType = "Sphere"
ClipFilter_6_4.ClipType.Center = [ x_06, y_06, -0.1 ]
ClipFilter_6_4.ClipType.Radius = RADIUS_OF_BIG_SPHERE

ClipFilter_6_5 = Clip()
ClipFilter_6_5.ClipType = "Sphere"
ClipFilter_6_5.ClipType.Center = [ x_06, y_06, -0.2 ]
ClipFilter_6_5.ClipType.Radius = RADIUS_OF_BIG_SPHERE

ClipFilter_6_6 = Clip()
ClipFilter_6_6.ClipType = "Sphere"
ClipFilter_6_6.ClipType.Center = [ x_06, y_06, -0.3 ]
ClipFilter_6_6.ClipType.Radius = RADIUS_OF_BIG_SPHERE

ClipFilter_6_7 = Clip()
ClipFilter_6_7.ClipType = "Sphere"
ClipFilter_6_7.ClipType.Center = [ x_06, y_06, -0.4 ]
ClipFilter_6_7.ClipType.Radius = RADIUS_OF_BIG_SPHERE

ClipFilter_6_8 = Clip()
ClipFilter_6_8.ClipType = "Sphere"
ClipFilter_6_8.ClipType.Center = [ x_06, y_06, -0.5 ]
ClipFilter_6_8.ClipType.Radius = RADIUS_OF_BIG_SPHERE

#----------------------------------------------------

#filter "Clip"

ClipFilter_7_1 = Clip()
ClipFilter_7_1.ClipType = "Sphere"
ClipFilter_7_1.ClipType.Center = [ x_07, y_07, 0.2 ]
ClipFilter_7_1.ClipType.Radius = RADIUS_OF_BIG_SPHERE

ClipFilter_7_2 = Clip()
ClipFilter_7_2.ClipType = "Sphere"
ClipFilter_7_2.ClipType.Center = [ x_07, y_07, 0.1 ]
ClipFilter_7_2.ClipType.Radius = RADIUS_OF_BIG_SPHERE

ClipFilter_7_3 = Clip()
ClipFilter_7_3.ClipType = "Sphere"
ClipFilter_7_3.ClipType.Center = [ x_07, y_07, 0.0 ]
ClipFilter_7_3.ClipType.Radius = RADIUS_OF_BIG_SPHERE

ClipFilter_7_4 = Clip()
ClipFilter_7_4.ClipType = "Sphere"
ClipFilter_7_4.ClipType.Center = [ x_07, y_07, -0.1 ]
ClipFilter_7_4.ClipType.Radius = RADIUS_OF_BIG_SPHERE

ClipFilter_7_5 = Clip()
ClipFilter_7_5.ClipType = "Sphere"
ClipFilter_7_5.ClipType.Center = [ x_07, y_07, -0.2 ]
ClipFilter_7_5.ClipType.Radius = RADIUS_OF_BIG_SPHERE

ClipFilter_7_6 = Clip()
ClipFilter_7_6.ClipType = "Sphere"
ClipFilter_7_6.ClipType.Center = [ x_07, y_07, -0.3 ]
ClipFilter_7_6.ClipType.Radius = RADIUS_OF_BIG_SPHERE

ClipFilter_7_7 = Clip()
ClipFilter_7_7.ClipType = "Sphere"
ClipFilter_7_7.ClipType.Center = [ x_07, y_07, -0.4 ]
ClipFilter_7_7.ClipType.Radius = RADIUS_OF_BIG_SPHERE

ClipFilter_7_8 = Clip()
ClipFilter_7_8.ClipType = "Sphere"
ClipFilter_7_8.ClipType.Center = [ x_07, y_07, -0.5 ]
ClipFilter_7_8.ClipType.Radius = RADIUS_OF_BIG_SPHERE

Show()
Render()




