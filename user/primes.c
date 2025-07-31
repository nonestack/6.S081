#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void prime_sieve(int *p2c)
{
  

  int start;
  int ret = read(p2c[0], &start, sizeof(start));

  if (ret == 0) exit(0);

  int p1[2];  // p -> c
  pipe(p1);

  if (fork() > 0) {  // parent
    close(p1[0]);
    fprintf(1, "prime %d\n", start);
    int num;
    while (read(p2c[0], &num, sizeof(num)) > 0) {
      if (num % start != 0) {
        write(p1[1], &num, sizeof(num));
      }
    }
    close(p2c[0]);
    close(p1[1]);
    wait(0);
  }
  else {  // child
    close(p1[1]);
    prime_sieve(p1);
    exit(0);
  }
  
}


int
main(int argc, char *argv[])
{
  int start = 2;
  int end = 35;

  int p1[2];  // p -> c

  pipe(p1);

  if (fork() > 0) {
    close(p1[0]);
    fprintf(1, "prime %d\n", start);
   
    for (int i = start + 1; i <= end; ++i) {
      if (i % start != 0) {
        // fprintf(1, "current %d is primes\n", i);
        write(p1[1], &i, sizeof(i));
      }
      
    }
    close(p1[1]);
    wait(0);
  }
  else {
    close(p1[1]);
    prime_sieve(p1);
    exit(0);
  }

  exit(0);
}
