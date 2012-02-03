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
#include "../tree_struct/xml_tree.h"
#endif

#ifndef TYPE_H_
#define TYPE_H_
#include "../type.h"
#endif

#ifndef TAG_TREE_STRUCT_H_
#define TAG_TREE_STRUCT_H_
#include "tag_tree_struct.h"
#endif

TagTreeType split_tagtext(string &text,Tag &tag);

class Tree_Search{
private:
    //Tag_Tree对象
    Tag_Tree tag_tree;
    //遍历中栈
    Stack<TagNode*> tg_stack;

public:
    Tree_Search();
    ~Tree_Search(); 
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
    TagTreeType find(string &text);
    //搜索主程序  在fa下搜索相应标签
    //根据标签名称进行查找
    TagTreeType search(TagNode *fnode,string &tgname,vector<TagNode*> &tags);
    //重载
    //根据 标签和属性进行查找  类似于 div[attrname=value]
    TagTreeType search(TagNode *fnode,string &tgname,string &attr,vector<TagNode*> &tags);
    //二级节点的查找
    //类似"div p"的搜索可以先搜索div 然后得到p
    TagTreeType search_by_two(TagNode *fnode,string &pa,string &child);
    //对一个节点进行属性判断
    //传入一段文本 自动进行拆分判断
    //！！！传入字符不得带引号
    bool match_attr(TagNode *tag,vector<string>&attrs);
    bool __has_attr(TagNode *tag,string &attrname,string &value);


};
