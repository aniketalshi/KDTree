#!
rm -rf main 
rm -rf generate
g++ generate.cpp -o generate
./generate 1000
g++ -Wall -g kdtree.cpp main.cpp -lm -o main
./main test/in01.txt
