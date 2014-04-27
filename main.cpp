#include <iostream>
#include "test.h"

using namespace std;

int main (int argc, char* argv[]) {

    test_2(argc, argv);

    double x1, y1, x2, y2;
    printf("\n Input the query points\n");
    cin >> x1 >> y1;
    cin >> x2 >> y2;

#if TIME_CAL
    
    struct timeval start, end;
    double seconds;
    gettimeofday(&start, NULL);

#endif

    test_1(x1, y1, x2, y2);

#if TIME_CAL

    gettimeofday(&end, NULL);
    seconds = (end.tv_sec - start.tv_sec) * 1000.0;
    seconds += (end.tv_usec - start.tv_usec)/1000.0;

    printf("\nElapsed time: %lf milliseconds\n", seconds);

#endif   
   return 0;
}
