#include <iostream>
using namespace std;

//二叉树节点
typedef struct node{
    char data;
    struct node *lchild,*rchild;
}BiTNode,*BiTree;

//NLR创建二叉树
void createBT(BiTree &root){
    char temp;
    scanf("%c",&temp);
    if (temp==' '){
        root=NULL;
    } else{
        if (!(root=(BiTree)malloc(sizeof(BiTNode)))){
            exit(0);
        }
        root->data=temp;

        createBT(root->lchild);
        createBT(root->rchild);
    }
}

//NLR创建二叉树,以默认值初始化
char temp[]={'H','D','A',' ',' ','C',' ','B',' ',' ','G','F',' ','E',' ',' ',' '};//先序遍历序列
int current=0;
void initBT(BiTree &root){

    if (temp[current++]==' '){
        root=NULL;
    } else{
        if (!(root=(BiTree)malloc(sizeof(BiTNode)))){
            exit(0);
        }
        root->data=temp[current-1];

        initBT(root->lchild);
        initBT(root->rchild);
    }
}


void preOrder(BiTree root){

    if (root!=NULL){
        cout<<root->data<<' ';
        preOrder(root->lchild);
        preOrder(root->rchild);
    }
}

void inOrder(BiTree root){

    if (root!=NULL){
        inOrder(root->lchild);
        cout<<root->data<<' ';
        inOrder(root->rchild);
    }
}

void backOrder(BiTree root){

    if (root!=NULL){
        backOrder(root->lchild);
        backOrder(root->rchild);
        cout<<root->data<<' ';
    }
}



int main() {

    BiTree root;
    initBT(root);

    cout<<"递归前中后序:"<<endl;
    preOrder(root);
    cout<<endl;
    inOrder(root);
    cout<<endl;
    backOrder(root);
    cout<<endl;



    return 0;
}
