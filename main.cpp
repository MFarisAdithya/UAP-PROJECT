#include <iostream>
#include <fstream>
#include <ncurses/curses.h>
#include <string>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
using namespace std;

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
