
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char* argv[]){

  printf("hello world (pid:%d)\n", (int)getpid());
  fflush(stdout);
  int rc = fork();
  printf("Value of the rc %d \n", rc);
  if (rc < 0) {
    // fork failed
    fprintf(stderr, "fork failed\n");
    exit(1);
  }
  else if (rc == 0){
       fflush(stdout);
       printf("hello, I am child (pid:%d)\n", (int)getpid());
       char * myargs[4];
       myargs[0] = strdup("wc");   // program: "wc" (word count)
              myargs[1] = strdup("-l");
       myargs[2] = strdup("p3.c"); // argument: file to count
       myargs[3] = NULL;           // marks end of array
       execvp(myargs[0], myargs);  // runs word count
       printf("this shouldn't print out");
  }
  else{
    // parent goes down this path (main)
    int wc = wait(NULL);
    printf("hello, I am parent of %d (rc_wait:%d) (pid:%d)\n", rc, wc, (int)getpid());
  }
  return 0;
  
}
