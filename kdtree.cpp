#include "kdtree.h"

using namespace std;
std::vector <point_t> pvec;

int compare (const point_t &p, const point_t &q, int dim) {
    
    switch (dim) {
        case XDIM : return p.x - q.x;
        case YDIM : return p.y - q.y;
        default : printf("error");
                  return -1;
    }
}

bool compare_x (const int p, const int q) {
    return (pvec[p].x < pvec[q].x);
}

bool compare_y (const int p, const int q) {
    return (pvec[p].y < pvec[q].y);
}

kdnode_t* makeKDNode (double x, double y, int dim, int count) {
        
    kdnode_t *kdnode = (kdnode_t *) malloc (sizeof(kdnode_t));
    kdnode->pt       = (point_t *) malloc (sizeof(point_t)); 
    kdnode->pt->x    = x; 
    kdnode->pt->y    = y;
    kdnode->dim      = dim;
    kdnode->count    = count;
    kdnode->left     = NULL;
    kdnode->right    = NULL;
    return kdnode;
}

stnode_t *makeSTNode (int first, int last, kdnode_t *node, bool child, int dim) {

    stnode_t *stnode = (stnode_t *) malloc (sizeof(stnode_t));
    stnode->first    = first;
    stnode->last     = last;
    stnode->node     = node;
    stnode->child    = child;
    stnode->dim      = dim;

    return stnode;
};

void KDTree :: construct () {
    
    if (pvec.size() == 0)
        return;
    
    std::vector <int> indexes;
    for(int i = 0; i < (int )pvec.size(); ++i)
        indexes.push_back(i);
     
    buildKDTree (indexes, XDIM, &root);
}


void buildKDTree (std::vector <int> &indexes, int dim, kdnode_t **root) {
    kdnode_t *kdnode = NULL; 
    stnode_t *nd = NULL;

    if (indexes.size() == 0)
        return;

    if (dim == XDIM)
        sort (indexes.begin(), indexes.end(), compare_x);
    else
        sort (indexes.begin(), indexes.end(), compare_y);

    std::queue <stnode_t> squeue;
    int split = indexes.size()/2;
    *root = makeKDNode (pvec[indexes[split]].x, pvec[indexes[split]].y, dim, indexes.size());     

    if (split - 0) {
        nd = makeSTNode (0, split, *root, LEFT, dim^1);  
        squeue.push(*nd); 
    } 
    
    if (indexes.size() - (split + 1) > 0) {
        nd = makeSTNode (split + 1, indexes.size(), *root, RIGHT, dim^1);  
        squeue.push(*nd); 
    }

    while (!squeue.empty()) {
        
        int first        = squeue.front().first;
        int last         = squeue.front().last;
        int dim          = squeue.front().dim;
        int child        = squeue.front().child;
        kdnode_t *parent = squeue.front().node;
        squeue.pop();
        
        //printf ("\n First: %d, Last : %d, dim: %d", first, last, dim); 
        if (last - first == 1) {
            kdnode = makeKDNode (pvec[indexes[first]].x, pvec[indexes[first]].y, dim, 1);     
        
            if (parent) {
                if (child == LEFT)
                     parent->left = kdnode;
                 else
                     parent->right = kdnode;
            }
        
        } else {
        
            if (dim == XDIM)
                sort (indexes.begin() + first, indexes.begin() + last, compare_x);
            else
                sort (indexes.begin() + first, indexes.begin() + last, compare_y);
                
            split = (first + last)/2;
            kdnode = makeKDNode (pvec[indexes[split]].x, pvec[indexes[split]].y, dim, last - first);
             
            if (parent) {
                if (child == LEFT)
                     parent->left = kdnode;
                 else
                     parent->right = kdnode;
            }
            
            int first1 = first, last1 = split, first2 = split + 1, last2 = last;
            
            //printf ("\n left size %d, right %d", (int )leftvec.size(), (int)rightvec.size());
            if (last1 - first1 > 0 && first1 >= 0) {
                 nd = makeSTNode (first1, last1, kdnode, LEFT, dim^1);  
                 squeue.push(*nd); 
            }
                  
            if (last2 - first2 > 0 && last2 <= (int )pvec.size()) {
                 nd = makeSTNode (first2, last2, kdnode, RIGHT, dim^1);  
                 squeue.push(*nd); 
            }
        }
    }
}

void query (kdnode_t *node, double xmin, double xmax, double ymin, double ymax, std::vector <point_t> &result) {
    
    if (node == NULL)
        return;
   
    point_t *nd = node->pt;

    if (xmin <= nd->x && xmax >= nd->x && ymin <= nd->y && ymax >= nd->y) 
        result.push_back(*nd);
    
    switch (node->dim) {
        case 0 : {      //printf ("\n xdim, nd->x : %f, xmin: %f, xmax: %f", nd->x, xmin, xmax); 
                        if (xmin <= nd->x)
                            query (node->left, xmin, xmax, ymin, ymax, result);
                        
                        if (xmax >= nd->x)
                            query (node->right, xmin, xmax, ymin, ymax, result);
                        
                        break;
                 }
        case 1 : {      //printf ("\n ydim, nd->y : %f, ymin: %f, ymax: %f", nd->x, xmin, xmax); 
                        if (ymin <= nd->y)
                            query (node->left, xmin, xmax, ymin, ymax, result);
                        
                        if (ymax >= nd->y)
                            query (node->right, xmin, xmax, ymin, ymax, result);
                        
                        break; 
                 }

        default : printf("error"); break;
    }
}

void rectangle_query (point_t point_one, point_t point_two, KDTree kd, std::vector <point_t> &result) {
   
   double xmin, xmax, ymin, ymax;
    
   xmin = (point_one.x < point_two.x) ? point_one.x : point_two.x;
   xmax = (point_one.x > point_two.x) ? point_one.x : point_two.x;

   ymin = (point_one.y < point_two.y) ? point_one.y : point_two.y;
   ymax = (point_one.y > point_two.y) ? point_one.y : point_two.y;

   //printf("\n xmax : %f, xmin : %f, ymax : %f, ymin : %f", xmax, xmin, ymax, ymin); 
   query (kd.root, xmin, xmax, ymin, ymax, result);
}

unsigned long rectangle_count (point_t point_one, point_t point_two, KDTree kd) {

   std::vector <point_t> result;
   rectangle_query (point_one, point_two, kd, result);

   return result.size();
}

void traversal (KDTree kd) {
   std::queue <kdnode_t> kdqueue;
   
   kdqueue.push(kd.getroot());

   while (!kdqueue.empty()) {
        kdnode_t kdn = kdqueue.front();
        kdqueue.pop();
        
        printf("\n val (%f, %f)", (kdn.pt)->x, (kdn.pt)->y);
        if(kdn.left)
            kdqueue.push(*(kdn.left)); 
        if(kdn.right) 
            kdqueue.push(*(kdn.right)); 
   }
}

void print_pvec () {
      
    for (int i = 0; i < (int )pvec.size(); ++i) 
        printf("\n (%f, %f)", pvec[i].x, pvec[i].y);
}
