#include <iostream>
#include <fstream>
#include <ncurses/curses.h>
#include <string>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
using namespace std;

void point(bool exist,string ul);
void login();


int main() {
    initscr();
    cb();
    noecho();
    cbreak();

    keypad(stdscr, TRUE);
	box(stdscr,1,1);
    // Daftar pilihan menu
    const char *opsi[] = {
        "Registration",
        "Login",
        "Keluar"
    };

    int jumlahopsi = sizeof(opsi) / sizeof(char *);
    int pilihanTerpilih = 0; // Indeks pilihan pertama
    int pilihan = -1; 
	loading(5);
    while (1) {
         // Menampilkan menu
		for (int i = 0; i < 3; i++) {
			if (pilihanTerpilih == i) attron(A_REVERSE);
			mvprintw(i+12,40, opsi[i]);
			refresh();
			if (pilihanTerpilih == i) attroff(A_REVERSE);
		}
		pilihanTerpilih;
        int tombol = wgetch(stdscr); // Membaca input dari keyboard
        switch (tombol) {
            case KEY_UP:
                if (pilihanTerpilih == 0) {
                    pilihanTerpilih = 2; // Kembali ke pilihan terakhir
                } else {
                    --pilihanTerpilih; // Pindah ke pilihan sebelumnya
                }
                break;

            case KEY_DOWN:
                if (pilihanTerpilih == 2) {
                    pilihanTerpilih = 0; // Kembali ke pilihan pertama
                } else {
                    ++pilihanTerpilih; // Pindah ke pilihan berikutnya
                }
                break;

            case 10: // Enter
                pilihan = pilihanTerpilih; // Menyimpan pilihan yang dipilih
                break;
        }

        refresh(); 
        if (pilihan == 2) { // Pilih "Keluar"
            break; // Keluar dari loop jika "Keluar" dipilih
        } else 
        if (pilihan == 0) { //pilih Register
        	loading(1);
			registration(); // masuk ke fungsi register
			
			pilihan = -1; //mengembalikan nilai pilihan
		} else
        if (pilihan == 1) {
        	loading(1);
        	login();
 
        	pilihan = -1;
        	
		}
    }

    endwin(); // Mengakhiri ncurses
    return 0;
}

void login() {
	refresh();
    ifstream myFile;
    char userLog[100], passLog[100];
    string  userData, storedPass;

    bool exist = false;

	cb();
	echo();
    mvprintw(9,45,"----------->LOGIN<-----------");
    mvprintw(11,45, "Enter username: ");
    mvgetnstr(11,61,userLog,99);

    mvprintw(12,45,"Enter password: ");
    mvgetnstr(12,61,passLog,99);
    noecho();


    // Memeriksa apakah username ada di daftar
    myFile.open("ListAccount.txt");
    while (myFile >> userData) {
        if (userData == userLog) {
            exist = true;
            break;
        }
    }
    myFile.close();
    string UserLog = userLog;
    string PassLog = passLog;
  
    // Memeriksa apakah password benar
    if (exist){
    	exist= false;
    	myFile.open(UserLog + ".txt");
    	myFile >> storedPass;	
    	if (storedPass == PassLog){
    		exist = true;
		}
		
	}
	cb();
    myFile.close();
    loading(1);
	point(exist, UserLog);
   
}

void point(bool exist,string UserLog) {
	string storedPass;
	 if (exist) {

        if (exist) {
            mvprintw(15,45,"Login successful!");
            

            // Proses skor
            ifstream scoreCheck;
            ofstream scoreFile;
            char topScore[100];
			int currentScore;
            string tumbal;

            scoreCheck.open(UserLog + ".txt");
            getline(scoreCheck, tumbal);  
            scoreCheck >> currentScore;      
            scoreCheck.close();

            mvprintw(16,45,"Input top score: ");
            echo();
            mvgetnstr(16,61,topScore,99);
            noecho();
			cb();
            // Update skor jika skor baru lebih tinggi
            if (atoi(topScore) > currentScore) {
                scoreFile.open(UserLog + ".txt");
                scoreFile << tumbal << endl;  // Simpan kembali password
                scoreFile << topScore;           // Simpan skor baru
                scoreFile.close();
                loading(3);
                mvprintw(19,45,"Your Top Score Is: %s",topScore);
            } else {
            	loading(3);
                mvprintw(19,45,"Your Top Score: %d", currentScore);
            }
        } else {
        	loading(3);
            mvprintw(19,45,"Incorrect password. Please try again."); 
        }
    } else {
        // Jika username tidak ditemukan
        mvprintw(11,40,"----------------------------------------");
        mvprintw(12,40,"                LOGIN ERROR             ");
        mvprintw(13,40,"Please check your username and try again");
        mvprintw(14,40,"----------------------------------------");
    }
    refresh();
    getch();
    cb();
    
}
