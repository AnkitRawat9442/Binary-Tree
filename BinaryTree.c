//___________________________BINARY TREE _____________________________________________//

#include <stdio.h>
#include <stdlib.h>
#define max(x, y) ((x > y) ? x : y)

/** Node of the tree
  [ [left][data][right] ]
      |     |      |
    left   data   right
    node   part    node
  address         address
***/
typedef struct nodeT
{
    int data;
    struct nodeT *left, *right;
} Tree;
//_______________________________________________________________________________//
/** node

      [ [node of tree] [next] ]
             |           |
         data part     address of
        which store     next node
        address Tree
        node
**/
typedef struct node
{
    Tree *data;
    struct node *next;
} queue, stack;

int heightOFTree(Tree *node);

//________________________________ Queue ___________________________________________//

// push the address node of Tree to the queue ( add at end )
void enqueue(queue **Q_Front, queue **Q_Rare, Tree *val)
{
    queue *newnode = (queue *)malloc(sizeof(queue));
    newnode->data = val;
    newnode->next = NULL;
    if ((*Q_Front) == NULL)
    {
        (*Q_Front) = newnode;
        (*Q_Rare) = newnode;
        return;
    }
    (*Q_Rare)->next = newnode;
    (*Q_Rare) = newnode;
}

// pop the address node of Tree from the queue (from first)
Tree *dequeue(queue **Q_Front)
{
    Tree *temp = (*Q_Front)->data;
    queue *temp1 = (*Q_Front);
    (*Q_Front) = temp1->next;
    free(temp1);
    return temp;
}

// check for empyt queue
int isEmptyQueue(queue *Q_Front)
{
    if (Q_Front == NULL)
        return 1;
    return 0;
}
//________________________________Stack______________________________________________//

// push the address node of the tree in the Stack
void push(stack **top, Tree *val)
{
    stack *newnode = (stack *)malloc(sizeof(stack));
    newnode->data = val;
    newnode->next = NULL;
    if ((*top) == NULL)
    {
        *top = newnode;
        return;
    }
    newnode->next = *top;
    *top = newnode;
}

// pop the address node from the stack (from top )
Tree *pop(stack **top)
{
    Tree *temp = (*top)->data;
    stack *temp1 = (*top);
    *top = temp1->next;
    free(temp1);
    return temp;
}

// check for stack empty
int isEmptyStack(stack *top)
{
    if (top == NULL)
        return 1;
    return 0;
}
//_____________________________________________________________________________//

