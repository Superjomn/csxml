/*#########################################
*   File:       xml_tree.cpp
*   @Author:    Chunwei
*   Date:       2012-01-26
*##########################################
*/
#include "./xml_tree.h"

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

template <typename T> inline bool is_odd(const T num)
{
    return num%2==1;
}
//private function ---------------------
bool Tag_Tree::is_completed()
{
    //cout<<"is_completed   step:size"<<this->step<<" "<<(this->source).size()<<endl;
    return this->step >= (this->source).size();
}

TagNode* Tag_Tree::create_new_tagnode()
{
    //cout<<"create_new_tagnode() "<<endl; 
    //新建一个tagnode
    TagNode *tg=new TagNode;
    //初始化
    (*tg).attr=NULL;
    (*tg).left=NULL;
    (*tg).right=NULL;
    //添加到stack中注册 便于最终同一注销
    this->tags.push(tg);
    return tg;
}

AttrNode* Tag_Tree::create_new_attrnode()
{
    //cout<<"create_new_attrnode() "<<endl;
    //新建一个tagnode
    AttrNode *tg=new AttrNode;
    //添加到stack中注册 便于最终同一注销
    (*tg).next=NULL;
    this->attrs.push(tg);
    //cout<<"attrs.size  "<<this->attrs.size()<<endl;  
    return tg;
}

void inline  Tag_Tree::__append_attr(TagNode *fa,string name,string value)
{
    /*
     * 为fa后接一个AttrNode
     */
    //cout<<"__append_attr()   name:value   "<<name<<"  "<<value<<endl;
    AttrNode *new_attr=this->create_new_attrnode(),
            *p=(*fa).attr;

    //cout<<"开始将attrnode进行赋值"<<endl;
    //进行赋值
    (*new_attr).name=name;
    (*new_attr).value=value;
    //cout<<"attr_value  "<<value<<endl; 
    //cout<<"开始将attrnode进行链接"<<endl;
    if((*fa).attr==NULL)
    {
        //cout<<"first attrnode"<<endl;
        (*fa).attr=new_attr;
    }
    else
    {
        //加到尾部
        while(p->next)
            p=p->next;
        p->next=new_attr;
    }

}

TagTreeType Tag_Tree::__tag_start(string &text ,TagNode &tag)
{
    /*对起始标签的处理
     * 需要独立传入一个字符串
     * 设立一个新节点，自动将相关属性组成属性链表
     * 将起始标签加入到标签stack中
     */
    cout<<"tag_start()"<<endl;
    cout<<"input text> "<<text<<endl;
    string::size_type s=0,c=0;
    string::size_type end;
    string attr_text;

    string attr_name,
           attr_value;
    //进行预处理 取除两侧无效空格
    trim(text);
    //cout<<"trim text "<<text<<endl;
    //利用更加优雅的方式
    //首次查找 不需要指定查找的起点
    s=text.find(' ');
    if(s>text.size())
    {
        //没有标签属性  
        tag.name=text;
        //cout<<"无属性标签 推出处理"<<endl;
    } 
    else
    {
         //存在标签属性 需要对标签属性进行处理
        //赋值给标签
        //cout<<"有属性标签"<<endl;
        tag.name=string(text,0,s+1);
        trim(tag.name);
        cout<<"tag.name is"<<tag.name<<endl;
        //trim(&tag.name); //两端去除空格

        //下面开始处理属性值------------------------------
        s++;    //跳过空格 name = value
        attr_text=string(text,s,text.size()-s);
        this->add_attr(&tag,attr_text);
    }

    //属性值处理完毕------------------------
    /*
     *将原tag_stack中的栈顶作为新tag的父节点进行修改
     *将起始标签加入到tag_stack中
     *后续需要对紧接其后的text交给新tag
     */
    TagNode *tag_top;
    TagTreeType res;
    string ntext;
    if(this->tg_stack.isempty())
        this->root=&tag;
    else
    {
        //取得栈顶节点进行处理
        this->tg_stack.gtop(tag_top);
        //栈顶元素的孩子设定
        this->append_child(tag_top,&tag);
    }
    cout<<"**push in tagstack"<<endl; 
    this->tg_stack.push(&tag);
    return RIGHT;
} 
//对终止标签的处理
TagTreeType Tag_Tree::__tag_end(string &text)
{
    /*
     tag_end:
         if gtop(stack)==newtag:
             add following_text to gtop(stack)
         else:
             error
     */
    string::size_type end;
    string ntext;
    TagTreeType res;
    TagNode *tag_top;

    trim(text);
    TagNode *ntag;
    console("stack size: " << this->tg_stack.size());
    if(this->tg_stack.gtop(ntag))
    {
        cout<<"ntag.name  '"<<(*ntag).name<<"'"<<endl;
        cout<<"end_tag.name  '"<<text<<"'"<<endl;
        cout<<"ntag.name  "<<(*ntag).name.size()<<endl;
        cout<<"end_tag.name  "<<text.size()<<endl;
        //栈非空
        if(text==((*ntag).name))
        {
            cout<<"匹配成功"<<endl; 
            //将匹配的tag弹出
            this->tg_stack.pop(ntag);
            //需要将尾接的text加入tag中
            //后续需要对紧接其后的text交给新tag
            //添加text的动作由scan完成
            //判断后续文本块属性
            TagTreeType scope_next_type=this->next_scope(this->step);

            if(scope_next_type==TEXT)
            {
                //将后续scope加入其中
                //将文本作为tag.pre
                res=this->scan_scope(this->step,end,ntext);
                //cout<<"From tag_end get next scope---------"<<ntext<<endl;
                (*ntag).folow=ntext;
                TagTreeError("scan_scope",res);
                this->step=end+1;
            }
            return RIGHT;
        }
        else
            //不匹配
            return ERROE_TAG_END_STACK_NO_MATCH;  
    }
    else
        //tag stack empty
        return ERROR_TAG_END_STACK_EMPTY;
}

