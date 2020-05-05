#include<bits/stdc++.h>
using namespace std;
map<string, string>mp_name;//保留字、符号的类型hash
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
void init()//初始化保留字和符号的hash表
{
    //类型
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
    mp_name["/"] = "slash";
    mp_name["="] = "eql";
    mp_name[">"] = "gtr";
    mp_name["<"] = "lss";
    mp_name[">="] = "geq";
    mp_name["<="] = "leg";
    mp_name["!="] = "neq";
    mp_name["=="] = "same";
    mp_name[","] = "comma";
    mp_name[";"] = "semicolon";
    mp_name["{"] = "lbparen";
    mp_name["}"] = "rbparen";
    mp_name["["] = "lbracket";
    mp_name["]"] = "rbracket";
    mp_name["("] = "lparen";
    mp_name[")"] = "rparen";
}
void getword(string &txt)//对txt字符串进行分析，并输出
{
    string tmp = "",sym;
    int pos = 0;//标记文本串的位置
    while(pos < txt.length())
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
            if(isResWord(tmp))//判断是否是保留字
                sym = mp_name[tmp];
            else
                sym = "IDENT";
        }
        else if(isNumber(tmp[0]))//如果是字母
        {
            while(isNumber(txt[pos]))//一直取数直到遇到非数字
                tmp += txt[pos++];
            sym = "NUMBER";
        }
        else if(isOperator(tmp[0]))
        {
            if((tmp[0] == '<' || tmp[0] == '>' || tmp[0] == '!' || tmp[0] == '=') && txt[pos] == '=')//如果碰到两个字符的运算符
                tmp += txt[pos++];
            sym = mp_name[tmp];

        }
        else //遇到错误（可能是未引入的符号）
        {
            sym="error";
        }
        cout << sym << '\t' << tmp << '\n';//输出类型
        tmp = "";
    }
}
string Read_word()//从缓冲区读取文本，返回一个string
{
    string txt;
    char c;
    while((c = getchar()) != EOF)//遇到文件尾就停止
    {
        txt += c;
    }
    return txt;
}
int main()
{
    freopen("in.in","r",stdin);
    freopen("out.out","w",stdout);
    init();
    string word=Read_word();//读取文本
    getword(word);
}
