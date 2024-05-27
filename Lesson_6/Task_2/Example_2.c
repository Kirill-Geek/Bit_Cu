#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int sum = 0;
typedef struct tree
{
    int key;
    struct tree *left, *right;
    struct tree *parent;
} tree;

int heightTree(tree *p)
{
    if (p == NULL)
        return 0;
    else
    {
        /* вычисляем высоту каждого поддерева */
        int lheight = heightTree(p->left);
        int rheight = heightTree(p->right);
        if (lheight > rheight)
        {
            return (lheight + 1);
        }

        else
        {
            return (rheight + 1);
        }
    }
}

int printCurrentLevel(tree *root, int level)
{

    if (root == NULL)
        return 0;
    if (level == 1)
    {
        sum = sum + root->key;
        printf("%d \n", root->key);
    }
    else if (level > 1)
    {

        printCurrentLevel(root->left, level - 1);
        printCurrentLevel(root->right, level - 1);
    }
    return sum;
}
void printBFS(tree *root)
{
    int count;
    int h = heightTree(root);
    for (int i = 1; i <= h; i++)
    {
        count = printCurrentLevel(root, i);
        
    }
    printf("Sum Tree = %d \n", count);
}

void insert(tree **root, int key, tree *pt)
{

    if (!(*root))
    {
        *root = (tree *)calloc(1, sizeof(tree));
        (*root)->key = key;
        (*root)->parent = pt;
    }
    else if (key < (*root)->key)
    {
        insert(&((*root)->left), key, *root);
    }
    else
    {
        insert(&((*root)->right), key, *root);
    }
}

int main(void)
{
    tree *tr = NULL;

    insert(&tr, 10, NULL);
    insert(&tr, 5, NULL);
    insert(&tr, 15, NULL);
    insert(&tr, 3, NULL);
    insert(&tr, 17, NULL);
    insert(&tr, 8, NULL);
    insert(&tr, 13, NULL);
    insert(&tr, 1, NULL);

 
    printBFS(tr);
}