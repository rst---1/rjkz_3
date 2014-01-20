#!/usr/bin/python

import sys
DIRECTORY = sys.path[0]
FileName_gpl = DIRECTORY + "/" + sys.argv[1]
FileName_csv = FileName_gpl[:-4] + ".csv"

import os
os.rename(FileName_gpl, FileName_csv)

rst = []
rst_line = ''
FirstString = '"Points:0","Points:1","Points:2","Points:3","Points:4","Points:5","Points:6","Points:7","Points:8","Points:9"\n'
FlagOfTab = 0
FlagOfNan = 0


rst.append(FirstString)
with open (FileName_csv) as fd:						#open file
	t = fd.read()									#read the file
	for line in t.splitlines():						#read each line
		for letter in line:							#read each letter
			if (letter == 'a'):						#"nan"
				FlagOfNan = 1
			if (letter == '\t'):					#replace '\t\t' to ','
				if  (FlagOfTab == 0):
					letter = ','
					FlagOfTab = 1
					rst_line = rst_line + letter
				else:
					FlagOfTab = 0
			elif (letter != ' '):					#skip spaces ' '
				rst_line = rst_line + letter
													#rst_line = rst_line + '\n'
		if (FlagOfNan == 0):
			rst.append(rst_line + '\n')
			rst_line = ''
		else:
			FlagOfNan = 0
			rst_line = ''
with open(FileName_csv, 'w') as fd:					#write file
	fd.write(''.join(rst))
rst = []

print '.	.	.	.	.	.	SUCCESS!'
