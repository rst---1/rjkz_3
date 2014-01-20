#!/usr/bin/pvpython
SETTINGS_FILE = "/home/rst/deal.II.8.0/rjkz_3/test_of_grid/Sections/0SETTINGS.txt"
#---------------------------------------------------------
Slice_x_ = []										#SLICES
Slice_y_ = []
with open (SETTINGS_FILE) as fd:					#open file
	t = fd.read()									#read file
	for line in t.splitlines():						#read each line
		if (line[:7] == "Slice_x"):
			Slice_x_.append( line[8:] )
		if (line[:7] == "Slice_y"):
			Slice_y_.append( line[8:] )
		if (line[:30] == "6_pvpython.py_DIRECTORY_OF_OUT"):
			DIRECTORY_OF_OUT = line[31:]
		if (line[:37] == "6_pvpython.py_TOLERANCE_OF_DELAUNAY2D"):
			TOLERANCE_OF_DELAUNAY2D = float(line[38:])
		if (line[:31] == "6_pvpython.py_DIRECTORY_OF_IN_1"):
			DIRECTORY_OF_IN_1 = line[32:]
		if (line[:31] == "6_pvpython.py_DIRECTORY_OF_IN_2"):
			DIRECTORY_OF_IN_2 = line[32:]
		if (line[:18] == "CSV_U_z_FILENAME_1"):
			CSV_U_z_FILENAME_1 = line[19:]
		if (line[:18] == "CSV_U_z_FILENAME_2"):
			CSV_U_z_FILENAME_2 = line[19:]
#---------------------------------------------------------
#DIRECTORY_OF_OUT = '/home/rst/deal.II.8.0/rjkz_3/test_of_grid/Sections'
#TOLERANCE_OF_DELAUNAY2D = 0.0
#DIRECTORY_OF_IN_1 = "/home/rst/deal.II.8.0/rjkz_3/test_of_grid/FU_z.csv"


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
Show()
Render()

#filter "Clip"
#ClipFilter_1 = Clip()
#ClipFilter_1.ClipType = "Box"
#ClipFilter_1.ClipType.Scale = [ 0.414, 0.414, 2.0 ]
#Render()

#filter "Slice"
sliceFilter_1 = Slice()
Show(sliceFilter_1)
Render()
#---------------------------------------------------------
for i_Files in range(len(Slice_x_)):
	sliceFilter_1.SliceType.Origin = [float(Slice_x_[i_Files]),0.0,0.0]
	sliceFilter_1.SliceType.Normal = [1.0,0.0,0.0]
	#Render()
	writer = CreateWriter(DIRECTORY_OF_OUT + "/" + CSV_U_z_FILENAME_1 + " U_z x("+str(Slice_x_[i_Files])+").csv")
	writer.WriteAllTimeSteps = 1
	writer.FieldAssociation = "Points"
	writer.UpdatePipeline()
#---------------------------------------------------------
for i_Files in range(len(Slice_y_)):
	sliceFilter_1.SliceType.Origin = [0.0,float(Slice_y_[i_Files]),0.0]
	sliceFilter_1.SliceType.Normal = [0.0,1.0,0.0]
	#Render()
	writer = CreateWriter(DIRECTORY_OF_OUT + "/" + CSV_U_z_FILENAME_1 + " U_z y("+str(Slice_y_[i_Files])+").csv")
	writer.WriteAllTimeSteps = 1
	writer.FieldAssociation = "Points"
	writer.UpdatePipeline()
#---------------------------------------------------------
#Delete filters1
Delete(sliceFilter_1)
#Delete(ClipFilter_1)
Delete(Delaunay2D_1)
Delete(TableToPoints_1)
Delete(reader_1)







#open file
from paraview.simple import *
reader_2 = CSVReader(FileName = [DIRECTORY_OF_IN_2])

#filter "Table To Points"
TableToPoints_2 = TableToPoints()
TableToPoints_2.XColumn = "Points:0"
TableToPoints_2.YColumn = "Points:1"
TableToPoints_2.ZColumn = "Points:2"
Render()

#filter "Delaunay2D"
SetActiveSource(TableToPoints_2)
Delaunay2D_2 = Delaunay2D()
Delaunay2D_2.Tolerance = TOLERANCE_OF_DELAUNAY2D
Show()
Render()

#filter "Clip"
ClipFilter_2 = Clip()
ClipFilter_2.ClipType = "Box"
ClipFilter_2.ClipType.Scale = [ 0.414, 0.414, 2.0 ]
Render()

#filter "Slice"
sliceFilter_2 = Slice()
Show(sliceFilter_2)
Render
#---------------------------------------------------------
for i_Files in range(len(Slice_x_)):
	sliceFilter_2.SliceType.Origin = [float(Slice_x_[i_Files]),0.0,0.0]
	sliceFilter_2.SliceType.Normal = [1.0,0.0,0.0]
	#Render()
	writer = CreateWriter(DIRECTORY_OF_OUT + "/" + CSV_U_z_FILENAME_2 + " U_z x("+str(Slice_x_[i_Files])+").csv")
	writer.WriteAllTimeSteps = 1
	writer.FieldAssociation = "Points"
	writer.UpdatePipeline()
#---------------------------------------------------------
for i_Files in range(len(Slice_y_)):
	sliceFilter_2.SliceType.Origin = [0.0,float(Slice_y_[i_Files]),0.0]
	sliceFilter_2.SliceType.Normal = [0.0,1.0,0.0]
	#Render()
	writer = CreateWriter(DIRECTORY_OF_OUT + "/" + CSV_U_z_FILENAME_2 + " U_z y("+str(Slice_y_[i_Files])+").csv")
	writer.WriteAllTimeSteps = 1
	writer.FieldAssociation = "Points"
	writer.UpdatePipeline()
#---------------------------------------------------------
#Delete filters2
Delete(sliceFilter_2)
Delete(ClipFilter_2)
Delete(Delaunay2D_2)
Delete(TableToPoints_2)
Delete(reader_2)






