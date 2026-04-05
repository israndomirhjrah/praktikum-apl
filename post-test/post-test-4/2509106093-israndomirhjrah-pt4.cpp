#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <limits>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Pemain {
    string namaPemain;
    int nomorPunggung;
    string posisi;
    int gol;
    int assist;
};

struct Tim {
    int id;
    string namaTim;
    string stadion;
    int tahunBerdiri;
    int poin;
    Pemain* skuad;
    int jumlahPemain;
    int kapasitasPemain;
};

struct User {
    string username;
    string password;
    string role;
    string namaLengkap;
};

map<string, User> databaseUsers;
const int MAKS_TIM = 20;
Tim daftarTim[MAKS_TIM];
int jumlahTim = 0;
int nextIdTim = 1;



void inisialisasiTim(Tim* tim, int id, string nama, string stadion, int tahun, int poin) {
    tim->id = id;
    tim->namaTim = nama;
    tim->stadion = stadion;
    tim->tahunBerdiri = tahun;
    tim->poin = poin;
    tim->jumlahPemain = 0;
    tim->kapasitasPemain = 11;
    tim->skuad = new Pemain[tim->kapasitasPemain];
}

void updatePoinTim(Tim& tim, int tambahanPoin) {
    tim.poin += tambahanPoin;
}

void alokasiTimBaru(Tim** daftarTim, int* kapasitas, int* jumlah, Tim* timBaru) {
    if (*jumlah >= *kapasitas) {
        int kapasitasBaru = *kapasitas * 2;
        Tim* temp = new Tim[kapasitasBaru];
        
        for (int i = 0; i < *jumlah; i++) {
            temp[i] = (*daftarTim)[i];
        }
        
        delete[] *daftarTim;
        *daftarTim = temp;
        *kapasitas = kapasitasBaru;
    }
    
    (*daftarTim)[*jumlah] = *timBaru;
    (*jumlah)++;
}



void tambahPoinTim(Tim* tim, int poin) {
    (*tim).poin += poin;
}

void updateStatistikPemain(Pemain* pemain, int golBaru, int assistBaru) {
    pemain->gol += golBaru;
    pemain->assist += assistBaru;
}

void tambahPemainKeTim(Tim** timPtr, Pemain* pemainBaru, bool* berhasil) {
    Tim* tim = *timPtr;
    
    if (tim->jumlahPemain < tim->kapasitasPemain) {
        tim->skuad[tim->jumlahPemain] = *pemainBaru;
        tim->jumlahPemain++;
        *berhasil = true;
    } else {
        *berhasil = false;
    }
}

Pemain* cariPemainByNomor(Tim* tim, int nomorPunggung) {
    for (int i = 0; i < tim->jumlahPemain; i++) {
        if (tim->skuad[i].nomorPunggung == nomorPunggung) {
            return &(tim->skuad[i]);
        }
    }
    return nullptr;
}


int hitungTotalGol(Pemain* skuad, int indeks, int jumlahPemain) {
    if (indeks >= jumlahPemain) {
        return 0;
    }
    return skuad[indeks].gol + hitungTotalGol(skuad, indeks + 1, jumlahPemain);
}

int hitungTotalAssist(Pemain* skuad, int indeks, int jumlahPemain) {
    if (indeks >= jumlahPemain) {
        return 0;
    }
    return skuad[indeks].assist + hitungTotalAssist(skuad, indeks + 1, jumlahPemain);
}

void tampilkanPemain(Pemain* skuad, int indeks, int jumlahPemain) {
    if (indeks >= jumlahPemain) {
        return;
    }
    
    cout << left 
         << setw(5) << indeks + 1
         << setw(25) << skuad[indeks].namaPemain.substr(0, 24)
         << setw(15) << skuad[indeks].nomorPunggung
         << setw(15) << skuad[indeks].posisi.substr(0, 14)
         << setw(10) << skuad[indeks].gol
         << setw(10) << skuad[indeks].assist
         << "\n";
    
    tampilkanPemain(skuad, indeks + 1, jumlahPemain);
}


void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void tampilkanHeader(string judul) {
    cout << "\n==========================================\n";
    cout << "   " << judul << "\n";
    cout << "==========================================\n";
}

void tampilkanGaris(char ch = '=', int panjang = 50) {
    cout << string(panjang, ch) << endl;
}

void tampilkanPesan(string pesan, bool tungguEnter = true) {
    cout << pesan << endl;
    if (tungguEnter) {
        cout << "Tekan Enter untuk melanjutkan...";
        cin.get();
    }
}

