#include<bits/stdc++.h>
using namespace std;
map<pair<string,string>,string>m;
pair<string,string>p;
stack<char>left,anal;
void init()
{
	p.first="E";
	p.second="i";
	m[p]="TE'";

	p.first="E";
	p.second="(";
	m[p]="TE'";

	p.first="E'";
	p.second="+";
	m[p]="+TE'";

	p.first="E'";
	p.second="-";
	m[p]="-TE'";

	p.first="E'";
	p.second=")";
	m[p]="ε";

	p.first="E'";
	p.second="#";
	m[p]="ε";

	p.first="T";
	p.second="i";
	m[p]="FT'";

	p.first="T";
	p.second="(";
	m[p]="FT'";

	p.first="T'";
	p.second="+";
	m[p]="ε";

	p.first="T'";
	p.second="-";
	m[p]="ε";

	p.first="T'";
	p.second="*";
	m[p]="*FT'";

	p.first="T'";
	p.second="/";
	m[p]="/FT'";

	p.first="T'";
	p.second=")";
	m[p]="ε";

	p.first="T'";
	p.second="#";
	m[p]="ε";

	p.first="F";
	p.second="i";
	m[p]="i";

	p.first="F";
	p.second="(";
	m[p]="(E)";
}
int main()
{
	string s;
	cin>>s;
}