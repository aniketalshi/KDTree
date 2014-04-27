#!
rm -rf main
g++ generate.cpp -o generate
./generate
g++ -Wall -g kdtree.cpp main.cpp -lm -o main
./main inputfile.txt
