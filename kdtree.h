#ifndef KDTREE
#define KDTREE

#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <ctime>
#include <stack>
#include <queue>
#include <sys/time.h>

#define TIME_CAL 1

enum dim {XDIM, YDIM  };
enum ch  {LEFT, RIGHT };

typedef struct Point {
    double x;
    double y;
} point_t;
 
typedef struct KDNode {
    point_t *pt; 
    int dim;
    
    int count;

    struct KDNode *left;
    struct KDNode *right;

} kdnode_t;

class KDTree {
    public:
    kdnode_t *root;
    int min, max;
    
    void construct ();
    kdnode_t getroot() { return *root; }
        
};

typedef struct stack_node {
    int first;
    int last;
    bool child;
    int dim;
    kdnode_t *node;

} stnode_t;

extern std::vector <point_t> pvec;

kdnode_t* makeKDNode          (double x, double y, int dim, int count);
stnode_t *makeSTNode          (int first, int last, kdnode_t *node, bool child, int dim);
void buildKDTree              (std::vector <int> &indexes, int dim, kdnode_t **root);
void rectangle_query          (point_t point_one, point_t point_two, KDTree kd, std::vector <point_t> &result);
unsigned long rectangle_count (point_t point_one, point_t point_two, KDTree kd);
void traversal                (KDTree kd);
void print_pvec               ();

#endif
