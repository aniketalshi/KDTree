/* author : Aniket Alshi
*  
*  A script to generate random points and output to file
*  Numbers : SIZE, Range : LO to HI
*/

#include "kdtree.h"
#include <fstream>

#define LO 0.0
#define HI 1.0

using namespace std;

int main (int argc, char *argv[]) {
    
    std::srand(std::time(0));     
    std::ofstream myfile;
    myfile.open ("test/inputfile.txt");
    
    
    if (argc != 2) {
        printf ("Error: Specify number of points to generate");
        return 0;
    }
    
    /* input - number of points */
    unsigned size = atoi(argv[1]);
    
    printf ("\n Number of Input points: %d, Range Low: %lf to High: %lf\n", size, LO, HI);
    
    double x, y; 
    unsigned i;
    myfile << size << endl;
    
    for (i = 0; i < size; ++i) {
       
       x = LO + rand() / (RAND_MAX / (HI - LO));
       y = LO + rand() / (RAND_MAX / (HI - LO));
       
       myfile << x << " ";
       myfile << y;
       myfile << endl;
    }
    
    myfile.close();
    return 0;
}
