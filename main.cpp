#include <iostream>
#include <queue>
#include <stack>

using namespace std;

//二叉树节点
typedef struct node {
    char data;
    struct node *lchild, *rchild;
} BiTNode, *BiTree;

typedef enum Tag {
    Link, Thread
};//指针，线索
//二叉线索树
typedef struct thr_node {
    char data;
    Tag lTag;
    Tag rTag;
    struct thr_node *left;
    struct thr_node *right;
} BiThrNode, *BiThrTree;

//NLR创建二叉树
void createBT(BiTree &root) {
    char ch;
    scanf("%c", &ch);
    if (ch == ' ') {
        root = NULL;
    } else {
        if (!(root = (BiTree) malloc(sizeof(BiTNode)))) {
            exit(0);
        }
        root->data = ch;

        createBT(root->lchild);
        createBT(root->rchild);
    }
}

//NLR创建二叉树,以默认值初始化
char pre[] = {'H', 'D', 'A', ' ', ' ', 'C', ' ', 'B', ' ', ' ', 'G', 'F', ' ', 'E', ' ', ' ', ' '};//先序遍历序列
int current = 0;

void initBT(BiTree &root) {

    if (pre[current++] == ' ') {
        root = NULL;
    } else {
        if (!(root = (BiTree) malloc(sizeof(BiTNode)))) {
            exit(0);
        }
        root->data = pre[current - 1];

        initBT(root->lchild);
        initBT(root->rchild);
    }

}


void initThrBT(BiThrTree &root) {

    if (pre[current++] == ' ') {
        root = NULL;
    } else {
        if (!(root = (BiThrTree) malloc(sizeof(BiThrNode)))) {
            exit(0);
        }
        root->data = pre[current - 1];

        initThrBT(root->left);
        initThrBT(root->right);
    }

}


//递归
void preOrder(BiTree root) {

    if (root != NULL) {
        cout << root->data << ' ';
        preOrder(root->lchild);
        preOrder(root->rchild);
    }
}

//非递归
void preOrderByStack(BiTree root) {

    stack<BiTree> s;
    s.push(root);

    while (!s.empty()) {
        BiTree temp = s.top();
        s.pop();
        cout << temp->data << " ";

        if (temp->rchild != NULL) {        //先进右子树
            s.push(temp->rchild);
        }
        if (temp->lchild != NULL) {         //后进左子树
            s.push(temp->lchild);
        }
    }

}

void inOrder(BiTree root) {

    if (root != NULL) {
        inOrder(root->lchild);
        cout << root->data << ' ';
        inOrder(root->rchild);
    }
}

void inOrderByStack(BiTree root) {

    stack<BiTree> s;
    s.push(root);
    BiTree p;

    while (!s.empty()) {

        while (p = s.top(), p != NULL) {        //所有左下节点入栈
            s.push(p->lchild);
        }

        s.pop();                 //空指针退栈

        if (!s.empty()) {        //无左孩子则访问之，并将其右孩子入栈
            p = s.top();
            s.pop();
            cout << p->data << " ";
            s.push(p->rchild);
        }
    }

}

void pastOrder(BiTree root) {

    if (root != NULL) {
        pastOrder(root->lchild);
        pastOrder(root->rchild);
        cout << root->data << ' ';
    }
}

void pastOrderByStack(BiTree root) {

    stack<BiTree> s;

    //TODO

}

void levelOrder(BiTree root) {

    queue<BiTree> q;
    q.push(root);

    while (!q.empty()) {
        BiTree p = (BiTree) q.front();
        q.pop();
        cout << p->data << " ";
        if (p->lchild != NULL) {
            q.push(p->lchild);
        }
        if (p->rchild != NULL) {
            q.push(p->rchild);
        }
    }

}

int depth(BiTree root) {
    int ldepth, rdepth;

    if (root == NULL) {
        return 0;
    } else {
        ldepth = depth(root->lchild);
        rdepth = depth(root->rchild);
        return ldepth > rdepth ? ldepth + 1 : rdepth + 1;
    }

}

//叶子节点数
void countLeaf(BiTree root, int &count) {
    if (root != NULL) {
        if (root->lchild == NULL && root->rchild == NULL) {
            count++;
        }
        countLeaf(root->lchild, count);
        countLeaf(root->rchild, count);
    }
}


void printStack(stack<char> s) {
    stack<char> temp;
    while (!s.empty()) {
        temp.push(s.top());
        s.pop();
    }
    while (!temp.empty()) {
        cout << temp.top() << " ";
        temp.pop();
    }
    cout << endl;
}

//根节点到叶子的所有路径
void allPath(BiTree root, stack<char> &s) {

    if (root != NULL) {
        s.push(root->data);

        if (root->lchild == NULL && root->rchild == NULL) {
            printStack(s);
        } else {
            allPath(root->lchild, s);
            allPath(root->rchild, s);
        }
        s.pop();    //子节点全部遍历完后退栈
    }

}


//中序线索化二叉树
void inThread(BiThrTree p, BiThrTree &pre) {
    if (p != NULL) {
        inThread(p->left, pre);     //左子树线索化

        if (p->left == NULL) {      //修改当前的前驱线索
            p->lTag = Thread;
            p->left = pre;
        }
        if (pre->right == NULL) {   //修改前驱的后继线索
            pre->rTag = Thread;
            pre->right = p;
        }

        pre = p;        //保持pre指向p的前驱
        inThread(p->right, pre);    //右子树线索化
    }
}

void inOrderThread(BiThrTree &thr, BiThrTree root) {
    //初始化头结点
    thr = (BiThrTree) malloc(sizeof(BiThrNode));
    thr->lTag = Link;
    thr->rTag = Thread;
    thr->right = thr;

    if (root == NULL) {
        thr->left = thr;
    } else {
        thr->left = root;
        BiThrTree pre = thr;

        //中序线索化
        inThread(root, pre);

        //处理最后节点的线索化
        pre->rTag = Thread;
        pre->right = thr;
        thr->right = pre;
    }

}

//中序遍历中序线索化二叉树（按Link遍历）
void inOrderThr(BiThrTree thr) {
    if (thr != NULL) {

        if(thr->lTag==Link){
            inOrderThr(thr->left);
        }
        cout << "(" << thr->data << ",lTag:" << (thr->lTag == Link ? "Link" : "Thread")
                << ",rTag:"<< (thr->rTag == Link ? "Link" : "Thread") << ") ";
        if (thr->rTag==Link){
            inOrderThr(thr->right);
        }

    }
}

int main() {

    BiTree root;
    initBT(root);

    cout << "前、中、后、层次：" << endl;
    preOrder(root);
    cout << endl;
    preOrderByStack(root);
    cout << endl;
    inOrder(root);
    cout << endl;
    inOrderByStack(root);
    cout << endl;
    pastOrder(root);
    cout << endl;
    levelOrder(root);
    cout << endl;

    cout << "树高：" << depth(root) << endl;

    int count = 0;
    countLeaf(root, count);
    cout << "叶子节点数：" << count << endl;

    stack<char> s;
    allPath(root, s);

    current = 0;
    BiThrTree thr, inThr;
    initThrBT(thr);
    inOrderThread(inThr, thr);
    cout<<"中序线索化二叉树:"<<endl;
    inOrderThr(inThr);

    return 0;
}