Tag_Tree::Tag_Tree()
{
    //this->tg_stack=Stack<TagNode>();
    //this->attr_stack=Stack<AttrNode>();
}
Tag_Tree::~Tag_Tree()
{}

void Tag_Tree::init(string source)
{
    //初始化 将内存中源码赋值到本类中
    this->step=0;
    this->source=source;
    trans((this->source) ) ;
    cout<<"source is  "<<this->source<<endl; 
}

void Tag_Tree::append_child(TagNode *fa, TagNode *child)
{
    //为fa添加一个孩子
    cout<<"append a child"<<endl; 
    TagNode *cur,
            *son;
    son=fa->left;
    cur=son;

    while(son)
    {
        cur=son;
        son=son->right;
    }
    cur?cur->right=child:fa->left=child;
}//end append_chil

TagTreeType Tag_Tree::add_attr(TagNode *tag,string &text)
{
    //传入包含有关属性值的字符串 进行属性值的赋值
    //如 "name=value name=value" 
    //string text
    /*算法：
        trim(text) 

        size_t s=0,e=0
        string arr[] 
        scan_text
        if cur==' ' or '=':
            arr.append(text[s..e]) 
            s=e
        else
            e++;
        //判断是否为偶数
        if_not_even(arr_num):
            return false
        //循环添加属性节点
        ...
    */
    // name= "value"
    //cout<<"add_attr()"<<endl;
    //cout<<"传入 attr_text  "<<text<<endl;
    string name;
    string::size_type s=0,e=0;
    TagTreeType res;
    vector<string> arr;
    int i=0;

    trim(text);

    if(text.empty())
        //text为空格
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
    for(i=0;i<size;i+=2) //4 0 2 4
    {
        cout<<"in for size  "<<i<<endl;
        this->__append_attr(tag,arr[i],arr[i+1]);
    } 
    //后续需要处理attr
}//end apend_attr

//在源码中 下一个文本块的类型
TagTreeType Tag_Tree::next_scope(string::size_type start)
{
    //去除空格影响
    while((this->source)[start]==' ')
        start++;
    //到达文件尾
    if (start==(this->source).size())
    {
        //cout<<"next scope is NONE"<<endl;
        return NONE;
    }
    //开始判别
    switch((this->source)[start])
    {
    case '<':
        //cout<<"next scope is TAGS"<<endl;
        return TAGS;
        break;
    default:
        //cout<<"next scope is TEXT"<<endl;
        return TEXT;
        break;
    }
}



