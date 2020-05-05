#include<bits/stdc++.h>
using namespace std;
map<pair<string, string>, string>m;
pair<string, string>p;
stack<string>anal;
string txt;
string code_txt;
map<string, string>mp_name;
char c;
int code_txt_pos = 0;
double NiBolan_ans;
queue<string>q_txt;
stack<string>NiBolan_stack;
stack<double>NiBolan_stack_Num;
queue<string>NiBolan_Buffer,NiBolan_queue;
double string_double(string s)
{
    double ans=0;
    for(int i=0;i<s.length();i++)
    {
        ans=ans*10.0;
        ans+=(s[i]-'0');
    }
    return ans;
}
void init_getword()//初始化保留字和符号的hash表
{
    mp_name["main"] = "mainsys";
    mp_name["bool"] = "boolsys";
    mp_name["void"] = "voidsys";
    mp_name["if"] = "ifsys";
    mp_name["int"] = "intsys";
    mp_name["double"] = "doublesys";
    mp_name["char"] = "charsys";
    mp_name["string"] = "stringsys";
    mp_name["float"] = "floatsys";
    mp_name["for"] = "forsys";
    mp_name["while"] = "whilesys";
    mp_name["do"] = "dosys";
    mp_name["return"] = "returnsys";
    mp_name["break"] = "breaksys";
    mp_name["continue"] = "continuesys";
    mp_name["+"] = "plus";
    mp_name["-"] = "minus";
    mp_name["*"] = "mult";
    mp_name["/"] = "slash";
    mp_name["="] = "eql";
    mp_name[">"] = "gtr";
    mp_name["<"] = "lss";
    mp_name[">="] = "geq";
    mp_name["<="] = "leg";
    mp_name["!="] = "neq";
    mp_name[","] = "comma";
    mp_name[";"] = "semicolon";
    mp_name["{"] = "lbparen";
    mp_name["}"] = "rbparen";
    mp_name["["] = "lbracket";
    mp_name["]"] = "rbracket";
    mp_name["("] = "lparen";
    mp_name[")"] = "rparen";
    mp_name["#"] = "hash";
    mp_name["'"] = "apostrophe";
    mp_name["\""] = "double quotation mark";
    mp_name["."] = "interpunct";
    mp_name["=="] = "same";

}
void init()//初始化预测分析表
{
    //构造预测分析表
    p.first = "E";
    p.second = "i";
    m[p] = "TE'";

    p.first = "E";
    p.second = "(";
    m[p] = "TE'";

    p.first = "E'";
    p.second = "+";
    m[p] = "+TE'";

    p.first = "E'";
    p.second = "-";
    m[p] = "-TE'";

    p.first = "E'";
    p.second = ")";
    m[p] = "ε";

    p.first = "E'";
    p.second = "#";
    m[p] = "ε";

    p.first = "T";
    p.second = "i";
    m[p] = "FT'";

    p.first = "T";
    p.second = "(";
    m[p] = "FT'";

    p.first = "T'";
    p.second = "+";
    m[p] = "ε";

    p.first = "T'";
    p.second = "-";
    m[p] = "ε";

    p.first = "T'";
    p.second = "*";
    m[p] = "*FT'";

    p.first = "T'";
    p.second = "/";
    m[p] = "/FT'";

    p.first = "T'";
    p.second = ")";
    m[p] = "ε";

    p.first = "T'";
    p.second = "#";
    m[p] = "ε";

    p.first = "F";
    p.second = "i";
    m[p] = "i";

    p.first = "F";
    p.second = "(";
    m[p] = "(E)";

    init_getword();//初始化词法分析相关数据，代码和词法分析中init()函数相同
}
int priority(char op)               //判断运算符级别函数；其中* /的级别为2，+ -的级别为1；
{
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    else
        return 0;
}
bool isLetter(char c)  //判断参数c是否为字母，返回bool值；
{
    if(c >= 'a' && c <= 'z')//小写字母
        return true;
    if(c >= 'A' && c <= 'Z')//大写字母
        return true;
    return false;
}
bool isNumber(char c) //判断参数c是否为数字，返回bool值；
{
    if(c >= '0' && c <= '9')
        return true;
    return false;
}
bool isSpace(char c) //判断参数c是否为空格，返回bool值；
{
    if(c == ' ' )
        return true;
    return false;
}
bool isUnderLine(char c) //判断参数c是否为下划线，返回bool值；
{
    if(c == '_' )
        return true;
    return false;
}
bool isOperator(char c) //判断参数c是否为运算符，返回bool值；
{
    if(c == '+' || c == '-' || c == '*' || c == '/' || c == '<' || c == '>' || c == '!' || c == '=' ||
            c == '(' || c == ')' || c == '{' || c == '}' || c == ',' || c == ';' )
        return true;
    return false;
}
bool isResWord(string resWord)//判断参数resWord是否为保留字，返回bool值；
{
    if(mp_name.find(resWord) != mp_name.end())//查询hash表
        return true;
    return false;
}

