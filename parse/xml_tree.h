/*#########################################
*   File:       xml_tree.h
*   @Author:    Chunwei
*   Date:       2012-02-26
*##########################################
*/
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#ifndef XML_TREE_H_
#define XML_TREE_H_
#endif

#ifndef TYPE_H_
#define TYPE_H_
#include "../type.h"
#endif

#ifndef STR_H_
#define STR_H_
#include "../tools/str.h" 
#endif

#ifndef TAG_TREE_STRUCT_H_
#define TAG_TREE_STRUCT_H_
#include "./tag_tree_struct.h"
#endif


/*
 * 功能描述：
 *  从xml源码建立xml树
 *///建立标签树的方法
/*
 * 整棵xml树采用二叉树存储（孩子兄弟)
 *
 * <div id='hd'>
 *      <span class='red'>hello world</span>
 *      <span class='red'>this is chun</span>
 * </div>
 *
 * 具体逻辑：
 *      访问到一个标签始
 */




class Tag_Tree{
private:
    Stack<TagNode *> tg_stack;
    //Stack<AttrNode> attr_stack;
    //处理的字符源字符 this->source将通过
    string *source;
    //始终指向下次扫描的位置 类似于PC
    string::size_type step;
    //private function ---------------------

public:
    //树的根节点
    TagNode *root;
    //注册tags 便于最后注销时统一
    Register_Arr<TagNode*> tags;
    //注册attrs 便于最后注销时同一
    Register_Arr<AttrNode*> attrs;

public:

    //是否已经完成 可以结束扫描
    bool is_completed();
    //malloc一个新标签 并且将地址存入stack中 便于最后free
    TagNode *create_new_tagnode();
    //malloc一个新标签 并且将地址存入stack中 便于最后free
    AttrNode* create_new_attrnode();

    void inline __append_attr(TagNode *fa,string name,string value);
    //对起始标签处理
    TagTreeType __tag_start(string &text,TagNode &tag);
    //对终止标签处理
    TagTreeType __tag_end(string &text);
    //下一个文本块的类型
    TagTreeType next_scope(string::size_type start);

    Tag_Tree();
    
    ~Tag_Tree();
    /*初始化
     *将源码复制一份，并进行预处理（将无用字符替换为空格 并且将多余空格去除
     *处理完的字符可直接用作机器处理
     */
    void init(string *source);
    //为一个节点添加子节点
    void append_child(TagNode *fa, TagNode *child);
    //为一个节点添加属性
    //传入有关属性的字符串 如"name=value  name=value" 
    //自动添加所有属性
    TagTreeType add_attr(TagNode *tag,string &text);
    //scan_scape 扫描
    //返回一个字段 (tag内的 or 夹在tag间的文本) 
    /*传入其中的 source start和end   start可以由this->step指定
     *每次返回一个scape 并且返回类型
     *同时将this->step指向下次扫描的起始位置
     */

    TagTreeType scan_scope(string::size_type step,string::size_type &end,string &data);
    //主程序 根据源码建立树
    //提前需要用init初始化
    bool scan_trans_tree();
    //测试
    void debug();
};


