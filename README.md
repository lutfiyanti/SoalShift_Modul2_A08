
# Soal 1

Elen mempunyai pekerjaan pada studio sebagai fotografer. Suatu hari ada seorang klien yang bernama Kusuma yang meminta untuk mengubah nama file yang memiliki ekstensi .png menjadi “[namafile]_grey.png”. Karena jumlah file yang diberikan Kusuma tidak manusiawi, maka Elen meminta bantuan kalian untuk membuat suatu program C yang dapat mengubah nama secara otomatis dan diletakkan pada direktori /home/[user]/modul2/gambar.
Catatan : Tidak boleh menggunakan crontab.

```
Nomor 1
  GNU nano 2.5.3                                                                                      File: soal1.c                                                                                                                                                                                   

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

```

### Penjelasan :
- Pada soal diminta untuk memindah file .png pada suatu folder ke home/(user)/modul2/gambar. Disini saya menggunakan folder `Documents`.        Code dibawah ini berisi deklarasi `direktori` sebagai sebuah direktori. Deklarasi `struct dirent = file_lama` yang digunakan untuk  menunjuk file dalam direktori. `chdir ("/home/lutfiy/")` mengubah file direktori saat ini ke `/home/lutfiy`.

- ` while((file_lama=readdir(opendir("Documents"))) != NULL)` untuk mengecek apakah dalam direktori document ada isinya atau tidak.

- `int panjang_namafile = strlen(file_lama->d_name) -4;` memasukan panjang nama file yang akan dipindah ke `panjang_namafile` dikurangi  4 karena tidak mengambil .png (jumlahnya 4).

- `strcpy(lama, "/home/lutfiy/Documents/")` memasukan string direktori asal ke variabel `nama`.

- `strcat(lama, file_lama->d_name);` menggabungkan `lama` dengan isi dari `file_lama->d_name' 

- `strcpy(file_baru, "/home/lutfiy/modul2/gambar/");` memasukan string direktori yang dituju ke file_baru.

- `strncat(file_baru, file_lama->d_name, panjang_namafile);`menggabungkan `file_baru` dengan `file_lama->d_name` dengan maksimum panjang   string sepanjang `panjang_namafile`.

- strcat(file_baru, "_grey.png"); menggabungkan _grey.png ke `file_baru`

- `char *argv[4] = {"mv", lama, file_baru, NULL};` 
   `execv("/bin/mv", argv);`
   memindahkan file dari variabel lama ke file_baru. 
   
   
   
 # Soal 5
 
Kerjakan poin a dan b di bawah:
Buatlah program c untuk mencatat log setiap menit dari file log pada syslog ke /home/[user]/log/[dd:MM:yyyy-hh:mm]/log#.log
Ket:
Per 30 menit membuat folder /[dd:MM:yyyy-hh:mm]
Per menit memasukkan log#.log ke dalam folder tersebut
‘#’ : increment per menit. Mulai dari 1
Buatlah program c untuk menghentikan program di atas.
NB: Dilarang menggunakan crontab dan tidak memakai argumen ketika menjalankan program.

 
 ```
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
        printf("%s", perwaktu);
        sprintf(direktorifile, "/home/lutfiy/modul2/hasil5/%s", perwaktu);
        mkdir(direktorifile, 0777); //777 biar bisa akses semua
        for(int i=1; i<30; i++){
                FILE *lama, *baru;
                lama = fopen("/var/log/syslog", "r");
                char nama_file[100];
                sprintf(nama_file, "/home/lutfiy/modul2/hasil5/%s/log%d.log", perwaktu, i);
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
 
 ```
- `time_t waktu_sekarang;`
  `time(&waktu_sekarang);` 
  Mendeklarasikan variabel `waktu_sekarang` dengan tipe data `time_t` dan dan memasukan current time ke `waktu_sekarang`.
  
- `struct tm *waktu;`
  `waktu = localtime(&waktu_sekarang);`
  Kemudian membuat `struct tm` dengan nama `waktu` menggunakan struct untuk memecah waktu.
  
- `sprintf(perwaktu, "%d:%d:%d-%d:%d", waktu->tm_mday, waktu->tm_mon+1, waktu->tm_year+1900, waktu->tm_hour, waktu->tm_min);`
  `
