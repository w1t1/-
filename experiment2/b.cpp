#include <bits/stdc++.h>
#include<string>
using namespace std;

#define OK 1
#define OVERFLOW -1
#define ERROR 0

#define STACK_INIT_SIZE 100 //存储空间的初始分配量
#define STACK_INCREMENT 10 //存储空间的分配增量

pair<string,string> p;//暂存预测分析表表头的对应关系
map<pair<string,string>,string> table;

string input="";//存储待输入串
const char start='E';

typedef char SElemType;
typedef char QElemType;
typedef int Status;

//定义栈的数据结构【顺序存储表示】
typedef struct{
    SElemType *base;//栈底元素的位置,在构造栈前和销毁后，值为null
    SElemType *top;//栈顶
    int stackSize;//已分配的存储空间
}Stack;

//定义队列的数据结构【链表】
//链表的结点
typedef struct QNode{
    QElemType data;//结点数据的类型
    struct QNode *next;//指向下一结点
}QNode, *QueuePtr;

//链表队列
typedef struct{
    QueuePtr front;//头指针
    QueuePtr rear;//尾指针
}LinkQueue;

/*********************************栈的操作*****************************/

//栈的初始化操作
Status InitStack(Stack &s){
    s.base=(char *)malloc(STACK_INIT_SIZE*sizeof(Stack));//创建头结点
    if(!s.base) //如果未分配头结点
        exit(OVERFLOW);
    s.top=s.base;//令栈顶指针指向头结点,此时栈中无元素
    s.stackSize=STACK_INIT_SIZE;//分配初始存储空间大小
    return OK;
}

//进栈操作
Status Push(Stack &s, SElemType e){
    if(s.top-s.base >= s.stackSize){//如果栈空间已满
        //重新分配栈空间
        s.base=(char *)realloc(s.base,(s.stackSize+STACK_INCREMENT)*sizeof(Stack));
        if(!s.base)//空间分配失败
            exit(OVERFLOW);
        s.top=s.base;//将栈顶指针指向新的栈底元素
        //s.top=s.base+s.stacksize
        s.stackSize+=STACK_INCREMENT;//栈空间增加
    }
    *s.top++=e;//e元素入栈
    return OK;
}

//出栈操作
Status Pop(Stack &s, SElemType &e){
    if(s.top!=s.base){//如果当前栈顶指针未指向栈底元素的位置，即栈内有值
        e=*--s.top;//令e指向栈顶元素
        return OK;
    }
    exit(OVERFLOW);
}

//得到栈顶元素
Status GetElem(Stack s, SElemType &e){
    if(s.top!=s.base){//如果当前栈顶指针未指向栈底元素的位置，即栈内有值
        e=*(s.top-1);//令e指向栈顶元素
    }
    else exit(OVERFLOW);
}

//打印出栈各个元素
string PrintStack(Stack s){
    string str="";//暂存栈中元素
    //如果不是空栈且有值（未指向头结点）
    Stack ss;//令指针now指向栈顶指针指向的位置
    ss.top=s.top;
    ss.base=s.base;
    //当栈顶元素不为空，且栈不为空时
    while(*(ss.top-1) && ss.top!=s.base){
        ss.top=ss.top-1;
        str+=*ss.top;
    }
    return str;
}

/********************************队列的操作****************************/

//初始化队列
Status InitQueue(LinkQueue &q){
    q.front=q.rear=(QueuePtr)malloc(sizeof(QNode));//动态分配空间，先只分配头结点
    if(!q.front)//分配空间失败
        exit(ERROR);
    q.front->next=NULL;
    return OK;
}

//在队尾插入新元素
Status EnQueue(LinkQueue &q, char e){
    QueuePtr p;
    p=(QueuePtr)malloc(sizeof(QNode));//创建新结点
    if(!p)//结点分配失败
        exit(ERROR);
    p->data=e;//结点赋值
    p->next=NULL;//结点的下一结点指向空
    q.rear->next=p;//尾结点的下一结点指向新创建的结点
    q.rear=p;//尾指针指向新加入的结点
    return OK;
}

