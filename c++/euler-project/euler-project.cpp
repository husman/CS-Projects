#include "include/euler-project.h"


int smallest_multiple_of_one_through_n(int number) {
    int smallest_multiple = 1;
    bool found_smallest = false;

    while(!found_smallest) {
        found_smallest = true;

        for(int i=number; i>0; --i)
            if(smallest_multiple % i != 0) {
                ++smallest_multiple;
                found_smallest = false;
                break;
            }

        if(found_smallest)
            break;

    }

    return smallest_multiple;
}

void print_tree_post_order(tree *t) {
    if(t != NULL) {
        print_tree_post_order(t->left);
        print_tree_post_order(t->right);
        printf("%c ", t->value);
    }
}

void print_tree_left_level(tree *t, int level) {
    static int current_level = 0;
    if(t != NULL) {
        if(current_level == level - 1) {
            if(t->left != NULL)
                printf("%c ", t->left->value);
            if(t->right != NULL)
                printf("%c ", t->right->value);
        } else {
            ++current_level;
            print_tree_left_level(t->left, level);
        }
    }
}
void print_tree_lowest_level_order(tree *t) {
    if(t == NULL)
        return;

    int level = -1;
    tree *root = t, *tmp = t;

    // Find the level of the lowest left-most subtree
    while(tmp != NULL) {
        ++level;
        tmp = tmp->left;
    }

    while(level > -1) {
        printf("\nprinting level == %d\n", level);
        print_tree_left_level(t, level);
        --level;
    }

    printf("%d ", level);
}

// level = 0
// print the lowest level of the left side of the tree and set the level to path
// print the right side of the tree with the given level
// decrement the level by 1 and print the left tree and right tree at the given levels
// continue to decrement the level until back at zero. Print zeroth level.
