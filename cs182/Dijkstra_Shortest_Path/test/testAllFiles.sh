#!/bin/bash
#Note: This file has unix line endings, and must only be opened in a linux editor,
#such as emacs/vim, or in a program that supports line ending conversions (notepad++)

baseName=dijkstra

# if you make any other files, include them here, but don't include test.cpp
g++ test.cpp minprio.cpp graph.cpp graphio.c dijkstra.cpp dfs.cpp topocycle.cpp -o "${baseName}" 
if [ $? -ne 0 ]; then
	echo "Program Did Not Compile"
else
	for f in ./*.txt
	do
		./"${baseName}" "$f"
	done
fi