#include<stdio.h>
#include<stdlib.h>
void fcfs(int a[3][2])
{
	int order[3]={a[0][0],a[1][0],a[2][0]},temp;
	for(int i=0;i<3;i++)
    {
        for(int j=0;j<(3-i-1);j++)
        {
            if(order[j]>order[j+1])
            {
                temp=order[j];
                order[j]=order[j+1];
                order[j+1]=temp;
            }
        }
    }
	printf("Order of processes will be:\n");
	for(int k=0;k<3;k++)
	{
		printf("%d-",order[k]);
	}
}
void main()
{
	FILE *r;
	char c[10];
	int a[3][2]={0}, ar=0,ac=0;
	r=fopen("data.txt","r");
	int i=0;
	while(fgets(c,10,r)!=NULL)
	{
		a[i][0]=(int)c[3]-48;
		a[i][1]=((int)c[5]-48)*10+((int)c[6]-48);
		i++;
	}
	fclose(r);
	fcfs(a);
}
