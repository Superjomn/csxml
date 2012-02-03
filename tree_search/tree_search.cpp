/*#########################################
*   File:       tree_search.h
*   @Author:    Chunwei
*   Date:       2012-01-29
*##########################################
*/
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#ifndef TREE_SEARCH_H_
#define TREE_SEARCH_H_
#include "./tree_search.h"
#endif /* TREE_SEARCH_H_ */


//查找解析
/*
 * .classname #idname
 * p.class   p#class
 * p[class=cname id=idname]
 */

TagTreeType split_tagtext(string &text,Tag &tag)
{
    string tagtext;
    string::size_type step,end;
    bool res;

    //进行解析
    trim(text);
    switch(text[0])
    {
    case '.':
    case '#':
        console("signal: . #");
        res=next_word(text,0,step,tagtext);
        if(!res)
            return NONE;
        tag.attrtext=tagtext;
        break;
    default:
        // p[attr=name] 
        // p#attr

        console("signal default");
        console("test> "<<text);

        res=get_word(text,0,step,tagtext);
        console("get_word: >"<<tagtext); 
        if(!res)
            return NONE;
        tag.tagname=tagtext;

        console("step "<<step);

        if(step==text.size())
        {
            //p 仅一个标签
            return RIGHT;
        } 
        //向后扫描. # [标签] 
        //去除空格影响
        while(step+1<text.size()&&isspace(text[step+1]))
            step++;
        step++;
        console("before switch step: "<<step);

        switch(text[step])
        {
            case '.':
            case '#':
                console("attr . #" );
                res=next_word(text,step,end,tagtext);
                if(!res)
                    return NONE;
                tag.attrtext=tagtext;
                return RIGHT;
            break;

            case '[':
                int ri=text.find_first_of(']',step);
                if(ri>=text.size())
                    //无右侧]
                    return  ERROR_TAG_NO_RIGHT_RIGHT_REC_BRACKET;

                tagtext=string(text,step+1,ri-step-1);
                if(!trim(tagtext))
                    return RIGHT;
                tag.attrtext=tagtext;
                return RIGHT;
            break;
        } //end switch
    }
    return RIGHT;
}

/*
查找方式：
    div a
    .classname #idname
    div#idname
    div[attrname=attrvalue] 
*/
//查找主程序
TagTreeType Tree_Search::find(string &text)
{
    TagNode* root=this->tag_tree.root;
    vector<string> tagtext;
    string::size_type s=0,e=0;
    string scope;
    //需要对查找text进行解析
    //如 find("div[class=name font=5px] p")
    //通过适当的空格分离
    //将多余连续的空格合并起来
    trim(text);
    trans(text);
    const int tsize=text.size();
    //扫描字符 将字符串分割为各个小单位 进行查找
    //如转化为  div[class=name]
    //          p
    for(int i=0;i<tsize;i++)
    {
        if(text[i]==' ')
        {
            e=i;
            scope=string(text,s,e);
            s=e;
            if(trim(scope))
            {
                tagtext.push_back(scope);
            }

        }
        else if(text[i]=='[')
        {
            e=text.find_first_of(']',i);
            if(s>=text.size())
                return ERROR_TAG_WRONG_SYNTAX;
            scope=string(text,s,e);
            s=e+1;
            i=s;
            if(trim(scope))
            {
                tagtext.push_back(scope);
            }
        }
    }
    //开始对分开的字符串进行处理
    //每块节点字符串一个单位 再进行解码分开
    const int size1=tagtext.size();
    Tag tag;

    for(int i=0;i<size1;i++)
    {
        //开始进行分割
        scope=tagtext[i];
        //一些格式： p[class=str font=13px]
        //.class
        //#idname
        //div#id   div.class
    }
}

TagTreeType Tree_Search::search(TagNode *fnode,string &tgname,vector<TagNode*> &tags)
{
    //一轮搜索
    TagNode *p=fnode->left;
    TagNode cnode;
    //在p为根的树下任意遍历便可
    //前序遍历树
    while(p!=NULL || !this->tg_stack.isempty())
    {
        while(p!=NULL)
        {
            //test this node
            if(p->name==tgname)
            {
                tags.push_back(p);
            }//test end

            this->tg_stack.push(p);
            p=p->left;
        }
        if(!this->tg_stack.isempty())
        {
            this->tg_stack.pop(p);
            p=p->right;
        }
    }
    return RIGHT;
} 

TagTreeType Tree_Search::search(TagNode *fnode,string &tgname,string &attr_text,vector<TagNode*> &tags)
{
    vector<TagNode*>cur_tags;
    vector<string> attrs;
    //先根据标签名称进行查找  然后进行筛选
    TagTreeType res;
    this->search(fnode,tgname,cur_tags);
    const int cur_size = cur_tags.size();
    if(cur_size==0)
    {
        //无标签
        return NONE;
    }
    //对attr_text进行转化
    //对传入的attr_text进行分解 
    res=split_trans_attr(attr_text,attrs);
    if(!TagTreeError("split_trans_attr",res)) 
    { 
        //有错误
        return NONE;
    }

    //对符合的arr一个个进行筛选
    for(int i=0;i<cur_size;i++)
    {
        //逐个检测判断
        if( this->match_attr(cur_tags[i],attrs))
        {
            tags.push_back(cur_tags[i]);
        } 

    }
}


bool Tree_Search::match_attr(TagNode *tag,vector<string> &attrs)
{
    const int size=attrs.size();
    for(int i=0;i<size;i+=2) 
    {
        if(!this->__has_attr(tag,attrs[i],attrs[i+1])) 
            return false;
    } 
    return true;
} 


bool Tree_Search::__has_attr(TagNode *tag,string &attrname,string &value)
{
    AttrNode *at;
    at=tag->attr;
    while(at) 
    {
        if(at->name==attrname && at->value==value)
            return true;
        at=at->next;
    } 
    return false;
} 
