#include <iostream>
#include <string>
#include <fstream>
#include<stdlib.h>
using namespace std;
#define SIZE 3
#define TIME_QUANTUM 5
struct proc
{
    string name;
    float arrtime;
    float burst;
}process[SIZE];
void roundRobin(proc* process) 
{
	int arrtime[SIZE],comptime[SIZE]={0},turnAround[SIZE], response[SIZE]={0}, WT[SIZE],left[SIZE];
	// This loop is the first to check whether there is any such process that gets
	// over in the first iteration itself, and if there is, add it to the response time.s
	int sum_rt = 0,sum_wait = 0,sum_tat = 0;
	for(int i = 0;i < SIZE; i++)
	{
		left[i] = process[i].burst;
		for(int j = i + 1;j < SIZE; j++)
		{
			if(left[i] < TIME_QUANTUM)
				response[j] += left[i];
			else
				response[j] += TIME_QUANTUM;
		}
	}
	for(int i=0;i<SIZE;i++)
		sum_rt+=response[i];
	// This is the step for Round Robin - ing
	while(true)
	{
		int is_all_over = 0;
		for(int i = 0; i < SIZE; i++)
		{
			is_all_over += left[i];
			for(int j = 0;j < SIZE; j++)
			{
				if(left[j] != 0)
				{  // if process not yet completed then add to its comptime
					if(left[i] < TIME_QUANTUM)
						comptime[j] += left[i];
					else
						comptime[j] += TIME_QUANTUM;
				}
			}   
			if(left[i] <= TIME_QUANTUM)
				left[i]=0;
			else
				left[i] -= TIME_QUANTUM;
		}
		if(!is_all_over) // Break out of the loop if is_all_over == 0
			break;
	}
	for(int i=0;i<SIZE;i++)
	{
		turnAround[i] = comptime[i] - process[i].arrtime;
		sum_tat+=turnAround[i];
		WT[i]=turnAround[i]-process[i].burst;
		sum_wait+=WT[i];
	}
	cout<<"\nRound Robin\n";
	cout<<"Process\tArr\tburst\tComp\tTAround\tWait\tResponse\n";
	for(int i=0;i<SIZE;i++)
		cout<<process[i].name<<"\t"<<process[i].arrtime<<"\t"<<process[i].burst<<"\t"<<comptime[i]<<"\t"<<turnAround[i]<<"\t"<<WT[i]<<"\t"<<response[i]<<endl;
    cout << "Penalty ratio per process = " << endl;
    for(int i = 0; i < SIZE; i++)
        cout << (float)turnAround[i] / process[i].burst << endl;
}
void pre_emptive_SJF(struct proc process[])
{
	int arrtime[SIZE], comptime[SIZE], turnAround[SIZE], RT[SIZE], WT[SIZE], lefttime[SIZE];
  	int minarrtime = process[0].arrtime;
	for(int i=0;i<SIZE;i++)
	{
		// Initialize computation time, remaining time and RT.
		comptime[i] = 0;
		RT[i] = 0;
		lefttime[i] = process[i].burst;
		if(process[i].arrtime < minarrtime) // Find minimum arrival time.
			minarrtime = process[i].arrtime;
	}
	int time = minarrtime;int sum_rt=0;
	while(true){
		int is_all_over = 0;
		for(int i=0;i<SIZE;i++)
		{
			is_all_over += lefttime[i];
			if(lefttime[i]!=0 && time >= process[i].arrtime)
			{
				if(lefttime[i] == process[i].burst)
				{
					RT[i]=time-process[i].arrtime;
					sum_rt+=RT[i];
				}
				time += 1;
				lefttime[i] -= 1;
				if(lefttime[i] == 0)
				comptime[i] = time;
				break;
			}
		}
		if(is_all_over == 0) //terminating condition
			break;
	}
	int sum_tat = 0,sum_wt = 0;
	for(int i = 0;i < SIZE; i++){
		turnAround[i] = comptime[i] - process[i].arrtime;
		sum_tat += turnAround[i];
		WT[i] = turnAround[i] - process[i].burst;
		sum_wt += WT[i];
	}
    cout << "\nPre - Emptive SJF\n";
	cout<<"Process\tArr\tburst\tComp\tTAround\tWait\tResponse\n";
	for(int i = 0;i < SIZE; i++){
		cout<<process[i].name<<"\t"<<process[i].arrtime<<"\t"<<process[i].burst<<"\t"<<comptime[i]<<"\t"<<turnAround[i]<<"\t"<<WT[i]<<"\t"<<RT[i]<<endl;
	}
    cout << "Penalty Ratio per process : " << endl;
    for(int i = 0; i < SIZE; i++)
        cout << process[i].name << " " <<(float)turnAround[i] / process[i].burst << endl;
}
int main(){
    int i;
    ifstream in("input.txt");
    if (!in){
        cerr << "File can't be opened! " << endl;
        exit(1);
    }
    for (int i=0; i < SIZE; i++){
        in >> process[i].name >> process[i].arrtime >>process[i].burst ;
    }
	roundRobin(process);
	pre_emptive_SJF(process);
    return 0;
}