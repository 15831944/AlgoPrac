/*��Craking the code interview>��P86-4.8
 * You have two very large binary trees:T1,with millions of nodes,and T2,with hundreds of nodes.Create an algorithm to decide if T2 is a sbutree of T1.
 * A tree T2 is a subtree of T1 if there exists a node n in T1 such that the subtree of n is identical to T2. That is,if you cut off the tree at node n, the two trees would be identical.
 *
 * �������һ�����Ľⷨ��������ÿT1��һ���ڵ㣬�����ж��Ըýڵ���Ϊ�����ǲ��Ǻ�T2��ͬ������
 * ���������������T1��T2��������������������ͨ�������Ӵ��ķ�ʽ����������
 * ���T2�������������T1�������������Ӵ�����ôT2��T1���Ӵ���
 * */


#include "stdio.h"
#include <stdlib.h>
/*�����������������ݽṹ*/
struct BSTreeNode{
    struct BSTreeNode *left;
    struct BSTreeNode *right;
    struct BSTreeNode *parent;
    int key;
};

/*�ж�TN2��TN1�ǲ���һ��*/
int is_same_tree(struct BSTreeNode *TN1,struct BSTreeNode *TN2){
	/*if(TN1 == NULL && TN2 == NULL) return 1;
	else if(TN1->key == TN2->key)
		return is_same_tree(TN1->left,TN2->left) && is_same_tree(TN1->right,TN2->right);
	else return 0;*/
	//if TN == NULL,then you call TN->key,it will report runtime errors.
	if(TN1 == NULL && TN2 == NULL) return 1;
    else if (TN1 != NULL && TN2 == NULL) return 0;
    else if (TN1 == NULL && TN2 != NULL) return 0;
	else if(TN1->key == TN2->key)
		return is_same_tree(TN1->left,TN2->left) && is_same_tree(TN1->right,TN2->right);
	else return 0;
}

/*�������*/
int preorder_search(struct BSTreeNode *TN1,struct BSTreeNode *TN2){
	int result = 0;
	if(TN1->key == TN2->key) result = is_same_tree(TN1,TN2);
	if(result!=1 && TN1->left !=NULL)
		result = preorder_search(TN1->left,TN2);
	if(result!=1 && TN1->right != NULL)
		result = preorder_search(TN1->right,TN2);
    
	return result;
}

/*�ж�TN2�ǲ���TN1������*/
int is_subtree(struct BSTreeNode *TN1,struct BSTreeNode *TN2){
	if(TN1 == NULL && TN2 == NULL) return 1;
	//empty tree is always the subtree
	if(TN1 != NULL && TN2 == NULL) return 1;
	return preorder_search(TN1,TN2);
}


/*����ڵ�*/
struct BSTreeNode* insert(int key,struct BSTreeNode *T){
	if(T != NULL){
		if(key < T->key){
			T->left = insert(key,T->left);
            T->left->parent = T;
		}else{
			T->right = insert(key,T->right);
            T->right->parent = T;
		}
	}else{
		struct BSTreeNode *new_node = malloc(sizeof(struct BSTreeNode));
		if (new_node == NULL){
			//FatalError("Out of space");
			printf("Out of space");
		}else{
			new_node->left = new_node->right = new_node->parent = NULL;
			new_node->key = key;
            T = new_node;
		}
	}
	return T;
}

int main(){
	struct BSTreeNode *tree1 = NULL,*tree2 = NULL;
    int a[] = {9,4,7,3,2,8,6,5,1};
	int i;
    tree1 = insert(a[0],tree1);
	for(i = 1;i < 9;i++){
        insert(a[i],tree1);
	}
    //delete(root->left->right);
	//inorder_treewalk(root);
	//
	tree2 = insert(7,tree2);
	insert(6,tree2);
	//insert(5,tree2);
	insert(8,tree2);
    
	int result;
	result = is_subtree(tree1,tree2);
	printf("is subtree %d\n",result);
	return 1;
}
