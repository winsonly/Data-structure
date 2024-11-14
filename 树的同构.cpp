/*
现给定两棵树，请你判断它们是否是同构的。
*/
#include<bits/stdc++.h> 
#include <iostream>
using namespace std;

#define max 10
struct Node {
	char data;
	int left;
	int right;
} t1[max],t2[max];

int check[max];

int Build(struct Node t[]) {
//传入数组，返回根节点
	int n;
	int root=-1;
	int i,j;
	memset(check,0,sizeof(check));
	char cl,cr;//左右孩子
	cin>>n;
	for(i=0; i<n; i++) {
		cin>>t[i].data>>cl>>cr;

		if(cl!='-') {
			t[i].left=cl-'0';
			check[t[i].left]=1;
		} else
			t[i].left=-1;

		if(cr!='-') {
			t[i].right=cr-'0';
			check[t[i].right]=1;
		} else
			t[i].right=-1;
	}

	for(i=0; i<n; i++)
		if(!check[i])
			root=i;
	return root;
}

int Isomorphic(int r1,int r2) {
//传入根节点，返回1或0
	if(r1==-1&&r2==-1)
		return 1;
	else if(r1==-1&&r2!=-1||r1!=-1&&r2==-1)
		return 0;
	else if(t1[r1].data!=t2[r2].data)
		return 0;
	else if(t1[r1].left==-1&&t2[r2].left==-1)
		return Isomorphic(t1[r1].right,t2[r2].right);
	else
		return Isomorphic(t1[r1].left,t2[r2].right)&&Isomorphic(t1[r1].right,t2[r2].left)
		       ||Isomorphic(t1[r1].left,t2[r2].left)&&Isomorphic(t1[r1].right,t2[r2].right);

}

int main() {
	int r1,r2;
	r1=Build(t1);
	r2=Build(t2);
	int x= Isomorphic(r1,r2);
	if(x)
		cout<<"Yes";
	else
		cout<<"No";
	return 0;
}

