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
  
  Penjelasan 

  sid = setsid();

  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  if ((
  
  ("/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);


  while(1) {
  DIR *direktori; //Tipe dakta direktori yg bernama direktori
  struct dirent *file_lama; //membuat struct dirent yang menunjuk isi dari direkktori
  chdir("/home/lutfiy/"); 
  while((file_lama=readdir(opendir("Documents"))) != NULL){

      if(strstr(file_lama->d_name,".png")!=NULL){

        int panjang_namafile = strlen(file_lama->d_name) -4;

        char file_baru[2000], lama[1000];// file_baru menampung nama string, tambahan untuk menampung grey, lama 

        memset(file_baru, '\0', sizeof(file_baru));
        memset(lama, '\0', sizeof(file_baru)); 

        strcpy(lama, "/home/lutfiy/Documents/");// destination,source
        strcat(lama, file_lama->d_name);
        strcpy(file_baru, "/home/lutfiy/modul2/gambar/");
        strncat(file_baru, file_lama->d_name, panjang_namafile);
        strcat(file_baru, "_grey.png");

      //wait, fork, exec
        pid_t child_id;
        int status;
        child_id = fork();

        if (child_id == 0) {
          char *argv[4] = {"mv", lama, file_baru, NULL};
          execv("/bin/mv", argv);
        }
        else{
          while ((wait(&status)) > 0);
        }
      }
  }
  closedir(direktori);
    sleep(1);
  }
  exit(EXIT_SUCCESS);
}
