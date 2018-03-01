#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"
#include "AVL_Tree.h"

int getMax(int a, int b){
    return (a > b)? a : b;
}

int getHeight(LINKED_TREE_AVL_NODE N){
    if (N == NULL)
        return 0;
    else
    	return N->height;
}

int getBalance(LINKED_TREE_AVL_NODE N){
    if (N == NULL)
        return 0;
    else
    	return getHeight(N->left) - getHeight(N->right);
}

int getRotationType(LINKED_TREE_AVL_NODE N)
{
	if(getBalance(N) > 1)
		if(getBalance(N->left) > 0)
			return 1;
		else
			return 2;
	else if(getBalance(N) < -1)
		if(getBalance(N->right) < 0)
			return 3;
		else
			return 4;
	else
		return 0;
}

void makeRotation(LINKED_TREE_AVL tree,LINKED_TREE_AVL_NODE currentNode, LINKED_TREE_AVL_NODE grandParent)
{	
	switch(getRotationType(currentNode)){
		case 1:
			if(tree->root == currentNode)
				tree->root = rightRotate(currentNode);
			else
				if(currentNode == grandParent->left)
					grandParent->left = rightRotate(currentNode);
				else
					grandParent->right = rightRotate(currentNode);
			break;
		case 2:
			currentNode->left = leftRotate(currentNode->left);
			if(tree->root == currentNode)
				tree->root = rightRotate(currentNode);
			else
			{
				if(currentNode == grandParent->right)
					grandParent->right = rightRotate(currentNode);
				else
					grandParent->left = rightRotate(currentNode);	
			}
			break;
		case 3:
			if(tree->root == currentNode)
				tree->root = leftRotate(currentNode);
			else
				if(currentNode == grandParent->right)
					grandParent->right = leftRotate(currentNode);
				else
					grandParent->left = leftRotate(currentNode);
			break;
		case 4:
			currentNode->right = rightRotate(currentNode->right);
			if(tree->root == currentNode)
				tree->root = leftRotate(currentNode);
			else
			{
				if(currentNode == grandParent->left)
					grandParent->left = leftRotate(currentNode);
				else
					grandParent->right = leftRotate(currentNode);	
			}
			break;
	}
}

int main()
{
	int arr[15] = {23,26,44,9,5,4,15,30,17,14,11,2,3,7,50};
	LINKED_TREE_AVL myTree = LINKED_TREE_AVL_INIT();
	int i;
	for(i=0;i<sizeof(arr)/sizeof(int);i++){
		LINKED_TREE_AVL_INSERT(myTree,&arr[i]);
	}
	printf("\n\n");
	LINKED_TREE_AVL_PRINT(myTree->root,1);
}

