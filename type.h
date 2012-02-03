#include <iostream>
#include <string>
using namespace std;

#ifndef TYPE_H_
#define TYPE_H_ 
#endif

typedef struct{
    string attr;
    string value;
}Attr;

typedef struct{
    string tagname;
    string attrtext;    //attri的文本
    /*
     * 如[class=a] 中的 class=a
     */
}Tag;

//属性节点
typedef struct attrnode{
    string name;
    string value;            //属性值
    struct attrnode *next;  //作为属性链表
}AttrNode;

//标签节点
typedef struct tagnode{
    string name;             //名称
    AttrNode *attr;         //第一个attr属性值
    string pre;          //tag内 在第一个子标签前的text
    string folow;        //紧接本tag其后的text
    struct tagnode *left;   //左侧代表孩子
    struct tagnode *right;  //右侧代码兄弟
}TagNode;

typedef enum{
    //scan_scape() 
    NONE,   //无效
    TAGS,   //标签块开始
    TAGE,   //标签块结束
    TEXT,   //文本块
    RIGHT,                              //正确
    ERROR_TAG_SCAN_SCAPE_NO_FULL_TAG,   //标签不完整
    ERROR_TAG_EMPTY_TAG,                //空标签<> 
    ERROR_TAG_ONLY_ATTRNAME,            //只存在attrname 无=
    //__tag_start() 
    ERROR_TAG_NOT_TRIM,                 //文本两侧空格未去除
    //__tag_end() 
    ERROR_TAG_END_STACK_EMPTY,          //栈空
    ERROE_TAG_END_STACK_NO_MATCH,       //栈顶不匹配
    //append_attr
    ERROR_TAG_EMPTY_TEXT,               //传入空字符
    //split_trans_tag
    ERROR_TAG_NO_A_TAG_WORD,                //解析不存在有效文本
    ERROR_TAG_NO_RIGHT_RIGHT_REC_BRACKET,   //解析无右侧括号
    //upper
    ERROR_DIV_0,                        //除数为0
    ERROR_TAG_WRONG_SYNTAX,             //语法错误
    ERROR_TAG_STR_NOT_EVEN              //数组内元素个数为奇数

}TagTreeType;

//错误处理中心
//对各种错误进行处理
bool TagTreeError(const string fun,const TagTreeType type);
