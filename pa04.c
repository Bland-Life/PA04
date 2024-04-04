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

customer* create_customer();
void add_tree_node();
void del_tree_node();
void sub_loyalty_points();
node* search_tree();
node* largest_node();

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
            add_tree_node(&root, name, points);
        }
        else if (strcmp(command, "sub") == 0) {
            sub_loyalty_points(root, name, points);
        }
        else if (strcmp(command, "del") == 0) {
            node* temp = search_tree(root, name, 0);
            if (temp == NULL) {
                printf("%s not found\n", name);
            }
            else {
                printf("DEL\n");
            }
            
        }
        else if (strcmp(command, "search") == 0) {
            node* temp = search_tree(root, name, 0);
            if (temp == NULL) {
                printf("%s not found\n", name);
            }
            else {
                printf("%s %d %d\n", temp->person->name, temp->person->points, temp->person->node_depth);
            }
        }
        else if (strcmp(command, "count_smaller") == 0) {
            printf("COUNT\n");
        }

        free(name);
    }
}


customer* create_customer(char* name, int points) {
    customer* person = (customer*) malloc(sizeof(customer));
    if (person == NULL) {
        return person;
    }

    person->name = (char*) malloc(sizeof(char) * NAME_LENGTH);
    if (person->name == NULL) {
        free(person);
        person = NULL;
        return person;
    }

    strcpy(person->name, name);
    person->points = points;
    person->node_depth = 0;
    return person;
}

node* init_node(char* name, int points) {
    node* temp = (node*) malloc(sizeof(node));
    
    if (temp == NULL) {
        return temp;
    }

    customer* person = create_customer(name, points);
    if (person == NULL) {
        free(temp);
        temp = NULL;
        return temp;
    }

    temp->person = person;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

void del_tree_node(node** root) {

    if ((*root)->left == NULL && (*root)->right == NULL) {
        printf("%s deleted\n", (*root)->person->name);
        free((*root)->person->name);
        free((*root)->person);
        free(*root);
    }

    else if ((*root)->left != NULL) {
        node* to_del = *root;
        *root = (*root)->left;
        printf("%s deleted\n", to_del->person->name);
        free(to_del->person->name);
        free(to_del->person);
        free(to_del);
    }

    else if ((*root)->right != NULL) {
        node* to_del = *root;
        *root = (*root)->right;
        printf("%s deleted\n", to_del->person->name);
        free(to_del->person->name);
        free(to_del->person);
        free(to_del);
    }

    else {
        node* max = largest_node((*root));
        printf("%s", max->person->name);
    }
}

node* largest_node(node* root) {

    if (root == NULL) {
        return root;
    }
    else if (root->right != NULL) {
        customer* temp = root->person;
        root->person = root->right->person;
        root->right->person = temp;
        largest_node(root->right);
    }
    else {
        return root;
    }    
}

node* search_tree(node* root, char* name, int last_node_flag) {
    if (root == NULL) {
        return root;
    }

    if (strcmp(name, root->person->name) == 0) {
        return root;
    }

    else if (strcmp(name, root->person->name) < 0) {

        if (root->left == NULL && last_node_flag == 1) {
            return root;
        }
        else {
            search_tree(root->left, name, last_node_flag);
        }
    }

    else if (strcmp(name, root->person->name) > 0) {

        if (root->right == NULL && last_node_flag == 1) {
            return root;
        }
        else {
            search_tree(root->right, name, last_node_flag);
        }
    }
}

void add_tree_node(node** root, char* name, int points) {

    node* temp = search_tree(*root, name, 1);

    if (temp == NULL) {
        temp = *root = init_node(name, points);
        printf("%s %d\n", temp->person->name, temp->person->points);
        return;
    }

    int result = strcmp(name, temp->person->name);

    // If the person exists in the tree, add the points
    if (result == 0) {
        temp->person->points += points;
        printf("%s %d\n", temp->person->name, temp->person->points);
    }

    // If the person's name comes (alphabetically) before the current node
    else if (result < 0) {

        if (temp->left == NULL) {
            node* new_node = init_node(name, points);
            temp->left = new_node;
            printf("%s %d\n", new_node->person->name, new_node->person->points);
            return;
        }
        else if (strcmp(name, temp->left->person->name) > 0) {
            node* new_node = init_node(name, points);
            new_node->left = temp->left;
            temp->left = new_node;
            printf("%s %d\n", new_node->person->name, new_node->person->points);
            return;
        }
        else {
            add_tree_node(&(temp->left), name, points);
        }
    }

    // If the person's name comes (alphabetically) after the current node
    else if (result > 0) {

        if (temp->right == NULL) {
            node* new_node = init_node(name, points);
            temp->right = new_node;
            printf("%s %d\n", new_node->person->name, new_node->person->points);
            return;
        }
        else if (strcmp(name, temp->right->person->name) < 0) {
            node* new_node = init_node(name, points);
            new_node->right = temp->right;
            temp->right = new_node;
            printf("%s %d\n", new_node->person->name, new_node->person->points);
            return;
        }
        else {
            add_tree_node(&(temp->right), name, points);
        }
    }
}

void sub_loyalty_points(node* root, char* name, int points) {

    node* temp = search_tree(root, name, 0);
    if (temp == NULL) {
        printf("%s not found\n", name);
        return;
    }

    if (strcmp(name, temp->person->name) == 0) {
        temp->person->points = (temp->person->points - points > 0) ? temp->person->points - points : 0;
        printf("%s %d\n", temp->person->name, temp->person->points);
    }
}