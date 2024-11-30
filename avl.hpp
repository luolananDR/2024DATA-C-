#include<iostream>
#include<vector>
using namespace std;

struct Tnode{
    string isbn; // 图书编码--以此作为AVL树判断条件
    string title;// 书名
    string author;// 作者
    string price;// 价格
    string isBorrowed;// 借阅状态

    //---图书的数据部分 
    int height=0;
    Tnode *left=NULL;
    Tnode *right=NULL;

    //---树形特征
    Tnode()=default;
    Tnode(string s,string t,string a,string p,string b):isbn(s),title(t),author(a),price(p),isBorrowed(b){}
    void showInfor(); // 显示图书信息
};
class Tree{
    public:
    Tnode *root=NULL;
    vector<Tnode*> vec;// 作为中序遍历的存储
    vector<Tnode*> vec1;// 前序遍历存储

    Tree();
    void initTree(); // 从文件读取并初始化树
    void save(); // 保存操作
    int GetHight(Tnode *node);  // 获取avl树高度
    void updateHeight(Tnode *node); // 更新高度
    Tnode* leftRotate(Tnode *node); // 左旋
    Tnode* rightRotate(Tnode *node); // 右旋
    int balanceFactor(Tnode *node); // 获取平衡因子
    void Add(Tnode *curr); // 添加
    Tnode* AddHelper(Tnode *node,Tnode *curr);// 递归添加辅助  
    void DeleteBook(); // 删除图书
    Tnode* Remove(string isbn); //删除
    Tnode* RemoveHelper(Tnode *node,string isbn); //删除辅助
    void SearchBook(); // 搜索
    Tnode* rotate(Tnode *node); // 旋转判定
    void ShowMenu();// 展示菜单
    void exitSystem(); // 退出程序
    void inOrder(Tnode *root); // 接口测试---中序遍历AVL树，看是否从小到大排序
    void preOrder(Tnode *root); // 前序遍历--用于文件存储
    void display();
    void AddBook(); // 添加图书
    bool Search_ISBN(string isbn);
};





