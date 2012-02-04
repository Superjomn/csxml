/*#########################################
*   File:       tag_struct.c
*   @Author:    Chunwei
*   Date:       2012-02-25
*##########################################
*/

#include "./tag_tree_struct.h" 

template <class Type>Stack<Type>::Stack()
{
    cout<<"Stack construct"<<endl;
} 

template <class Type>Stack<Type>::~Stack()
{
    cout<<"stack space is freed!"<<endl; 
}

template <class Type> bool Stack<Type>::isempty()
{
    return this->data.empty();
} 

template <class Type> void Stack<Type>::push(Type x)
{
    console("push  "<<x);
    this->data.push_back(x);
    console("stack size: "<<this->data.size());
} 

template <class Type> int Stack<Type>::size()
{
    return this->data.size();
}

template <class Type> bool Stack<Type>::pop(Type &x)
{
    print("pop");
    if(this->isempty()) 
        return false;
    x=this->data.back();
    this->data.pop_back();
    return true;
} 

template <class Type> bool Stack<Type>::gtop(Type &x)
{
    print("gtop");
    if(this->isempty()) 
        return false;
    x=this->data.back();
    return true;
} 

//cStack-----------------------------------

template <class Type> cStack<Type>::cStack()
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

template <class Type> cStack<Type>::~cStack()
{
    printf("C space is freed!\n");
    if(this->data)
        free(this->data);
}

template <class Type> bool cStack<Type>::isempty()
{
    return this->top == -1;
}

template <class Type> void cStack<Type>::push(Type *x)
{
    if (this->top == this->space-1){
        //cout<<"push in tag_stack"<<endl;
        //cout<<"tagstack size: "<<this->top+1<<endl; 
        Type **base =(Type ** )  realloc(this->data,sizeof(Type *)*(this->space += STACK_PER_ADD));
        this->data=base;
    }

    this->data[++ this->top] = x;
}

template <class Type> void cStack<Type>::size_control()
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


template <class Type> bool cStack<Type>::pop(Type *&x)
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

template <class Type> bool cStack<Type>::gtop(Type* &x)
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

template <class Type> void cStack<Type>::debug()
{
    cout<<"the status is"<<endl;
    cout<<"top:"<<this->top<<endl;
    cout<<"sapce:"<<this->space<<endl;
    cout<<"------------------"<<endl;
}

//Register_Arr----------------------

template <class Type> Register_Arr<Type>::~Register_Arr()
{
    cout<<"delete all TagNode space"<<endl;
    int size=this->arr.size();
    for(int i=0;i<size;i++)
    {
        delete(this->arr[i]);
    }
}

template <class Type> int Register_Arr<Type>::size()
{
    return this->arr.size();
}

template <class Type> void Register_Arr<Type>::push(Type tg)
{
    this->arr.push_back(tg);
}
