#include "avl.hpp"

int main(){
    Tree tree;
    tree.ShowMenu();
    int choice;
    cout<<"需要进行什么操作："<<endl;
    flag:
    cin>>choice;
    switch(choice)
    {
        case 0: //* 退出系统
        tree.exitSystem();
            break;
        case 1: //* 添加信息
        tree.AddBook();
            break;
        case 2:
        tree.display();
            break;
        case 3:
        tree.DeleteBook();
            break;
        case 4:
        tree.SearchBook();
            break;
        default:
            cout<<"不支持该选项！"<<endl;
            break;

    }
    cout<<"还有呢："<<endl;
    goto flag;
    system("pause");
    return 0;
}