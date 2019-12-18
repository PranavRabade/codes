#include<stdio.h>
#include<stdlib.h>
struct node
{
	int data;
	struct node *next;
};
struct node *push(struct node *stack,int i)
{
	struct node *a=stack;
	if(a==NULL)
		return NULL;
	else
	{
		while(a->next!=NULL)
			a=a->next;
		struct node *o=(struct node*)malloc(sizeof(struct node));
		o->data=i;
		o->next=NULL;
		a->next=o;
		return stack;
	}
}
struct node *trav(int a[5][5],int visited[5],struct node *stack,int j)
{
	int k=0,g=0;
	while(k<5)
	{
		if(visited[k]==0)
		{
			g=1;
			break;
		}
		k++;
	}
	if(g==0)
		return NULL;
	int i=0;
	while(i<5)
	{
		if(a[j][i]==1 && visited[i]==0)
		{
			visited[i]=1;
			stack=trav(a,visited,stack,i);
			stack=push(stack,i);
		}
		i++;
	}
}
struct node *topo(int a[5][5],int visited[5],struct node *stack)
{
	int i=0,j=0,k=0,g=0;
	while(k<5)
	{
		if(visited[k]==0)
		{
			g=1;
			break;
		}
		k++;
	}
	if(g==0)
		return NULL;
	while(i<5)
	{
		if(visited[i]==0)
		{
			j=i;
			break;
		}
		i++;
	}
	int o=j;
	visited[j]=1;
	stack=trav(a,visited,stack,j);
	stack=push(stack,o);
	return stack;
}
void main()
{
	int a[5][5]={0};
	a[0][1]=a[0][3]=a[1][2]=a[3][2]=a[2][4]=1;
	struct node *stack=NULL;
	int visited[5]={0};
	stack=topo(a,visited,stack);
}
