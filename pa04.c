/*============================================================================
| Assignment: Computer Science I Program 4 Theater Loyalty Program
|
| Author: Donaldo Martinez
| Language: C
|
| Class: COP 3502C - Computer Science I - Spring 2024
| Instructor: Torosdagli
| Due Date: April 3, 2024
+===========================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 13 character command + 19 character name + 3 digit number = 35
// multiplied by 2 for assurance and an additional 2 characters for newline and null character
#define MAX_LINE_LENGTH 72
#define NAME_LENGTH 21

typedef struct customer {
    char* name;
    int points;
    int node_depth;
} customer;

typedef struct tree_node {
    struct customer* person;
    struct tree_node* left;
    struct tree_node* right;
} node;

customer* create_customer(char* name, int points);
void add_tree_node();
void delete_tree_node();
void subtract_customer_points();
int search_customer_tree();


int main(int argc, char* argv[]) {

    FILE* input_fp;
    if ((input_fp = fopen(argv[1], "r")) == NULL) {
        return -1;
    }

    // Creates the buffer to read each line of the file
    char buffer[MAX_LINE_LENGTH];

    // The first line is always the number of commands which is stored into command_count
    fgets(buffer, MAX_LINE_LENGTH, input_fp);
    int command_count = atoi(buffer);

    node* root = (node*) malloc(sizeof(node));
    if (root == NULL) {
        return -1;
    }
    root->person = NULL;
    root->left = NULL;
    root->right = NULL;

    for (int i = 0; i < command_count; i++) {

        fgets(buffer, MAX_LINE_LENGTH, input_fp);
        char command[13];
        char name[19];
        int points;
        sscanf(buffer, "%s %s %d", command, name, &points);
        
        if (strcmp(command, "add") == 0) {
            printf("ADD\n");
            customer* person = create_customer(name, points);
            if (person == NULL) {
                return -1;
            }
        }
        else if (strcmp(command, "sub") == 0) {
            printf("SUB\n");
        }
        else if (strcmp(command, "del") == 0) {
            printf("DEL\n");
        }
        else if (strcmp(command, "search") == 0) {
            printf("SEARCH\n");
        }
        else if (strcmp(command, "count_smaller") == 0) {
            printf("COUNT\n");
        }
    }
}

customer* create_customer(char* name, int points) {
    customer* person = (customer*) malloc(sizeof(customer));
    if (person == NULL) {
        return person;
    }

    person->name = name;
    person->points = points;
    person->node_depth = 0;
    return person;
}

void add_tree_node() {
    
}