int cariTim(int idTim, int jumlahTim, Tim daftarTim[]) {
    for (int i = 0; i < jumlahTim; i++) {
        if (daftarTim[i].id == idTim) {
            return i;
        }
    }
    return -1;
}

int cariTim(string namaTim, int jumlahTim, Tim daftarTim[]) {
    for (int i = 0; i < jumlahTim; i++) {
        if (daftarTim[i].namaTim == namaTim) {
            return i;
        }
    }
    return -1;
}

void infoTim(Tim tim) {
    cout << "ID: " << tim.id << " | " << tim.namaTim 
         << " (Pemain: " << tim.jumlahPemain << "/" << tim.kapasitasPemain 
         << ", Poin: " << tim.poin << ")";
}

void infoTim(Tim tim, bool detailLengkap) {
    if (detailLengkap) {
        cout << "\n=== DETAIL TIM ===\n";
        cout << "ID Tim         : " << tim.id << "\n";
        cout << "Nama Tim       : " << tim.namaTim << "\n";
        cout << "Stadion        : " << tim.stadion << "\n";
        cout << "Tahun Berdiri  : " << tim.tahunBerdiri << "\n";
        cout << "Poin           : " << tim.poin << "\n";
        cout << "Jumlah Pemain  : " << tim.jumlahPemain << "/" << tim.kapasitasPemain << "\n";
    } else {
        infoTim(tim);
    }
}

bool validasiTahunBerdiri(int tahun) {
    return (tahun >= 1800 && tahun <= 2024);
}

bool validasiNomorPunggung(int nomor, Tim tim) {
    if (nomor < 1 || nomor > 99) return false;
    
    for (int i = 0; i < tim.jumlahPemain; i++) {
        if (tim.skuad[i].nomorPunggung == nomor) {
            return false;
        }
    }
    return true;
}

int inputAngka(string pesan, int minValue, int maxValue) {
    int angka;
    while (true) {
        cout << pesan;
        cin >> angka;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Input harus berupa angka! Silakan coba lagi.\n";
        } else if (angka < minValue || angka > maxValue) {
            cout << "Input harus antara " << minValue << " - " << maxValue << "! Silakan coba lagi.\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return angka;
        }
    }
}

int inputAngka(string pesan) {
    return inputAngka(pesan, INT_MIN, INT_MAX);
}

bool registrasi(map<string, User>* database, User* userBaru) {
    if (database->find(userBaru->username) != database->end()) {
        return false;
    }
    
    if (userBaru->password.length() < 6) {
        return false;
    }
    
    userBaru->role = "User";
    (*database)[userBaru->username] = *userBaru;
    return true;
}

bool loginUser(map<string, User>* database, string username, string password, User* currentUser) {
    auto it = database->find(username);
    if (it != database->end() && it->second.password == password) {
        *currentUser = it->second;
        return true;
    }
    return false;
}



bool tambahTimBaru(Tim* daftarTim, int* jumlahTim, int* nextId, Tim* timBaru) {
    if (*jumlahTim >= MAKS_TIM) {
        return false;
    }
    
    timBaru->id = (*nextId)++;
    timBaru->jumlahPemain = 0;
    timBaru->kapasitasPemain = 11;
    timBaru->skuad = new Pemain[timBaru->kapasitasPemain];
    
    daftarTim[*jumlahTim] = *timBaru;
    (*jumlahTim)++;
    return true;
}

bool tambahPemainBaru(Tim* tim, Pemain* pemainBaru) {
    if (tim->jumlahPemain >= tim->kapasitasPemain) {
        return false;
    }
    
    tim->skuad[tim->jumlahPemain] = *pemainBaru;
    tim->jumlahPemain++;
    return true;
}

bool hapusTimDariLiga(Tim* daftarTim, int* jumlahTim, int idTim) {
    int indeks = cariTim(idTim, *jumlahTim, daftarTim);
    if (indeks == -1) {
        return false;
    }
    
    delete[] daftarTim[indeks].skuad;
    
    for (int i = indeks; i < *jumlahTim - 1; i++) {
        daftarTim[i] = daftarTim[i + 1];
    }
    (*jumlahTim)--;
    return true;
}

