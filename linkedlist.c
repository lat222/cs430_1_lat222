#include "linkedlist.h"
 
node* make_node(int R, int B, int G)
{
    // allocate some space for the node
    node* newNode = (node*) malloc(sizeof(node));

    // check the space was allocated
    if(newNode == NULL)
    {
        fprintf(stderr, "Unable to allocate memory for new node\n");
        exit(-1);
    }

    // set the node's data
    newNode->R = R;
    newNode->G = B;
    newNode->B = G;

    // don't connect the node to anything
    newNode->next = NULL;

    // return the newly created node
    return newNode;
}

// editted, but based off of 
// http://stackoverflow.com/questions/5797548/c-linked-list-inserting-node-at-the-end
 void insert_node(node *newNode, node *head){

    // set current to the head of the linked list
    // current will then be used to loop through the entire list until the end, where the newNode will be added
    node *current = head;
    while(1) 
    {
        if(current->next == NULL)
        {
            current->next = newNode;
            break;
        }
        current = current->next;
    }
}

void set_value(node *nodeToSet, char color, int value)
{
    if(color == 'R')
    {
        nodeToSet->R = value;
    }
    else if(color  == 'G')
    {
        nodeToSet->G = value;
    }
    else if(color == 'B')
    {
        nodeToSet->B = value;
    }
}

int get_value(node *nodeToSet, char color)
{
    if(color == 'R')
    {
        return (int) nodeToSet->R;
    }
    else if(color  == 'G')
    {
        return (int) nodeToSet->G;
    }
    else if(color == 'B')
    {
        return (int) nodeToSet->B;
    }
    return -1;
}
