#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>

using namespace std;

bool login() {
    string password = "093";
    string nama = "rando";
    string katasandi;

    int percobaan = 1;
    
    cout << "\t MENU LOGIN PASSWORD \n";
    
    while(percobaan <= 3) {

        cout << "NAMA ANDA :";
        cin >> nama;

        cout << "Inputkan kata sandi: ";
        cin >> katasandi;
        
        if (katasandi == password) {
            cout << "\nKata sandi benar\n";
            return true;
        } else {
            percobaan++;
            if(percobaan == 4) {
                cout << "\nLogin gagal - Kesempatan habis!\n";
                return false;
            } else {
                cout << "Kata sandi salah. Kesempatan tersisa: " << (4-percobaan) << endl;
            }
        }
    }
    return false;
}

void konversiJam() {
    double jam;
    cout << "Masukkan nilai Jam: ";
    cin >> jam;
    double menit = jam * 60;
    double detik = jam * 3600;
    
    cout << "\nHasil Konversi:" << endl;
    cout << fixed << setprecision(2);
    cout << jam << " Jam = " << menit << " Menit dan " << detik << " Detik" << endl << endl;
}

void konversiMenit() {
    double menit;
    cout << "Masukkan nilai Menit: ";
    cin >> menit;
    double jam = menit / 60;
    double detik = menit * 60;
    
    cout << "\nHasil Konversi:" << endl;
    cout << fixed << setprecision(2);
    cout << menit << " Menit = " << jam << " Jam dan " << detik << " Detik" << endl << endl;
}

void konversiDetik() {
    double detik;
    cout << "Masukkan nilai Detik: ";
    cin >> detik;
    double jam = detik / 3600;
    double menit = detik / 60;
    
    cout << "\nHasil Konversi:" << endl;
    cout << fixed << setprecision(2);
    cout << detik << " Detik = " << jam << " Jam dan " << menit << " Menit" << endl << endl;
}

void tampilkanMenu() {
    cout << "--- MENU UTAMA ---" << endl;
    cout << "1. Konversi Jam -> Menit dan Detik" << endl;
    cout << "2. Konversi Menit -> Jam dan Detik" << endl;
    cout << "3. Konversi Detik -> Jam dan Menit" << endl;
    cout << "4. Keluar" << endl;
    cout << "------------------" << endl;
}

int main() {

    if (!login()) {
        return 0;
    }


    int pilihan;
    while (true) {
        tampilkanMenu();
        cout << "Pilih menu (1-4): ";
        cin >> pilihan;

        if (pilihan == 1) {
            konversiJam();
        } else if (pilihan == 2) {
            konversiMenit();
        } else if (pilihan == 3) {
            konversiDetik();
        } else if (pilihan == 4) {
            cout << "Terima Kasih Telah Menggunakan Program ini" << endl;
            break;
        } else {
            cout << "Pilihan Tidak Valid Pilihan Sampai 1-4 Saja" << endl << endl;
            cin.clear(); 
            cin.ignore(10000, '\n'); 
        }
    }

    return 0;
}