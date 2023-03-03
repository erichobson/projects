#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "obstacles.h"
#include "display.h"


// This is a helper function that determines whether or not line segment (v1---v2) intersects line segment (v3---v4)
unsigned char linesIntersect(short v1x, short v1y, short v2x, short v2y, short v3x, short v3y, short v4x, short v4y) {
  	float uA = ((v4x-v3x)*(v1y-v3y) - (v4y-v3y)*(v1x-v3x)) / (float)(((v4y-v3y)*(v2x-v1x) - (v4x-v3x)*(v2y-v1y)));
  	float uB = ((v2x-v1x)*(v1y-v3y) - (v2y-v1y)*(v1x-v3x)) / (float)(((v4y-v3y)*(v2x-v1x) - (v4x-v3x)*(v2y-v1y)));

  	// If uA and uB are between 0-1, there is an intersection
  	if (uA > 0 && uA < 1 && uB > 0 && uB < 1) 
		return 1;

	return 0;
}

// Create a rrt using the growthAmount and maximumNodes parameters in the given environment.
void createRRT(Environment *env) {	

	// counter for loops
	unsigned short i;

    // coordinates for random 'q' node
    unsigned short x, y;

    // variables used to calculate the distance between node and 'q'
    short shortestDistance;
    double distance, minDistance;

    // flags used when calculating linesIntersect()
    unsigned char edge1, edge2, edge3, edge4;

    // memory is dynamically allocated for env->rrt array
	env->rrt = (TreeNode **)malloc(env->maximumNodes*sizeof(TreeNode *));

    // if memory allocation failed, print and exit program 
    if(env->rrt == NULL){
        printf("Out of Memory Error When Allocating env->rrt Array\n");
        exit(-1);
    }

    // every element of env->rrt array is allocated and called upon individually in createRRT
    // this is to save having to allocate every time a new element in needed
	for(i = 0; i < env->maximumNodes; i++) env->rrt[i] = (TreeNode *) malloc(sizeof(TreeNode));

    // root node is initialized
    // parent is set to NULL so that we know for later this is the root node
	env->rrt[0]->x = env->startX;
	env->rrt[0]->y = env->startY;
	env->rrt[0]->parent = NULL;
	env->rrt[0]->firstChild = NULL;

    // env->numNodes is incremented
    // this is so we know which element of the array to initialize since every element has been malloced
	env->numNodes = 1;

    // initialize nodes to use throughout do/while loop
	TreeNode *n;    // this node is used as the closest TreeNode to 'q'
	Child *last;    // this node is used when *->firstChild != NULL, iterates through nextSibling

	do{
		TreeNode *c = env->rrt[env->numNodes];  // first node in array that has not been initialized, to be initialized
		unsigned char oFlag = 1;	            // flag used to determine is a point is in an obstacle or intersects with a line

		while(oFlag == 1){                                      // loop until ALL checks are passed
			x = rand() % env->maximumX;                         // calculate rand() x using maximumX
			y = rand() % env->maximumY;                         // calculate rand() y using maximumY
			oFlag = 0;                                          // set flag to 0

			for(i = 0; i < env->numObstacles; i++) {            // iterate through obstacles
				short a = env->obstacles[i].x;          
				short b = env->obstacles[i].y;
				short w = env->obstacles[i].w;
				short h = env->obstacles[i].h;
				if(x <= a+w && x >= a && y <= b && y >= b-h){   // test if x and y are in obstacle
					oFlag = 1;
                    break;
                }
            }
            if(oFlag == 0){                             // if x and y are not in obstacle

				minDistance = -1;                       // initialize to -1 so minDistance is always set to distance after first calculation
                for(i = 0; i < env->numNodes; i++){
                    distance = sqrt(pow(x - env->rrt[i]->x ,2)+pow(y - env->rrt[i]->y,2));
                    if(distance < minDistance || minDistance == -1){
						minDistance = distance;
						shortestDistance = i;           // saves location of shortestDistance 
                    }
                }
				n = env->rrt[shortestDistance];                                     // n is set to element at shortestDistance
                c->x = n->x + cos(atan2(y - n->y, x - n->x)) * env->growthAmount;   // the location of c->x is calculated and initialized
                c->y = n->y + sin(atan2(y - n->y, x - n->x)) * env->growthAmount;   // the location of c->y is calculated and initialized

                /* iterates through the obstacles and calculates whether the line created between n and c
                   intersects with any of the 4 lines of each obstacle */
				for(i = 0; i < env->numObstacles; i++){  
                    edge1 = linesIntersect(n->x, n->y, c->x, c->y, env->obstacles[i].x, env->obstacles[i].y,
                                                         env->obstacles[i].x + env->obstacles[i].w, env->obstacles[i].y);
                    edge2 = linesIntersect(n->x, n->y, c->x, c->y, env->obstacles[i].x + env->obstacles[i].w, env->obstacles[i].y,
                                                         env->obstacles[i].x + env->obstacles[i].w, env->obstacles[i].y - env->obstacles[i].h);
                    edge3 = linesIntersect(n->x, n->y, c->x, c->y, env->obstacles[i].x + env->obstacles[i].w, env->obstacles[i].y - env->obstacles[i].h,
                                                         env->obstacles[i].x, env->obstacles[i].y - env->obstacles[i].h);
                    edge4 = linesIntersect(n->x, n->y, c->x, c->y, env->obstacles[i].x, env->obstacles[i].y - env->obstacles[i].h,
                                                         env->obstacles[i].x, env->obstacles[i].y);
					if(edge1 == 1 || edge2 == 1 || edge3 == 1 || edge4 == 1){
                        oFlag = 1;
                        break;
					}
				}
                // this check is probably not necessary, but was running into issues occasionally where c ended up inside an obstacle 
				if(oFlag == 0){
					for(i = 0; i < env->numObstacles; i++) {
						int a = env->obstacles[i].x;
						int b = env->obstacles[i].y;
						int w = env->obstacles[i].w;
						int h = env->obstacles[i].h;
						if(c->x <= a+w && c->x >= a && c->y <= b && c->y >= b-h){
							oFlag = 1;
							break;
						}
					}
				}	
                // if oFlag == 1 here loop resets and creates new random 'q' variables
            }
		}	

        // at this point all obstacle checks have passed
		c->parent = n;          // sets c->parent to n
		c->firstChild = NULL;   // sets c->firstChild to NULL
		env->numNodes++;        // increments numNodes

		if(n->firstChild == NULL){                  // if n->firstChild has not been initialized
			n->firstChild = (Child *) malloc(sizeof(Child));        // allocates memory
            if(n->firstChild == NULL){                              // if memory allocation failed, print and exit program 
                printf("Out of Memory Error When Allocating n->firstChild\n");
                exit(-1);
            }
			n->firstChild->node = c;                // set node to c
			n->firstChild->nextSibling = NULL;      // sets nextSibling to NULL (needed for later iteration)

		}else if(n->firstChild != NULL){            // if n-> firstChild has already been initialized
			last = n->firstChild;                   // sets last to be firstChild
			while(last->nextSibling != NULL){       // iterates through all nextSibling until nextSibling == NULL
				last = last->nextSibling;
			}
			last->nextSibling = (Child *) malloc(sizeof(Child));    // allocates memory
            if(last->nextSibling == NULL){                          // if memory allocation failed, print and exit program 
                printf("Out of Memory Error When Allocating last->nextSibling\n");
                exit(-1);
            }
			last->nextSibling->node = c;            // set node to c
			last->nextSibling->nextSibling = NULL;  // sets nextSibling to NULL (needed for later iteration)
		}
    } while (env->numNodes < env->maximumNodes);    // loops until every element of env->rrt has been initialized
}


