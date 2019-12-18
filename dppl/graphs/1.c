#include<stdio.h>
#include<stdlib.h>
struct node
{
	int data;
	struct node *next;
};
struct node *pop(struct node* stack)
{
	if(stack->next==NULL)
	{
		free(stack);
		return NULL;
	}
	struct node *p=stack;
	while(p->next->next!=NULL)
		p=p->next;
	free(p->next);
	p->next=NULL;
	return stack;
}
void dfs(int a[5][5],int visited[5],struct node *stack)
{
	int k=0,d=0;
	while(k<5)
	{
		if(visited[k]==0)
			d=1;
		k++;
	}
	if (visited[0]==0)
	{
		stack=(struct node*)malloc(sizeof(struct node));
		stack->data=0;
		stack->next=NULL;
		visited[0]=1;
		printf("0-");
		dfs(a,visited,stack);
	}
	else
	{
		if(d==1)
		{
			int j=0;
			struct node *temp=stack;
			while(temp->next!=NULL)
				temp=temp->next;
			int key=temp->data;
			int i=0;
			while(i<5)
			{
				if (a[key][i]==1 && visited[i]==0)
				{
					struct node *o=(struct node*)malloc(sizeof(struct node));
					o->data=i;
					o->next=NULL;
					temp->next=o;
					visited[i]=1;
					j=1;
					printf("%d-",i);
				}
				if(a[i][key]==1 && visited[i]==0)
				{
					struct node *o=(struct node*)malloc(sizeof(struct node));
					o->data=i;
					o->next=NULL;
					temp->next=o;
					visited[i]=1;
					j=1;
					printf("%d-",i);
				}
				i++;
			}
			dfs(a,visited,stack);
			if(j==0)
			{
				stack=pop(stack);
				dfs(a,visited,stack);
			}
			else
				dfs(a,visited,stack);
		}
	}
}
struct node *dequeue(struct node *queue)
{
	struct node *a=queue;
	queue=queue->next;
	free(a);
	return queue;
}
void bfs(int a[5][5],int visited[5],struct node *queue)
{
	int k=0,d=0;
	while(k<5)
	{
		if(visited[k]==0)
			d=1;
		k++;
	}
	if(visited[0]==0)
	{
		queue=(struct node*)malloc(sizeof(struct node));
		queue->data=0;
		queue->next=NULL;
		visited[0]=1;
		printf("0-");
		bfs(a,visited,queue);
	}
	else
	{
		if(d==1)
		{
			int j=0;
			struct node *temp=queue;
			int key=queue->data;
			int i=0;
			while(i<5)
			{
				if (a[key][i]==1 && visited[i]==0)
				{
					struct node *o=(struct node*)malloc(sizeof(struct node));
					o->data=i;
					o->next=NULL;
					temp->next=o;
					visited[i]=1;
					j=1;
					printf("%d-",i);
					bfs(a,visited,queue);
					break;
				}
				if(a[i][key]==1 && visited[i]==0)
				{
					struct node *o=(struct node*)malloc(sizeof(struct node));
					o->data=i;
					o->next=NULL;
					temp->next=o;
					visited[i]=1;
					j=1;
					printf("%d-",i);
					bfs(a,visited,queue);
					break;
				}
				i++;
			}
			if(j==0)
			{
				queue=dequeue(queue);
				bfs(a,visited,queue);
			}
			else
				bfs(a,visited,queue);
		}
	}
}
void main()
{
	int a[5][5]={0};
	int visited[5]={0};
	a[0][1]=a[0][3]=a[1][2]=a[3][2]=a[2][4]=1;
	struct node *stack=NULL;
	dfs(a,visited,stack);
	printf("\n");
	struct node *queue=NULL;
	int i=0;
	while(i<5)
	{
		visited[i]=0;
		i++;
	}
	bfs(a,visited,queue);
	printf("\n");
}
