
## KDTree Library for C++

This repo provides C++ library for using KDTree datastructure for orthogonal range searching, circle queries, nearest neighbor search queries etc.

Functions provided by the library:
<pre>
1. isPresent() : It is used to verify if a given point exists within an input set or not
2. rectangle_query() : Used to report all the points present within the query rectangle specified by two points.
3. rectangle_count() : used to give the count of all the points present within query rectangle.
4. circle_query() : used to report all points present within given circle represented by point and radius.
5. circle_count() : used to report the count of all the points present within circle.
6. nearest() : point nearest to given point.
</pre>

### Instructions for running the project

To Run the complete project just run command : sh run.sh

1. ***Test folder*** : Input testcases and corresponding output files
2. ***./generate*** <inputsize> : this will generate random input pts in file inputfile.txt
3. ***./main*** <inputfile>     : will take input from the inputfile

4.Files:
* generate.cpp - generates random input and stores in inputfile.txt
* kdtree.h - kdtree header file which can be included in main program
* kdtree.cpp - implementation of kdtree funcitons
* test.h - main test file for testing all testcases
* main.cpp - driver file


