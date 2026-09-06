#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <poll.h>

int main(){
  char name[255];
  int counter = 0;
  struct pollfd mypoll[3];

  memset(&mypoll, 0, sizeof(mypoll));
  mypoll[0].fd = 0;
  mypoll[0].events = POLLIN;


  printf("Enter your name:\n");

  while (1)
  {
    if (poll(&mypoll[0], 1, 100) == 1)
    {
      read(0, name, sizeof(name));
      printf("Hello: %s", name);
      break;
    }
    else {
      counter++;
    }
  }

  printf("It took you %d ms to type your name\n", counter * 100);
  return 0;
}
