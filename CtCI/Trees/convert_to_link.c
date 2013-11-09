/*
 *������������ת�����ź���Ķ�������
 * ��ѡ΢������ݽṹ+�㷨����100�� No.1
1.�Ѷ�Ԫ������ת��������˫������
��Ŀ: ����һ�ö�Ԫ������,���ö�Ԫ������ת����һ�������˫������ Ҫ���ܴ����κ��µĽ��,ֻ����ָ���ָ��
	 10
  	 /\ 
	6 14 
   / \/ \
  4 8 12 16 
  ת����˫������ 4=6=8=10=12=14=16��
 
*/

#include "stdio.h"
#include <stdlib.h>

/*�����������������ݽṹ*/
struct BSTreeNode{
    struct BSTreeNode *left;
    struct BSTreeNode *right;
    int key;
};

/*��Ҫȫ�ֱ�����pHead��ʾ˫����ı�ͷ
��Ϊ�������½��ڵ㣬��ͷ���ǵ�һ����һ���ڵ�
currentָʾ��ǰ˫��������һ���ڵ�*/
struct BSTreeNode *pHead,*currentIndex;

/*��һ���µĽڵ���뵽˫������*/
void append_to_list(struct BSTreeNode *current){
	if(current == NULL) return;
	current->left = currentIndex;
	if(currentIndex == NULL){//��һ�ν���ú���
		pHead = current;//Ҫ����pHead
	}else{
		currentIndex ->right = current;
	}
	currentIndex = current;
}

/*����ڵ�*/
struct BSTreeNode* insert(int key,struct BSTreeNode *T){
	if(T != NULL){
		if(key < T->key){
			T->left = insert(key,T->left);
 		}else{
			T->right = insert(key,T->right);
		}
	}else{
		struct BSTreeNode *new_node = malloc(sizeof(struct BSTreeNode));
		if (new_node == NULL){
			//FatalError("Out of space");
			printf("Out of space");
		}else{
			new_node->left = new_node->right = NULL;
			new_node->key = key;
            T = new_node;
		}
	}
	return T;
}

/*�������*/
void inorder_treewalk(struct BSTreeNode *T){
	if (T != NULL){
		inorder_treewalk(T->left);
		printf("%d\n",T->key);
		append_to_list(T);
		inorder_treewalk(T->right);
	}
}

int main(){
	struct BSTreeNode *root = NULL;
    int a[] = {9,4,7,3,2,8,6,5,1};
	int i;
    root = insert(a[0],root);
	for(i = 1;i < 9;i++){
        insert(a[i],root);
	}
	pHead = NULL;
	currentIndex = NULL;
	inorder_treewalk(root);
	
	return 1;
}
