#include<iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;
class process{
public:
	int pid, arrival, new_arrival_time, burst, burst_time_temp, io, cpu, tat, wait;
	process* next;
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
void FCFS(int n)
{
	process *t=head,*iterator=NULL;
	int elapsed_time = 0,time2 = 0;
	int flag = 1;
	while(flag != 0)
	{
		flag = 0;
		iterator=NULL;
		t = head;
		while(t!=NULL)
		{     // Iterate through the whole Queue.
			if(t->burst != 0)
			{
				flag += 1;
                if(iterator == NULL || iterator->new_arrival_time > t->new_arrival_time)
                    iterator = t;
			}
			t=t->next;
		}
		if(iterator->new_arrival_time > elapsed_time)
		{	// This is the time elapsed.
			elapsed_time = iterator->new_arrival_time;
		}
		iterator->wait += elapsed_time - iterator->new_arrival_time;
		if(iterator->burst >= iterator->cpu){	// If the CPU burst > IO per CPU 
			elapsed_time += iterator->cpu;				// then increment the elapsed time by IO per CPU
			if(time2 <= elapsed_time){
				time2 = elapsed_time + iterator->io;
				iterator->new_arrival_time = time2;
			}else{
				iterator->wait += time2-elapsed_time;
				time2+=iterator->io;
				iterator->new_arrival_time=time2;
			}
			iterator->burst -= iterator->cpu;		
		}else{
			elapsed_time+=iterator->burst;
			iterator->burst = 0;
			iterator->new_arrival_time=elapsed_time;
		}
		if(iterator->burst == 0) 
            flag-=1;	
		iterator->tat = iterator->new_arrival_time - iterator->arrival;
	}
	cout << "Total Computational Time : " << elapsed_time << endl;
	/* printf("Total Computational Time : %d",elapsed_time); */
	float throughput = (float)n/elapsed_time;
	printf("\nThroughput = %f",throughput);
}

void stats(int n)
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
	cout << "Avg. Wait. Time : " << (float)wait/n << " Avg. TurnAround : " << (float)tat / n << endl;
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
	FCFS(NO_OF_PROCESSES);
	stats(NO_OF_PROCESSES);
}