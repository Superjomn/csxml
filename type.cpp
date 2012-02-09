#include <iostream>
#include <string>
using namespace std;

#ifndef TYPE_H_
#define TYPE_H_ 
#include "./type.h"
#endif

void func(const string &fun) 
{
    cout<<"Function: "<<fun<<"()"<<endl;   
} 

void error(const string &er)
{
    cout<<"Error: ---"+er<<endl;
}

bool TagTreeError(const string fun,const TagTreeType type)
{
    //显示函数名称
    func(fun); 

    if(type==RIGHT)
        return true;
    //scan_scope----------------------------------
    if(fun=="scan_scope")
    {
        switch(type)
        {
        case ERROR_TAG_SCAN_SCAPE_NO_FULL_TAG:
            error("标签不完整");
            return false;
            break;
        case ERROR_TAG_EMPTY_TAG:
            error("空标签 <>");
            return false;
            break;
        default:
            return true;
            break;
        }
    }
    //scan_scope----------------------------------
    if(fun=="append_child") 
    {
        switch(type) 
        {
            case ERROR_TAG_EMPTY_TEXT:
                error("传入字符为空或空格");
                return false;
                break;
            case ERROR_TAG_STR_NOT_EVEN:
                error("根据空格和=分割的字符串个数非偶\n导致attrname和attrvalue不配套"); 
                return false;
                break;
            default:
                return true;
        } 

    } 
    //upper----------------------------------
    if(fun=="upper" ) 
    {
        switch(type) 
        {
            case ERROR_DIV_0:
                error("严重错误 除数为0" ) ;
                return false;
                break;
            default:
                return true;
        } 
    } 
    //split_trans_attr----------------------------------
    if(fun=="split_trans_attr" ) 
    {
        switch(type) 
        {
            case ERROR_TAG_EMPTY_TEXT:
                error("传入了空字符");
                return false;
                break;
            case ERROR_TAG_STR_NOT_EVEN:
                error("根据空格和=分割的字符串个数非偶\n导致attrname和attrvalue不配套"); 
                return false;
                break;
            default:
                return true;
                break;
        } 
    } 

    //__tag_start----------------------------------
    if(fun=="__tag_start" ) 
    {
        switch(type) 
        {
            case ERROR_TAG_NOT_TRIM:
                error("文本两侧空格未去除" );
                return false;
                break;
        } 
    } 
    //__tag_end----------------------------------
    if(fun=="__tag_end") 
    {
        switch(type) 
        {
            case ERROR_TAG_END_STACK_EMPTY:
                error("tag_stack 为空" );
                return false;
                break;
            case ERROE_TAG_END_STACK_NO_MATCH:
                error("tag_stack栈顶不匹配");
                return false;
                break;
        } 
    } 
    //find----------------------------------
    if(fun=="find")
    {
        switch(type)
        {
        case ERROR_TAG_WRONG_SYNTAX:
            error("find 语法错误");
            return false;
            break;
        default:
            return true;
        }
    }
    //find----------------------------------
    if(fun=="split_tagtext" )
    {
        switch(type)
        {
            case ERROR_TAG_NO_A_TAG_WORD:
                error("解析错误 不存在有效tagtext");  
                return false;
            break;
            case ERROR_TAG_NO_RIGHT_RIGHT_REC_BRACKET:
                error("解析 无右侧]");
                return false;
            break;
            default:
            return true;
            break;
        } 
    } 
    return true;

}
