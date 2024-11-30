#include "avl.hpp"
#include<fstream>
#include<iomanip>
#define File "dataStructure/book.txt"
void Tree::ShowMenu(){
    cout<<"**************************"<<endl;
    cout << "**欢迎使用图书管理系统!***" << endl;
	cout << "******0.退出管理系统******" << endl;
	cout << "******1.增加图书信息******" << endl;
	cout << "******2.显示图书信息******" << endl;
	cout << "******3.删除图书**********" << endl;
	cout << "******4.查找图书信息******" << endl;
	cout << "**************************" << endl;
	cout << endl;
}

void Tnode::showInfor(){
    cout<<std::left<<setw(30)<<title<<setw(10)
    <<author<<setw(18)<<isbn<<setw(12)<<price<<setw(12)<<((isBorrowed=="是")?"借出":"在库")<<endl;
}

void Tree::exitSystem(){
	cout<<"欢迎下次使用！"<<endl;
    system("pause");
   	exit(0); //* 退出程序
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
//* 构造函数
Tree::Tree() {
    // 从文件中读取书籍信息并初始化AVL树
    ifstream ifs; 
    ifs.open(File,ios::in);
    if(ifs.fail()){
        cout<<"数据库读取失败！请重试！"<<endl;
        root=NULL;
        ifs.close();
        system("pause");
        exit(0);
    }
    else 
    // 文件存在
    initTree();
}
void Tree::initTree(){
    ifstream ifs;
    ifs.open(File,ios::in);
    string isbn,title,author,price,isborrow;
    while(ifs >> isbn >> title >> author >> price >> isborrow){
        Tnode* curr=new Tnode(isbn,title,author,price,isborrow);
        Add(curr); // 添加节点
    }
}
void Tree::Add(Tnode *curr){
    root=AddHelper(root,curr);// 从根节点开始检索
}
Tnode* Tree::AddHelper(Tnode *node,Tnode *curr){
    if(node==nullptr)
        return curr;  
    // 找到位置后插入节点
    if(curr->isbn<node->isbn){
        node->left=AddHelper(node->left,curr);
    }
    else if(curr->isbn>node->isbn){
        node->right=AddHelper(node->right,curr);
    }
    else 
        return node; // 如果相等违背AVL树性质
    updateHeight(node);
    // 从插入的结点开始向上判断旋转
    node=rotate(node);
    return node;
}
void Tree::inOrder(Tnode* root){
        
        if(root==NULL)
        return;
        inOrder(root->left);
        vec.push_back(root);
        inOrder(root->right);
    }
void Tree::display(){
    vec.clear();
    inOrder(root);
    cout << std::left << setw(30) << "书名"
              << setw(10) << "作者"
              << setw(18) << "ISBN码"
              << setw(10) << "价格"
              << setw(10) << "在库状态" << endl;
    cout << std::setfill('-') << setw(80) << "-" << std::setfill(' ') << endl;    
    for(int i=0;i<vec.size();i++){
        vec[i]->showInfor();
    }
    cout<<endl;
}
void Tree::save(){
    ofstream ofs;
    ofs.open(File,ios::out);
    preOrder(root); // 以前序序列同步文件修改
    for(int i=0;i<vec1.size();i++){
        ofs<<vec1[i]->isbn<<" "<<vec1[i]->title<<" "<<vec1[i]->author
        <<" "<<vec1[i]->price<<" "<<vec1[i]->isBorrowed<<endl;
    }
    ofs.close();
}   
void Tree::preOrder(Tnode* root){
    if(root==NULL)
        return;
    vec1.push_back(root);
    preOrder(root->left);
    preOrder(root->right);
}
void Tree::AddBook(){
    string is,ti,au,pr;
    cout<<"正在添加图书..."<<endl;
    cout<<"请输入需要添加的图书信息："<<endl;
    cout<<"ISBN码:";
    cin>>is;
    cout<<"书名：";
    cin>>ti;
    cout<<"作者：";
    cin>>au;
    cout<<"价格：";
    cin>>pr;
    
    // 添加
    Tnode* temp=new Tnode(is,ti,au,pr,"否");// 新添加的图书默认在库
    this->Add(temp);
    this->save();
    cout<<"添加成功！"<<endl;
}
Tnode* Tree::Remove(string isbn){
    return root=RemoveHelper(root,isbn);
}
Tnode* Tree::RemoveHelper(Tnode* node,string isbn){
   if (node == nullptr)
        return nullptr;
    /* 1. 查找节点并删除 */
    if (isbn < node->isbn)
        node->left = RemoveHelper(node->left, isbn);
    else if (isbn > node->isbn)
        node->right = RemoveHelper(node->right, isbn);
    else {
        if (node->left == nullptr || node->right == nullptr) {
            Tnode *child = node->left != nullptr ? node->left : node->right;
            // 子节点数量 = 0 ，直接删除 node 并返回
            if (child == nullptr) {
                delete node;
                return nullptr;
            }
            // 子节点数量 = 1 ，直接删除 node
            else {
                delete node;
                node = child;
            }
        } else {
            // 子节点数量 = 2 ，则将中序遍历的下个节点删除，并用该节点替换当前节点
            Tnode *temp = node->right;
            while (temp->left != nullptr) {
                temp = temp->left;
            }
            string tempIsbn = temp->isbn;
            node->right = RemoveHelper(node->right, temp->isbn);
            node->isbn = tempIsbn;
        }
    }
    updateHeight(node); // 更新节点高度
    /* 2. 执行旋转操作，使该子树重新恢复平衡 */
    node = rotate(node);
    // 返回子树的根节点
    return node;
}
void Tree::DeleteBook(){
    cout<<"正在删除图书..."<<endl;
    cout<<"请输入图书的ISBN码：";
    string isbn;
    cin>>isbn;
    if(!Search_ISBN(isbn)){
        cout<<"没有找到这本书！请检查信息！"<<endl;
        return;
    }
    this->Remove(isbn);
    this->save();
    cout<<"删除成功！"<<endl;
}
void Tree::SearchBook(){
    cout<<"正在查找图书..."<<endl;
    cout<<"请选择查找方式"<<endl
    <<"1---按ISBN码 (精确查找)"<<endl
    <<"2---按书名 3---按作者 (模糊查找)"<<endl;
    int choice;
    cin>>choice;
    vec.clear();
    this->inOrder(root);
    if(choice==1){
        cout<<"请输入ISBN码：";
        string is;
        cin>>is;
        for(int i=0;i<vec.size();i++){
            if(vec[i]->isbn==is)
            {
                cout<<"为你找到ISBN码为"<<is<<"的书："<<endl;
                vec[i]->showInfor();
                return;
            }
    }
    cout<<"没有找到这本书！请检查信息！"<<endl;
}
    else if(choice==2){
        cout<<"请输入书名：";
        string ti;
        cin>>ti;
        bool flag=0;
        cout<<"为你找到可能的书："<<endl;
        for(int i=0;i<vec.size();i++){
            if(vec[i]->title.find(ti)!=-1)
            {
                vec[i]->showInfor();
                flag=1;
            }
    }
        if(flag==0)
        cout<<"无"<<endl;
    }
    else if(choice==3){
        cout<<"请输入作者名：";
        string au;
        cin>>au;
        bool flag=0;
        cout<<"为你找到可能的书："<<endl;
        for(int i=0;i<vec.size();i++){
            if(vec[i]->author.find(au)!=-1)
            {
                vec[i]->showInfor();
                flag=1;
            }
    }
        if(flag==0)
            cout<<"无"<<endl;
}    
}
bool Tree::Search_ISBN(string isbn){
    vec.clear();
    this->inOrder(root);
    for(int i=0;i<vec.size();i++){
        if(vec[i]->isbn==isbn)
        return true;
    }
    return false;
}