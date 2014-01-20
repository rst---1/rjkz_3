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
		if (line[:30] == "1_pvpython.py_DIRECTORY_OF_OUT"):
			DIRECTORY_OF_OUT = line[31:]
		if (line[:37] == "1_pvpython.py_TOLERANCE_OF_DELAUNAY2D"):
			TOLERANCE_OF_DELAUNAY2D = float(line[38:])
		if (line[:31] == "1_pvpython.py_DIRECTORY_OF_IN_1"):
			DIRECTORY_OF_IN_1 = line[32:]
		if (line[:31] == "1_pvpython.py_DIRECTORY_OF_IN_2"):
			DIRECTORY_OF_IN_2 = line[32:]
		if (line[:14] == "CSV_FILENAME_1"):
			CSV_FILENAME_1 = line[15:]
		if (line[:14] == "CSV_FILENAME_2"):
			CSV_FILENAME_2 = line[15:]
#---------------------------------------------------------
#DIRECTORY_OF_OUT = '/home/rst/deal.II.8.0/rjkz_3/test_of_grid/Sections'
#TOLERANCE_OF_DELAUNAY2D = 0.0
#DIRECTORY_OF_IN_1 = "/home/rst/deal.II.8.0/rjkz_3/test_of_grid/1layer 1_to_1_boxgrid.csv"

#filter "Slice"
sliceFilter_6 = Slice()
Show(sliceFilter_6)
Render()
#---------------------------------------------------------
for i_Files in range(len(Slice_x_)):
	sliceFilter_6.SliceType.Origin = [float(Slice_x_[i_Files]),0.0,0.0]
	sliceFilter_6.SliceType.Normal = [1.0,0.0,0.0]
	Render()
	writer = CreateWriter(DIRECTORY_OF_OUT + "/" + CSV_FILENAME_2 + " tau_zy x("+str(Slice_x_[i_Files])+").csv")
	writer.WriteAllTimeSteps = 1
	writer.FieldAssociation = "Points"
	writer.UpdatePipeline()
#---------------------------------------------------------
for i_Files in range(len(Slice_y_)):
	sliceFilter_6.SliceType.Origin = [0.0,float(Slice_y_[i_Files]),0.0]
	sliceFilter_6.SliceType.Normal = [0.0,1.0,0.0]
	Render()
	writer = CreateWriter(DIRECTORY_OF_OUT + "/" + CSV_FILENAME_2 + " tau_zy y("+str(Slice_y_[i_Files])+").csv")
	writer.WriteAllTimeSteps = 1
	writer.FieldAssociation = "Points"
	writer.UpdatePipeline()
#---------------------------------------------------------
#Delete filters6
Delete(sliceFilter_6)
#Delete(ClipFilter_6)
Delete(Delaunay2D_6)
Delete(TableToPoints_6)
Delete(reader_6)
