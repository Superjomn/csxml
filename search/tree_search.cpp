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
//此模块包含完整的解析过程
//将传入的查询字符串进行拆分  分割为tag string 队列
//如 find("p#id div[class=hello]")  =>  p#id   div[class=hello] 
struct kh{
    int s;
    int e;
};//方括号位置记录

bool inline within_range(int a,int b,int x)
{
    return x>a&&x<b;
}
/*
* 测试通过-----------------------------------------------------------
* 测试:
    * string text="p#id  div[cname=value cname=vlaue]"
    * vector<string> v_tags;
    * split_text_tags(text,v_tags);
*/
TagTreeType split_text_tags(string &text,vector<string> &v_tags)
{
    if(!trim(text) && !trans(text))
        return NONE;
    console("text is not empty");
    //只有[]需要另外对待 其余均可以
    //第一步通过空格查找隔开
    //之后通过对[]的匹配 将[]中间的空格除去
    vector<int> spacePos;
    vector<struct kh> v_kh;
    console("text is transed >"<<text);
    //spacePos 记录所有空格的位置

    //记录[]的位置 将无关空格去除
    int step=0;
    console("begin to find [");

    int size=text.size();

    step=0;
    while(step<size&&step>=0)
    {
        console("in [] while");
        struct kh nkuo;
        nkuo.s=step;
        step=text.find_first_of("[",step+1);
        if(step<size&&step>=0)
        {
            nkuo.s=step;
            
            step=text.find_first_of("]",step+1);
            if(step<size&&step>=0)
            {
                nkuo.e=step;
                console("nkuo> "<<nkuo.s<<"  "<<nkuo.e);
                v_kh.push_back(nkuo);
            }
            else{
                console("[]不匹配");
                //括号不匹配
                return ERROR_TAG_NO_MATCH_KH;
            }
        }
        else
        {
            console("no []");
        }
    }
   
    step=text.find_first_of(' ',0);
    console("first space >"<<step);
    console("开始查找空格 并进行统计");
    while(step<size&&step>0)
    {
        int is_within = 0;
        console("in space while");
        //过滤在[]内的空格
        for(int i=0;i<v_kh.size();i++)
        {
            if(within_range(v_kh[i].s,v_kh[i].e,step)) 
            {
                is_within=1;
                break;
            }
        }
        if(!is_within)
        {
            spacePos.push_back(step);
            console("the space is>"<<step);
        }
        else
            console("in []");
        step=text.find_first_of(' ',step+1);
    }

    console("out of filter for");
    //利用有效空格将字符串隔开
    size=spacePos.size();
    string tagtext;
    for(int i=0;i<=size;i++)
    {
        console("in text for");
        if(i==0)
        {
            //首个连通text开始处
            tagtext=string(text,0,spacePos[i]);
            if(trim(tagtext)) 
            {
                v_tags.push_back(tagtext);
            }
        }//end if
        else if(i==size)
        {
            //末尾space连通text末尾
            tagtext=string(text,spacePos[i],text.size());
            if(trim(tagtext)) 
            {
                v_tags.push_back(tagtext);
            }
        }
        else{
            //中间字符
            tagtext=string(text,spacePos[i-1],spacePos[i]);
            if(trim(tagtext)) 
            {
                v_tags.push_back(tagtext);
            }
        }//end else
    }
    return RIGHT;
} 

