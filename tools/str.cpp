/*#########################################
*   File:       tools/str.cpp
*   @Author:    Chunwei
*   Date:       2012-01-29
*##########################################
*/
#include "str.h" 

/*
void console(int n_values, ...)
{
    va_list var_arg;
    int i;
    //准备访问可变参数
    va_start(var_arg,n_values);
    for(i = 0; i < n_values;i += 1)
    {
        cout<<va_arg(var_arg,string)<<"  ";
    } 
    cout<<endl;
    va_end(var_arg);
} 
*/


//将string中间的字符进行转换 将无用字符及连续的无效字符用空格转换
TagTreeType split_trans_attr(string &text,vector<string> &attrs)
{
    int i=0;
    vector<string> arr;
    string name;
    string::size_type s=0,e=0;

    trim(text); 
    if(text.empty()) 
    {
        return ERROR_TAG_EMPTY_TEXT;
    } 
    //开始分割字符串为字符数组
    while(i<text.size())
    {
        //cout<<"attr->scaning:  "<<"+>--"<<text[i]<<endl;
        //需要考虑引号的影响
        if(text[i]=='=')
        {
            e=i;
            name=string(text,s,e-s);
            if(trim(name))
            {
                //cout<<"attrword  "<<name<<endl;
                arr.push_back(name);
            }
            s=e+1;
            i=e;
        }
        else if(text[i]=='\'')
        {
            s=i;
            e=text.find_first_of('\'',s+1);
            if(e<text.size())
            {
                name=string(text,s,e-s+1);
                rm_mark(name);
                //cout<<"find ' "<<name<<endl;
                s=e+1;
                i=e;
                if(trim(name))
                {
                    //cout<<"attrword  "<<name<<endl;
                    arr.push_back(name);
                }
            }
        }
        else if(text[i]=='"')
        {
            s=i;
            e=text.find_first_of('"',s+1);
            if(e<text.size())
            {
                name=string(text,s,e-s+1);
                rm_mark(name);
                s=e+1;
                i=e;
                if(trim(name))
                {
                    arr.push_back(name);
                    //cout<<"attrword  "<<name<<endl;
                }
            }
        }
        else if(text[i]==' ')
        {
            e=i;
            name=string(text,s,e-s+1);
            if(trim(name))
            {
                //cout<<"attrword  "<<name<<endl;
                arr.push_back(name);
            }
            s=e;
        }
        i++;
    }

    int size=arr.size();
    if (is_odd(size))
        return ERROR_TAG_STR_NOT_EVEN;
    //cout<<"the arrstack size  "<<size<<endl;
    //开始循环添加属性t
    attrs=arr;
    return RIGHT;
} 
//从s开始的下一个word 如.class 中的class
bool next_word(const string &text,const string::size_type s,string::size_type &e,string &word)
{
    cout<<"next_word()"<<endl;
    const int size=text.size();
    string::size_type start=s+1;
    e=-1;
    if(size==start)
        return false;

    while(isspace(text[start]))
    {
        if(start+1<size)
            start++;
        else
            break;
    } 

    for(int i=start;i<size;i++)
    {
        if(!isalpha(text[i]))
        {//非字母 视为一个单词的结束
            e=i-1;
            break;
        }
    }
    if(e==-1)
        e=size-1;
    //cout<<"end: >"<<e<<endl;
    if(start==e&&e<size)
        word=text[e]; 
    else
        word=string(text,start,e);
    //cout<<"mid word >"<<word<<endl;
    if(!trim(word)) return false;
    return true;
}
//从当前位置向后取得一个word
bool get_word(const string &text,const string::size_type s,string::size_type &e,string &word)
{
    /*
    cout<<"get_word()"<<endl;
    const int size=text.size();
    string::size_type start=s;
    e=-1;
    if(size==start)
        return false;

    while(isspace(text[start]))
    {
        if(start+1<size)
            start++;
        else
            break;
    } 

    for(int i=start;i<size;i++)
    {
        if(!isalpha(text[i]))
        {//非字母 视为一个单词的结束
            e=i-1;
            break;
        }
    }
    if(e==-1)
        e=size-1;
    //cout<<"end: >"<<e<<endl;
    if(start==e&&e<size)
        word=text[e]; 
    else
        word=string(text,start,e);
    //cout<<"mid word >"<<word<<endl;
    if(!trim(word)) return false;
    return true;
    */
    return next_word(text,s-1,e,word);


}

bool trans(string &text)
{
    //如果为空 则返回false 否则 返回 true
    if ((text).empty())
        return false;

    string::size_type i=0,
                     s=0,
                    e=0;

    s=text.find("  "); 
    while(s<text.size() ) 
    {
        //cout<<"fir find two space: s   "<<s<<endl; 
        i=s+1;
        e=i;
        while(text[i+1]==' ') 
        {
            i++;
            e=i;
        } 
        //保留一个空格
        text.erase(s,e-s); 

        s=text.find("  "); 
        //cout<<"in while s,size  "<<s<<"  "<<text.size()<<endl;   
    } 

    return true;
}

//将string两端空格或无用字符去除
bool trim(string &s)
{
    //cout<<"trim()"<<endl; 
    //如果为空 则返回false 否则 返回 true
    string::size_type start=0,
                      end=s.size()-1;
    if (s.empty())
    {
        return false;
    } 

    while(true) 
    {
        if(s[start]==' ')
        {
            start++;
            continue;
        } 
        else break;
    } 
    while(true) 
    {
        if(s[end]==' ')
        {
            end--;
            continue;
        } 
        else break;
    } 
    //修改字符
    s=string(s,start,end-start+1 ) ;
    //cout<<"trimed s "<<s<<endl;  
    if(s.empty())
        return false;
    return true;
}

//删除字符两侧引号 主要用作属性值的处理
void rm_mark(string &text)
{
    string::size_type start=0,
                       end=text.size()-1 ;
    //去除空格的影响
    while(true)
    {
        switch(text[start])
        {
        case '"':
        case '\'':
        case ' ':
            start ++;
            continue;
            break;
        default:
            break;
        }
        break;
    }while(true)
    {
        switch(text[end])
        {
        case '"':
        case '\'':
        case ' ':
            end--;
            continue;
            break;
        default:
            break;
        }
        break;
    }

    if(start==end) 
        text=" ";

    text=string(text,start,end-start+1) ;
} 


template <typename T> inline bool is_even(const T num)
{
    return num%2==0;
} 

template <typename T> inline bool is_odd(const T num)
{
    return num%2==1;
} 

template <typename T> inline T min(const T a,const T b) 
{
    return (a>b)?b:a; 
} 

template <typename T> inline T max(const T a,const T b) 
{
    return (a>b)?a:b; 
}
