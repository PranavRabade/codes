#include<stdio.h>
#include<stdlib.h>
void flip(int a[], int n)
{
	int temp=a[0],i; 
	for(i=0;i<n-1;i++)
		a[i]=a[i+1];
	a[i]=temp;
}
int search(int a[],int n,int x)
{
	int f=0,k=n,l=n-1;
	int m=((n/2)+l)/2;
	if(a[0]>x)
	{
		while(a[m]!=x && k)
		{	
			if(a[m]>x)
			{
				l=m-1;
				m=(f+l)/2;
			}
			else
			{
				f=m+1;
				m=(f+l)/2;
			}
			k--;
		}
	}
	m=(f+l)/2;
	while(a[m]!=x && k)
	{
		if(a[m]>x)
		{
			l=m-1;
			m=(f+l)/2;
		}
		else
		{
			f=m+1;
			m=(f+l)/2;
		}
		k--;
	}
	return m;
}
void main()
{
	int a[1000],size,i,j,k,temp;
	printf("Enter the size of array: ");
	scanf("%d",&size);
	printf("\n");
	for(i=0;i<size;i++)
	{
		if(i==0)
			a[0]=rand()%10;
		else
		{
			if(rand()%2==0)
				a[i]=a[i-1];
			else
			{
				j=rand()%3;
				if(j==0)
					a[i]=a[i-1]+1;
				if(j==1)
					a[i]=a[i-1]+2;
				if(j==2)
					a[i]=a[i-1]+3;
			}
		}
	}
	i=0;
	while(i<size)
	{
		printf("%d-",a[i]);
		i++;
	}
	printf("\n");
	i=0;
	while(i<(rand()%100))
	{
		flip(a,size);
		i++;
	}
	i=0;
	while(i<size)
	{
		printf("%d-",a[i]);
		i++;
	}
	printf("\nEnter the number to be searched: ");
	scanf("%d",&i);
	j=search(a,size,i);
	printf("The element is at: %d\n",j);
}
