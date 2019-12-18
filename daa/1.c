#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
   double price;
   double apprate;
} item;

#define INFINITY 1e256

item *genitems ( int n )
{
   item *A;
   int i;

   A = (item *)malloc(n * sizeof(item));
   for (i=0; i<n; ++i) {
      A[i].price = 10 + rand() % 190;
      A[i].apprate = 1 + (double)(1 + rand() % 1500) / (double)1000;
   }
   printf("\nInitial prices\n");
   for (i=0; i<n; ++i) {
      printf("%-8d", (int)(A[i].price));
      if (i % 10 == 9) printf("\n");
   }
   if (i % 10) printf("\n");
   printf("\nAppreciation rates\n");
   for (i=0; i<n; ++i) {
      printf("%-5.3lf   ", A[i].apprate);
      if (i % 10 == 9) printf("\n");
   }
   if (i % 10) printf("\n");
   return A;
}

double **genallrates ( item *A, int n )
{
   double **R;
   int i, j;

   R = (double **)malloc(n * sizeof(double *));
   for (i=0; i<n; ++i) {
      R[i] = (double *)malloc(n * sizeof(double));
      R[i][0] = 1; R[i][1] = A[i].apprate;
      for (j=2; j<n; ++j) R[i][j] = R[i][j-1] * A[i].apprate;
   }
   return R;
}

void printseq ( item *A, double **R, int *S, int n )
{
   int i, k;
   double cost, c;

   cost = 0; k = (n+2)/3;
   for (i=0; i<k; ++i) {
      c = A[S[i]].price * R[S[i]][i];
      printf("    [%2d %2d %14.6lf]", i, S[i], c);
      cost += c;
      if (i+k<n) {
         c = A[S[i+k]].price * R[S[i+k]][i+k];
         printf("    [%2d %2d %14.6lf]", i+k, S[i+k], c);
         cost += c;
      }
      if (i+2*k<n) {
         c = A[S[i+2*k]].price * R[S[i+2*k]][i+2*k];
         printf("    [%2d %2d %14.6lf]", i+2*k, S[i+2*k], c);
         cost += c;
      }
      printf("\n");
   }
   printf("--- Total cost = %.6lf\n", cost);
}

void esrec ( item *A, double **R, int *P, int *Q, int n, int k, double cost, double *mincost, int *ncall )
{
   double c;
   int i, t;

   ++(*ncall);

   if (k == n) {
      *mincost = cost;
      for (i=0; i<n; ++i) Q[i] = P[i];
      return;
   }
   for (i=k; i<n; ++i) {
      t = P[i]; P[i] = P[k]; P[k] = t;
      c = cost + A[P[k]].price * R[P[k]][k];
      if (c < *mincost) esrec(A,R,P,Q,n,k+1,c,mincost,ncall);
      t = P[i]; P[i] = P[k]; P[k] = t;
   }
}

int *exhsearch ( item *A, double **R, int n )
{
   double mincost;
   int i, ncall;
   int *P, *Q;

   if (n > 12) {
      fprintf(stderr, "*** n is too large, skipping exhaustive search\n");
      return NULL;
   }
   P = (int *)malloc(n * sizeof(int));
   Q = (int *)malloc(n * sizeof(int));
   for (i=0; i<n; ++i) P[i] = i;
   mincost = INFINITY; ncall = 0;
   esrec(A,R,P,Q,n,0,0,&mincost,&ncall);
   printf("    Number of recursive calls = %d\n", ncall);
   free(P);
   return Q;
}

int *grdsearch1 ( item *A, double **R, int n )
{
   int *S, *bought, i, j, k;
   double cost, maxcost;

   S = (int *)malloc(n * sizeof(int));
   bought = (int *)malloc(n * sizeof(int));
   for (i=0; i<n; ++i) bought[i] = 0;
   for (i=0; i<n; ++i) {
      maxcost = 0; k = -1;
      for (j=0; j<n; ++j) {
         if (!bought[j]) {
            cost = A[j].price * R[j][i];
            if (cost > maxcost) { maxcost = cost; k = j; }
         }
      }
      S[i] = k; bought[k] = 1;
   }
   free(bought);
   return S;
}

int *grdsearch2 ( item *A, double **R, int n )
{
   int *S, *bought, i, j, k;
   double cost, mincost;

   S = (int *)malloc(n * sizeof(int));
   bought = (int *)malloc(n * sizeof(int));
   for (i=0; i<n; ++i) bought[i] = 0;
   for (i=n-1; i>=0; --i) {
      mincost = INFINITY; k = -1;
      for (j=0; j<n; ++j) {
         if (!bought[j]) {
            cost = A[j].price * R[j][i];
            if (cost < mincost) { mincost = cost; k = j; }
         }
      }
      S[i] = k; bought[k] = 1;
   }
   free(bought);
   return S;
}

int *grdsearch3 ( item *A, double **R, int n )
{
   int *S, *bought, i, j, k;
   double incr, maxincr;

   S = (int *)malloc(n * sizeof(int));
   bought = (int *)malloc(n * sizeof(int));
   for (i=0; i<n; ++i) bought[i] = 0;
   for (i=0; i<n; ++i) {
      k = -1;
      if (i == n-1) {
         for (j=0; j<n; ++j) if (!bought[j]) k = j;
      } else {
         maxincr = 0;
         for (j=0; j<n; ++j) {
            if (!bought[j]) {
               incr = A[j].price * (R[j][i+1] - R[j][i]);
               if (incr > maxincr) { maxincr = incr; k = j; }
            }
         }
      }
      S[i] = k; bought[k] = 1;
   }
   free(bought);
   return S;
}

/* This implements the minimum price increase last heuristic */
int *grdsearch4 ( item *A, double **R, int n )
{
   int *S, *bought, i, j, k;
   double incr, minincr;

   S = (int *)malloc(n * sizeof(int));
   bought = (int *)malloc(n * sizeof(int));
   for (i=0; i<n; ++i) bought[i] = 0;
   for (i=n-1; i>=0; --i) {
      k = -1;
      if (i == 0) {
         for (j=0; j<n; ++j) if (!bought[j]) k = j;
      } else {
         minincr = INFINITY;
         for (j=0; j<n; ++j) {
            if (!bought[j]) {
               incr = A[j].price * (R[j][i] - R[j][i-1]);
               if (incr < minincr) { minincr = incr; k = j; }
            }
         }
      }
      S[i] = k; bought[k] = 1;
   }
   free(bought);
   return S;
}

int main ( int argc, char *argv[] )
{
   item *A;
   double **R;
   int n, *S;

   if (argc > 1) n = atoi(argv[1]); else scanf("%d", &n);
   printf("n = %d\n", n);
   srand((unsigned int)time(NULL));

   A = genitems(n);
   R = genallrates(A,n);
   
   printf("\n+++ Greedy search 1\n"); S = grdsearch1(A,R,n); printseq(A,R,S,n); free(S);
   printf("\n+++ Greedy search 2\n"); S = grdsearch2(A,R,n); printseq(A,R,S,n); free(S);
   printf("\n+++ Greedy search 3\n"); S = grdsearch3(A,R,n); printseq(A,R,S,n); free(S);
   printf("\n+++ Greedy search 4\n"); S = grdsearch4(A,R,n); printseq(A,R,S,n); free(S);

   printf("\n+++ Exhaustive search\n"); S = exhsearch(A,R,n);
   if (S) { printseq(A,R,S,n); free(S); }

   exit(0);
}