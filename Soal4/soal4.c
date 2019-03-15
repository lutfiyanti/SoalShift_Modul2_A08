#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>

int main() {
  pid_t pid, sid;

  pid = fork();

  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();

  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  if ((chdir("/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  int i = 1;
  while(1) {
    	struct stat att;
    	stat("/home/reyhanzo/modul2/makanan/makan_enak.txt", &att);
	time_t access = att.st_atime;	
	time_t now = time(NULL);
	double det = difftime(now, access);
	char number[10000];
	sprintf(number,"%d", i);
	char namefile[]="/home/reyhanzo/modul2/makanan/makan_sehat";

	if(det<=30)
	{
		FILE* makan;
		strcat(namefile, number);
      		strcat(namefile,".txt"); 
		makan = fopen(namefile, "w+"); 
      		fclose(makan);
      		i++;
	}
    sleep(5);
  }
  exit(EXIT_SUCCESS);
}
