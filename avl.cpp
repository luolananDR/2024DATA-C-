#include "avl.hpp"

void Tree::ShowMenu(){
    cout<<"****************************"<<endl;
    cout << "**欢迎使用图书管理系统!***" << endl;
	cout << "******0.退出管理系统******" << endl;
	cout << "******1.增加图书信息******" << endl;
	cout << "******2.显示图书信息******" << endl;
	cout << "******3.删除图书**********" << endl;
	cout << "******4.修改图书信息******" << endl;
	cout << "******5.查找图书信息******" << endl;
	cout << "******6.选择方式排序********" << endl;
	cout << "****************************" << endl;
	cout << endl;
}

void Tnode::showInfor(){
    cout<<"名称："<<title<<endl
    <<"作者："<<author<<endl
    <<"ISBN:"<<code<<endl
    <<"价格："<<price<<endl
    <<"在库状态："<<(isBorrowed?"借出":"在库")<<endl;
}

int Tree::GetHight(Tnode *node){
    // 空节点高度为 -1 ，叶节点高度为 0
    return node==NULL? -1 :node->height;
}

void Tree::updateHeight(Tnode *node) {
// 节点高度等于最高子树高度 + 1
    node->height = max(GetHight(node->left), GetHight(node->right)) + 1;
}
// 获取平衡因子
int Tree::balanceFactor(Tnode *node){
    // 空节点为0
    if(node==NULL)
        return 0;
    return GetHight(node->left)-GetHight(node->right);
}
//* 右旋
Tnode* Tree::rightRotate(Tnode* node){
    Tnode *child=node->left;// 失衡节点的子节点
    Tnode *grandChild=child->right;
    child->right=node;
    node->left=grandChild;
    // 更新高度
    updateHeight(node);
    updateHeight(child);
    return child;
}
//* 左旋
Tnode* Tree::leftRotate(Tnode* node){
    Tnode *child=node->right;
    Tnode *grandChild=child->left;
    child->left=node;
    node->right=grandChild;
    updateHeight(node);
    updateHeight(child);
    return child;
}
//* 最后根据节点的平衡因子来判断旋转
Tnode* Tree::rotate(Tnode *node){
    int _balanceFactor=balanceFactor(node);
    // 左偏树
    if (_balanceFactor > 1) {
        if (balanceFactor(node->left) >= 0) {
            // 右旋
            return rightRotate(node);
    } else {
    // 先左旋后右旋
        node->left = leftRotate(node->left);
            return rightRotate(node);
}
    }
    // 右偏树
    if (_balanceFactor < -1) {
        if (balanceFactor(node->right) <= 0) {
            // 左旋
            return leftRotate(node);
    } else {
            // 先右旋后左旋
            node->right = rightRotate(node->right);
            return leftRotate(node);
}
    }
    // 平衡树，无须旋转，直接返回
    return node;
}
//* 添加结点
