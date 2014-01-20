#!/usr/bin/pvpython
SETTINGS_FILE = "/home/rst/deal.II.8.0/rjkz_3/test_of_grid/Sections/0SETTINGS.txt"
#---------------------------------------------------------
with open (SETTINGS_FILE) as fd:					#open file
	t = fd.read()									#read file
	for line in t.splitlines():						#read each line
		if (line[:30] == "6_pvpython.py_DIRECTORY_OF_OUT"):
			DIRECTORY_OF_OUT = line[31:]
		if (line[:37] == "6_pvpython.py_TOLERANCE_OF_DELAUNAY2D"):
			TOLERANCE_OF_DELAUNAY2D = float(line[38:])
		if (line[:31] == "6_pvpython.py_DIRECTORY_OF_IN_1"):
			DIRECTORY_OF_IN_1 = line[32:]
		if (line[:31] == "6_pvpython.py_DIRECTORY_OF_IN_2"):
			DIRECTORY_OF_IN_2 = line[32:]
#---------------------------------------------------------
#DIRECTORY_OF_OUT = '/home/rst/deal.II.8.0/rjkz_3/test_of_grid/Sections'
#TOLERANCE_OF_DELAUNAY2D = 0.0
#DIRECTORY_OF_IN_1 = "/home/rst/deal.II.8.0/rjkz_3/test_of_grid/FU_z.csv"
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
reader_1 = CSVReader(FileName = [DIRECTORY_OF_IN_1])

#filter "Table To Points"
TableToPoints_1 = TableToPoints()
TableToPoints_1.XColumn = "Points:0"
TableToPoints_1.YColumn = "Points:1"
TableToPoints_1.ZColumn = "Points:2"
Render()

#filter "Delaunay2D"
SetActiveSource(TableToPoints_1)
Delaunay2D_1 = Delaunay2D()
Delaunay2D_1.Tolerance = TOLERANCE_OF_DELAUNAY2D
#Show()
Render()

#filter "Clip"
#ClipFilter_1_1 = Clip()
#ClipFilter_1_1.ClipType = "Sphere"
#ClipFilter_1_1.ClipType.Center = [ x_01, y_01, 0.2 ]
#ClipFilter_1_1.ClipType.Radius = RADIUS_OF_BIG_SPHERE

Show()
Render()









