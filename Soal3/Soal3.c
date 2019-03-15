#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>

int main() {
        pid_t pid1, pid2, pid3;
        int pipe1[2], pipe2[2];
        int p1;
        pipe(pipe1);
        pipe(pipe2);
        char *unzip[] = {"unzip", "/home/ltfiy/modul2/soal3/campur2.zip", NULL};
        char *ls[] = {"ls", "/home/lutfiy/modul2/campur2", NULL};
        char *grep[] = {"grep", ".txt$", NULL};
        // Process1
        pid1 = fork();

        if (pid1 < 0) exit(EXIT_FAILURE);

        if (pid1 == 0) 
                execvp("unzip", unzip);
        } else {
                int p2;
                while(wait(&p1) > 0); //wait until Process1 end

                // Process2
                pid2 = fork();

                if (pid2 < 0) exit(EXIT_FAILURE);

                if(pid2 == 0){
                        dup2(pipe1[1], STDOUT_FILENO); // connect pipeEnds1 Write to STDOUT Process2
                        close(pipe1[1]); // close pipeEnds1 Write that connected to File Table 4
                        close(pipe1[0]); // close pipeEnds1 Read that connected to File Table  4
                        execvp("ls", ls);
                }
                else{
                        while(wait(p2) > 0); //wait until Process2 end

                        // Process3
                        child_id3 = fork();

                        if (child_id3 < 0) exit(EXIT_FAILURE);

                        if(child_id3 == 0){
                                execvp("grep", grep);
                        }
                        else{

                        }
                }
        }
        return 0;
}
