#ifndef LINKEDLIST
#define LINKEDLIST

#include <stdio.h>
#include <stdlib.h>


/* A linked list node */
typedef struct node
{
    // The metadata is stored in the node
    int R;
    int G;
    int B;
 
    struct node *next;
}node;

// makes a node based on args and returns the new node
node* make_node(char opChar, char* opCmd, int opCycleTime);

// inserts a node into the end of the linked list
void insert_command(node *newNode, node *head);

void set_value(node *nodeToSet, char color, int value);

int get_value(node *nodeToGet, char color);

#endif