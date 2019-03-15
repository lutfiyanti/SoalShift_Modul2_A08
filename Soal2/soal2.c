#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>

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

  while(1) {
    chdir("/home/reyhanzo/hatiku");
  struct stat awo;
  stat("/home/reyhanzo/hatiku/elen.ku", &awo);
  struct passwd *weh = getpwuid(awo.st_uid);
  struct group *hew = getgrgid(awo.st_gid);
  int ret;

  if(strcmp(weh->pw_name, "www-data") == 0 && strcmp(hew->gr_name, "www-data") == 0) {
      remove("/home/reyhanzo/hatiku/elen.ku");
}
    sleep(3);
  }
  
  exit(EXIT_SUCCESS);
}