void tampilkanStatistikTim(Tim* tim) {
    cout << "\n=== STATISTIK TIM: " << tim->namaTim << " ===\n";
    cout << "Total Gol Semua Pemain  : " << hitungTotalGol(tim->skuad, 0, tim->jumlahPemain) << endl;
    cout << "Total Assist Semua Pemain : " << hitungTotalAssist(tim->skuad, 0, tim->jumlahPemain) << endl;
    
    if (tim->jumlahPemain > 0) {
        Pemain* topScorer = &(tim->skuad[0]);
        for (int i = 1; i < tim->jumlahPemain; i++) {
            if (tim->skuad[i].gol > topScorer->gol) {
                topScorer = &(tim->skuad[i]);
            }
        }
        cout << "Top Scorer              : " << topScorer->namaPemain 
             << " (" << topScorer->gol << " gol)" << endl;
    }
}



void registrasiMenu(map<string, User>* database) {
    clearScreen();
    tampilkanHeader("REGISTRASI AKUN BARU");
    
    User userBaru;
    
    cout << "Masukkan Username: ";
    getline(cin, userBaru.username);
    cout << "Masukkan Password (minimal 6 karakter): ";
    getline(cin, userBaru.password);
    cout << "Masukkan Nama Lengkap: ";
    getline(cin, userBaru.namaLengkap);
    
    if (registrasi(database, &userBaru)) {
        cout << "\n==========================================\n";
        cout << "         REGISTRASI BERHASIL!\n";
        cout << "==========================================\n";
        cout << "Username    : " << userBaru.username << "\n";
        cout << "Nama        : " << userBaru.namaLengkap << "\n";
        cout << "Role        : User \n";
        cout << "==========================================\n";
        cout << "Silakan login menggunakan akun Anda.\n";
        cout << "\nTekan Enter untuk melanjutkan...";
        cin.get();
    } else {
        cout << "\n==========================================\n";
        cout << "           REGISTRASI GAGAL!\n";
        cout << "==========================================\n";
        if (database->find(userBaru.username) != database->end()) {
            cout << "Username '" << userBaru.username << "' sudah digunakan!\n";
        } else if (userBaru.password.length() < 6) {
            cout << "Password harus minimal 6 karakter!\n";
        } else {
            cout << "Terjadi kesalahan saat registrasi.\n";
        }
        cout << "==========================================\n";
        cout << "\nTekan Enter untuk melanjutkan...";
        cin.get();
    }
}

bool loginMenu(map<string, User>* database, User* currentUser) {
    string username, password;
    int percobaan = 0;
    const int maxPercobaan = 3;
    
    while (percobaan < maxPercobaan) {
        clearScreen();
        tampilkanHeader("MENU LOGIN");
        cout << "Username: ";
        getline(cin, username);
        cout << "Password: ";
        getline(cin, password);
        
        if (loginUser(database, username, password, currentUser)) {
            tampilkanGaris('-');
            cout << "\nLOGIN BERHASIL!\n";
            cout << "Selamat datang, " << currentUser->namaLengkap << "!\n";
            cout << "Role: " << currentUser->role << "\n";
            tampilkanGaris('-');
            
            cout << "\nTekan Enter untuk melanjutkan...";
            cin.get();
            return true;
        }
        
        percobaan++;
        if (percobaan < maxPercobaan) {
            cout << "\nUsername atau password salah! Silakan coba lagi.\n";
            cout << "Sisa percobaan: " << (maxPercobaan - percobaan) << "\n";
            cout << "Tekan Enter untuk melanjutkan...";
            cin.get();
        }
    }
    
    clearScreen();
    tampilkanHeader("LOGIN GAGAL");
    cout << "\nAnda telah gagal login 3 kali.\n";
    cout << "Tekan Enter untuk keluar...";
    cin.get();
    return false;
}

void lihatSemuaTim(Tim* daftarTim, int* jumlahTim) {
    clearScreen();
    tampilkanHeader("DAFTAR SEMUA TIM");
    
    if (*jumlahTim == 0) {
        tampilkanPesan("Belum ada tim terdaftar.", true);
        return;
    }
    
    cout << left 
         << setw(5) << "ID"
         << setw(25) << "Nama Tim"
         << setw(25) << "Stadion"
         << setw(15) << "Tahun"
         << setw(10) << "Poin"
         << setw(15) << "Pemain"
         << "\n";
    tampilkanGaris('-', 95);
    
    for (int i = 0; i < *jumlahTim; i++) {
        cout << left 
             << setw(5) << daftarTim[i].id
             << setw(25) << daftarTim[i].namaTim.substr(0, 24)
             << setw(25) << daftarTim[i].stadion.substr(0, 24)
             << setw(15) << daftarTim[i].tahunBerdiri
             << setw(10) << daftarTim[i].poin
             << setw(15) << daftarTim[i].jumlahPemain
             << "\n";
    }
    tampilkanGaris('=', 95);
    
    cout << "\nTekan Enter untuk kembali...";
    cin.get();
}