//出队首元素
Status DeQueue(LinkQueue &q, char &e){
    if(q.front==q.rear)//队列为空
        exit(ERROR);
    QueuePtr p;//将队列头结点赋值给p
    e=q.front->next->data;//将队首元素（头结点的下一个结点）赋值给e
    if(q.front->next==q.rear){//如果队列中仅有一个元素
        p=q.rear;//直接令p指向最后一个位置
        q.rear=q.front;//队列头尾指针重合，表示队列为空
        q.front->next=NULL;
    }
    else{//队列中不止一个元素
        p=q.front->next;//p指向首元素
        q.front->next=p->next;//q的头指针向后移动一个位置
        p->next=NULL;
    }
    free(p);
    return OK;
}

//打印队列元素
string PrintQueue(LinkQueue &q){
    string str="";//暂存当前队列中的元素
    LinkQueue p;//创建结点p，将q复制给p
    p.front=q.front;
    if(p.front!=p.rear){//如果队列不为空
        do{//先打印一个队首元素
            p.front=p.front->next;
            str+=p.front->data;
        }while(p.front->next);//如果下一个结点不为空
    }
    return str;
}

/***********************表驱动LL(1)语法分析**********************/

//初始化预测分析表
void InitTable(){
    p.first="E";
    p.second="i";
    table[p]="TE'";

    p.first = "E";
    p.second = "(";
    table[p] = "TE'";

    p.first = "E'";
    p.second = "+";
    table[p] = "+TE'";

    p.first = "E'";
    p.second = "-";
    table[p] = "-TE'";

    p.first = "E'";
    p.second = ")";
    table[p] = "ε";

    p.first = "E'";
    p.second = "#";
    table[p] = "ε";

    p.first = "T";
    p.second = "i";
    table[p] = "FT'";

    p.first = "T";
    p.second = "(";
    table[p] = "FT'";

    p.first = "T'";
    p.second = "+";
    table[p] = "ε";

    p.first = "T'";
    p.second = "-";
    table[p] = "ε";

    p.first = "T'";
    p.second = "*";
    table[p] = "*FT'";

    p.first = "T'";
    p.second = "/";
    table[p] = "/FT'";

    p.first = "T'";
    p.second = ")";
    table[p] = "ε";

    p.first = "T'";
    p.second = "#";
    table[p] = "ε";

    p.first = "F";
    p.second = "i";
    table[p] = "i";

    p.first = "F";
    p.second = "(";
    table[p] = "(E)";
}

void Do(Stack &analyse, LinkQueue &wait){
    int error_pos=-1;
    char s,q;
//    while();
    //如果分析栈中仅剩‘#’，而待输入队列队首元素不是'#'
    if(Pop(analyse,s)==OK && DeQueue(wait,q)==OK &&
        s=='#' && s!=q){
        printf("在第%d个字母位置出错（该句第x个词语）\n");
        return;
    }
   // if()
}

int main()
{
    InitTable();//设置预测分析表

   /* freopen("s.txt","r",stdin);
    freopen("result.txt","w",stdout);*/

    int num=0;
    while(getline(cin,input)){//每次从文件中读入一个字符串
        //创建分析栈，并初始化
        Stack analyse;
        InitStack(analyse);
        Push(analyse,'#');
        Push(analyse,start);

        //创建待输入串队列，并初始化
        LinkQueue wait;
        InitQueue(wait);
        for(int i=0;i<input.length();i++)
            EnQueue(wait,input[i]);
        EnQueue(wait,'#');

        cout<<setiosflags(ios::left)<<setw(5)<<num<<resetiosflags(ios::left)
            <<setiosflags(ios::left)<<setw(20)<<PrintStack(analyse)<<resetiosflags(ios::right)
            <<setiosflags(ios::right)<<setw(30)<<PrintQueue(wait)<<resetiosflags(ios::right)<<endl;

        //Do(analyse,wait);

        num++;
    }
    return 0;
}
