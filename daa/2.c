#include<stdio.h>
#include<stdlib.h>
struct node
{
    char str[100];
    struct node *next;
};
struct node *norepsubseq(struct node *head, char *a, int n)
{
    int i=0,j=0;
    char temp=a[0];
    struct node *t;
    while(i<n)
    {
        if(i==0)
        {
            head=(struct node *)malloc(sizeof(struct node));
            head->str[0]=a[0];
            head->next=NULL;
            t=head;
            j++;
        }
        else
        {
            if(temp!=a[i])
            {
                t->next=(struct node *)malloc(sizeof(struct node));
                t=t->next;
                t->str[0]=a[i];
                t->next=NULL;
                temp=a[i];
                j++;
            }
        }
        i++;
    }
    return head;
}
int size(struct node *head)
{
    int a=0;
    while(head)
    {
        a++;
        head=head->next;
    }
    return a;
}
void print(struct node *head)
{
    while(head)
    {
        printf("%s",head->str);
        head=head->next;
    }
    printf("\n");
}
int checkpal(struct node *a, int z)
{
    struct node *b=a;
    struct node *c=a;
    struct node *d=a;
    int i=0;
    while(z!=0)
    {
        c=a;
        int o=z;
        while(o!=0)
        {
            c=c->next;
        }
        if(c->str[0]!=b->str[0])
            return 0;
        b=b->next;
        z--;
    }
    return 1;
}
struct node *paldecomp(struct node *head, int a)
{
    struct node *h;
    struct node *o;
    struct node *w;
    int i=1,s=0,p=0,u,z;
    struct node *t=head;
    while(t)
    {
        w=head;
        p=0;
        z=a-s;
        while(1)
        {
            while(z!=0)
            {
                i=checkpal(t, z);
                if(p==1)
                    break;
                z--;
            }
            if(h==NULL)
            {
                u=z;
                h=(struct node *)malloc(sizeof(struct node));
                while(u!=0)
                {
                    h->str[z-u]=t->str[0];
                    t=t->next;
                }
                h->next=NULL;
                o=h;
            }
            else
            {
                u=z;
                o->next=(struct node *)malloc(sizeof(struct node));
                o=o->next;
                while(u!=0)
                {
                    o->str[z-u]=t->str[0];
                    s++;
                    t=t->next;
                }
                o->next=NULL;
            }
        }
        i++;
    }
    printf("Part II: %d substrings: ",i);
    struct node *r=h;
    while(r)
    {
        printf("%s ",r->str);
        r=r->next;
    }
    return h;
}
void main()
{
    int n;
    printf("Enter the size of the string: ");
    scanf("%d",&n);
    char a[n];
    printf("Enter the string: ");
    scanf("%s",a);
    struct node *head;
    head=norepsubseq(head, a, n);
    int o=size(head);
    struct node *h=paldecomp(head, a);
    printf("n = %d\n",n);
    printf("S = %s\n",a);
    printf("Part I: ");
    print(head);
}