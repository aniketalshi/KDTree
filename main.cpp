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
    

#if TIME_CAL
    
    struct timeval start1, end1;
    double seconds1;
    gettimeofday(&start1, NULL);

#endif

    test_optimal(x1, y1, x2, y2);

#if TIME_CAL

    gettimeofday(&end1, NULL);
    seconds1 = (end1.tv_sec - start1.tv_sec) * 1000.0;
    seconds1 += (end1.tv_usec - start1.tv_usec)/1000.0;

    printf("\nElapsed time Optmizied version: %lf milliseconds\n", seconds1);

#endif   


#if TIME_CAL
    
    struct timeval start, end;
    double seconds;
    gettimeofday(&start, NULL);

#endif

    test_unoptimal(x1, y1, x2, y2);

#if TIME_CAL

    gettimeofday(&end, NULL);
    seconds = (end.tv_sec - start.tv_sec) * 1000.0;
    seconds += (end.tv_usec - start.tv_usec)/1000.0;

    printf("\nElapsed time unoptimized version: %lf milliseconds\n", seconds);

#endif   


return 0;
}
