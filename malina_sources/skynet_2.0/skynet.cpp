#include <stdio.h>
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string>
#include "types.h"


int wirelessHandler(void);

extern volatile unsigned char loopLocker;
void log2file(const char *record);
void sigint_handler(int sig)
{
    loopLocker = 0;
}


int main(int argc, char **argv)
{
  pid_t pid;
  //int rv;
  FILE *mf;
  unsigned int skynetPID;
  switch(argc)
  {
    case 1:
      printf("no command - no action\n");
      printf("commands:\n");
      printf("'start' - start skynet \n");
      printf("'stop'  - stop skynet \n");
    break;
    case 2:
      if(strcmp(argv[1],"start")==0)
      {
        log2file(std::string("check if PID storage exist").c_str());
        mf = fopen("/home/pi/skynet_2.0/skynet_pid","r");
        if(mf)
        {
          fclose(mf);
          printf("skynet is already running and will kill you!\n");
          log2file(std::string("skynet is already running and will kill you!").c_str());
        }
        else
        {        
          log2file(std::string("executing fork()").c_str());
          switch(pid = fork()) 
          {
            case -1:
              perror("fork");  
              exit(1);         
            break;
            case 0:
              struct sigaction sa;
              sa.sa_handler = sigint_handler;
              sa.sa_flags = SA_RESTART; // or SA_RESTART
              sigemptyset(&sa.sa_mask);
              if (sigaction(SIGUSR1, &sa, NULL) == -1) {
                  perror("sigaction");
                  exit(1);
              }    
              log2file(std::string("creating PID storage").c_str());
              mf = fopen("/home/pi/skynet_2.0/skynet_pid","w");
              fprintf(mf,"%d",getpid());
              fclose(mf);
              log2file(std::string("start wireless handler").c_str());
              wirelessHandler();
              log2file(std::string("removing PID storage").c_str());
              remove("/home/pi/skynet_2.0/skynet_pid");
              printf("Skynet is dead!\n");  
              
              exit(0);
            default:
                printf("Skynet Daemon is running!\n");          
          }
        }
      }
      else if(strcmp(argv[1],"stop")==0)
      {
        mf = fopen("/home/pi/skynet_2.0/skynet_pid","r");
        if(mf)
        {
          fscanf(mf,"%d",&skynetPID);
          fclose(mf);
          printf("skynet pid:%d\n",skynetPID); 
          kill(skynetPID, SIGUSR1);
          printf("skynet is stoped!\n");          
        }
        else
        {
          printf("skynet is not running!\n");
        }
      }
      else if(strcmp(argv[1],"clean")==0)
      {
        printf("cleaning\n");
        remove("/home/pi/skynet_2.0/skynet_pid");
        remove("/home/pi/skynet_2.0/log.txt");
      }
      else if(strcmp(argv[1],"help")==0)
      {
        printf("commands:\n");
        printf("'start' - start skynet \n");
        printf("'stop'  - stop skynet \n");
        printf("'clean'  - delete skynet_pid and log.txt \n");
      }      
      
    break;
  }
   
    return 0;
}