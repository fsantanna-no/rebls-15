// Taken directly from Knuth TAoCP v4 7.2.1.1
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
  // Algorithm L (Loopless Gray binary generation).
  // This algorithm, like Algorithm G, visits all binary n-tuples
  // (a[n-1], ..., a[0]) in the order of the Gary binary code.
  // But instead of maintaining a parity bit,
  // it uses an array of "focus pointers",
  // (f[n], ..., f[0]), whose significance is discussed below.
  int n;
  int* a;
  int* f;
  int j;

  assert(argc == 2);
  n = atoi(argv[1]);
  a = (int*)calloc(n, sizeof(int));
  f = (int*)calloc(n+1, sizeof(int));
 Initialize:
  for (j = 0; j < n; j += 1) {
    a[j] = 0;
    f[j] = j;
  }
  f[n] = n;
 Visit:
  printf("(");
  for (j = n-1; j >= 0; j -= 1) {
    printf("%d", a[j]);
    if (j-1 >= 0) {
      printf(", ");
    }
  }
  printf(")\n");
 Choose:
  j = f[0];
  f[0] = 0;
  if (j == n) {
    return 0;
  }
  f[j] = f[j+1];
  f[j+1] = j+1;
 Complement:
  a[j] = 1 - a[j];
  goto Visit;
}

  

  
  
