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

void test_query (double x1, double y1, double x2, double y2, KDTree kdtree) {

    printf("\n**************Running Test ******************\n"); 

    std::vector <point_t> result;
    point_t *p1 = (point_t *) malloc (sizeof (point_t));
    p1->x       = x1;
    p1->y       = y1;
    
    point_t *p2 = (point_t *) malloc (sizeof (point_t));
    p2->x       = x2;
    p2->y       = y2;
    
    printf ("\n Rectangle Query : (%f, %f), (%f, %f) \n ", p1->x, p1->y, p2->x, p2->y);
    rectangle_query(*p1, *p2, kdtree, result);
        
    //printf("\n Points within query rectangle \n");
    //for (int i = 0; i < (int )result.size(); ++i)
    //   printf("\n ( %f, %f)", result[i].x, result[i].y);
    
    printf("\n Count : %ld", rectangle_count(*p1, *p2, kdtree));
    
    //free(p1);
    //free(p2);

}

void test_optimal (double x1, double y1, double x2, double y2) {
    
    KDTree kdtree; 
    //print_pvec();

    kdtree.construct ();
    //traversal(kdtree); 

    printf("\n Optimized KDTree");    

#if TIME_CAL
    
    struct timeval start1, end1;
    double seconds1;
    gettimeofday(&start1, NULL);

#endif
    test_query(x1, y1, x2, y2, kdtree);

#if TIME_CAL

    gettimeofday(&end1, NULL);
    seconds1 = (end1.tv_sec - start1.tv_sec) * 1000.0;
    seconds1 += (end1.tv_usec - start1.tv_usec)/1000.0;

    printf("\nElapsed time Optmizied version: %lf milliseconds\n", seconds1);

#endif   


}

void test_unoptimal (double x1, double y1, double x2, double y2) {
    
    KDTree kdtree2; 
    //print_pvec();
    kdtree2.construct_unopt ();
    //traversal(kdtree2);
    
    printf("\n non-optimal KDTree");    

#if TIME_CAL
    
    struct timeval start2, end2;
    double seconds2;
    gettimeofday(&start2, NULL);

#endif

    test_query(x1, y1, x2, y2, kdtree2);

#if TIME_CAL

    gettimeofday(&end2, NULL);
    seconds2 = (end2.tv_sec - start2.tv_sec) * 1000.0;
    seconds2 += (end2.tv_usec - start2.tv_usec)/1000.0;

    printf("\nElapsed time unoptimized version: %lf milliseconds\n", seconds2);

#endif   

}

void bruteforce (double x1, double y1, double x2, double y2) {
    
   printf("\n The bruteforce approach \n");
   std::vector <point_t> result;
   double xmin, ymin, xmax, ymax;
   int i;
   
   xmin = (x1 <= x2) ? x1 : x2; 
   xmax = (x1 >= x2) ? x1 : x2;

   ymin = (y1 <= y2) ? y1 : y2; 
   ymax = (y1 >= y2) ? y1 : y2;

   for (i = 0; i < (int )pvec.size(); ++i) {
        
        if (pvec[i].x >= xmin && pvec[i].x <= xmax && pvec[i].y >= ymin && pvec[i].y <= ymax)
            result.push_back(pvec[i]);
   }

   //printf("\n Points within query rectangle \n");
   //for (i = 0; i < (int )result.size(); ++i)
   //    printf("\n ( %f, %f)", result[i].x, result[i].y);

    printf("\n Count : %ld", result.size());
}

void test_input(int argc, char *argv[]) {
    
    if (argc != 2) {
        printf("Error: filename needed");
    
    } else {
        
        std::ifstream myfile; 
        myfile.open (argv[1], std::ifstream::in);
        printf ("\n Input File : %s \n", argv[1]);         

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
