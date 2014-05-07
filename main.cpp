#include <iostream>
#include "test.h"

using namespace std;

int main (int argc, char* argv[]) {
    

    double x1, y1, x2, y2;
    
    /*Read the Input from the file given by user*/
    test_input(argc, argv);
    
    /*seed the value before using rand*/
    std::srand(std::time(0));     
    
    /* Randomly generate the query points in range [x1, x1+0.1] [y1, y1 + 0.1] */
    x1 = 0.0 + rand()/ (RAND_MAX/1.0); 
    y1 = 0.0 + rand()/ (RAND_MAX/1.0);
    
    x2 = x1 + rand()/ (RAND_MAX/0.8);
    y2 = y1 + rand()/ (RAND_MAX/0.8); 
   
    /* Test Function to construct KDTree optimally 
     * Report points within [x1, x2] - [y1, y2] rectangle
     */
    test_optimal(x1, y1, x2, y2);
    
    /* Test Function to construct KDTree recursively
     * Report points within [x1, x2] - [y1, y2] rectangle
     */
    test_unoptimal(x1, y1, x2, y2);
    
    /* Uses naive bruteforce method to iterate over all points
     * and check if they lie within range [x1, x2] - [y1, y2]
     */
    bruteforce(x1, y1, x2, y2);

    return 0;
}
