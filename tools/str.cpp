/*#########################################
*   File:       tools/str.cpp
*   @Author:    Chunwei
*   Date:       2012-01-29
*##########################################
*/
#include "./str.h" 

//从s开始的下一个word 如.class 中的class
bool next_word(const string &text,const string::size_type s,string::size_type &e,string &word)
{
    int i=s;
    if(isspace(text[i]))
    {
        while(isspace(text[i]))
            i++;
        return get_word(text,i,e,word);
    }
    return get_word(text,s+1,e,word);
}

//从当前位置向后取得一个word
bool get_word(const string &text,const string::size_type s,string::size_type &e,string &word)
{
    //开端为空格 必须能够保留位置
    if(isspace(text[s]))
        return false;

    if(s==text.size())
        return false;

    console("not empty");
    string::size_type i=s;
    
    while(isalpha(text[i]))
    {
        console("i++");
        i++;
    }
    e=i-1;
    console("i >"<<i);
    word=string(text,s,i-s);
    return trim(word);
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
    while(isspace(s[start]))
        start++;
    while(isspace(s[end]))
        end--;
    s=string(s,start,end-start+1);
    return !(s.empty());
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
