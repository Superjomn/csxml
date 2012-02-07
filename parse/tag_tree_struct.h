/*#########################################
*   File:       tag_struct.c
*   @Author:    Chunwei
*   Date:       2012-02-25
*##########################################
*/
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <stdio.h>
#include <stdlib.h>

#ifndef TAG_TREE_STRUCT_H_
#define TAG_TREE_STRUCT_H_
#endif

#ifndef TYPE_H_
#define TYPE_H_
#include "../type.h"
#endif

#ifndef STR_H_
#define STR_H_
#include "../tools/str.h" 
#endif

using namespace std;

/*
 * 功能描述：
 *  有关基础数据结构
 */

template <typename T> inline TagTreeType upper(const T num,const T per,T &size)
{
    if(per==0) 
    {
        return ERROR_DIV_0;
    } 
    int s=num/per;
    size=per*(s+1); 
} 

/*
 * 实现栈
 */
//栈初始分配大小
const int STACK_INIT_SIZE = 100;
//每次分配大小
const int STACK_PER_ADD = 20;

template <class Type> class Stack{
private:
    list<Type> data;
public:
    Stack()
    {
        cout<<"Stack construct"<<endl;
    } 

    ~Stack()
    {
        cout<<"stack space is freed!"<<endl; 
    } 

    bool isempty()
    {
        return this->data.empty();
    } 


    void push(Type x)
    {
        console("push  "<<x);
        this->data.push_back(x);
        console("stack size: "<<this->data.size());
    } 

    int size()
    {
        return this->data.size();
    }

    bool pop(Type &x)
    {
        print("pop");
        if(this->isempty()) 
            return false;
        x=this->data.back();
        this->data.pop_back();
        return true;
    } 

    //取得顶部节点值
    bool gtop(Type &x)
    {
        print("gtop");
        if(this->isempty()) 
            return false;
        x=this->data.back();
        return true;
    } 
};

//注册数组类
//用于对TagNode和AttrNode进行注册 最后同一注销
template <class Type> class Register_Arr{
public:
    vector<Type>arr;
public:
    ~Register_Arr()
    {
        cout<<"delete all TagNode space"<<endl;
        int size=this->arr.size();
        for(int i=0;i<size;i++)
        {
            delete(this->arr[i]);
        }
    }
    int size()
    {
        return this->arr.size();
    }
    void push(Type tg)
    {
        this->arr.push_back(tg);
    }
};