// create a Tree Node
Tree *newNodeTree(int val)
{
    Tree *temp = (Tree *)malloc(sizeof(Tree));
    temp->data = val;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

// Create the tree
Tree *createTree()
{
    queue *start = NULL, *rare = NULL;
    int val, choice;
    Tree *root, *temp;
    printf("Enter the root val  : ");
    scanf("%d", &val);
    root = newNodeTree(val);
    enqueue(&start, &rare, root);
    while (!isEmptyQueue(start))
    {
        Tree *node = dequeue(&start);
        printf("node -> %d \n", node->data);
        printf("Enter left data :  ");
        scanf("%d", &val);
        if (val >= 0)
        {
            node->left = newNodeTree(val);
            enqueue(&start, &rare, node->left);
        }
        printf("Enter right data :  ");
        scanf("%d", &val);
        if (val >= 0)
        {
            node->right = newNodeTree(val);
            enqueue(&start, &rare, node->right);
        }
    }
    return root;
}
/***    _________ Recurssive Traversal ______________

                       1
                      / \
                     2   3
                    / \ / \
                   4  5 6  7

     1. PreOrder Traversal   -> O(n)   ->  1 2 4 5 3 6 7
     2. Inorder Traversal    -> O(n)   ->  4 2 5 1 6 3 7
     3. PostOrder Traversal  -> O(n)   ->  4 5 2 6 7 3 1
     4. LevelWise Traversal  ->o(n)    ->  1 2 3 4 5 6 7
     5. Reverse Level Order Traversal  ->  4 5 6 7 2 3 1
***/

// __ 1. Preorder traversal
void preorder(Tree *root)
{
    if (root != NULL)
    {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

// ___ 2.  Inorder traversal
void inorder(Tree *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

// ___ 3. Postorder traversal
void postorder(Tree *root)
{
    if (root != NULL)
    {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

// ___ 4. LevelWise Recurssive traversal
void printLevelData(Tree *node, int level)
{
    if (node == NULL)
        return;
    else if (level == 1)
        printf("%d ", node->data);
    else
    {
        printLevelData(node->left, level - 1);
        printLevelData(node->right, level - 1);
    }
}
void LevelWiseRcurssive(Tree *node)
{
    int height = heightOFTree(node);
    for (int i = 1; i <= height; i++) // i >= 1; --i)
    {
        printLevelData(node, i);
    }
    printf("\n");
}

// ____ 5. Rverse Level Order Traversal
void reversalLevelOrderTraversalRecursive(Tree *node)
{
    int height = heightOFTree(node);
    for (int i = height; i >= 1; --i)
    {
        printLevelData(node, i);
    }
    printf("\n");
}

// ________________________________________________________________________________//

/***   __________________________  Iterative Traversals _____________________________

                       1
                      / \
                     2   3
                    / \ / \
                   4  5 6  7

     1. PreOrder Traversal   -> O(n)   ->  1 2 4 5 3 6 7
     2. Inorder Traversal    -> O(n)   ->  4 2 5 1 6 3 7
     3. PostOrder Traversal  -> O(n)   ->  4 5 2 6 7 3 1
     4. LevelWise Traversal  ->o(n)    ->  1 2 3 4 5 6 7
     5. Reverse Level Order Traversal  ->  4 5 6 7 2 3 1


****/

//______ 1. PreOrder Iterative Traversals
void preorderIT(Tree *node)
{
    stack *top = NULL;
    while (node != NULL || !isEmptyStack(top))
    {
        if (node != NULL)
        {
            printf("%d ", node->data);
            push(&top, node);
            node = node->left;
        }
        else
        {
            node = pop(&top);
            node = node->right;
        }
    }
    printf("\n");
}

//______ 2. InOrder Iterative Traversals
void inorderIT(Tree *node)
{
    stack *top = NULL;
    while (node != NULL || !isEmptyStack(top))
    {
        if (node != NULL)
        {
            push(&top, node);
            node = node->left;
        }
        else
        {
            node = pop(&top);
            printf("%d ", node->data);
            node = node->right;
        }
    }
    printf("\n");
}

/****
                       1
                      / \
                     2   3
                    / \ / \
                   4  5 6  7

   1. first root val 1 is pushed into stack1
        | 1 |        |   |
        |___|        |___|
        stack1       stack2

    while (stack1 not empty ) -> repeat step 2
   2.  val (1) from stack1 is poped and pushed into stack2 , then left and right node
       is pushed into stack1 if any .
        |  |         | 1 |          | 3 |
        |__|         |___|  ---->>  |___|
       stack1        stack2         | 2 |
                                    |___|
                                    stack1

   3.
      | 2 |          | 3 |              | 7 |
      |___|          |___|              |___|
      stack1         | 1 |     ----->   | 6 |
                     |___|              |___|
                    stack2              | 2 |
                                        |___|
                                        stack1

   while (stack2 not empty ) -> repeat step 4
       4 . pop and print stack2 .


  ***/
//______ 3. PostOrder Iterative Traversals
void postorderIT(Tree *node)
{
    stack *top1 = NULL, *top2 = NULL;
    if (node != NULL)
    {
        push(&top1, node);
    }
    while (!isEmptyStack(top1))
    {
        node = pop(&top1);
        push(&top2, node);
        if (node->left != NULL)
            push(&top1, node->left);
        if (node->right != NULL)
            push(&top1, node->right);
    }
    while (!isEmptyStack(top2))
    {
        node = pop(&top2);
        printf("%d ", node->data);
    }
    printf("\n");
}
// ____ 4. levelWise Traversal
void levelWise(Tree *node)
{
    queue *start = NULL, *rare = NULL;
    if (node != NULL)
    {
        enqueue(&start, &rare, node);
    }
    while (!isEmptyQueue(start))
    {
        node = dequeue(&start);
        printf("%d ", node->data);
        if (node->left != NULL)
            enqueue(&start, &rare, node->left);
        if (node->right != NULL)
            enqueue(&start, &rare, node->right);
    }
    printf("\n");
}

// __ 5. Reverse Level Order Traversal Iterative
void reversalLevelOrderTraversalIterative(Tree *node)
{
    queue *start = NULL, *end = NULL;
    stack *top = NULL;
    if (node != NULL)
        enqueue(&start, &end, node);
    while (!isEmptyQueue(start))
    {
        node = dequeue(&start);
        push(&top, node);
        if (node->right != NULL)
            enqueue(&start, &end, node->right);
        if (node->left != NULL)
            enqueue(&start, &end, node->left);
    }
    while (!isEmptyStack(top))
    {
        node = pop(&top);
        printf("%d ", node->data);
    }
    printf("\n");
}

// _________________________height of the Binary Tree ________________________________//

int heightOFTree(Tree *node) // time complexity -> O(n)
{
    if (node == NULL)
    {
        return 0;
    }
    int leftHeight = heightOFTree(node->left);
    int rightHeight = heightOFTree(node->right);
    return max(leftHeight, rightHeight) + 1;
}

//_________________________number of node in the Binary tree _______________________//

// number of node
int numbOFNode(Tree *node) // time complexity -> O(n)
{
    if (node == NULL)
    {
        return 0;
    }
    int numberOfNodeINLeft = numbOFNode(node->left);
    int numberOfNodeINRight = numbOFNode(node->right);
    return numberOfNodeINLeft + numberOfNodeINRight + 1;
}

// number of leaf node
int numbOFLeafNode(Tree *node) // time complexity -> O(n)
{
    if (node == NULL)
        return 0;
    else if (node->left == NULL && node->right == NULL)
    {
        return 1;
    }
    int numberOfLeafNodeINLeft = numbOFLeafNode(node->left);
    int numberOfLeafNodeINRight = numbOFLeafNode(node->right);
    return numberOfLeafNodeINLeft + numberOfLeafNodeINRight;
}

//____________________________Diameter Of Tree  __________________________________//

/**
int diameter(Tree *node ) // time cpmplexity -> o(n^2)
{
    if (node == NULL)
    {
        return 0;
    }
    int leftheight = heightOFTree(node->left);
    int rightheight = heightOFTree(node->right);
    int leftdiameter = diameter(node->left);
    int rightdiameter = diameter(node->right);
    int currentDiameter = leftheight + rightheight + 1;
    return max(currentDiameter, max(leftdiameter, rightdiameter));
}
**/

// optimise Version to find diamter of tree in O(n) time complexity
int diameterOPtimise(Tree *node, int *height) // time cpmplexity -> o(n)
{
    if (node == NULL)
    {
        *height = 0;
        return 0;
    }
    int leftheight = 0, rightheight = 0;
    int leftdiameter = diameterOPtimise(node->left, &leftheight);
    int rightdiameter = diameterOPtimise(node->right, &rightheight);
    *height = max(leftheight, rightheight) + 1;
    int currentDiameter = leftheight + rightheight + 1;
    return max(currentDiameter, max(leftdiameter, rightdiameter));
}

//___________________________Mirror / Symmetric Tree _________________________//

/****
// Iterative Approach To find Mirror Tree 
void mirrorTree(Tree **root) //   time complexity -> O(n)
{
    Tree *node, *temp;
    queue *start = NULL, *end = NULL;
    if (root != NULL)
        enqueue(&start, &end, *root);
    while (!isEmptyQueue(start))
    {
        node = dequeue(&start);
        temp = node->left;
        node->left = node->right;
        node->right = temp;
        if (node->left != NULL)
        {
            enqueue(&start, &end, node->left);
        }
        if (node->right != NULL)
        {
            enqueue(&start, &end, node->right);
        }
    }
}
****/
// Recurssive Function to find Mirror Tree 
void mirror(Tree **node)  //    time complexity -> O(n)
{
    Tree *temp;
    if (*node == NULL)
        return;
    temp = (*node)->left;
    (*node)->left = (*node)->right;
    (*node)->right = temp;

    mirror(&((*node)->left));
    mirror(&((*node)->right));
}



// _________________________________________________________________________________________________//
int main()
{
    printf("Hello , this is Ankit Rawat \n");
    int height = 0;
    Tree *Root = createTree();
    printf("\npreorder Recursive  : ");
    preorder(Root);
    printf("\npreorder Iterative  : ");
    preorderIT(Root);
    printf("inorder Recursive     : ");
    inorder(Root);
    printf("\ninorder Iterative   : ");
    inorderIT(Root);
    printf("postorder Recursive   : ");
    postorder(Root);
    printf("\npostorder Iterative : ");
    postorderIT(Root);
    printf("LevelWise Recursive  Traversal   : ");
    LevelWiseRcurssive(Root);
    printf("LevelWise Iterative Traversal    : ");
    levelWise(Root);
    printf("Reverse Level Order Traversal Recusive   : ");
    reversalLevelOrderTraversalRecursive(Root);
    printf("Reverse Level Order Traversal iterative  : ");
    reversalLevelOrderTraversalIterative(Root);
    printf("Height of the Tree is           : %d\n", heightOFTree(Root));
    printf("number of node in Tree  is      : %d\n", numbOFNode(Root));
    printf("number of Leafnode in Tree  is  : %d\n", numbOFLeafNode(Root));
    printf("diameter of th tree             : %d \n", diameterOPtimise(Root, &height)); // O(n)
                                                                                        //  printf("diameter of th tree             : %d \n", diameter(Root));  // o(n^2)
    printf("______________________________\n");
    printf("Original Tree : ");
    levelWise(Root);
    mirrorTree(&Root);
    printf("Mirror Tree   : ");
    levelWise(Root);
    // mirror(&Root);
    // printf("Original Tree : ");
    // levelWise(Root);
    return 0;
}
