/*
（1）按给定数据序列及其顺序构建二叉排序树；
（2）按给定数据序列及其顺序构建平衡二叉树；
（3）计算并输出二叉排序树中所有数据元素在查找等概率下的平均查找长度；
（4）计算并输出平衡二叉树中所有数据元素在查找等概率下的平均查找长度。
*/
#include <iostream>
#include <cstdlib>
#include <algorithm>

using namespace std;

typedef struct TreeNode {
    int num;
    int deep;
    int bf;
    TreeNode *left;
    TreeNode *right;
} *Tree;

Tree build_bst(Tree p, Tree t) {
    Tree n;
    n = t;
    int i = 1;
    if (t->num == -1) {
        t->num = p->num;
        t->deep = i;
    } else {
        while (true) {
            i++;
            if (p->num < n->num) {
                if (n->left == NULL) {
                    p->deep = i;
                    n->left = p;
                    break;
                } else {
                    n = n->left;
                }
            } else {
                if (n->right == NULL) {
                    p->deep = i;
                    n->right = p;
                    break;
                } else {
                    n = n->right;
                }
            }
        }
    }
    return t;
}

int get_deep(TreeNode *t) {
    if (t == NULL)
        return -1;
    else
        return t->deep;
}

bool is_balanced(TreeNode *left, TreeNode *right) {
    return abs(get_deep(left) - get_deep(right)) < 2;
}

TreeNode *single_rotate_left(TreeNode *t2) {
    TreeNode *t1;
    t1 = t2->left;
    t2->left = t1->right;
    t1->right = t2;

    t2->deep = max(get_deep(t2->left), get_deep(t2->right)) + 1;
    t1->deep = max(get_deep(t1->left), get_deep(t1->right)) + 1;
    return t1;
}

TreeNode *single_rotate_right(TreeNode *t2) {
    TreeNode *t1;
    t1 = t2->right;
    t2->right = t1->left;
    t1->left = t2;

    t2->deep = max(get_deep(t2->left), get_deep(t2->right)) + 1;
    t1->deep = max(get_deep(t1->left), get_deep(t1->right)) + 1;
    return t1;
}

TreeNode *double_rotate_lr(TreeNode *t3) {
    t3->left = single_rotate_right(t3->left);
    return single_rotate_left(t3);
}

TreeNode *double_rotate_rl(TreeNode *t3) {
    t3->right = single_rotate_left(t3->right);
    return single_rotate_right(t3);
}

TreeNode *insert(int v, TreeNode *root) {
    if (root == NULL) {
        root = (Tree)malloc(sizeof(TreeNode));
        root->num = v;
        root->left = NULL;
        root->right = NULL;
        root->deep = 0;
        return root;
    }
    if (v > root->num) { //节点插入在右子树中
        root->right = insert(v, root->right);
        if (!is_balanced(root->left, root->right)) {
            if (v > root->right->num)
                root = single_rotate_right(root);
            else
                root = double_rotate_rl(root);
        }
    } else {
        root->left = insert(v, root->left);
        if (!is_balanced(root->left, root->right)) {
            if (v < root->left->num)
                root = single_rotate_left(root);
            else
                root = double_rotate_lr(root);
        }
    }
    root->deep = max(get_deep(root->left), get_deep(root->right)) + 1;
    return root;
}

int bst_avl(Tree t) {
    if (t->left == NULL && t->right == NULL) {
        return t->deep;
    } else {
        if (t->left == NULL) {
            return bst_avl(t->right) + t->deep;
        }
        if (t->right == NULL) {
            return bst_avl(t->left) + t->deep;
        }
    }
    return t->deep + bst_avl(t->left) + bst_avl(t->right);
}

void fun(Tree t) {
    if (t->left != NULL) {
        t->left->deep = t->deep + 1;
        fun(t->left);
    }
    if (t->right != NULL) {
        t->right->deep = t->deep + 1;
        fun(t->right);
    }
}

int main() {
    int n;
    char s;
    Tree t;
    Tree root;
    root = NULL;
    t = (Tree)malloc(sizeof(TreeNode));
    t->num = -1;
    t->left = NULL;
    t->right = NULL;
    cin >> n;
    int a[n + 5];
    for (int i = 0; i < n; i++) {
        Tree p, q;
        p = (Tree)malloc(sizeof(TreeNode));
        p->left = NULL;
        p->right = NULL;
        q = (Tree)malloc(sizeof(TreeNode));
        q->left = NULL;
        q->right = NULL;
        q->bf = 0;
        if (i != 0) {
            cin >> s;
        }
        cin >> p->num;
        t = build_bst(p, t);
        root = insert(p->num, root);
    }
    cout << "BST-ASL:" << bst_avl(t) << endl;
    root->deep = 1;
    fun(root);
    cout << "AVL-ASL:" << bst_avl(root);
    return 0;
}
