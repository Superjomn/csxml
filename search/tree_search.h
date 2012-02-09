/*#########################################
*   File:       tree_search.h
*   @Author:    Chunwei
*   Date:       2012-02-29
*##########################################
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

#ifndef TREE_SEARCH_H_
#define TREE_SEARCH_H_
#endif /* TREE_SEARCH_H_ */

#ifndef XML_TREE_H_
#define XML_TREE_H_
#include "../parse/xml_tree.h"
#endif

#ifndef TYPE_H_
#define TYPE_H_
#include "../type.h"
#endif

#ifndef TAG_TREE_STRUCT_H_
#define TAG_TREE_STRUCT_H_
#include "./tag_tree_struct.h"
#endif



/*
 * 将传入的查询字符拆分为各个tag的字符
 * 如： "p#id div.class"    =>      p#id / div.class
 */
TagTreeType split_text_tags(string text,vector<string> &v_tags);

/*
 * 将单个查询tagtext拆分为  tagname; tagattr 并返回tag
 * 如： "p#idname"          tagname:p
 *                          tagattr:id=idname
 */
TagTreeType split_tagtext(string text,Tag &tag);
/*
 * 将单个tag的attrtext进行拆分为多个attr
 * 如： "class=classname id=idname"     =>  class:classname
 *                                          id:idname
 */
TagTreeType split_attr_text(string &text,vector<Attr> &attrs);

class Tree_Search{

private:
    //Tag_Tree对象
    Tag_Tree tag_tree;
    //遍历中栈
    Stack<TagNode*> tg_stack;

public:

    bool __detect_right_search(Tag tag, Search_Type &type);

    bool __right_search(const TagNode *fnode,Tag tag,vector<TagNode*> &tags);

    bool __tags_filter(vector<TagNode*> &tags,const Tag &tag);

    //对tags检测 是否符合tag的要求
    bool match_tags(bool init,const TagNode* root,Tag tg,vector<TagNode*> &tagnodes);

public:
    bool init(string source);
    //进行查找
    /*
    匹配规则由外在函数指针传入
    匹配的结果节点指针保留到vector中
    最终的外围API也将由函数指针组成
    */
    //默认最多对两个节点如 "div a"进行判断 若多个 可以继续进行判断

    //查询总入口
    //各种差错控制
    //查询主程序 负责对查取text作分析 调用适当的search程序
    bool find(const string &text, vector<TagNode*> tagnodes);


    //搜索主程序  在fa下搜索相应标签
    //根据标签名称进行查找
    //传入 Tag tag 将会自动调用相关函数进行拆分判断
    bool search(const TagNode *fnode,const string &tgname,vector<TagNode*> &tags);

    //重载
    //根据 标签和属性进行查找  类似于 div[attrname=value]
    bool search(const TagNode *fnode,const string &tgname,vector<Attr> &attrs,vector<TagNode*> &tags);

    //#id 或 .id等无tag name的搜索
    bool search(const TagNode *fnode,vector<Attr> &attrs,vector<TagNode*> &tags);
    //二级节点的查找
    //类似"div p"的搜索可以先搜索div 然后得到p
    //对一个节点进行属性判断
    //传入一段文本 自动进行拆分判断
    //！！！传入字符不得带引号
    bool match_attr(const TagNode *tag,const vector<Attr> &attrs);
    //单个属性的检测
    bool __has_attr(const TagNode *tag,const Attr &attr);

};
