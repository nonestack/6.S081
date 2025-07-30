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

  if (fork() > 0) {
    close(p1[0]);
    int num;
    while (read(p2c[0], &num, sizeof(num)) > 0) {
      if (num % start != 0) {
        write(p1[1], &num, sizeof(num));
      }
    }
  }
  
  close(read_pipe[1]);
  close(write_pipe[0]);
  int start;
  read(read_pipe[0], &start, sizeof(start));
  fprintf(1, "prime %d\n", start);
  int num;
  while (read(read_pipe[0], &num, sizeof(num)) > 0) {
    if (num % start != 0) {
      write(write_pipe[1], &num, sizeof(num));
    }
  }
  close(read_pipe[0]);
  close(write_pipe[1]);
  exit(0);
}


int
main(int argc, char *argv[])
{
  int start = 2;
  int end = 35;

  int p1[2];  // p -> c

  pipe(p1);
  pipe(p2);

  if (fork() > 0) {
    close(p1[0]);

    int num = start + 1;

    for (int i = start + 1; i <= end; ++i) {
      if (i % start != 0) write(p[0], &i, sizeof(i));
      
    }
    close(p1[1]);
    wait(0);
  }
  else {
    
  }

  exit(0);
}
