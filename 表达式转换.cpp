/*
输入格式:
输入在一行中给出不含空格的中缀表达式，可包含+、-、*、/以及左右括号()，表达式不超过20个字符。

输出格式:
在一行中输出转换后的后缀表达式，要求不同对象（运算数、运算符号）之间以空格分隔，但结尾不得有多余空格。

输入样例:
2+3*(7-4)+8/4
输出样例:
2 3 7 4 - * + 8 4 / +
*/

#include<bits/stdc++.h>
using namespace std;

int main(){
	stack<char>s;
	map<char,int>m;//设置符号间的优先级
	
	m['+'] = 1; m['-'] = 1;
	m['*'] = 2; m['/'] = 2;
	m['('] = 3; m[')'] = 3;
	
	int flag = 0;
	string str;
	cin >> str;
	
	for( int i = 0; i < str.size(); i++ )
	{

		if( ( ((i == 0) || str[i - 1] == '(') && (str[i] == '+' || str[i] == '-'))// 如果是负数则 eg（-10)  其中 i = 0 考虑到 第一个数 如果是 eg +10 
		   || ( str[i] >='0' && str[i] <= '9') 
		   || ( str[i] == '.' )
		  )
		{
			if(flag != 0 )
			{
				cout << ' ';	
			} 
			
			if( str[i] != '+')
			{
				cout << str[i];
			}
			//这是要输出的数字eg 5.5 
			while( (str[i+1] == '.') || (str[i + 1] >= '0' && str[i + 1] <= '9'))
			{ 
				i++;
				cout << str[i];
			} 
			
			flag = 1;
				
		} 
		
		else
		{
		    if(str[i] == ')')
			{
				while(!s.empty() && s.top() != '(')
				{
				     cout << ' ' << s.top();
				     s.pop();	
				}
				s.pop();//将栈中的'(' 删除 
			}
			
			else if(s.empty() || m[str[i]] > m[s.top()])
			{
				s.push(str[i]);	
			}
			
			else
			{
				
				while( !s.empty() && s.top() != '(')
				{
					cout << ' ' << s.top();
					s.pop();	
				}	
				s.push(str[i]);
			} 					
		} 	
	}
	//将栈中剩余的符号输出来
	
	while(!s.empty())
	{
		cout << ' ' << s.top();
		s.pop(); 
	} 

} 

