#include <iostream>
#include "test.h"

using namespace std;

int main (int argc, char* argv[]) {

    test_input(argc, argv);

    double x1, y1, x2, y2;
    std::srand(std::time(0));     
    
    x1 = 0.0 + rand()/ (RAND_MAX/1.0); 
    y1 = 0.0 + rand()/ (RAND_MAX/1.0);
    
    x2 = x1 + rand()/ (RAND_MAX/0.8);
    y2 = y1 + rand()/ (RAND_MAX/0.8); 
    
    test_optimal(x1, y1, x2, y2);
    
    //test_unoptimal(x1, y1, x2, y2);

#if TIME_CAL
    
    struct timeval start3, end3;
    double seconds3;
    gettimeofday(&start3, NULL);

#endif

    bruteforce(x1, y1, x2, y2);

#if TIME_CAL

    gettimeofday(&end3, NULL);
    seconds3 = (end3.tv_sec - start3.tv_sec) * 1000.0;
    seconds3 += (end3.tv_usec - start3.tv_usec)/1000.0;

    printf("\nElapsed time brutforce version: %lf milliseconds\n", seconds3);

#endif   
    return 0;
}