bool getword()//词法分析
{
    int num = 0, pos = 0;
    pos = 0;
    txt = "";
    string tmp = "";
    while(!anal.empty()) anal.pop();//清空分析栈
    while(!anal.empty()) NiBolan_stack.pop();//清空分析栈
    while(!q_txt.empty())q_txt.pop();//清空剩余输入队列
    while(!NiBolan_Buffer.empty())NiBolan_Buffer.pop();//清空剩余输入队列
    while((c = getchar()) != '\n' && c != EOF) //读取一行的句子
    {
        txt += c;
    }
    if(c == EOF) //遇到文件尾，结束程序
        return 1;
    cout << txt << endl;
    while(pos < txt.length())//词法分析函数，与实验一大体相同
    {
        if(txt[pos] == '\n' || txt[pos] == ' ' || txt[pos] == '\t')//如果遇到空格，换行符和制表符，直接略过
        {
            pos++;
            continue;
        }
        tmp += txt[pos++];//读取一个字符
        if(isLetter(tmp[0]))//如果是字母
        {
            while(!isSpace(txt[pos]))//遇到空格就停止
            {
                if(!isLetter(txt[pos]) && !isNumber(txt[pos]) && !isUnderLine(txt[pos]))//如果遇到非变量名能使用的字符就停止
                    break;
                tmp += txt[pos++];
            }
        }
        else if(isNumber(tmp[0]))//如果是字母
        {
            while(isNumber(txt[pos]))//一直取数直到遇到非数字
                tmp += txt[pos++];;
        }
        else if(isOperator(tmp[0]))
        {
            if((tmp[0] == '<' || tmp[0] == '>' || tmp[0] == '!' || tmp[0] == '=') && txt[pos] == '=')//如果碰到两个字符的运算符
                tmp += txt[pos++];
        }
        q_txt.push(tmp);//生成输入队列
        tmp = "";
    }
    return 0;//读入一行代码成功
}
void analyze(string s)//预测可能的错误原因
{
    if(s == "(")
        printf("缺少(   \n");
    if(s == ")")
        printf("缺少)   \n");
    if(s == "+")
        printf("+缺少参数或者多余的+   \n");
    if(s == "-")
        printf("-缺少参数或者多余的-   \n");
    if(s == "*")
        printf("*缺少参数或者多余的*   \n");
    if(s == "/")
        printf("/缺少参数或者多余的/   \n");
    if(txt[txt.length() - 1] != ';')
        printf("缺少;\n");
}

void setNiBolan(string tmp)
{
    if(isNumber(tmp[0]))
    {
        NiBolan_queue.push(tmp);
    }
    else if(isOperator(tmp[0]))
    {
        if(tmp[0] == ')')
        {
            while(NiBolan_stack.top() != "(")
            {
                NiBolan_queue.push(NiBolan_stack.top());
                NiBolan_stack.pop();
            }
        }
        else if(tmp[0] == '(')
        {
            NiBolan_stack.push("(");
        }
        else
        {
            while(1)
            {
                if(NiBolan_stack.empty() || NiBolan_stack.top() == "(" || priority(tmp[0]) > priority(NiBolan_stack.top()[0]))
                {
                    NiBolan_stack.push(tmp);
                    break;
                }
                else
                {
                    NiBolan_queue.push(NiBolan_stack.top());
                    NiBolan_stack.pop();
                }
            }

        }
    }

}

void getNiBolan(bool fg)
{
    NiBolan_ans=0;
    while(!NiBolan_stack.empty())
    {
        if(NiBolan_stack.top() == ")" || NiBolan_stack.top() == "(")
        {
            NiBolan_stack.pop();
            continue;
        }
        NiBolan_queue.push(NiBolan_stack.top());
        NiBolan_stack.pop();
    }
    while(!NiBolan_queue.empty())
    {
        cout<<NiBolan_queue.front()<<" ";
        if(!isOperator(NiBolan_queue.front()[0]))
        {
            NiBolan_stack_Num.push(string_double(NiBolan_queue.front()));
        }
        else 
        {
            double num2=NiBolan_stack_Num.top();
            NiBolan_stack_Num.pop();
            double num1=NiBolan_stack_Num.top();
            NiBolan_stack_Num.pop();
            /*cout<<endl<<num1<<"  "<<num2<<endl;*/
            if(NiBolan_queue.front()=="+")
            {
                NiBolan_stack_Num.push(num1+num2);
            }
            else if(NiBolan_queue.front()=="-")
            {
                NiBolan_stack_Num.push(num1-num2);
            }
            else if(NiBolan_queue.front()=="*")
            {
                NiBolan_stack_Num.push(num1*num2);
            }
            else if(NiBolan_queue.front()=="/")
            {
                NiBolan_stack_Num.push(num1/num2);
            }
        }
        NiBolan_queue.pop();
    }
    if(fg)
    cout<<endl<<"结果为："<<NiBolan_stack_Num.top()<<endl;
    NiBolan_stack_Num.pop();
}


