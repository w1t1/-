#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include<string>
#include<map>
using namespace std;
map<string, string>mp_name;
map<string, int>mp_fg;
string KEYWORD[8] = { "if","int","for","while","do",   //保留字
          "return","break","continue"};
char SEPARATER[8] = { ';',',','{','}','[',']','(',')' };  //分隔符
char OPERATOR[7] = { '+','-','*','/','>','<','=' };   //运算符

char token[20]; //存放字符（单词）
string sym;
/**判断是否为保留字**/
bool isResWord(string resWord) {
    for (int i = 0; i < 8; i++) {
        if (KEYWORD[i] == resWord) {
            return true;
        }
    }
    return false;
}

/**判断是否为运算符**/
bool isOperator(char c) {
    for (int i = 0; i < 7; i++) {
        if (OPERATOR[i]==c)
        {
            return true;
        }
    }
    return false;
}

/**判断是否为字母**/
bool isLetter(char c) {
    if (c >= 'A' && c <= 'Z' | c>='a' && c<='z') 
        return true;
    return false;
}

/**判断是否为数字**/
bool isNumber(char c) {
    if (c >= '0' && c <= '9') return true;
    return false;
}

//判断是否为分隔符
bool isSeparater(char c) 
{
    for (int i = 0; i < 8; i++)
    {
        if (SEPARATER[i] == c)
        {
            return true;
        }
    }
    return false;
}

bool isSpace(char c) //判断参数c是否为空格，返回bool值；
{
    if (c == ' ')
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

/**词法分析**/
void scanner(int &p, string s)
{
    init();
    string sym;
    int count = 0;
    //判断是否为空格和换行
    if (s[p] == ' ' || s[p] == '\n')
    {
        p++;
    }
    //不是空格
    else if (!isSpace(s[p]))
    {
        while (isNumber(s[p]) || isLetter(s[p]))//字母和数字
        {
            token[count++] = s[p];
            p++;
        }
        token[count] = '\0';    //'\0'作为结束符 ,将单词分隔开 
        if (isLetter(token[0]))//以字母开头
        {
                if (!isLetter(s[p]) && !isNumber(s[p])) //保留字，标识符
                {
                    if (mp_fg[token] == 1)
                    {
                        sym = mp_name[token];
                    }
                    else
                        sym = "ident";
                }
            cout << sym << '\t' << token <<'\n';
        }
        else if (isNumber(token[0]))//以数字开头
        {
            while (isNumber(s[p]))
            {
                token[count++] = s[p];
                p++;
            }
            token[count] = '\0';//结束标识
            sym = "number";
            cout << sym << '\t' << token << '\n';
        }
        else 
        {
            token[count] = s[p];
            sym = mp_name[token];
            cout << sym << '\t' << token << '\n';
        }
        p++;
    }

}

int main()
{
    string s;
    while (cin >> s)
    {
        int p = 0;
        while (p < s.length())   //循环条件 ,p还未指到字符串最后  
        {
            scanner(p, s);
        }
    }
    return 0;
}