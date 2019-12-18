#include<stdio.h>
#include<stdlib.h>
int q=0;
struct node
{
	int data;
	struct node *next;
};
struct node *dequeue(struct node *queue)
{
	struct node *a=queue;
	queue=queue->next;
	free(a);
	return queue;
}
int check(int a[7][7],int visited[7],struct node *queue,int i)
{
	int k=0,d=0;
	while(k<7)
	{
		if(visited[k]==0)
			d=1;
		k++;
	}
		if(d==0)
			return 0;
		else
		{
			int j=0;
			struct node *temp=queue;
			int key=queue->data;
			int w=0;
			while(w<7)
			{
				if (a[key][w]==1 && visited[w]==0)
				{
					struct node *o=(struct node*)malloc(sizeof(struct node));
					o->data=w;
					o->next=NULL;
					temp->next=o;
					visited[w]=1;
					j=1;
					return check(a,visited,queue,i)+1;
					break;
				}
				if(a[w][key]==1 && visited[w]==0)
				{
					struct node *o=(struct node*)malloc(sizeof(struct node));
					o->data=w;
					o->next=NULL;
					temp->next=o;
					visited[w]=1;
					j=1;
					return check(a,visited,queue,i)+1;
					break;
				}
				w++;
			}
			if(j==0)
			{
				queue=dequeue(queue);
				if(queue==NULL)
					return 0;
				return check(a,visited,queue,i)+1;
			}
			else
				return check(a,visited,queue,i)+1;
		}
}
int mother(int a[7][7])
{
	int i=0;
	int h=0;
	struct node *queue=NULL;
	int visited[7]={0};
	while(i<7)
	{
		h=0;
		free(queue);
		queue=(struct node*)malloc(sizeof(struct node));
		queue->data=i;
		queue->next=NULL;
		int j=0;
		while(j<0)
		{
			visited[j]=0;
			j++;
		}
		visited[i]=1;
		h=check(a,visited,queue,i);
		if(h==6)
			return i;
		i++;
	}
	return 7;
}
void main()
{
	int a[7][7]={0};
	a[0][1]=a[0][2]=a[1][3]=a[4][1]=a[5][2]=a[5][6]=a[6][0]=a[6][4]=1;
	int j=mother(a);
	if(j==7)
		printf("It has no mother vertex");
	else
		printf("The mother vertex is: %d",j);
}
