#include <stdio.h>
#include <stdlib.h>

struct n
{
    int data;
    struct n * left;
    struct n * right;
};
typedef struct n node;

node * makeTree(node * tree, int x){
    if(tree == NULL){
        node * root = (node*)malloc(sizeof(node));
        root->left = NULL;
        root->right = NULL;
        root->data = x;
        return root;
    }

    if(tree->data < x ){
            tree->right = makeTree(tree->right,x);
            return tree;
    }
    tree->left = makeTree(tree->left,x);
    return tree;
}

void travinfix(node * tree){
    if(tree == NULL)
        return;
    travinfix(tree->left);
    printf("%d ", tree->data);
    travinfix(tree->right);
}
int find(node * tree,int wanted){
    if(tree == NULL)
        return-1;
    if(tree->data == wanted)
        return 1;
    if(find(tree->right,wanted) == 1)
        return 1;
    if(find(tree->left,wanted) == 1)
        return 1;
    return -1;
}

int maximum(node *tree)
{
    if (tree == NULL)
        return -1; 
    while (tree->right != NULL)
        tree = tree->right;
    return tree->data;
}

int minimum(node *tree)
{
    if (tree == NULL)
        return -1; 
    while (tree->left != NULL)
        tree = tree->left;
    return tree->data;
}
node *delete(node *tree, int x)
{
    if (tree == NULL)
        return NULL;

    if (x < tree->data)
    {
        tree->left = delete(tree->left, x);
    }
    else if (x > tree->data)
    {
        tree->right = delete(tree->right, x);
    }
    else
    {
        if (tree->left == NULL)
        {
            node *temp = tree->right;
            free(tree);
            return temp;
        }
        else if (tree->right == NULL)
        {
            node *temp = tree->left;
            free(tree);
            return temp;
        }

        tree->data = minimum(tree->right);
        tree->right = delete(tree->right, tree->data);
    }
    return tree;
}

int main(){
    node * tree = NULL;
    tree = makeTree(tree,15);
    tree = makeTree(tree,1235);
    tree = makeTree(tree,193);
    tree = makeTree(tree,14);
    tree = makeTree(tree,25);
    tree = makeTree(tree,2);
    travinfix(tree);

    printf("\nArama sonucu: %d",find(tree,15));
    printf("\nMax: %d",maximum(tree));
    printf("\nMin: %d",minimum(tree));

    printf("\n");

    tree = delete(tree,25);
    tree = delete(tree,1235);
    travinfix(tree);
    return 0;
}