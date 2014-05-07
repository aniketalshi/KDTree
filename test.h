#include "kdtree.h"
#include <fstream>
#include <string>

using namespace std;

void test_query (double x1, double y1, double x2, double y2, KDTree kdtree) {

    std::vector <point_t> result;
    
    point_t *p1 = (point_t *) malloc (sizeof (point_t));
    p1->x       = x1;
    p1->y       = y1;
    
    point_t *p2 = (point_t *) malloc (sizeof (point_t));
    p2->x       = x2;
    p2->y       = y2;
    
    printf ("\n Rectangle Query : (%f, %f), (%f, %f) \n ", p1->x, p1->y, p2->x, p2->y);
   
    /* Queries the input to report points within rectangle given by p1, p2 
     * and outputs vector of points that lie in the range */
    rectangle_query(*p1, *p2, kdtree, result);
        
    //printf("\n Points within query rectangle \n");
    //for (int i = 0; i < (int )result.size(); ++i)
    //   printf("\n ( %f, %f)", result[i].x, result[i].y);
    
    printf("\n Count : %ld", result.size());
    
    free(p1);
    free(p2);

}

void circle_query_test (double x1, double y1, double radius, KDTree kdtree) {

    std::vector <point_t> result;
    
    point_t *p1 = (point_t *) malloc (sizeof (point_t));
    p1->x       = x1;
    p1->y       = y1;
    
    
    printf ("\n Circle Query : (%lf, %lf), %lf \n ", p1->x, p1->y, radius);
   
    /* Queries the input to report points within a circle 
     * and outputs vector of points that lie in the range */
    circle_query(*p1, radius, kdtree, result);
    printf("\n Count : %ld", result.size());

    if (result.size() > 0){
        if(isPresent(result.at(0), kdtree))
            printf("\n Point (%lf, %lf) is present", result[0].x, result[0].y);
   
    }
}

void test_optimal (double x1, double y1, double x2, double y2) {
    
    KDTree kdtree; 
    /*Debug function to print input points*/ 
    //print_pvec();
    
    /*Construct KDTree*/
    kdtree.construct ();
    
    /*Debug : Function to print kdtree levelorder */ 
    //traversal(kdtree); 
    
    printf("\n ***************Optimal KDTree***************");    

#if TIME_CAL
    
    struct timeval start1, end1;
    double seconds1;
    gettimeofday(&start1, NULL);

#endif
    
    /* Report points within [x1, x2] [y1, y2]*/
    //test_query(x1, y1, x2, y2, kdtree);
    circle_query_test (x1, y1, x2, kdtree);

#if TIME_CAL

    gettimeofday(&end1, NULL);
    seconds1 = (end1.tv_sec - start1.tv_sec) * 1000.0;
    seconds1 += (end1.tv_usec - start1.tv_usec)/1000.0;

    printf("\nElapsed time Optmizied version: %lf milliseconds\n", seconds1);

#endif   
}

void test_unoptimal (double x1, double y1, double x2, double y2) {
    KDTree kdtree2; 
    
    /*Debug function to print input points*/ 
    //print_pvec();
    
    /*Construct KDTree*/
    kdtree2.construct_unopt ();
    
    /*Debug : Function to print kdtree levelorder */ 
    //traversal(kdtree2);
    
    printf("\n ***************non-optimal KDTree***************");    

#if TIME_CAL
    
    struct timeval start2, end2;
    double seconds2;
    gettimeofday(&start2, NULL);

#endif

    /* Report points within [x1, x2] [y1, y2]*/
    test_query(x1, y1, x2, y2, kdtree2);

#if TIME_CAL

    gettimeofday(&end2, NULL);
    seconds2 = (end2.tv_sec - start2.tv_sec) * 1000.0;
    seconds2 += (end2.tv_usec - start2.tv_usec)/1000.0;

    printf("\nElapsed time unoptimized version: %lf milliseconds\n", seconds2);

#endif   
}

void bruteforce (double x1, double y1, double x2, double y2) {
    
#if TIME_CAL
    
    struct timeval start3, end3;
    double seconds3;
    gettimeofday(&start3, NULL);

#endif
   
   printf("\n ***************The bruteforce approach \n");
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

#if TIME_CAL

    gettimeofday(&end3, NULL);
    seconds3 = (end3.tv_sec - start3.tv_sec) * 1000.0;
    seconds3 += (end3.tv_usec - start3.tv_usec)/1000.0;
    printf("\nElapsed time brutforce version: %lf milliseconds\n", seconds3);

#endif   
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
