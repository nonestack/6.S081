#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int p1[2];  // p -> c
  int p2[2];  // c -> p

  pipe(p1);
  pipe(p2);



  if (fork() > 0) { // parent process
    char b = 12;
    close(p1[0]);
    close(p2[1]);
    
    write(p1[1], "h", 1);
    
    read(p2[0], &b, 1);
    fprintf(1, "%d: received pong\n", getpid());
    
    wait(0);
  }
  else { // child process
    char b = 12;
    close(p1[1]);
    close(p2[0]);
    
    read(p1[0], &b, 1);
    fprintf(1, "%d: received ping\n", getpid());

    write(p2[1], "w", 1);

    exit(0);
  }
  exit(0);
}
