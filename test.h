#include "kdtree.h"
#include <fstream>
#include <string>

using namespace std;

int myrand(int i) { return std::rand()%i; }

void populate_pvec () {

    std::srand(std::time(0));     
    for (int i = 1; i < 10; ++i) {
        point_t *p = (point_t *) malloc (sizeof (point_t));
        p->x = myrand(i*10); 
        p->y = myrand(i*20); 
        pvec.push_back(*p);
    }
    std::random_shuffle (pvec.begin(), pvec.end(), myrand);
}

void test_1(double x1, double y1, double x2, double y2) {

    printf("\n**************Running Test ******************\n"); 
    KDTree kdtree; 
    printf("\n Input Points :\n"); 
    
    //print_pvec();
    kdtree.construct ();

    std::vector <point_t> result;
    point_t *p1 = (point_t *) malloc (sizeof (point_t));
    p1->x = x1;
    p1->y = y1;
    
    point_t *p2 = (point_t *) malloc (sizeof (point_t));
    p2->x = x2;
    p2->y = y2;
    
    printf ("\n Rectangle Query : (%f, %f), (%f, %f) \n ", p1->x, p1->y, p2->x, p2->y);
    rectangle_query(*p1, *p2, kdtree, result);
        
    printf("\n Points within query rectangle \n");
    for (int i = 0; i < (int )result.size(); ++i)
        printf("\n ( %f, %f)", result[i].x, result[i].y);
    
    printf("\n Count : %ld", rectangle_count(*p1, *p2, kdtree));
    
    free(p1);
    free(p2);
}


void test_2(int argc, char *argv[]) {
    
    if (argc != 2) {
        printf("Error: filename needed");
    
    } else {
        
        std::ifstream myfile; 
        //std::string str = std::string(argv[1]); 
        
        myfile.open (argv[1], std::ifstream::in);
        
        if (myfile.fail()) {
            printf("Error: couldnot open the file");
        } else {

            int numlines = 0;
            double xval, yval;
            point_t *p;
            
            myfile >> numlines;
            
            for (int i = 0; i < numlines; ++i) {
                myfile >> xval;
                myfile >> yval; 
                
                p = (point_t *) malloc (sizeof (point_t));
                p->x = xval;
                p->y = yval;
                pvec.push_back(*p);
            }
            myfile.close();     
        }
    }

}
