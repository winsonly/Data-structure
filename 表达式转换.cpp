/*
�����ʽ:
������һ���и��������ո����׺���ʽ���ɰ���+��-��*��/�Լ���������()�����ʽ������20���ַ���

�����ʽ:
��һ�������ת����ĺ�׺���ʽ��Ҫ��ͬ������������������ţ�֮���Կո�ָ�������β�����ж���ո�

��������:
2+3*(7-4)+8/4
�������:
2 3 7 4 - * + 8 4 / +
*/

#include<bits/stdc++.h>
using namespace std;

int main(){
	stack<char>s;
	map<char,int>m;//���÷��ż�����ȼ�
	
	m['+'] = 1; m['-'] = 1;
	m['*'] = 2; m['/'] = 2;
	m['('] = 3; m[')'] = 3;
	
	int flag = 0;
	string str;
	cin >> str;
	
	for( int i = 0; i < str.size(); i++ )
	{

		if( ( ((i == 0) || str[i - 1] == '(') && (str[i] == '+' || str[i] == '-'))// ����Ǹ����� eg��-10)  ���� i = 0 ���ǵ� ��һ���� ����� eg +10 
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
			//����Ҫ���������eg 5.5 
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
				s.pop();//��ջ�е�'(' ɾ�� 
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
	//��ջ��ʣ��ķ��������
	
	while(!s.empty())
	{
		cout << ' ' << s.top();
		s.pop(); 
	} 

} 

