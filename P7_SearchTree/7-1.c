#include <stdio.h>
#include <stdlib.h>

struct Node
{
    struct Node *parent;
    struct Node *leftChild;
    struct Node *rightChild;
    struct Node *key;
} typedef NODE;



int main()
{

    NODE *root = (NODE *)malloc(sizeof(NODE));
    

    char command;
    while (1)
    {
        scanf("%c", &command);

        if (command == 'q')
            break;
        else if (command == 'i')
        {
        }
    }

    return 0;
}