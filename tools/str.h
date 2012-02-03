/*#########################################
*   File:       tools/str.h
*   @Author:    Chunwei
*   Date:       2012-01-29
*##########################################
*/
#include <iostream>
#include <string>
#include <vector>
#include <stdarg.h>
using namespace std;

#ifndef STR_H_
#define STR_H_
#endif /* STR_H_ */

#ifndef TYPE_H_
#define TYPE_H_
#include "../type.h"
#endif
//空格
#define SPACE "  " 
//强制转化
#define S(x) (string)x
#define print(x) cout<<x<<endl;
//控制台输出
#define console(x) cout<<x<<endl;


//控制台输出 便于测试
//void console(string n_values, ...);
//将传入的属性字符串分割为属性和值
//并以vectori返回
TagTreeType split_trans_attr(string &text,vector<string> &attrs);
//将string两端空格或无用字符去除
bool trim(string &s);

//将string中间的字符进行转换 将无用字符及连续的无效字符用空格转换
bool trans(string &s);

//删除字符两侧引号 主要用作属性值的处理
void  rm_mark(string &text) ;

//从s开始的下一个word
bool next_word(const string &text,const string::size_type s,string::size_type &e,string &word);
//从当前位置向后取得一个word
bool get_word(const string &text,const string::size_type s,string::size_type &e,string &word);


//是否为偶数
template <typename T> inline bool is_even(const T num);
//是否为奇数
template <typename T> inline bool is_odd(const T num);
//min
template <typename T> inline T min(const T a,const T b) ;
//max
template <typename T> inline T max(const T a,const T b) ;




