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
node* search_tree();


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
        char* name = (char*) malloc(sizeof(char) * NAME_LENGTH);
        if (name == NULL) {
            return -1;
        }
        int points;
        sscanf(buffer, "%s %s %d", command, name, &points);
        
        if (strcmp(command, "add") == 0) {
            printf("ADD\n");
            customer* person = create_customer(name, points);
            if (person == NULL) {
                return -1;
            }

            add_tree_node(root, person);
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

node* init_node(customer* person) {
    node* temp = (node*) malloc(sizeof(node));
    if (temp == NULL) {
        printf("Error allocating memory for new tree node");
        return temp;
    }

    temp->person = person;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

node* search_tree(node* root, char* name) {
    if (root->person == NULL) {
        return root;
    }

    if (strcmp(name, root->person->name) == 0) {
        printf("%s %d %d", root->person->name, root->person->points, root->person->node_depth);
        return root;
    }
    else if (strcmp(name, root->person->name) < 0) {
        if (root->left == NULL) {
            return root;
        }
        else if (strcmp(name, root->left->person->name) > 0) {
            return root;
        }
        else {
            search_tree(root->left, name);
        }
    }
    else if (strcmp(name, root->person->name) > 0) {
        if (root->right == NULL) {
            return root;
        }
        else if (strcmp(name, root->right->person->name) < 0) {
            return root;
        }
        else {
            search_tree(root->right, name);
        }
    }

}

void add_tree_node(node* root, customer* person) {
    
    // If the person field is empty then the root node is as well, so add the person to the root node 
    // and leave the children null
    if (root->person == NULL) {
        root->person = person;
        return;
    }

    // If the person's name comes (alphabetically) before the current node
    if (strcmp(person->name, root->person->name) < 0) {

        // If the current node doesn't have a left child, create a new node with the person and make it
        // the left child of the current node
        if (root->left == NULL) {
            node* new_node = init_node(person);
            root->left = new_node;
            printf("Left Leaf: %s\n", new_node->person->name);
            return;
        }

        // Else if the current node has a left child and the left child has a name that comes before the person
        // being added, make a new node and place it between the root node and left child node
        else if (strcmp(person->name, root->left->person->name) > 0) {
            node* new_node = init_node(person);
            new_node->left = root->left;
            root->left = new_node;
            printf("Left Between: %s\n", new_node->person->name);
            return;
        }

        // Finally, if none of the other conditions are true then the current person must continue to traverse down
        // the left of the tree
        else {
            add_tree_node(root->left, person);
        }
    }

    // If the person's name comes (alphabetically) after the current node
    else if (strcmp(person->name, root->person->name) > 0) {
        // printf("%s    %s   %d", person->name, root->person->name, strcmp(person->name, root->person->name));
        // If the current node doesn't have a right child, create a new node with the person and make it
        // the right child of the current node
        if (root->right == NULL) {
            node* new_node = init_node(person);
            root->right = new_node;
            printf("Right Leaf: %s\n", new_node->person->name);
            return;
        }

        // Else if the current node has a right child and the right child has a name that comes after the person
        // being added, make a new node and place it between the root node and right child node
        else if (strcmp(person->name, root->right->person->name) < 0) {
            node* new_node = init_node(person);
            new_node->right = root->right;
            root->right = new_node;
            printf("Right Between: %s\n", new_node->person->name);
            return;
        }

        // Finally, if none of the other conditions are true then the current person must continue to traverse down
        // the right of the tree
        else {
            add_tree_node(root->right, person);
        }
    }

    else if (strcmp(person->name, root->person->name) == 0) {
        root->person->points += person->points;
    }
}