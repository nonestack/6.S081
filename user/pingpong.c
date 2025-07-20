#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int p[2];

  pipe(p);
  char b = 12;


  if (fork() > 0) { // parent process
    int ret = write(p[1], (void *)&b, 1);
    fprintf(1, "parent write ret = %d\n", ret);
    if (ret != 1) {
      fprintf(2, "parent process write error\n");
    }
    ret = read(p[0], &b, 1);
    fprintf(1, "parent read ret = %d\n", ret);
    if (ret != 1) {
      fprintf(2, "parent process read error\n");
    }
    fprintf(1, "%d:received pong\n", getpid());
    wait(0);
  }
  else { // child process
    int ret = read(p[0], &b, 1);
    fprintf(1, "child read ret = %d\n", ret);
    if (ret != 1) {
      fprintf(2, "child process read error\n");
    }

    fprintf(1, "%d:received ping\n", getpid());

    ret = write(p[1], (void *)&b, 1);
    fprintf(1, "child write ret = %d\n", ret);
    if (ret != 1) {
      fprintf(2, "child process write error\n");
    }
    exit(0);
  }
  exit(0);
}
