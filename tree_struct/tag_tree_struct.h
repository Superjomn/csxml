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
    Stack();

    ~Stack();

    bool isempty();

    void push(Type x);

    int size();

    bool pop(Type &x);

    //取得顶部节点值
    bool gtop(Type &x);
};

template <class Type> class cStack{
private:
    int top;
public:
    Type **data;
    int space;
    cStack();

    ~cStack();

    bool isempty();

    void push(Type *x);

    //控制内存消耗 若分配空间过大 定期缩小内存消耗
    void size_control();

    bool pop(Type *&x);

    //取得顶部节点值
    bool gtop(Type* &x);

    void debug();
};

//注册数组类
//用于对TagNode和AttrNode进行注册 最后同一注销
template <class Type> class Register_Arr{
public:
    vector<Type>arr;
public:
    ~Register_Arr();

    int size();

    void push(Type tg);
};

