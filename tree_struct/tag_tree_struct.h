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

template <class Type> class cStack{
private:
    int top;
public:
    Type **data;
    int space;
    cStack()
    {
        cout<<"Stack construct"<<endl;
        this->top=-1;
        this->space = 0;
        //分配空间及初始化
        Type **base = (Type **) malloc(sizeof(Type *)*(this->space += STACK_INIT_SIZE));
        if(base==NULL)
            exit(0);  
        this->data = base;
        this->space = STACK_INIT_SIZE;
    }

    ~cStack()
    {
        printf("C space is freed!\n");
        if(this->data)
            free(this->data);
    }

    bool isempty()
    {
        return this->top == -1;
    }

    void push(Type *x)
    {
        if (this->top == this->space-1){
            //cout<<"push in tag_stack"<<endl;
            //cout<<"tagstack size: "<<this->top+1<<endl; 
            Type **base =(Type ** )  realloc(this->data,sizeof(Type *)*(this->space += STACK_PER_ADD));
            this->data=base;
        }

        this->data[++ this->top] = x;
    }

    //控制内存消耗 若分配空间过大 定期缩小内存消耗
    void size_control()
    {
        cout<<"space control"<<endl;
        //超出连个单位 需要进行缩减空间 缩为超出一个空间
        if(this->space > this->top+1+2*STACK_PER_ADD )
        {
            int size;
            upper(this->top+1,STACK_PER_ADD,size);
            Type **base =(Type ** )  realloc(this->data,sizeof(Type *)*size);
            this->data=base;
            this->space=size;
        }
    }

    bool pop(Type *&x)
    {
        //cout<<"pop out"<<endl;
        //cout<<"former stack size: "<<this->top+1<<endl; 
        if (this->isempty())
            return false;
        x=this->data[this->top];
        this->top--;
        //cout<<"latter stack size: "<<this->top+1<<endl;  
        return true;
    }
    //取得顶部节点值
    bool gtop(Type* &x)
    {
        //cout<<"gtop"<<endl;
        if (this->isempty())
        {
            //cout<<"tagstack size: "<<this->top+1<<endl;
            return false;
        } 
        x = this->data[this->top];
        //cout<<"tagstack size: "<<this->top+1<<endl;
        return true;
    }

    void debug()
    {
        cout<<"the status is"<<endl;
        cout<<"top:"<<this->top<<endl;
        cout<<"sapce:"<<this->space<<endl;
        cout<<"------------------"<<endl;
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

