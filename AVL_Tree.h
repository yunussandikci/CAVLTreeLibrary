#ifndef YUNUSSANDICKI_AVLTREE
#define YUNUSSANDIKCI_AVLTREE

typedef struct LINKED_TREE_AVL_NODE_s *LINKED_TREE_AVL_NODE;
typedef struct LINKED_TREE_AVL_NODE_s{
    LINKED_TREE_AVL_NODE right;
    LINKED_TREE_AVL_NODE left;
    void *data;
    int height;
} LINKED_TREE_AVL_NODE_t[1];
typedef struct LINKED_TREE_AVL_s *LINKED_TREE_AVL;
typedef struct LINKED_TREE_AVL_s{
    LINKED_TREE_AVL_NODE root;
} LINKED_TREE_AVL_t[1];
LINKED_TREE_AVL LINKED_TREE_AVL_INIT() {
	LINKED_TREE_AVL newTree = (LINKED_TREE_AVL) malloc(sizeof(LINKED_TREE_AVL_t));
	newTree->root = NULL;
	return newTree;
}
LINKED_TREE_AVL_NODE AVL_TREE_NODE_INIT(void *data) {
	LINKED_TREE_AVL_NODE newNode = (LINKED_TREE_AVL_NODE) malloc(sizeof(LINKED_TREE_AVL_NODE_t));
	newNode->data = data;
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->height = 1;
	return newNode;
}
LINKED_TREE_AVL_NODE rightRotate(LINKED_TREE_AVL_NODE y)
{
    LINKED_TREE_AVL_NODE x = y->left;
    LINKED_TREE_AVL_NODE T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = getMax(getHeight(y->left), getHeight(y->right))+1;
    x->height = getMax(getHeight(x->left), getHeight(x->right))+1;
    return x;
}
LINKED_TREE_AVL_NODE leftRotate(LINKED_TREE_AVL_NODE x)
{
    LINKED_TREE_AVL_NODE y = x->right;
    LINKED_TREE_AVL_NODE T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = getMax(getHeight(x->left), getHeight(x->right))+1;
    y->height = getMax(getHeight(y->left), getHeight(y->right))+1;
    return y;
}

void LINKED_TREE_AVL_INSERT(LINKED_TREE_AVL tree, void *data){
	if(tree->root != NULL)
	{
		STACK nodeStack = STACK_INIT();
		LINKED_TREE_AVL_NODE currentNode = tree->root;
		while(1)
		{
			STACK_PUSH(nodeStack,currentNode);
			if(*(int *)data > *(int *)currentNode->data){
				if(currentNode->right == NULL){
					currentNode->right = AVL_TREE_NODE_INIT(data);
					break;
				}
				else{
					currentNode = currentNode->right;
				}		
			}
			else if(*(int *)data < *(int *)currentNode->data){			
				if(currentNode->left == NULL){
					currentNode->left = AVL_TREE_NODE_INIT(data);
					break;
				}
				else{
					currentNode = currentNode->left;
				}			
			}
			else{
				printf("Invalid Data\n");
				break;
			}
		}
		while(nodeStack->height > 0)
		{
			LINKED_TREE_AVL_NODE currentNode = STACK_POP(nodeStack);
			currentNode->height = 1 + getMax(getHeight(currentNode->left),getHeight(currentNode->right));	
			if(getBalance(currentNode) > 1 || getBalance(currentNode) < -1)
				makeRotation(tree,currentNode,STACK_POP(nodeStack));
		}
	}
	else{
		tree->root = AVL_TREE_NODE_INIT(data);
	}
}

void LINKED_TREE_AVL_PRINT(LINKED_TREE_AVL_NODE node,int i){
	if(node != NULL){
		LINKED_TREE_AVL_PRINT(node->right,i+1);
		int a;
		for(a=1;a<i;a++)
			printf("----");
		printf("%d\n",*(int *)node->data);
		LINKED_TREE_AVL_PRINT(node->left,i+1);
	}	
}

void LINKED_TREE_AVL_DEBUG(LINKED_TREE_AVL_NODE node){
	if(node != NULL)
	{
		LINKED_TREE_AVL_DEBUG(node->left);
		LINKED_TREE_AVL_DEBUG(node->right);
		printf("n:%d h:%d b:%d",*(int *)node->data,node->height,getBalance(node));
		if(node->left != NULL)
			printf(" left:%d",*(int *)node->left->data);
		if(node->right != NULL)
			printf(" right:%d",*(int *)node->right->data);
		printf("\n");
	}
}

#endif
