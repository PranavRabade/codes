#include<stdio.h>
#include<stdlib.h>
// The free list will contain all the free chunks of the memory
// It will show the free memory as
// Size of the chunk and it's starting point
struct freE
{
	int start;
	int size;
	struct freE *next;
};
// The allocated list will contain the chunks of memory in which the memory is allocated
// It contains the name starting address and the size of the array
struct alloc
{
	char name;
	int start;
	int size;
	struct alloc *next;
};
// The node structure is made for allocation of memory
struct node
{
	char data;
	struct node *next;
};
// Initialy the heap must be empty so the memory allocate must be empty
// Also we need to allocate a free list
// We assume that the heap is of size 1000 starting from 0 to 999
struct freE *initialise(struct freE *l)
{
	struct freE *d=l;
	while(l)
		l=l->next;
	l=(struct freE*)malloc(sizeof(struct freE));
	l->start=0;
	l->size=1000;
	l->next=NULL;
	return d;
}
// It is used when the free memory is filled by any memory
struct freE *fillfree(struct freE *l, int size)
{
	l->start=l->start+size;
	l->size=l->size-size;
	return l;
}
// Fills the allocated list on each memory allocation
struct alloc *fillalloc(struct alloc *a, struct freE *l, int s, char* name)
{
	a=(struct alloc*)malloc(sizeof(struct alloc));
	a->name=name[0];
	a->start=l->start;
	a->size=s;
	a->next=NULL;
	return a;
}
// This is a self created malloc funtion which  illustrates the allocation of memory
struct node *newMalloc(struct node *start, char* name, int s, struct freE *l, struct alloc *a)
{
	start=(struct node *)malloc(sizeof(struct node));
	start->data=name[0];
	start->next=NULL;
	a=fillalloc(a, l, s, name);
	l=fillfree(l, s);
	return start;
}
// This used when we add a block in the free memory
struct freE *addfree(struct freE *f, struct alloc *a, char* name)
{
	struct freE *l=f;
	struct freE *g;
	while(a)
	{
		if(a->name==name[0])
			break;
		a=a->next;
	}
	while(l)
	{
		if(((l->start)+(l->size))==((a->start)-1))
			break;
		if(((l->start)+(l->size))<=a->start)
			g=l;
		if(((l->start)+(l->size))>=a->start)
			break;
		l=l->next;
	}
	if(((l->start)+(l->size))==((a->start)-1))
		l->size=(l->size)+(a->size);
	else
	{
		struct freE *i=(struct freE*)malloc(sizeof(struct freE));
		i->start=a->start;
		i->size=a->size;
		i->next=g->next;
		g->next=i;
	}
	return f;
}
// Used when we free a memory block
struct alloc *freealloc(struct alloc *a, char *name)
{
	struct alloc *z=a;
	struct alloc *b;
	while(z->name!=name[0])
		z=z->next;
	b=z->next->next;
	free(z->next);
	z->next=b;
	return a;
}
// Free function example
struct node *del(struct node *head, char* name, struct freE *l, struct alloc *a)
{
	struct node *d=head;
	while(d->next->data!=name[0])
		d=d->next;
	struct node *g=d->next->next;
	free(d->next);
	d->next=g;
	l=addfree(l, a, name);
	a=freealloc(a,name);
	return head;
}
// First fit
struct node *firstfit(struct node *head, char *name, int size, struct freE *f, struct alloc *a)
{
	if(head=NULL)
		head=newMalloc(head, name, size, f, a);
	else
	{
		struct node *k=head;
		while(k)
			k=k->next;
		if(f->size<size)
		{
			while(f)
			{
				if(f->size>=size)
					break;
				f=f->next;
			}
			if(f==NULL)
				printf("Need Grabage management");
			else
			{
				head=newMalloc(k, name, size, f, a);
			}	
		}
		else
			head=newMalloc(k, name, size, f, a);
	}
	return head;
}
// Best fit
struct node *bestfit(struct node *head, char *name, int size, struct freE *f, struct alloc *a)
{
	if(head=NULL)
		head=newMalloc(head, name, size, f, a);
	else
	{
		struct node *k=head;
		while(k)
			k=k->next;
		struct freE *d=NULL;
		while(f)
		{
			if(d==NULL)
			{
				if(f->size>=size)
					d=f;
			}
			else
			{
				if(f->size>=size && f->size<d->size)
					d=f;
			}
			f=f->next;
		}
		if(d==NULL)
			printf("Need Grabage management");
		else
			head=newMalloc(k, name, size, d, a);
	}
	return head;
}
// Next fit
struct node *nextfit(struct node *head, char *name, int size, struct freE *f, struct alloc *a)
{
	if(head=NULL)
		head=newMalloc(head, name, size, f, a);
	else
	{
		struct node *k=head;
		while(k)
			k=k->next;
		struct freE *d;
		if(f->size<size)
		{
			while(f)
			{
				if(f->size>=size)
					d=f;
				f=f->next;
			}
			if(d==NULL)
				printf("Need Grabage management");
			else
			{
				head=newMalloc(k, name, size, d, a);
			}	
		}
		else
		{
			k=newMalloc(k, name, size, f, a);
		}
	}
	return head;
}
void main()
{
	struct freE *f;
	// Initialising the free list
	f=initialise(f);
	struct alloc *a;
	struct node *head;
//	head=nextfit(head, "A", 3, f, a);
//	head=firstfit(head, "B", 4, f, a);
//	head=bestfit(head, "C", 3, f, a);
//	head=del(head, "B", f, a);
}