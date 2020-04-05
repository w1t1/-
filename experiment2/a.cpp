#include<bits/stdc++.h>
using namespace std;
map<pair<string, string>, string>m;
pair<string, string>p;
stack<string>anal;
string txt, sym;
string tmp = "";
map<string, string>mp_name;
map<string, int>mp_fg;
int num = 0, pos = 0;
char c;
queue<string>q_txt;
void init_getword()
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
    mp_fg["*"] = 1;
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
    mp_fg["#"] = 1;
    mp_fg["'"] = 1;
    mp_fg["\""] = 1;
    mp_fg["."] = 1;

}
void init()
{
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

    init_getword();
}

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

bool getword()
{
	pos=0;
	txt="";
	while(!anal.empty()) anal.pop();
	while(!q_txt.empty())q_txt.pop();
    while((c = getchar()) != '\n' && c!=EOF)
    {
        txt += c;
    }
    if(c==EOF)
    	return 1;
    cout<<txt<<endl;
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
        q_txt.push(tmp);
        //out << sym << '\t' << tmp << '\n';
        tmp = "";
    }
    return 0;
}
void analyze(string s)
{
	if(s=="(")
		printf("缺少(   ");
	if(s==")")
		printf("缺少)   ");
	if(s=="+")
		printf("+缺少参数或者多余的+   ");
	if(s=="-")
		printf("-缺少参数或者多余的-   ");
	if(s=="*")
		printf("*缺少参数或者多余的*   ");
	if(s=="/")
		printf("/缺少参数或者多余的/   ");
	if(txt[txt.length()-1]!=';')
		printf("缺少;");
}
bool check()
{
	cout<<endl<<endl;
    if(getword())
    	return 1;
    q_txt.push("#");
    anal.push("#");
    anal.push("E");
    pos = 0;
    num = 0;
   /* p.first = "E";
    p.second = "i";
    cout << m[p][2] << endl;*/
    while(1)
    {
    	if(q_txt.front()==";")
    	{
    		q_txt.pop();
    	}
        if(anal.top() == "#" && q_txt.front() == "#")
        {
        	if(txt[txt.length()-1]!=';')
				printf("提示：缺少;");
			else
            	cout << "accept";
            return 0;
        }
        string tmp = q_txt.front();
        string wd_txt;
        int tmp_num = tmp.length();
        pos += tmp.length();
        num++;
        q_txt.pop();
        if(!mp_fg[tmp])
            wd_txt = "i";
        else wd_txt = tmp;
        if(anal.top()==wd_txt)
        {
        	//cout<<"------------"<<endl;
        	anal.pop();
        	continue;
        }
        while(anal.top() != wd_txt)
        {
            string wd_anal = anal.top();
            anal.pop();
            p.first = wd_anal;
            p.second = wd_txt;
            //cout<<"top:  "<<wd_anal<<" m[p]: "<<m[p]<<"  ";
            //cout << wd_anal << " " << wd_txt << endl;
            if(m[p] == "")
            {
                pos -= tmp_num;

                for(int i = 1; i <= pos; i++)
                    printf(" ");
                for(int i = 1; i <= tmp_num; i++)
                    printf("^");
                printf("\n");
                printf("在第%d个词即第%d个char位置出错\n", num, pos);
                // cout<<wd_txt<<" "<<wd_anal<<endl;
                
                printf("提示：");
                //cout<<wd_anal<<" "<<wd_txt<<endl;
                if(wd_txt!="#")
                	analyze(wd_txt);
            	else 
            		analyze(wd_anal);
                return 0;
            }
            else if(m[p]=="ε")
            	continue;
            else
            {
                string stk = m[p];
                if(m[p]==wd_txt)
               		break;
                //cout<<stk<<endl;
                for(int i = stk.length() - 1; i >= 0; i--)
                {
                	//cout<<i<<' '<<stk[i]<<endl;

                    if(stk[i] == '\'')
                    {
                        char tmp_char[3];
                        tmp_char[0]=stk[i-1];
                        tmp_char[1]=stk[i];
                        tmp_char[2]='\0';
                        i--;
                        string cnt=tmp_char;
                        anal.push(cnt);
                       	//cout<<"cnt:"<<' '<<cnt<<endl;
                    }
                    else
                    {
                        char tmp_char[2];
                        tmp_char[0]=stk[i];
                         tmp_char[1]='\0';
                        string cnt=tmp_char;
                        anal.push(cnt);
                        //cout<<"cnt:"<<' '<<cnt<<endl;
                    }
                }
            }
        }
        if(anal.top()==wd_txt && anal.top()!="#")
        {
        	//cout<<"------------"<<endl;
        	anal.pop();
        	continue;
        }
        if(anal.top()==wd_txt && anal.top()=="#")
        {
        	if(txt[txt.length()-1]!=';')
				printf("提示：缺少;");
			else
        		cout << "accept" << endl;
            return 0;
        }
    }
}
int main()
{
	init();
	while(!check())
    {

    }
}