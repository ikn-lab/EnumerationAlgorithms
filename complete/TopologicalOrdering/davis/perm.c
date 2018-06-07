/* Tutorial on Reverse Search */
/* Section 4: C Implementation for Permutations */

#include <stdio.h>
#define TRUE 1
#define FALSE 0

typedef int perm[100];

int n;				/* global variable for size of permutation */

void output (perm v)
{
  int i;
  return;
  for (i = 1; i <= n; i++)
    printf (" %d", v[i]);
  printf ("\n");
}

void copy (perm w, perm v)
{
  int i;

  for (i = 1; i <= n; i++)
    w[i] = v[i];
}

int equal (perm w, perm v)
{
  int i;
  for (i = 1; i <= n; i++)
    if (w[i] != v[i])
      return FALSE;
  return TRUE;
}

int root (perm v)
{
  int i;
  for (i = 1; i <= n; i++)
    if (v[i] != i)
      return FALSE;
  return TRUE;
}

void swap (perm v, int j)
{
  int t;
  t = v[j];
  v[j] = v[j + 1];
  v[j + 1] = t;
}

void Adj (perm v, int j)	/* adjacency oracle */
{
  swap (v, j);
}

void f (perm v)			/* local search function */
{
  int i=1;
  while ( i < n && v[i] <= v[i + 1] ) i++;
  if (i < n)
    swap (v, i);
}

int reverse (perm v, int j)
{
  perm w;
  copy (w, v);
  Adj (w, j);
  f (w);
  return equal (v, w);
}

int backtrack (perm v)
{
  perm child;
  int j = 0;
  int found = FALSE;
  copy (child, v);
  f (v);			/* v is parent of child */
  do{
      j++;
      Adj (v, j);               /* v replaced by jth child */
      found = equal (child, v);
      swap (v, j);		/* restore v */
     }  while (!found);
  return j;
}

int reversesearch (perm v, int maxdeg)
{
  int j=0, count=1;
  output (v);
  while ( j <= maxdeg )
    {
      do j++;
          while (j <= maxdeg && !reverse (v, j));
      if (j <= maxdeg)
        {
          Adj (v, j);
          output (v); count++;
          j = 0;
        }
      else if(! root(v))
          j = backtrack (v);
    }
  return count;
}

int main ()				/* simple reverse search for permutations */
{
  int v[100];
  int i, count;

  scanf ("%d", &n);

  for (i = 1; i <= n; i++)
    v[i] = i;

  count = reversesearch (v, n - 1);
  printf ("\nnumber of permutations=%d\n", count);
  return 0;
}
