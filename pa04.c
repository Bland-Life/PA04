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
void del_tree_node();
void sub_loyalty_points();
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

    node* root = NULL;

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
            customer* person = create_customer(name, points);
            if (person == NULL) {
                return -1;
            }

            add_tree_node(&root, person);
            // printf("%s    ", root->person->name);
        }
        else if (strcmp(command, "sub") == 0) {
            customer* person = create_customer(name, points);
            if (person == NULL) {
                return -1;
            }
            sub_loyalty_points(root, person);
        }
        else if (strcmp(command, "del") == 0) {
            printf("DEL\n");
        }
        else if (strcmp(command, "search") == 0) {
            customer* person = create_customer(name, points);
            node* temp = search_tree(root, person->name, 0, root);
            if (temp == NULL) {
                printf("%s not found\n", person->name);
            }
            else if (strcmp(person->name, temp->person->name) == 0) {
                printf("%s %d %d\n", temp->person->name, temp->person->points, temp->person->node_depth);
            }
            else {
                printf("%s not found\n", temp->person->name);
            }

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

void del_tree_node(node** root, customer* person) {
    node* parent = search_tree(root, person->name, 1, root);
    if (parent == NULL) {
        printf("%s not found\n", person->name);
        return;
    }

    // If the root we are deleting is the root node of our entire tree
    if (strcmp(person->name, parent->person->name) == 0) {

        if (parent->left == NULL && parent->right == NULL) {
            printf("%s deleted\n", parent->person->name);
            free(parent->person->name);
            free(parent->person);
            free(parent);
            parent = NULL;
        }
        else if (parent->left == NULL) {
            node* to_del = parent;
            parent = parent->right;
            printf("%s deleted", to_del->person->name);
            free(to_del->person->name);
            free(to_del->person);
            free(to_del);
        }
        else if (parent->right == NULL) {
            node* to_del = parent;
            parent = parent->left;
            printf("%s deleted", to_del->person->name);
            free(to_del->person->name);
            free(to_del->person);
            free(to_del);
        }
        else {
            // inorder
        }
    }

    else if (parent->left != NULL && strcmp(person->name, parent->left->person->name) == 0) {

        node* to_del = parent->left;

        if (to_del->left == NULL && to_del->right == NULL) {
            printf("%s deleted\n", to_del->person->name);
            free(to_del->person->name);
            free(to_del->person);
            free(to_del);
            parent->left = NULL;
        }
        else if (to_del->left == NULL) {
            parent->left = to_del->right;
            printf("%s deleted\n", to_del->person->name);
            free(to_del->person->name);
            free(to_del->person);
            free(to_del);
        }
        else if (to_del->right == NULL) {
            parent->right = to_del->left;
            printf("%s deleted\n", to_del->person->name);
            free(to_del->person->name);
            free(to_del->person);
            free(to_del);
        }
        else {
            // in order
        }
    }
    else if (parent->right != NULL && strcmp(person->name, parent->right->person->name) == 0) {
        node* to_del = parent->right;

        if (to_del->left == NULL && to_del->right == NULL) {
            printf("%s deleted\n", to_del->person->name);
            free(to_del->person->name);
            free(to_del->person);
            free(to_del);
            parent->left = NULL;
        }
        else if (to_del->left == NULL) {
            parent->left = to_del->right;
            printf("%s deleted\n", to_del->person->name);
            free(to_del->person->name);
            free(to_del->person);
            free(to_del);
        }
        else if (to_del->right == NULL) {
            parent->right = to_del->left;
            printf("%s deleted\n", to_del->person->name);
            free(to_del->person->name);
            free(to_del->person);
            free(to_del);
        }
        else {
            // in order
        }
    }
    else {
        printf("%s not found\n", person->name);
    }

}

node* search_tree(node* root, char* name, int parent_flag, node* parent) {

    if (root == NULL) {
        return root;
    }

    if (strcmp(name, root->person->name) == 0) {
        return (parent_flag == 1) ? parent : root;
    }

    else if (strcmp(name, root->person->name) < 0) {
        if (root->left == NULL) {
            return root;
        }
        else if (strcmp(name, root->left->person->name) > 0) {
            return root;
        }
        else {
            search_tree(root->left, name, parent_flag, root);
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
            search_tree(root->right, name, parent_flag, root);
        }
    }
}

void add_tree_node(node** root, customer* person) {

    node* temp = search_tree(*root, person->name, 0, *root);

    if (temp == NULL) {
        *root = init_node(person);
        printf("%s %d\n", (*root)->person->name, (*root)->person->points);
        return;
    }

    int result = strcmp(person->name, temp->person->name);

    // If the person's name comes (alphabetically) before the current node
    if (result < 0) {

        if (temp->left == NULL) {
            node* new_node = init_node(person);
            temp->left = new_node;
            printf("%s %d\n", new_node->person->name, new_node->person->points);
            return;
        }
        else if (strcmp(person->name, temp->left->person->name) > 0) {
            node* new_node = init_node(person);
            new_node->left = temp->left;
            temp->left = new_node;
            printf("%s %d\n", new_node->person->name, new_node->person->points);
            return;
        }
        else {
            add_tree_node(&(temp->left), person);
        }
    }

    // If the person's name comes (alphabetically) after the current node
    else if (result > 0) {

        if (temp->right == NULL) {
            node* new_node = init_node(person);
            temp->right = new_node;
            printf("%s %d\n", new_node->person->name, new_node->person->points);
            return;
        }
        else if (strcmp(person->name, temp->right->person->name) < 0) {
            node* new_node = init_node(person);
            new_node->right = temp->right;
            temp->right = new_node;
            printf("%s %d\n", new_node->person->name, new_node->person->points);
            return;
        }
        else {
            add_tree_node(&(temp->right), person);
        }
    }

    else if (result == 0) {
        temp->person->points += person->points;
        printf("%s %d\n", temp->person->name, temp->person->points);
    }
}

void sub_loyalty_points(node* root, customer* person) {

    node* temp = search_tree(root, person->name, 0, root);
    if (temp == NULL) {
        printf("%s not found\n", person->name);
        return;
    }

    if (strcmp(person->name, temp->person->name) == 0) {
        temp->person->points = (temp->person->points - person->points > 0) ? temp->person->points - person->points : 0;
        printf("%s %d\n", temp->person->name, temp->person->points);
    }

    else {
        printf("%s not found\n", person->name);
    }
}