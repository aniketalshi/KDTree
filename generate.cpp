/* author : Aniket Alshi
*  
*  A script to generate random points and output to file
*  Numbers : SIZE, Range : LO to HI
*/

#include "kdtree.h"
#include <fstream>

#define LO 0.0
#define HI 1.0
#define SIZE 10000

using namespace std;

int main () {
    
    printf ("\n Number of Input points: %d, Range Low: %lf to High: %lf\n", SIZE, LO, HI);

    std::srand(std::time(0));     
    std::ofstream myfile;
    myfile.open ("inputfile.txt");

    double x, y; 
    myfile << SIZE << endl;
    
    for (int i = 0; i < SIZE; ++i) {
       
       x = LO + rand() / (RAND_MAX / (HI - LO));
       y = LO + rand() / (RAND_MAX / (HI - LO));
       
       myfile << x << " ";
       myfile << y;
       myfile << endl;
    }
    
    myfile.close();
    return 0;
}
