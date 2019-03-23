
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
   
   Berikut adalah file di Documents dengan ekstensi .png yang nantinya akan dipindahkan ke home/lutfiy/modul2/gambar. Dengan ditambah _grey.png
   
   ![gambar 1](https://github.com/lutfiyanti/SoalShift_Modul2_A08/blob/master/1%20isi%20Document.png)
   
   
   
   Setelah itu file soal1.c di bash dan cek direktori gambar di dalam direktori modul2
   
    ![gambar 2](https://github.com/lutfiyanti/SoalShift_Modul2_A08/blob/master/1%20Bash%20dan%20Hasil.png)
    
    seluruh file di Documents dipindah ke direktori home/lutfiy/modul2/gambar. Dengan ditambah _grey.png
    
   
 # Soal 2
 Pada suatu hari Kusuma dicampakkan oleh Elen karena Elen dimenangkan oleh orang lain. Semua kenangan tentang Elen berada pada file bernama “elen.ku” pada direktori “hatiku”. Karena sedih berkepanjangan, tugas kalian sebagai teman Kusuma adalah membantunya untuk menghapus semua kenangan tentang Elen dengan membuat program C yang bisa mendeteksi owner dan group dan menghapus file “elen.ku” setiap 3 detik dengan syarat ketika owner dan grupnya menjadi “www-data”. Ternyata kamu memiliki kendala karena permission pada file “elen.ku”. Jadi, ubahlah permissionnya menjadi 777. Setelah kenangan tentang Elen terhapus, maka Kusuma bisa move on.
Catatan: Tidak boleh menggunakan crontab

 
 ```
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
  ``` 
  ### Penjelasan :
  1. ubah directory ke folder hatiku
  
2. lalu kita pakai stat untuk mengarahkan ke path folder, misalkan namanya awo

3. ada owner, yaitu user(kita). kita harus mencari password user, dengan melakukan getpwuid("path", st_uid)

4. ada group, kita juga harus mencari group denagn melakukan getgrgid("path", st_gid)

5. lalu kita compare dari owner dan group tersebut dengan www-data, jika keduanya memiliki ukuran string yg sama dengan www-data, maka kita remove file elen.ku

6. lalu pasang daemon agar dapat dijalankan setiap 3 detik dari awal dijalankan kode tersebut. 

# Soal 3
Diberikan file campur2.zip. Di dalam file tersebut terdapat folder “campur2”. 
Buatlah program C yang dapat :
i)  mengekstrak file zip tersebut.
ii) menyimpan daftar file dari folder “campur2” yang memiliki ekstensi .txt ke dalam file daftar.txt. 
Catatan:  
Gunakan fork dan exec.
Gunakan minimal 3 proses yang diakhiri dengan exec.
Gunakan pipe
Pastikan file daftar.txt dapat diakses dari text editor


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

                        if (pid3 < 0) exit(EXIT_FAILURE);

                        if(pid3 == 0){
                                execvp("grep", grep);
                        }
                        else{

                        }
                }
        }
        return 0;
}
```
- `char *unzip[] = {"unzip", "/home/ltfiy/modul2/soal3/campur2.zip", NULL};` Untuk mengunzip file campur2.
- `char *ls[] = {"ls", "/home/lutfiy/modul2/campur2", NULL};` untuk mengecek semua file didalam folder campur 2
- `char *grep[] = {"grep", ".txt$", NULL};` untuk mencari file .txt.
- `pid1 = fork();` membuat fork untuk pid1.
- `if (pid1 < 0) exit(EXIT_FAILURE);`jika kurang dr 0 berarti bukan childnya.
- `if (pid1 == 0)` jika = 0 maka dia adalah childnya. 
                `execvp("unzip", unzip);` setelah itu file di unzip.
                
- ```          
      if(pid2 == 0){
             dup2(pipe1[1], STDOUT_FILENO); 
             close(pipe1[1]); 
             close(pipe1[0]); 
             execvp("ls", ls);
  ```
  
 


# Soal 4 :
Dalam direktori /home/[user]/Documents/makanan terdapat file makan_enak.txt yang berisikan daftar makanan terkenal di Surabaya. Elen sedang melakukan diet dan seringkali tergiur untuk membaca isi makan_enak.txt karena ngidam makanan enak. Sebagai teman yang baik, Anda membantu Elen dengan membuat program C yang berjalan setiap 5 detik untuk memeriksa apakah file makan_enak.txt pernah dibuka setidaknya 30 detik yang lalu (rentang 0 - 30 detik).
Jika file itu pernah dibuka, program Anda akan membuat 1 file makan_sehat#.txt di direktori /home/[user]/Documents/makanan dengan '#' berisi bilangan bulat dari 1 sampai tak hingga untuk mengingatkan Elen agar berdiet.

Contoh:
File makan_enak.txt terakhir dibuka pada detik ke-1
Pada detik ke-10 terdapat file makan_sehat1.txt dan makan_sehat2.txt

Catatan: 
dilarang menggunakan crontab
Contoh nama file : makan_sehat1.txt, makan_sehat2.txt, dst


```
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
```
### Penjelasan :
1. kita perlu struct file yg berisi path menuju file makan_enak.txt, misalkan namanya att (atribut)
2. disini juga perlu mengukur waktu karena diminta membuat file makan_sehat setiap 5 detik dengan range 30 detik, maka perlu memberi program access dan now
  a. access sebagai waktu akses
  b. now sebagai waktu ketika program berjalan
3. lalu dibuat range diantara access dan now
4. jika sudah dibuat rangenya, kita disuruh membuat file bernama makan_sehat(angka 1- dst).txt yg digunakan sebagai pengingat
5. dan jangan lupa dibuat urut filenya
6. lalu kita fopen untuk file makan_sehat yg kita buat, baru close

   
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
 
 ```
- `time_t waktu_sekarang;`
  `time(&waktu_sekarang);` 
  Mendeklarasikan variabel `waktu_sekarang` dengan tipe data `time_t` dan dan memasukan current time ke `waktu_sekarang`.
  
- `struct tm *waktu;`
  `waktu = localtime(&waktu_sekarang);`
  Kemudian membuat `struct tm` dengan nama `waktu` menggunakan struct untuk memecah waktu.
  
- `sprintf(perwaktu, "%d:%d:%d-%d:%d", waktu->tm_mday, waktu->tm_mon+1, waktu->tm_year+1900, waktu->tm_hour, waktu->tm_min);` memasukan            format waktu `"%d:%d:%d-%d:%d"` ke dalam `perwaktu`.

- `sprintf(direktorifile, "/home/lutfiy/modul2/hasil5/%s", perwaktu);` menyimpan nama direktori + filenya di `direktorifile`.

- `mkdir(direktorifile, 0777);` membuat direktori  sesuai isi direktorifile.

- ```
  for(int a=1; a<30; a++){
            ...
       sleep(60);
  }
  ```
 dijalankan 30 kali dengan waktu tunggu 60 detik, karena mintanya per menit.
 
 - `lama = fopen("/var/log/syslog", "r");` membuka file syslog read saja.
 
 - `sprintf(nama_file, "/home/lutfiy/modul2/hasil5/%s/log%d.log", perwaktu, a);` menyimpan nama direktori dan file dengan s adalah nama        folder berdasarkan waktu dan a adalah nama tambahan yg di increament.
 
 - `baru = fopen(nama_file, "w");` membuat file dengan write isinya ke file baru.
 
 - ```
    while(fscanf(lama, "%c", &karakter) != EOF)
    {fprintf(baru, "%c", karakter);}
   ```
 scanf isi file syslognya sampai end of file kemudian karakternya dicetak di file baru.
 
 Setelah program soal5.c di bash maka akan terbuat direktori dengan namanya adalah timestamp. Direktori ini dibuat setiap 30 menit sekali. Dimana menit pertama akan membuat direktori terlebih dahulu.
 
 ![Gambar 6](https://github.com/lutfiyanti/SoalShift_Modul2_A08/blob/master/5%20direktori.png)
 
 Setelah membuat direktori menit berikutnya dengan jeda waktu setiap 1 menit akan membuat file didalam direktori tersebut. Nama file adalah log%d.log dimana %d adalah angka 1-29 tergantung dimenit ke-berapa dibuatnya. Counter. 
 
 ![Gambar 7](https://github.com/lutfiyanti/SoalShift_Modul2_A08/blob/master/5%20file.png)
  
  
#### Kill Proses 

```
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
```

meng kill proses yang punya pid dr file soal5
