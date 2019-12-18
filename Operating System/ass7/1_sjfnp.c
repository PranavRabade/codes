#include<stdlib.h>
#include<stdio.h>
struct order
{
    char a[3];
    int arrival, burstt, speed;
};
struct order** readF()
{
    struct order** p = (struct order**)malloc(sizeof(struct order*)*3);
    for(int i = 0; i < 3; i++)
        p[i] = NULL;
    FILE* f = fopen("input.txt", "r");
    for(int i = 0; i < 3; i++)
    {
        p[i] = (struct order*)malloc(sizeof(struct order));
        fscanf(f, "%s %d %d", p[i]->a, &p[i]->arrival, &p[i]->burstt);
        p[i]->speed = 0;
    }
    fclose(f);
    return p;
}
struct order* next(struct order** p,  int timer)
{
    struct order* minProc = p[0];
    for(int i = 0; i < 3; i++){
        if(!p[i]->speed && p[i]->burstt < minProc->burstt && p[i]->arrival < timer){
            minProc = p[i];
        }
    }
    return minProc;
}
void sjf(struct order** p, int timer)
{
    struct order* current = p[0];
    int waittime[3]={0},arr[3]={0};
    for(int i = 0; i < 3; i++)
    {
        if(i == 0)
        {
            timer += current->burstt;
            waittime[i] = 0;
            arr[0] = current->burstt; 
            continue;
        }
        current = next(p,timer);
        int number;
        for(int i = 0; i < 3; i++)
            if(p[i] == current)
                number = i;
        waittime[number] = timer;
        timer += current->burstt;
        arr[number] = (timer - current->arrival);
        current->speed = timer;
    }
   for(int i = 0; i < 3; i++)
   {
        float ratio = (arr[i] / p[i]->burstt);
        printf("%s waittime = %d TurnAround  = %d Completion = %d Penalty Ratio = %f\n", p[i]->a, waittime[i], arr[i], p[i]->speed, ratio);
    }
    // The system throughput can be found by finding the max of the completion
    // time and then dividing the number of orderes by the found maximum
    return;
}
int myComp(const void* a, const void* b)
{
    struct order* a1 = (struct order*) a;
    struct order* a2 = (struct order*) b;
    return a1->arrival < a2->arrival;
}  
int main()
{
    struct order** p = readF();
    int timer = 0;
    qsort(p, 3, sizeof(p[0]), myComp);
    timer = p[0]->arrival; // Because the time elapsed till the first order arrivalives is wasted.
    sjf(p, timer);
    return(0); 
}