/*
* 测试通过-----------------------------------------------------
* 测试：
*
            string text="div[id='idname' class='classname']";
            text="div#p";
            text="#p";
            Tag tag;
            split_tagtext(text,tag);
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
        console("signal: . !");
        res=next_word(text,0,step,tagtext);
        if(!res)
            return NONE;
        tag.attrtext="class="+tagtext;
        return RIGHT;
        break;
    case '#':
        console("signal: # !");
        console("text >"<<text);
        res=get_word(text,1,step,tagtext);
        if(!res)
            return NONE;
        tag.attrtext="id="+tagtext;
        return RIGHT;
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
        console("get tagname "<<tagtext);

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
                console("attr # !" );
                res=next_word(text,step,end,tagtext);
                if(!res)
                    return NONE;
                tag.attrtext="class="+tagtext;
                return RIGHT;
            case '#':
                console("attr # !" );
                res=next_word(text,step,end,tagtext);
                if(!res)
                    return NONE;
                tag.attrtext="id="+tagtext;
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
* 测试：
*/
//将attr_text进行拆分 变为各个 attr
//如 传入 "class=classname id=idname"   => class=classname 
TagTreeType split_attr_text(string &text,vector<Attr> &attrs)
{
    int i=0;
    vector<string> arr;
    string name;
    string::size_type s=0,e=0;

    if(!trim(text))
        return ERROR_TAG_EMPTY_TEXT;
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
    for(int i=0;i<arr.size();i+=2)
    {
        Attr attr_node;
        attr_node={arr[i],arr[i+1]};
        attrs.push_back(attr_node);
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
bool Tree_Search::find(const string &te)
{
    string text=te;
    unsigned int size=0;
    TagNode* root=this->tag_tree.root;
    //开始对传入的查询字符进行处理
    vector<string> v_tags;
    
    //拆分为不同字符字段
    split_text_tags(te,v_tags);
    //将字段内拆分为tag
    vector<Tag> tags;
    size=v_tags.size();
    for(int i=0;i<size;i++)
    {
        Tag tg;
        if(!TagTreeError(split_tagtext(tags[i],tg)))
            return false;
        tags.push_back(tg);

    }








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

/*
 * 测试：
Tag_Tree tg= Tag_Tree();
TagTreeType res;
tg.init(&source);
tg.scan_trans_tree();
console("root"<<tg.root);
//搜索方法
Tree_Search ts=Tree_Search();
vector<TagNode*> tags;
ts.search(tg.root,"foot",tags);
console("tags size >"<<tags.size());
测试通过----------------------------------------
 */
TagTreeType Tree_Search::search(TagNode *fnode,const string &tgname,vector<TagNode*> &tags)
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

//p#id
/*
 * 测试
 * 测试通过--------------------------------------------------
vector<Attr> attrs;
Attr a={"class","apple"};
Attr b={"id","football"};
attrs.push_back(a);
attrs.push_back(b);
//div#id
ts.search(tg.root,"span",attrs,tags);
show_tags(tags);
 */
TagTreeType Tree_Search::search(const TagNode *fnode,const string &tgname,vector<Attr> &attrs,vector<TagNode*> &tags)
{
    //一轮搜索
    TagNode *p=fnode->left;
    TagNode cnode;
    unsigned int i=0;
    unsigned int size=0;
    //在p为根的树下任意遍历便可
    //前序遍历树
    while(p!=NULL || !this->tg_stack.isempty())
    {
        while(p!=NULL)
        {
            //test this node
            size=attrs.size();
            if(p->name==tgname)
            {
                //测试attr
                for(i=0;i<size;i++)
                {
                    if(this->match_attr(p,attrs))
                    {
                        tags.push_back(p);
                        break;
                    }
                }
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
//#id 或 .id等无tag name的搜索
/*
 * 测试：
//#id 测试通过---------------------------------------------
vector<Attr> attrs;
Attr a={"class","apple"};
Attr b={"id","football"};
attrs.push_back(a);
attrs.push_back(b);
ts.search(tg.root,attrs,tags);
console("tags size >"<<tags.size());
show_tags(tags);
*/
TagTreeType Tree_Search::search(const TagNode *fnode,vector<Attr> &attrs,vector<TagNode*> &tags)
{
    //一轮搜索
    TagNode *p=fnode->left;
    TagNode cnode;
    unsigned int i=0;
    unsigned int size=0;
    //在p为根的树下任意遍历便可
    //前序遍历树
    while(p!=NULL || !this->tg_stack.isempty())
    {
        while(p!=NULL)
        {
            //test this node
            if(this->match_attr(p,attrs))
            {
                tags.push_back(p);
            }
            //test end
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


bool Tree_Search::match_attr(const TagNode *tag,const vector<Attr> &attrs)
{
    const int size=attrs.size();
    for(int i=0;i<size;i++)
    {
        if(!this->__has_attr(tag,attrs[i]))
            return false;
    } 
    return true;
} 


bool Tree_Search::__has_attr(const TagNode *tag,const Attr &attr)
{
    AttrNode *at;
    at=tag->attr;
    while(at) 
    {
        if(at->name== attr.attr && at->value==attr.value)
            return true;
        at=at->next;
    } 
    return false;
} 


