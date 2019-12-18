#include<iostream>
#include<stdlib.h>
using namespace std;
struct graph//creating adjacency list
{
	int v;
	struct graph *next;
};
graph* create(int vertex)
{
	graph *g1=(graph *)malloc(vertex*sizeof(graph));
	for(int i=0;i<vertex;i++)
	{
		g1[i].next=NULL;
	}
	return g1;
}
graph* addedge(graph *s1,int source,int destination,int arr[],int n)
{
	graph *a=new graph;
	a->v=source;
	a->next=NULL;
	graph *a1=new graph;
	a1->v=destination;
	a1->next=NULL;
	int i;
	for(i=0;i<n;i++)//go to the edge
	{
		if(arr[i]==source)
		break;
	}
	if((s1[i].next)==NULL)//check if destination is valid or not
	{
		if(destination!=-1)
			a->next=a1;
		s1[i].next=a;//add edge
	}
	else
	{
		graph *temp;
		temp=s1[i].next;
		while(temp->next!=NULL)//traverse the list of vertex
			temp=temp->next;
		temp->next=a1;
	}
	return s1;
}
int is_cycle(graph *s,int n,int *h)
{
	int varr[n];//crreating a visited array
	for(int i=0;i<n;i++)
	{
		*h=0;
		if(s[i].next!=NULL)
		{
			graph *temp=s[i].next;
			varr[*h]=temp->v;
			temp=temp->next;
			while(temp!=NULL)
			{
				*h=1;
				varr[*h]=temp->v;//adding elements to visited array
				(*h)++;
				for(int j=0;j<n;j++)
				{
		        	        if(s[j].next!=NULL && s[j].next->v==varr[(*h)-1])//traverse to check the if alredy visited
		        	        {
		        	        	graph *temp1=s[j].next;
						for(int k=0;k<(*h);k++)
						{
							if(varr[0]==temp1->next->v)//if already visited return 1
								return 1;
						}
						varr[(*h)]=temp1->next->v;
						(*h)++;
						j=-1;
					}
				}
				temp=temp->next;
			}
		}
	}//else return
	return 0;
}
int main()
{
	int n=7,j;
	int arr[]={0,1,2,3,4,5,6};
	graph *s1=(graph *)malloc(n*sizeof(graph));
	s1=create(n);
	//question 1 graph
	s1=addedge(s1,0,1,arr,n);
	s1=addedge(s1,0,2,arr,n);
	s1=addedge(s1,6,0,arr,n);
	s1=addedge(s1,4,1,arr,n);
	s1=addedge(s1,5,2,arr,n);
	s1=addedge(s1,5,6,arr,n);
	s1=addedge(s1,6,4,arr,n);
	s1=addedge(s1,1,3,arr,n);
	//cyclic graph
	graph *s2=(graph *)malloc(n*sizeof(graph));
	s2=create(5);
	n=5;
	s2=addedge(s2,0,2,arr,n);
	s2=addedge(s2,1,0,arr,n);
	s2=addedge(s2,2,1,arr,n);
	s2=addedge(s2,0,3,arr,n);
	s2=addedge(s2,3,4,arr,n);
	int h=0;
	if(is_cycle(s1,n,&h)&& h>2)
		cout<<"Cycle exist";
	else
		cout<<"Cycle does not exist";
	h=0;
	if(is_cycle(s2,n,&h)&& h>2)
		cout<<"Cycle exist";
	else
		cout<<"Cycle does not exist";
}
