#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/dir.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>


int main(){

        int total_length = 0;
        char line[total_length];
        FILE * command = popen("pidof soal5", "r");

        fgets(line, total_length, command);

        pid_t pid = strtoul(line,NULL,10);
        kill (pid,SIGKILL);
        pclose(command);
}