bool check()//语法分析主函数
{
    int num = 0, pos = 0;//pos:当前在第几个字符，num:当前是第几个单词
    cout << endl << endl;
    if(getword())//遇到文件尾，结束程序
        return 1;
    q_txt.push("#");//向剩余输入串尾添加#
    anal.push("#");//向分析栈内添加#E
    anal.push("E");
    while(1)
    {
        if(q_txt.front() == ";") //特判句子结束的；
        {
            q_txt.pop();
        }
        if(anal.top() == "#" && q_txt.front() == "#")//匹配成功的情况
        {
            if(txt[txt.length() - 1] != ';') //判断句子是否缺少；结尾
                printf("提示：缺少;");
            else
                cout << "accept";
            return 0;
        }
        string tmp = q_txt.front();//剩余输入串队首元素
        string wd_txt;//保存剩余输入串队首元素对应的符号
        int tmp_num = tmp.length();//记录当前单词位置
        pos += tmp.length();
        num++;
        q_txt.pop();
        if(!isResWord(tmp))//将剩余输入串队首元素转换成对应的符号
            wd_txt = "i";
        else wd_txt = tmp;
        if(anal.top() == wd_txt) //分析栈顶和剩余输入串队首匹配成功
        {
            anal.pop();
            continue;
        }
        while(anal.top() != wd_txt)//分析栈顶和剩余输入串队首匹配不成功
        {
            string wd_anal = anal.top();
            anal.pop();//分析栈弹栈
            p.first = wd_anal;
            p.second = wd_txt;
            if(m[p] == "")//预测分析表中为空白即出错
            {
                pos -= tmp_num;//当前单词的位置
                for(int i = 1; i <= pos; i++)
                    printf(" ");
                for(int i = 1; i <= tmp_num; i++)
                    printf("^");
                printf("\n");
                printf("在第%d个词即第%d个char位置出错\n", num, pos);
                printf("提示：");
                if(wd_txt != "#") //分析可能的错误原因
                    analyze(wd_txt);
                else
                    analyze(wd_anal);

                getNiBolan(0);
                return 0;
            }
            else if(m[p] == "ε") //预测分析表位置为ε
                continue;
            else
            {
                string stk = m[p];
                if(m[p] == wd_txt) //分析栈顶和剩余输入串队首匹配成功
                    break;
                for(int i = stk.length() - 1; i >= 0; i--)//查表得相应字符并倒序入栈
                {
                    if(stk[i] == '\'')//遇到E'，T'需要特殊处理
                    {
                        char tmp_char[3];//使即将入栈的字符串为X'类型(X为E或T)
                        tmp_char[0] = stk[i - 1];
                        tmp_char[1] = stk[i];
                        tmp_char[2] = '\0';
                        i--;
                        string cnt = tmp_char;
                        anal.push(cnt);
                    }
                    else
                    {
                        char tmp_char[2];//直接入栈当前字符
                        tmp_char[0] = stk[i];
                        tmp_char[1] = '\0';
                        string cnt = tmp_char;
                        anal.push(cnt);
                    }
                }
            }
        }
        if(anal.top() == wd_txt && anal.top() != "#") //分析栈顶和剩余输入串队首匹配成功但语法分析未结束
        {
            if(isOperator(tmp[0]))
            {
                NiBolan_Buffer.push(tmp);
            }
            else
            {
                while(!NiBolan_Buffer.empty())
                {
                    setNiBolan(NiBolan_Buffer.front());
                    NiBolan_Buffer.pop();
                }
                setNiBolan(tmp);
            }
            anal.pop();
            continue;
        }
        if(anal.top() == wd_txt && anal.top() == "#") //分析栈顶和剩余输入串队首匹配成功且语法分析结束
        {
            {
                if(txt[txt.length() - 1] != ';')
                    printf("提示：缺少;");
                else
                    cout << "accept" << endl;
                getNiBolan(1);
                return 0;
            }
        }
        if(isOperator(tmp[0]))
        {
            NiBolan_Buffer.push(tmp);
        }
        else
        {
            while(!NiBolan_Buffer.empty())
            {
                setNiBolan(NiBolan_Buffer.front());
                NiBolan_Buffer.pop();
            }
            setNiBolan(tmp);
        }

    }
}
int main()
{
    /*   freopen("in", "r", stdin);
       freopen("out", "w", stdout);*/
    init();
    while(!check())
    {

    }
}