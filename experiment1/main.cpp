#include<bits/stdc++.h>
using namespace std;
string txt, sym;
string tmp = "";
map<string, string>mp_name;
map<string, int>mp_fg;
int num = 0, pos = 0;
bool isLetter(char c)  //判断参数c是否为字母，返回bool值；
{
    if(c >= 'a' && c <= 'z')
        return true;
    if(c >= 'A' && c <= 'Z')
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
void init()
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

    mp_fg["main"] = 1;
    mp_fg["bool"] = 1;
    mp_fg["void"] = 1;
    mp_fg["double"] = 1;
    mp_fg["char"] = 1;
    mp_fg["string"] = 1;
    mp_fg["float"] = 1;
    mp_fg["if"] = 1;
    mp_fg["int"] = 1;
    mp_fg["for"] = 1;
    mp_fg["while"] = 1;
    mp_fg["do"] = 1;
    mp_fg["return"] = 1;
    mp_fg["break"] = 1;
    mp_fg["continue"] = 1;
    mp_fg["+"] = 1;
    mp_fg["-"] = 1;
    mp_fg["/"] = 1;
    mp_fg["="] = 1;
    mp_fg[">"] = 1;
    mp_fg["<"] = 1;
    mp_fg[">="] = 1;
    mp_fg["<="] = 1;
    mp_fg["!="] = 1;
    mp_fg[","] = 1;
    mp_fg[";"] = 1;
    mp_fg["{"] = 1;
    mp_fg["}"] = 1;
    mp_fg["["] = 1;
    mp_fg["]"] = 1;
    mp_fg["("] = 1;
    mp_fg[")"] = 1;
}
char c;
int main()
{
    init();
    while((c = getchar()) != EOF)
    {
        txt += c;
    }
    while(pos < txt.length())
    {
        if(txt[pos] == '\n' || txt[pos] == ' ' || txt[pos] == '\t')
        {
            pos++;
            continue;
        }
        if(tmp == "")
            tmp += txt[pos++];
        if(isLetter(tmp[0]))
        {
            while(!isSpace(txt[pos]))
            {
                if(!isLetter(txt[pos]) && !isNumber(txt[pos]) && !isUnderLine(txt[pos]))
                    break;
                tmp += txt[pos++];
            }
            if(mp_fg[tmp] == 1)
                sym = mp_name[tmp];
            else
                sym = "IDENT";
        }
        else if(isNumber(tmp[0]))
        {
            while(isNumber(txt[pos]))
                tmp += txt[pos++];
            sym = "NUMBER";
        }
        else
        {
            if((tmp[0] == '<' || tmp[0] == '>') && txt[pos] == '=')
                tmp += txt[pos++];
            sym = mp_name[tmp];

        }
        cout << sym << '\t' << tmp << '\n';
        tmp = "";
    }
}