void lihatDetailTim(Tim* daftarTim, int* jumlahTim, int* nextIdTim) {
    clearScreen();
    tampilkanHeader("DETAIL TIM DAN PEMAIN");
    
    if (*jumlahTim == 0) {
        tampilkanPesan("Belum ada tim terdaftar.", true);
        return;
    }
    
    lihatSemuaTim(daftarTim, jumlahTim);
    
    int idTim = inputAngka("\nMasukkan ID Tim yang ingin dilihat detailnya: ", 1, *nextIdTim - 1);
    
    int indeksTim = cariTim(idTim, *jumlahTim, daftarTim);
    
    if (indeksTim == -1) {
        tampilkanPesan("Tim dengan ID " + to_string(idTim) + " tidak ditemukan!", true);
        return;
    }
    
    clearScreen();
    infoTim(daftarTim[indeksTim], true);
    
    if (daftarTim[indeksTim].jumlahPemain == 0) {
        cout << "\nBelum ada pemain di tim ini.\n";
    } else {
        cout << "\nDAFTAR PEMAIN:\n";
        tampilkanGaris('-', 70);
        cout << left 
             << setw(5) << "No"
             << setw(25) << "Nama Pemain"
             << setw(15) << "No Punggung"
             << setw(15) << "Posisi"
             << setw(10) << "Gol"
             << setw(10) << "Assist"
             << "\n";
        tampilkanGaris('-', 70);
        
        tampilkanPemain(daftarTim[indeksTim].skuad, 0, daftarTim[indeksTim].jumlahPemain);
        tampilkanGaris('=', 70);
        
        tampilkanStatistikTim(&daftarTim[indeksTim]);
    }
    
    cout << "\nTekan Enter untuk kembali...";
    cin.get();
}

void tambahTimMenu(Tim* daftarTim, int* jumlahTim, int* nextIdTim) {
    clearScreen();
    tampilkanHeader("TAMBAH TIM BARU");
    
    if (*jumlahTim >= MAKS_TIM) {
        tampilkanPesan("Database tim sudah penuh (maksimal " + to_string(MAKS_TIM) + " tim)!", true);
        return;
    }
    
    Tim timBaru;
    
    cout << "Nama Tim: ";
    getline(cin, timBaru.namaTim);
    cout << "Stadion: ";
    getline(cin, timBaru.stadion);
    
    do {
        timBaru.tahunBerdiri = inputAngka("Tahun Berdiri: ");
        if (!validasiTahunBerdiri(timBaru.tahunBerdiri)) {
            cout << "Tahun harus antara 1800 - 2024!\n";
        }
    } while (!validasiTahunBerdiri(timBaru.tahunBerdiri));
    
    timBaru.poin = inputAngka("Poin Awal: ", 0, 100);
    
    if (tambahTimBaru(daftarTim, jumlahTim, nextIdTim, &timBaru)) {
        tampilkanPesan("\nTim " + timBaru.namaTim + " berhasil ditambahkan! ID Tim: " + 
                      to_string(timBaru.id), true);
    } else {
        tampilkanPesan("\nGagal menambahkan tim!", true);
    }
}

