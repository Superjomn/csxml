#include <iostream>
#include <string>
using namespace std;
#include "./tree_struct/xml_tree.h"
#include "./tree_search/tree_search.h"


int main()
{

    //string source="<body id='b1'>哈哈，我是春为哦  <div id='h1'  class  =   \"c2\" > 哈哈hello world</div>这是后面的哦<h1 style=\"font-weight:bold; font-size:13px;\"  >大家好</h1> </body>";

string source=" <html>\
    <head>\
        <title>hello world</title>\
        <style>\
            .classname{\
                font:\"20px\"; \
                color:#000;\
            } \
        </style>\
        <script>\
            function hello() \
            {\
                print 'hello world';\
            } \
        </script>\
    </head>\
    <body>\
        <div id=\"b1\">\
        你好\
        </div>\
    </body>\
</html>" ;


    
    /*
    body->left=div
    div->right=h1

    */
    Tag_Tree tg= Tag_Tree();
    TagTreeType res;

    tg.init(&source);
    /*

    string::size_type end;
    string scope;
    res=tg.scan_scope(39,end,&scope);
    cout<<"end "<<end<<endl;
    switch(res)
    {
    case TAGS:
        cout<<"TAGS"<<endl;
        break;
    case TAGE:
        cout<<"TAGE"<<endl;
        break;
    case TEXT:
        cout<<"TEXT"<<endl;
        break;
    }
    cout<<scope<<endl;
    */

    /*
    tg.scan_trans_tree();
    cout<<"------------------------------------"<<endl;
    tg.debug();
    string text="# class hello world";
    string word;
    string::size_type end;
    bool resu= next_word(text,0,end,word);
    if(resu)
        cout<<"next_word >"<<word<<endl;
    else
        cout<<"wrong"<<endl;

    text="p#pclass";
    Tag tag;
    split_tagtext(text,tag);
    cout<<"tag:attr  >"<<tag.tagname<<" "<<tag.attrtext<<endl;
    
    Stack<int> istack;
    for(int i=0;i<10;i++)
        istack.push(i);
    int num;
    istack.gtop(num);
    print("num  "<<num);
    istack.gtop(num);
    istack.gtop(num);
    print("num  "<<num);
    istack.pop(num);
    console("num  "<<num);
    istack.gtop(num);
    console("num  "<<num);


    //console("num>",string(ndhm));

     */

    string tt="p [ classname = value id = idname]";

    console("text: >"<<tt);
    Tag tag;
    split_tagtext(tt,tag);
    console("tg:at  " << tag.tagname <<"  "<<tag.attrtext);



    return 0;
}
