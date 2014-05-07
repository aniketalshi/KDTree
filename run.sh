#!
rm -rf main 
rm -rf generate
g++ generate.cpp -o generate
./generate 100
g++ -Wall -g kdtree.cpp main.cpp -lm -o main
./main inputfile.txt