void tambahPemainMenu(Tim* daftarTim, int* jumlahTim, int* nextIdTim) {
    clearScreen();
    tampilkanHeader("TAMBAH PEMAIN KE TIM");
    
    if (*jumlahTim == 0) {
        tampilkanPesan("Belum ada tim terdaftar. Tambah tim terlebih dahulu.", true);
        return;
    }
    
    cout << "DAFTAR TIM:\n";
    tampilkanGaris('-', 50);
    for (int i = 0; i < *jumlahTim; i++) {
        infoTim(daftarTim[i]);
        cout << endl;
    }
    tampilkanGaris('-', 50);
    
    int idTim = inputAngka("\nMasukkan ID Tim: ", 1, *nextIdTim - 1);
    int indeksTim = cariTim(idTim, *jumlahTim, daftarTim);
    
    if (indeksTim == -1) {
        tampilkanPesan("Tim dengan ID " + to_string(idTim) + " tidak ditemukan!", true);
        return;
    }
    
    if (daftarTim[indeksTim].jumlahPemain >= daftarTim[indeksTim].kapasitasPemain) {
        tampilkanPesan("Tim sudah mencapai maksimal pemain (" + to_string(daftarTim[indeksTim].kapasitasPemain) + " pemain)!", true);
        return;
    }
    
    cout << "\nMenambah pemain untuk tim: " << daftarTim[indeksTim].namaTim << "\n";
    cout << "Jumlah pemain saat ini: " << daftarTim[indeksTim].jumlahPemain 
         << "/" << daftarTim[indeksTim].kapasitasPemain << "\n\n";
    
    Pemain pemainBaru;
    cout << "Nama Pemain: ";
    getline(cin, pemainBaru.namaPemain);
    
    do {
        pemainBaru.nomorPunggung = inputAngka("Nomor Punggung (1-99): ", 1, 99);
        if (!validasiNomorPunggung(pemainBaru.nomorPunggung, daftarTim[indeksTim])) {
            cout << "Nomor punggung sudah digunakan atau tidak valid!\n";
        }
    } while (!validasiNomorPunggung(pemainBaru.nomorPunggung, daftarTim[indeksTim]));
    
    cout << "Posisi: ";
    getline(cin, pemainBaru.posisi);
    pemainBaru.gol = inputAngka("Jumlah Gol: ", 0, 100);
    pemainBaru.assist = inputAngka("Jumlah Assist: ", 0, 100);
    
    bool berhasil;
   
    Tim* timPtr = &daftarTim[indeksTim];
    tambahPemainKeTim(&timPtr, &pemainBaru, &berhasil);
    
    if (berhasil) {
        tampilkanPesan("\nPemain " + pemainBaru.namaPemain + " berhasil ditambahkan ke " + 
                      daftarTim[indeksTim].namaTim + "!", true);
    } else {
        tampilkanPesan("\nGagal menambahkan pemain!", true);
    }
}

void hapusTimMenu(Tim* daftarTim, int* jumlahTim, int* nextIdTim) {
    clearScreen();
    tampilkanHeader("HAPUS TIM DARI LIGA");
    
    if (*jumlahTim == 0) {
        tampilkanPesan("Belum ada tim terdaftar.", true);
        return;
    }
    
    lihatSemuaTim(daftarTim, jumlahTim);
    
    int idTim = inputAngka("\nMasukkan ID Tim yang akan dihapus: ", 1, *nextIdTim - 1);
    
    int indeksHapus = cariTim(idTim, *jumlahTim, daftarTim);
    if (indeksHapus == -1) {
        tampilkanPesan("\nTim dengan ID " + to_string(idTim) + " tidak ditemukan!", true);
        return;
    }
    
    cout << "\nAnda akan menghapus tim:\n";
    cout << "Nama Tim    : " << daftarTim[indeksHapus].namaTim << "\n";
    cout << "Stadion     : " << daftarTim[indeksHapus].stadion << "\n";
    cout << "Jumlah Pemain: " << daftarTim[indeksHapus].jumlahPemain << " pemain\n\n";
    cout << "Yakin ingin menghapus tim ini? (y/n): ";
    
    char konfirmasi;
    cin >> konfirmasi;
    cin.ignore();
    
    if (konfirmasi == 'y' || konfirmasi == 'Y') {
        if (hapusTimDariLiga(daftarTim, jumlahTim, idTim)) {
            tampilkanPesan("\nTim berhasil dihapus dari liga!", true);
        } else {
            tampilkanPesan("\nGagal menghapus tim!", true);
        }
    } else {
        tampilkanPesan("\nPenghapusan dibatalkan.", true);
    }
}

void menuAdmin(User* currentUser, Tim* daftarTim, int* jumlahTim, int* nextIdTim) {
    int pilihan;
    bool running = true;
    
    do {
        clearScreen();
        tampilkanHeader("MENU ADMIN");
        cout << "User: " << currentUser->username << " | " << currentUser->namaLengkap << "\n\n";
        cout << "1. Tambah Pemain ke Tim\n";
        cout << "2. Lihat Semua Tim\n";
        cout << "3. Tambah Tim Baru\n";
        cout << "4. Hapus Tim dari Liga\n";
        cout << "5. Lihat Detail Tim dan Pemain\n";
        cout << "6. Logout\n\n";
        
        pilihan = inputAngka("Pilih menu (1-6): ", 1, 6);
        
        switch (pilihan) {
            case 1: tambahPemainMenu(daftarTim, jumlahTim, nextIdTim); break;
            case 2: lihatSemuaTim(daftarTim, jumlahTim); break;
            case 3: tambahTimMenu(daftarTim, jumlahTim, nextIdTim); break;
            case 4: hapusTimMenu(daftarTim, jumlahTim, nextIdTim); break;
            case 5: lihatDetailTim(daftarTim, jumlahTim, nextIdTim); break;
            case 6: 
                cout << "\nLogout berhasil!\n";
                running = false;
                break;
        }
    } while (running);
}

