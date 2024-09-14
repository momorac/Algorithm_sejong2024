#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct Node
{
    struct Node *right;
    struct Node *left;
    int elem;
} typedef NODE;

NODE *getNode()
{
    NODE *new = (NODE *)malloc(sizeof(NODE));
    new->elem = 0;
    new->left = NULL;
    new->right = NULL;

    return new;
}

bool setLeaf(NODE *node, int a, int l, int r)
{
    bool isValid = false;

    // 대상이면
    if (node->elem == a)
    {
        if (l != 0)
        {
            NODE *left = getNode();
            left->elem = l;
            node->left = left;
        }
        if (r != 0)
        {
            NODE *right = getNode();
            right->elem = r;
            node->right = right;
        }
        // 노드에 값 저장하고 종료
        return true;
    }

    // 대상이 아니면
    if (!isValid)
    {
        // 왼쪽, 오른쪽 자식에 각각 수행
        if (node->left != NULL)
        {
            isValid = setLeaf(node->left, a, l, r);
        }
        if (node->right != NULL)
        {
            isValid = setLeaf(node->right, a, l, r);
        }
    }

    return false;
}

void inOrderTraverse(NODE *root)
{
    printf("%d", root->elem);
    if (root->left != NULL)
        inOrderTraverse(root->left);
    if (root->right != NULL)
        inOrderTraverse(root->right);
}

void traverse(NODE *root, char *com)
{
    if (root == NULL)
        return;

    printf(" %d", root->elem);

    if (*com == 'L')
    {
        traverse(root->left, com + 1);
    }
    else if (*com == 'R')
    {
        traverse(root->right, com + 1); 
    }
}

int main()
{

    int n;
    scanf("%d", &n);

    // 트리 루트 생성
    NODE *root = getNode();

    int a, l, r;
    scanf("%d %d %d", &a, &l, &r);

    root->elem = a;
    setLeaf(root, a, l, r);

    for (int i = 1; i < n; i++)
    {
        scanf("%d %d %d", &a, &l, &r);
        setLeaf(root, a, l, r);
    }

    int s;
    scanf("%d", &s);

    char command[101];

    for (int i = 0; i < s; i++)
    {
        getchar();
        scanf("%s", command);
        traverse(root, command);
        printf("\n");
    }

    return 0;
}