// Trace the path back from the node that is closest to the given (x,y) coordinate to the root
void tracePath(Environment *env, unsigned short x, unsigned short y) {	
    
    // iterator variables
	short i;
	unsigned short count = 1;    // or counting the required length for env->path

    // variables used to calculate the distance between node and given (x,y)
    short shortestDistance;
    double distance, minDistance;

    // same loop used to calculate distance between nodes in createRRT()
    minDistance = -1;                    // initialize to -1 so minDistance is always set to distance after first calculation
    for(i = 0; i < env->numNodes; i++){
        distance = sqrt(pow(x - env->rrt[i]->x ,2)+pow(y - env->rrt[i]->y,2));
        if(distance < minDistance || minDistance == -1){
            minDistance = distance;
			shortestDistance = i;       // saves location of shortestDistance
        }
    }
    
    // creates a pointer to the node with the shortest distance from (x,y)
	TreeNode *start = env->rrt[shortestDistance];
    
    // calculates the length (count) needed for path by checking the parent until parent == NULL (root node) 
	while(start->parent != NULL){
		start = start->parent;
		count++;
	}

    // memory is dynamically allocated for env->path array
	env->path = (TreeNode **)malloc(count*sizeof(TreeNode *));

    // if memory allocation failed, print and exit program 
    if(env->path == NULL){
        printf("Out of Memory Error When Allocating env->path Array\n");
        exit(-1);
    }

    // sets start to node closest to (x,y)
	start = env->rrt[shortestDistance];

    // sets each element of path to each node's parent
    // with path[0] being the node closest to (x,y), and path[count - 1] being the root node
	for(i = 0; i < count; i++){
		env->path[i] = start;
		start = start->parent;
	}
}

// This procedure cleans up everything by freeing all alocated memory
void cleanupEverything(Environment *env) {
    // free obstacles
	free(env->obstacles);

    // iterate through rrt to free each pointer
	for(int i = 0; i < env->numNodes; i++){

        // temp pointers used to free any Child pointers that were malloced
		TreeNode *temp = env->rrt[i];
		Child *tempChild = temp->firstChild;

		if(tempChild != NULL){
            // create another temp pointer used to free nextSiblings if != NULL
			Child *tempSibling = tempChild->nextSibling;
			free(tempChild);    // <- free the child
			while(tempSibling != NULL){                 // <- until tempSibling is NULL
				tempChild = tempSibling;                // <- set tempChild to tempSibling
				tempSibling = tempChild->nextSibling;   // <- set tempSibling to the nextSibling
				free(tempChild);                        // <- free the child
			}   // loops until all the children are free
		}
		free(env->rrt[i]);  // <- free that pointer in the array
	}
    // free rrt
	free(env->rrt);        

    // free path
	free(env->path);       
}