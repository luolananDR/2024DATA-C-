#include<iostream>
using namespace std;

struct Tnode{
    string code; // 图书编码--以此作为AVL树判断条件
    string title;// 书名
    string author;// 作者
    double price;// 价格
    bool isBorrowed;// 借阅状态

    //---图书的数据部分 
    int height=0;
    Tnode *left;
    Tnode *right;

    //---树形特征
    Tnode()=default; 
    Tnode(string c,string t,string a,double p):code(c),title(t),author(a),price(p),isBorrowed(false){}
    void showInfor(); // 显示图书信息
};
class Tree{
    public:
    Tnode *root;
    
    int GetHight(Tnode *node);  // 获取avl树高度
    void updateHeight(Tnode *node); // 更新高度
    Tnode* leftRotate(Tnode *node); // 左旋
    Tnode* rightRotate(Tnode *node); // 右旋
    int balanceFactor(Tnode *node); // 获取平衡因子
    void Add(string code); // 添加
    Tnode* AddHelper(Tnode *node,string code);// 递归添加辅助  
    Tnode* Delete(string code); // 删除
    Tnode* Search(string code); // 搜索
    Tnode* rotate(Tnode *node); // 旋转判定
    void ShowMenu();// 展示菜单

};





