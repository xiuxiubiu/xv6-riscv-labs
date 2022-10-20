
// primes.c: prime sieve using pipes

#include "../kernel/types.h"
#include "user.h"

int main() {

  int fds[2];
  if (pipe(fds) < 0) {
    printf("create pipe error");
    exit(1);
  }

  for (int n = 2; n <= 35; n++) {
    int i;
    for (i = 2; i <= n / 2; i++)
      if (n % i == 0)
        break;
    if (i == n / 2 + 1) {

      write(fds[1], &n, 4);

      int pid = fork();
      if (pid == 0) {

        int prime;
        read(fds[0], &prime, 4);
        printf("prime %d\n", prime);

        exit(0);
      } else {
        wait((int *)0);
      }
    }
  }

  exit(0);
}