//整体的source已经是经过转换的 有效的字符串
TagTreeType Tag_Tree::scan_scope(string::size_type step,string::size_type &end,string &data)
{
    /*将无效字符进行剔除
     *返回类型  字符串于data中返回
     *end保存此块的末尾
     *同时将两边多余的无用字符去除
     *将其中无效的字符去除 并替换为空格
     */
    //查找区域
    string::size_type ap,   //  <
                      ab,   //  >
                      start=step; 
    /*
     * hello world<div>that is</div>
     */
    //去除初始的空格
    ////cout<<"scan_scope"<<"取除去空格"<<endl;
    while((this->source)[start]==' ') 
        start++;
    //标签开始  判断首字符
    //cout<<"switch source start"<<endl;
    //cout<<"start "<<(this->source)[start]<<endl;
    switch((this->source)[start]) 
    {
        case '<':
            //标签类型判断
            //cout<<"< 号"<<endl;
            ab = (this->source).find_first_of('>',start);
            //cout<<"ab:start  "<<ab<<" "<<start<<endl;   
            if(ab>start)
            {
                //cout<<"in scope"<<endl; 
                //>位置有效  对标签进行判断
                //start: < 
                //end:   >
                //this->end可以动态设置为 end+1
                end=ab;
                //隔开<> 有ab-start-1个有效字符  从start+1开始
                if(ab-start-1==0) 
                    //空标签
                    return ERROR_TAG_EMPTY_TAG;
                //返回标签内容
                
                data=string((this->source) ,start+1,ab-start-1);
                //分辨标签种类
                if ((this->source)[start+1]=='/') 
                {
                    //去除 / 影响
                    data=string(data,1,data.size()-1);
                    //cout<<"scan_scope data:>>>---------------->>  "<<data<<endl;
                    return TAGE;//标签结束
                }
                //cout<<"scan_scope data:>>>---------------->>  "<<data<<endl;
                return TAGS;//标签开始
            }
            else{
                //>位置无效 标签不闭合 
                return ERROR_TAG_SCAN_SCAPE_NO_FULL_TAG;
            } 
                
        break;

        default:
            //字符串
            //cout<<"default 字符串"<<endl;
            ap = (this->source).find_first_of('<',start);
            //之间默认隔着字符
            data=string((this->source) ,start,ap-start);
            //cout<<"scan_scope 字符串<<<<<<< "<<data<<endl;
            end=ap-1;
            //this->step始终指向下次扫描的起始位置
            return TEXT;
    } 
    //this->step 保持为最后扫描过的位置
}

bool Tag_Tree::scan_trans_tree()
{
    //cout<<"this is scan_trans_tree"<<endl;
    //扫描文本 转化为树
    //this->step 代表现在扫描的起始位置   this->step始终指向下次扫描的起始位置
    string scope;
    string::size_type end;
    TagTreeType stype;
    TagNode *tag_top;
    TagNode *newtag;
    string ntext;
    

    //cout<<"begin to test if completed"<<endl;
    this->step = 0;
    //对各个返回结果类型的保留值
    TagTreeType res;
    //已经完成
    if(this->is_completed())
    {
        //cout<<"it is completed"<<endl;
        return true;
    }

    //cout<<"get to while out"<<endl;

    while(!this->is_completed())
    {
        //cout<<"this is while begin to scope"<<endl;
        //遍历扫描  end指向结束位置
        stype=this->scan_scope(this->step,end,scope);
        TagTreeError("scan_scope",stype);
        //cout<<"after scan_scope" <<endl;
        //cout<<"this-step:end "<<this->step<<" "<<end<<endl;  
        this->step=end+1;
        //cout<<"this->step: "<<this->step<<endl;

        //cout<<"this-step:end "<<this->step<<" "<<end<<endl;  

        //cout<<"scope :"<<scope<<endl;
        //cout<<"stype :"<<stype<<endl;
        switch(stype)
        {
        case TAGS:
        {
            //起始标签
            //cout<<"TAGS  "<<scope<<endl;
            newtag = this->create_new_tagnode();
            res=this->__tag_start(scope,*newtag);
            TagTreeError("__tag_start",res);

            //若有后续text 接在头部
            //后续需要对紧接其后的text交给新tag
            //添加text的动作由scan完成
            //判断后续文本块属性
            //cout<<"开始判断下一个块属性"<<endl;
            TagTreeType scope_next_type=this->next_scope(this->step);

            if(scope_next_type==TEXT)
            {
                //cout<<"下一个块为字符串"<<endl;
                //将后续scope加入其中
                if(this->tg_stack.gtop(tag_top))
                {
                    //将文本作为tag.pre
                    res=this->scan_scope(this->step,end,ntext);
                    //cout<<"next text is "<<ntext<<endl;
                    (*tag_top).pre=ntext;
                    TagTreeError("scan_scope",res);
                    this->step=end+1;
                }
                //cout<<"pre text 处理完毕"<<endl;
             }
            break;
        }
        case TAGE:
            //cout<<"TAGE  "<<scope<<endl;
            //终止标签
            res=this->__tag_end(scope);
            TagTreeError("__tag_end",res);
            break;
        case TEXT:
            //cout<<"TEXT"<<endl;
            //文本
            //将文本添加到首端
            break;
        case NONE:
            //cout<<"NONE"<<endl;
            //结束
            break;
        default:
            //cout<<"未知属性"<<endl;
            break;
        }
    }
}

