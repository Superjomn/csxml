#include <iostream>
#include <string>
using namespace std;
#include "./parse/xml_tree.h"
#include "./search/tree_search.h"

void show_tag(TagNode *p);
void show_tags(vector<TagNode*> tags);

void show_tags(vector<TagNode*> tags)
{
    const unsigned int size=tags.size();
    for(int i=0;i<size;i++)
    {
        show_tag(tags[i]);
    }
}
void show_tag(TagNode *p)
{
    console("show Tag");
    console("node *  >"<<p);
    console("tagname  >"<<p->name);
    console("tagattrs ---------------");
    AttrNode *at;
    at=p->attr;
    while(at)
    {
        console(at->name<<"  "<<at->value);
        at=at->next;
    }
}

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
        <span class='apple' id='football'>嘟嘟<b>大大</b></span>\
        </div>\
        <div id=\"b2\">哈哈</div>\
    </body>\
</html>" ;
    
    /*
    Tag_Tree tg= Tag_Tree();
    TagTreeType res;
    tg.init(&source);

    string tt="p [ classname = value id = idname]";

    console("text: >"<<tt);
    Tag tag;
    split_tagtext(tt,tag);
    console("tg:at  " << tag.tagname <<"  "<<tag.attrtext);
    */
    int test=6;

    switch(test)
    {
        case 1:
        {
            //测试split_text_tags
            string text="p#id div[class=name id = name]";
            vector<string> v_tags;
            split_text_tags(text,v_tags);
            for(int i=0;i<v_tags.size();i++)
            {
                console("tagtext: >"<<v_tags[i]);
            }

        }
        break;
        case 2:
        {
            string text="div[id='idname' class='classname']";
            text="div#p";
            text="#p";
            Tag tag;
            split_tagtext(text,tag);

            console("tag: >  "<<tag.tagname<<"  >"<<tag.attrtext);
        }
        break;
        case 3:
        {
            string text="#div";
            string::size_type s=1,e;
            string word;
            bool res;
            res=get_word(text,1,e,word);
            console("get_word>"<<word);
            res=next_word(text,0,e,word);

            console("next_word>"<<word);
        }
        break;

        case 4:
        {
            string text="div[";
            string::size_type s=0,e;
            string word;
            next_word(text,s-1,e,word);
            console("next_wrod >"<<word);
        }
        break;
        case 5:
        {
            vector<Attr> attrs;
            string text="class = classname id = idname id='idname'";
            split_attr_text(text,attrs);
            console("attrs>");
            for(int i=0;i<attrs.size();i++)
            {
                console("attr: "<<attrs[i].value<<"  "<<attrs[i].value);
            }

        }
        break;
        case 6:
        {
            //测试search
            Tag_Tree tg= Tag_Tree();
            TagTreeType res;
            tg.init(&source);
            tg.scan_trans_tree();
            console("root"<<tg.root);
            //搜索方法
            Tree_Search ts=Tree_Search();
            vector<TagNode*> tags;
            //div
            ts.search(tg.root,"foot",tags);
            console("tags size >"<<tags.size());
            tags.clear();
            //#id
            vector<Attr> attrs;
            Attr a={"class","apple"};
            Attr b={"id","football"};
            attrs.push_back(a);
            attrs.push_back(b);
            ts.search(tg.root,attrs,tags);
            console("tags size >"<<tags.size());
            show_tags(tags);
            //div#id
            ts.search(tg.root,"span",attrs,tags);
            show_tags(tags);

        }
    }

    return 0;
}
