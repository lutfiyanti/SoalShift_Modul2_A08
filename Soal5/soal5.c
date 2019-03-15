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

       while(1) {
       // main program here
       time_t waktu_sekarang;// waktu mempunyai tipe time 
       time(&waktu_sekarang);// menggunakan fungsi time untuk mengambil waktu saat ini
       struct tm *waktu; //struct tm mengandung kalender date time dimana udah terpecah

       //mengkonversi raw time di time_t biar jd kepisah pisah hari jam bulan
       waktu = localtime(&waktu_sekarang); //waktu diisi sama waktu_sekarang yang td udah diambil
       char direktorifile[100];
       char perwaktu[100];
       sprintf(perwaktu, "%d:%d:%d-%d:%d", waktu->tm_mday, waktu->tm_mon+1, waktu->tm_year+1900, waktu->tm_hour, waktu->tm_min);
       sprintf(direktorifile, "/home/lutfiy/modul2/hasil5/%s", perwaktu);
       mkdir(direktorifile, 0777); //777 biar bisa akses semua
       for(int a=1; a<30; a++){
               FILE *lama, *baru;
               lama = fopen("/var/log/syslog", "r");
               char nama_file[100];
               sprintf(nama_file, "/home/lutfiy/modul2/hasil5/%s/log%d.log", perwaktu, a);
               baru = fopen(nama_file, "w");
               //pindah seluruh isi file ke log$#.log
               char karakter;
               while(fscanf(lama, "%c", &karakter) != EOF)
               {fprintf(baru, "%c", karakter);}
               fclose(lama);
               fclose(baru);
               sleep(60);
       }
 }


 exit(EXIT_SUCCESS);
}