void show_tg(int space,const TagNode* tg) 
{
    for(int i=0;i<space;i++) 
    {
        cout<<"...";
    } 
    cout<<"tag.name  "<<(*tg).name<<endl;
    /*cout<<"tag.pre   "<<(*tg).pre<<endl;
    cout<<"tag.fol   "<<(*tg).folow<<endl;
    cout<<"tag.left:tag.right   "<<(*tg).left<<"  "<<(*tg).right<<endl;
    */
} 

void show_at(int space,const AttrNode* at) 
{
    for(int i=0;i<space;i++) 
    {
        cout<<"***";
    } 
    cout<<"attr  "<<(*at).name<<" = "<<(*at).value<<  endl;  
} 

void show_attr(const TagNode* at) 
{
    AttrNode *attr;
    attr=at->attr;
    int i=1;
    while(attr) 
    {
        show_at(i,attr);
        attr=attr->next;
        ++i;
    } 
} 

void show_child(const TagNode *tg)
{
    TagNode* p;
    int i=1;
    p=tg->left;
    if(!p) 
    {
        cout<<"no child"<<endl; 
        return;
    } 
    cout<<"child " <<i<<endl;
    ++i;
    show_tg(i,p);

    while(p->right)
    {
        p=p->right;
        cout<<"child " <<i<<endl;
        ++i;
        show_tg(i,p);
    } 
}


void Tag_Tree::debug()
{
    cout<<"show tags-----------------------------"<<endl;
    int size1=this->tags.size();
    for(int i=0;i<size1;i++)
    {
        cout<<"th:"<<i<<">>>>"<<endl;
        cout<<"tag                  "<<this->tags.arr[i]<<endl;
        cout<<"tag.name             "<<(*this->tags.arr[i]).name<<endl;
        cout<<"tag.pre              "<<(*this->tags.arr[i]).pre<<endl;
        cout<<"tag.fol              "<<(*this->tags.arr[i]).folow<<endl;
        cout<<"tag.left:tag.right   "<<(*this->tags.arr[i]).left<<"  "<<(*this->tags.arr[i]).right<<endl;
    }

    const int size2=this->attrs.size(); 
    for(int j=0;j<size2;j++) 
    {
        cout<<"th:"<<j<<">>>>"<<endl;
        cout<<"attr.name  "<<(*(this->attrs.arr[j])).name<<endl;
        cout<<"attr.value  "<<(*(this->attrs.arr[j])).value<<endl;
    } 
    cout<<"show tags-----------------------------"<<endl;
    cout<<"show tags-----------------------------"<<endl;

    for(int j=0;j<size1;j++) 
    {
        cout<<"tags.name  "<<(*(this->tags.arr[j])).name<<endl;
        show_child(this->tags.arr[j]) ;
        cout<<"show attrs---------" <<endl;
        show_attr(this->tags.arr[j]) ;
    } 
}

