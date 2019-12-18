#include<iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;
class process
{
public:
	int pid, arrival, new_arrival_time, burst, burst_time_temp, io, cpu, tat, wait;
	process* next;
    int left_in_cpu;
};
#define NO_OF_PROCESSES 4
#define TAB "\t"
process* head = NULL;	// Initialize the head of the linked list.

// Make a priority Q and insert into linked list according to 
// the arrival time of the process.
void initialize(int i,int a,int b,int io,int cpu)
{
	process* newP = new process();
	newP->arrival = newP->new_arrival_time = a;	// new_arrival_time is a temp. variable for calculation
	newP->burst = newP->burst_time_temp = b;
	newP->pid = i;
	newP->wait = 0;	// Initilize the initial Wait of every process to 0.
	newP->io = io;
	newP->cpu = cpu;	// Store the IO freq in cpu.
	newP->next = NULL;
    newP->left_in_cpu = 0;
	process *t;
	if(head == NULL){
		head=newP;
	}else if(head->arrival > newP->arrival){
		newP->next = head;
		head = newP;
	}else{
		t=head;
		while(t->next != NULL && t->next -> arrival < newP->arrival){
			t = t->next;
		}
		newP->next=t->next;
		t->next=newP;
	}
}

void stats()
{
	cout << endl << "Process\tWT\tTAT\tPenalty Ratio" << endl;
	int wait=0,tat=0;
	process *iter = head;
	while(iter!=NULL){
		cout << iter->pid << TAB << iter->wait << TAB << iter->tat << TAB << (float)iter->tat / iter->burst_time_temp << endl;
		wait += iter->wait;
		tat += iter->tat;
		iter = iter->next;
	}
	cout << "Avg. Wait. Time : " << (float)wait/NO_OF_PROCESSES << " Avg. TurnAround : " << (float)tat / NO_OF_PROCESSES << endl;
}

int min(int a,int b)
{
	if(a<=b) return a;
	else return b;
}

void SJF(int n)
{
	process *t=head,*p=NULL,*q;
	int time_elapsed=0,time2=0;
	float throughput;
	int flag=1;
	while(flag!=0)
	{
		flag = 0;
		p = NULL;
		t=head;
		while(t!=NULL)
		{
			if(t->burst!=0)
			{
				if(t->left_in_cpu==0)
					t->left_in_cpu = min(t->cpu,t->burst);
				flag += 1;
				if(t->burst_time_temp <= time_elapsed)
				{
					if(p==NULL || (p->left_in_cpu > t->left_in_cpu || (p->left_in_cpu==t->left_in_cpu && p->new_arrival_time > t->new_arrival_time)))
					{
						p = t;
					}
				}
			}
			t=t->next;
		}
		if(p==NULL)
		{
			t=head;
			while(t!=NULL)
			{
				if(t->burst!=0)
				{
					if(p==NULL)
					{
						p=t;
					}
					else
					{
						if(p->burst_time_temp>t->burst_time_temp)
						{
							p=t;
						}
					}
				}
				t=t->next;	
			}
			time_elapsed=p->burst_time_temp;
		}
		p->wait+=time_elapsed - p->burst_time_temp;
		if(flag > 1)
		{
			t = head;
			q = NULL;
			while(t!=NULL)
			{
				if(t->burst!=0)
				{
					if(t->burst<(time_elapsed + t->left_in_cpu) && t->burst_time_temp>time_elapsed)
					{
						if(t->left_in_cpu + t->burst_time_temp < p->left_in_cpu + time_elapsed)
						{
							if(q==NULL || q->burst_time_temp > t->burst_time_temp)
							{
								q=t;
							}							
						}
					}
				}
				t=t->next;
			}			
		}
		if(q==NULL)
		{
			{
				time_elapsed += p->left_in_cpu;
				if(time2<=time_elapsed)
				{
					time2=time_elapsed + p->io;
				}
				else
				{
					p->wait += time2-time_elapsed;
					time2 += p->io;
				}				
				p->burst_time_temp=time2;
				p->burst= p->burst - p->left_in_cpu;		
			}
			p->tat=p->burst_time_temp-p->arrival;
			p->left_in_cpu=0;		
        }
		else
		{
			p->left_in_cpu = p->left_in_cpu - (q->new_arrival_time - time_elapsed);
			p->burst -= (q->new_arrival_time - time_elapsed);
			time_elapsed = q->new_arrival_time;
			p->new_arrival_time=time_elapsed;
		}
		if(p->burst==0) flag -= 1;	
	}
	printf("%d",time_elapsed);
	if(time2>time_elapsed) 
	{
		printf(" IO %d",time2);
		throughput = (float)NO_OF_PROCESSES / time2;
	}
	else	
	{
		throughput = (float)NO_OF_PROCESSES/time_elapsed;
	}
	printf("\n\nThroughput = %f",throughput);
}




int main()
{
	int i;
	process* temp;
	FILE *fp; 
	int pid[3];
	int burst[NO_OF_PROCESSES],arrival[NO_OF_PROCESSES],cpu[NO_OF_PROCESSES],io[NO_OF_PROCESSES];   // burst for CPU burst and cpu for io burst / cpu burst 
    fp = fopen("data2.txt", "r") ; 
    if ( fp == NULL ) 
    { 
        printf( "Text file failed to open." ) ; 
    }
	for(int i = 0; i < 4; i++){
		fscanf(fp, "%d %d %d %d %d", &pid[i], &arrival[i], &burst[i], &io[i], &cpu[i]);
	}
	fclose(fp); 
    for(int i = 0; i < 4; i++)
        initialize(pid[i], arrival[i], burst[i], io[i], cpu[i]);
	SJF(NO_OF_PROCESSES);
	stats();
}