void menuUser(User* currentUser, Tim* daftarTim, int* jumlahTim, int* nextIdTim) {
    int pilihan;
    bool running = true;
    
    do {
        clearScreen();
        tampilkanHeader("MENU USER");
        cout << "User: " << currentUser->username << " | " << currentUser->namaLengkap << "\n\n";
        cout << "1. Lihat Semua Tim\n";
        cout << "2. Lihat Detail Tim dan Pemain\n";
        cout << "3. Logout\n\n";
        
        pilihan = inputAngka("Pilih menu (1-3): ", 1, 3);
        
        switch (pilihan) {
            case 1: lihatSemuaTim(daftarTim, jumlahTim); break;
            case 2: lihatDetailTim(daftarTim, jumlahTim, nextIdTim); break;
            case 3:
                cout << "\nLogout berhasil!\n";
                running = false;
                break;
        }
    } while (running);
}

void inisialisasiData(Tim* daftarTim, int* jumlahTim, int* nextIdTim) {
    srand(time(0));
    
    User admin;
    admin.username = "rando";
    admin.password = "2509106093";
    admin.namaLengkap = "Administrator";
    admin.role = "Admin";
    databaseUsers["rando"] = admin;
    
    User user;
    user.username = "rando1";
    user.password = "093";
    user.namaLengkap = "Biasa User";
    user.role = "User";
    databaseUsers["rando1"] = user;
    
    if (*jumlahTim == 0) {
        Tim tim1, tim2, tim3;
        
        inisialisasiTim(&tim1, (*nextIdTim)++, "Manchester City", "Etihad Stadium", 1880, 73);
        inisialisasiTim(&tim2, (*nextIdTim)++, "Arsenal", "Emirates Stadium", 1886, 71);
        inisialisasiTim(&tim3, (*nextIdTim)++, "Liverpool", "Anfield", 1892, 70);
        
        daftarTim[(*jumlahTim)++] = tim1;
        daftarTim[(*jumlahTim)++] = tim2;
        daftarTim[(*jumlahTim)++] = tim3;
    }
}

void cleanupData(Tim* daftarTim, int* jumlahTim) {
    for (int i = 0; i < *jumlahTim; i++) {
        delete[] daftarTim[i].skuad;
    }
}

void menuAwal() {
    int pilihan;
    bool programRunning = true;
    User currentUser;
    
    Tim timArray[MAKS_TIM];
    int jumlahTimLocal = 0;
    int nextIdTimLocal = 1;
    
    inisialisasiData(timArray, &jumlahTimLocal, &nextIdTimLocal);
    
    do {
        clearScreen();
        tampilkanHeader("SISTEM MANAJEMEN LIGA PREMIER");
        cout << "Selamat datang di Sistem Manajemen Liga Premier\n\n";
        cout << "1. Registrasi Akun Baru\n";
        cout << "2. Login\n";
        cout << "3. Keluar\n\n";
        
        pilihan = inputAngka("Pilih menu (1-3): ", 1, 3);
        
        switch (pilihan) {
            case 1:
                registrasiMenu(&databaseUsers);
                break;
            case 2:
                if (loginMenu(&databaseUsers, &currentUser)) {
                    if (currentUser.role == "Admin") {
                        menuAdmin(&currentUser, timArray, &jumlahTimLocal, &nextIdTimLocal);
                    } else {
                        menuUser(&currentUser, timArray, &jumlahTimLocal, &nextIdTimLocal);
                    }
                } else {
                    programRunning = false;
                }
                break;
            case 3:
                cout << "\nTerima kasih telah menggunakan program ini!\n";
                programRunning = false;
                break;
        }
    } while (programRunning);
    
    cleanupData(timArray, &jumlahTimLocal);
}

int main() {
    menuAwal();
    return 0;
}