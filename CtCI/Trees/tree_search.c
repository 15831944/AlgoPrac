/*�����ݽṹ���㷨����-c���������桷
 *���������
 *���롢ɾ��������������ÿ�
 * */

#include "stdio.h"

/*�����������������ݽṹ*/
struct BSTreeNode{
    struct BSTreeNode *left;
    struct BSTreeNode *right;
    struct BSTreeNode *parent;
    int key;
};

/* ������СԪ�� */
struct BSTreeNode * find_min(struct BSTreeNode *TN){
    if (TN->left == NULL) {
        return TN;
    }else{
        return find_min(TN->left);
    }
}

/*ɾ��һ���ڵ�*/
/* 1�����TN��������Ϊ�գ�ֻ��Ҫɾ��TN
 * 2�����TN��һ������Ϊ�գ�ֻ�轫�ú������TN�ĵ�
 * ��TN->left->parent = TN->pparent;TN->parent->left = TN->left��
 * 3�����TN���������Ӷ��ڣ���Ҫ�ҵ�TN�ĺ�̣������滻TN*/
void delete(struct BSTreeNode *TN){
	//case1:
	if(TN->left == NULL && TN->right == NULL){
		//free(TN);
		TN = NULL;
	}else if(TN->right == NULL){//case 2:
		TN->left->parent = TN->parent;
		if(TN == TN->parent->left) TN->parent->left = TN->left;
		else if(TN == TN->parent->right) TN->parent->right = TN->left;
	}else if(TN->left == NULL){
		if(TN == TN->parent->left) TN->parent->left = TN->right;
		else if(TN == TN->parent->right) TN->parent->right = TN->right;
	}else{//case 3:
		struct BSTreeNode *min = find_min(TN->right);
		if(min == TN->right){//case 3.1 min is the right child of TN
			if(TN == TN->parent->left) {
                TN->parent->left = TN->right;
                TN->right->parent = TN->parent;
                TN->right->left = TN->left;
                TN->left->parent = TN->right;
            }
			else if(TN == TN->parent->right) {
                TN->parent->right = TN->right;
                TN->right->parent = TN->parent;
                TN->right->left = TN->left;
                TN->left->parent = TN->right;
            }
		}else{//case 3.2 min is not the right child of TN
			min->right->parent = min->parent;
			min->parent->left = min->right;
			if(TN == TN->parent->left) {
				TN->parent->left = min;
				min->parent = TN->parent;
				min->left = TN->left;
				min->right = TN->right;
				TN->left->parent = min;
				TN->right->parent = min;
			}
			else if(TN == TN->parent->right){
				TN->parent->right = TN->right;
				min->parent = TN->parent;
				min->left = TN->left;
				min->right = TN->right;
				TN->left->parent = min;
				TN->right->parent = min;
			}
		}
	}
}

/*Make a tree to be an empty tree*/
struct BSTreeNode* make_empty(struct BSTreeNode * T){
	if(T != NULL){
		make_empty(T->left);
		make_empty(T->right);
		free(T);
	}
	return NULL;
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

/*�������*/
void inorder_treewalk(struct BSTreeNode *T){
	if (T != NULL){
		inorder_treewalk(T->left);
		printf("%d\n",T->key);
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
    delete(root->left->right);
	inorder_treewalk(root);
	
	return 1;
}
