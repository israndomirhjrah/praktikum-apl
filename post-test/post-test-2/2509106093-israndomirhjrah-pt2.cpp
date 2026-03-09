#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <limits>
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
    Pemain skuad[11];       
    int jumlahPemain;
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


int inputAngka(string pesan) {
    int angka;
    while (true) {
        cout << pesan;
        cin >> angka;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Input harus berupa angka! Silakan coba lagi.\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return angka;
        }
    }
}


void registrasi() {
    clearScreen();
    tampilkanHeader("REGISTRASI AKUN BARU");
    
    User userBaru;
    
    cout << "Masukkan Username: ";
    getline(cin, userBaru.username);
    

    if (databaseUsers.find(userBaru.username) != databaseUsers.end()) {
        cout << "\n[ERROR] Username sudah digunakan! Silakan gunakan username lain.\n";
        cout << "Tekan Enter untuk melanjutkan...";
        cin.get();
        return;
    }
    
    cout << "Masukkan Password: ";
    getline(cin, userBaru.password);
    

    if (userBaru.password.length() < 6) {
        cout << "\n[ERROR] Password minimal 6 karakter!\n";
        cout << "Tekan Enter untuk melanjutkan...";
        cin.get();
        return;
    }
    
    cout << "Masukkan Nama Lengkap: ";
    getline(cin, userBaru.namaLengkap);
    

    cout << "\nPilih Role:\n";
    cout << "1. Admin (Memiliki akses penuh ke manajemen liga)\n";
    cout << "2. User (Hanya dapat melihat data)\n";
    int pilihanRole = inputAngka("Pilih role (1-2): ");
    
    if (pilihanRole == 1) {
        userBaru.role = "Admin";
    } else {
        userBaru.role = "User";
    }
    

    databaseUsers[userBaru.username] = userBaru;
    
    tampilkanGaris('-');
    cout << "\nREGISTRASI BERHASIL!\n";
    cout << "Selamat datang, " << userBaru.namaLengkap << "!\n";
    cout << "Username: " << userBaru.username << "\n";
    cout << "Role: " << userBaru.role << "\n";
    tampilkanGaris('-');
    
    cout << "\nTekan Enter untuk melanjutkan...";
    cin.get();
}


bool login(User &currentUser) {
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
        
     
        auto it = databaseUsers.find(username);
        if (it != databaseUsers.end() && it->second.password == password) {
            currentUser = it->second;
            
            tampilkanGaris('-');
            cout << "\nLOGIN BERHASIL!\n";
            cout << "Selamat datang, " << currentUser.namaLengkap << "!\n";
            cout << "Role: " << currentUser.role << "\n";
            tampilkanGaris('-');
            
            cout << "\nTekan Enter untuk melanjutkan...";
            cin.get();
            return true;
        }
        
        percobaan++;
        if (percobaan < maxPercobaan) {
            cout << "\nUsername atau password salah! Silakan coba lagi.\n";
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


void lihatSemuaTim() {
    clearScreen();
    tampilkanHeader("DAFTAR SEMUA TIM");
    
    if (jumlahTim == 0) {
        cout << "Belum ada tim terdaftar.\n";
    } else {
        cout << left 
             << setw(5) << "ID"
             << setw(25) << "Nama Tim"
             << setw(25) << "Stadion"
             << setw(15) << "Tahun Berdiri"
             << setw(10) << "Poin"
             << setw(15) << "Jumlah Pemain"
             << "\n";
        tampilkanGaris('-', 95);
        
        for (int i = 0; i < jumlahTim; i++) {
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
    }
    
    cout << "\nTekan Enter untuk kembali...";
    cin.get();
}


void lihatDetailTim() {
    clearScreen();
    tampilkanHeader("DETAIL TIM DAN PEMAIN");
    
    if (jumlahTim == 0) {
        cout << "Belum ada tim terdaftar.\n";
        cout << "\nTekan Enter untuk kembali...";
        cin.get();
        return;
    }
    
    lihatSemuaTim();
    
    int idTim;
    cout << "\nMasukkan ID Tim yang ingin dilihat detailnya: ";
    cin >> idTim;
    cin.ignore();
    

    int indeksTim = -1;
    for (int i = 0; i < jumlahTim; i++) {
        if (daftarTim[i].id == idTim) {
            indeksTim = i;
            break;
        }
    }
    
    if (indeksTim == -1) {
        cout << "Tim dengan ID " << idTim << " tidak ditemukan!\n";
    } else {
        clearScreen();
        tampilkanHeader("DETAIL TIM");
        cout << "ID Tim         : " << daftarTim[indeksTim].id << "\n";
        cout << "Nama Tim       : " << daftarTim[indeksTim].namaTim << "\n";
        cout << "Stadion        : " << daftarTim[indeksTim].stadion << "\n";
        cout << "Tahun Berdiri  : " << daftarTim[indeksTim].tahunBerdiri << "\n";
        cout << "Poin           : " << daftarTim[indeksTim].poin << "\n";
        cout << "Jumlah Pemain  : " << daftarTim[indeksTim].jumlahPemain << "/11\n\n";
        
        if (daftarTim[indeksTim].jumlahPemain == 0) {
            cout << "Belum ada pemain di tim ini.\n";
        } else {
            cout << "DAFTAR PEMAIN:\n";
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
            
            for (int j = 0; j < daftarTim[indeksTim].jumlahPemain; j++) {
                cout << left 
                     << setw(5) << j + 1
                     << setw(25) << daftarTim[indeksTim].skuad[j].namaPemain.substr(0, 24)
                     << setw(15) << daftarTim[indeksTim].skuad[j].nomorPunggung
                     << setw(15) << daftarTim[indeksTim].skuad[j].posisi.substr(0, 14)
                     << setw(10) << daftarTim[indeksTim].skuad[j].gol
                     << setw(10) << daftarTim[indeksTim].skuad[j].assist
                     << "\n";
            }
            tampilkanGaris('=', 70);
        }
    }
    
    cout << "\nTekan Enter untuk kembali...";
    cin.get();
}


void tambahTim() {
    clearScreen();
    tampilkanHeader("TAMBAH TIM BARU");
    
    if (jumlahTim >= MAKS_TIM) {
        cout << "Database tim sudah penuh (maksimal " << MAKS_TIM << " tim)!\n";
        cout << "Tekan Enter untuk kembali...";
        cin.get();
        return;
    }
    
    Tim timBaru;
    timBaru.id = nextIdTim++;
    timBaru.jumlahPemain = 0;
    
    cout << "Nama Tim: ";
    getline(cin, timBaru.namaTim);
    cout << "Stadion: ";
    getline(cin, timBaru.stadion);
    cout << "Tahun Berdiri: ";
    cin >> timBaru.tahunBerdiri;
    cout << "Poin Awal: ";
    cin >> timBaru.poin;
    cin.ignore();
    
    daftarTim[jumlahTim] = timBaru;
    jumlahTim++;
    
    cout << "\nTim " << timBaru.namaTim << " berhasil ditambahkan!\n";
    cout << "ID Tim: " << timBaru.id << "\n";
    cout << "Tekan Enter untuk kembali...";
    cin.get();
}


void tambahPemain() {
    clearScreen();
    tampilkanHeader("TAMBAH PEMAIN KE TIM");
    
    if (jumlahTim == 0) {
        cout << "Belum ada tim terdaftar. Tambah tim terlebih dahulu.\n";
        cout << "Tekan Enter untuk kembali...";
        cin.get();
        return;
    }
    
  
    cout << "DAFTAR TIM:\n";
    tampilkanGaris('-', 50);
    for (int i = 0; i < jumlahTim; i++) {
        cout << "ID: " << daftarTim[i].id << " | " << daftarTim[i].namaTim 
             << " (Pemain: " << daftarTim[i].jumlahPemain << "/11)\n";
    }
    tampilkanGaris('-', 50);
    
    int idTim;
    cout << "\nMasukkan ID Tim: ";
    cin >> idTim;
    cin.ignore();
    
    
    int indeksTim = -1;
    for (int i = 0; i < jumlahTim; i++) {
        if (daftarTim[i].id == idTim) {
            indeksTim = i;
            break;
        }
    }
    
    if (indeksTim == -1) {
        cout << "Tim dengan ID " << idTim << " tidak ditemukan!\n";
        cout << "Tekan Enter untuk kembali...";
        cin.get();
        return;
    }
    
    if (daftarTim[indeksTim].jumlahPemain >= 11) {
        cout << "Tim sudah mencapai maksimal pemain (11 pemain)!\n";
        cout << "Tekan Enter untuk kembali...";
        cin.get();
        return;
    }
    
    cout << "\nMenambah pemain untuk tim: " << daftarTim[indeksTim].namaTim << "\n";
    cout << "Jumlah pemain saat ini: " << daftarTim[indeksTim].jumlahPemain << "/11\n\n";
    
    Pemain pemainBaru;
    cout << "Nama Pemain: ";
    getline(cin, pemainBaru.namaPemain);
    cout << "Nomor Punggung: ";
    cin >> pemainBaru.nomorPunggung;
    cin.ignore();
    cout << "Posisi: ";
    getline(cin, pemainBaru.posisi);
    cout << "Jumlah Gol: ";
    cin >> pemainBaru.gol;
    cout << "Jumlah Assist: ";
    cin >> pemainBaru.assist;
    cin.ignore();
    
    daftarTim[indeksTim].skuad[daftarTim[indeksTim].jumlahPemain] = pemainBaru;
    daftarTim[indeksTim].jumlahPemain++;
    
    cout << "\nPemain " << pemainBaru.namaPemain << " berhasil ditambahkan ke " 
         << daftarTim[indeksTim].namaTim << "!\n";
    cout << "Tekan Enter untuk kembali...";
    cin.get();
}


void hapusTim() {
    clearScreen();
    tampilkanHeader("HAPUS TIM DARI LIGA");
    
    if (jumlahTim == 0) {
        cout << "Belum ada tim terdaftar.\n";
        cout << "Tekan Enter untuk kembali...";
        cin.get();
        return;
    }
    
    
    cout << "DAFTAR TIM:\n";
    tampilkanGaris('-', 70);
    cout << left 
         << setw(5) << "ID"
         << setw(25) << "Nama Tim"
         << setw(25) << "Stadion"
         << setw(10) << "Poin"
         << setw(15) << "Jumlah Pemain"
         << "\n";
    tampilkanGaris('-', 70);
    
    for (int i = 0; i < jumlahTim; i++) {
        cout << left 
             << setw(5) << daftarTim[i].id
             << setw(25) << daftarTim[i].namaTim.substr(0, 24)
             << setw(25) << daftarTim[i].stadion.substr(0, 24)
             << setw(10) << daftarTim[i].poin
             << setw(15) << daftarTim[i].jumlahPemain
             << "\n";
    }
    tampilkanGaris('=', 70);
    
    int idTim;
    cout << "\nMasukkan ID Tim yang akan dihapus: ";
    cin >> idTim;
    cin.ignore();
    
    int indeksHapus = -1;
    for (int i = 0; i < jumlahTim; i++) {
        if (daftarTim[i].id == idTim) {
            indeksHapus = i;
            break;
        }
    }
    
    if (indeksHapus == -1) {
        cout << "\nTim dengan ID " << idTim << " tidak ditemukan!\n";
    } else {
        string namaTimHapus = daftarTim[indeksHapus].namaTim;
        int jumlahPemainTerhapus = daftarTim[indeksHapus].jumlahPemain;
        
        cout << "\nAnda akan menghapus tim:\n";
        cout << "Nama Tim    : " << namaTimHapus << "\n";
        cout << "Stadion     : " << daftarTim[indeksHapus].stadion << "\n";
        cout << "Jumlah Pemain: " << jumlahPemainTerhapus << " pemain\n\n";
        cout << "Yakin ingin menghapus tim ini? (y/n): ";
        
        char konfirmasi;
        cin >> konfirmasi;
        cin.ignore();
        
        if (konfirmasi == 'y' || konfirmasi == 'Y') {
           
            for (int i = indeksHapus; i < jumlahTim - 1; i++) {
                daftarTim[i] = daftarTim[i + 1];
            }
            jumlahTim--;
            
            cout << "\nTim " << namaTimHapus << " berhasil dihapus dari liga!\n";
            if (jumlahPemainTerhapus > 0) {
                cout << jumlahPemainTerhapus << " pemain juga ikut terhapus.\n";
            }
        } else {
            cout << "\nPenghapusan dibatalkan.\n";
        }
    }
    
    cout << "\nTekan Enter untuk kembali...";
    cin.get();
}


void menuAdmin(User &currentUser) {
    int pilihan;
    bool running = true;
    
    do {
        clearScreen();
        tampilkanHeader("MENU ADMIN - AKSES PENUH");
        cout << "User: " << currentUser.username << " | " << currentUser.namaLengkap << "\n\n";
        cout << "1. Tambah Pemain ke Tim\n";
        cout << "2. Lihat Semua Tim\n";
        cout << "3. Tambah Tim Baru\n";
        cout << "4. Hapus Tim dari Liga\n";  
        cout << "5. Lihat Detail Tim dan Pemain\n";
        cout << "6. Logout\n\n";
        
        pilihan = inputAngka("Pilih menu (1-6): ");
        
        switch (pilihan) {
            case 1:
                tambahPemain();
                break;
            case 2:
                lihatSemuaTim();
                break;
            case 3:
                tambahTim();
                break;
            case 4:
                hapusTim();  
                break;
            case 5:
                lihatDetailTim();
                break;
            case 6:
                cout << "\nLogout berhasil!\n";
                running = false;
                break;
            default:
                cout << "\nPilihan tidak valid!\n";
                cout << "Tekan Enter untuk melanjutkan...";
                cin.get();
        }
    } while (running);
}


void menuUser(User &currentUser) {
    int pilihan;
    bool running = true;
    
    do {
        clearScreen();
        tampilkanHeader("MENU USER - HANYA MELIHAT");
        cout << "User: " << currentUser.username << " | " << currentUser.namaLengkap << "\n\n";
        cout << "1. Lihat Semua Tim\n";
        cout << "2. Lihat Detail Tim dan Pemain\n";
        cout << "3. Logout\n\n";
        
        pilihan = inputAngka("Pilih menu (1-3): ");
        
        switch (pilihan) {
            case 1:
                lihatSemuaTim();
                break;
            case 2:
                lihatDetailTim();
                break;
            case 3:
                cout << "\nLogout berhasil!\n";
                running = false;
                break;
            default:
                cout << "\nPilihan tidak valid!\n";
                cout << "Tekan Enter untuk melanjutkan...";
                cin.get();
        }
    } while (running);
}


void inisialisasiDataDefault() {
   
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
    
 
    if (jumlahTim == 0) {
        Tim tim1;
        tim1.id = nextIdTim++;
        tim1.namaTim = "Manchester City";
        tim1.stadion = "Etihad Stadium";
        tim1.tahunBerdiri = 1880;
        tim1.poin = 73;
        tim1.jumlahPemain = 0;
        daftarTim[jumlahTim++] = tim1;
        
        Tim tim2;
        tim2.id = nextIdTim++;
        tim2.namaTim = "Arsenal";
        tim2.stadion = "Emirates Stadium";
        tim2.tahunBerdiri = 1886;
        tim2.poin = 71;
        tim2.jumlahPemain = 0;
        daftarTim[jumlahTim++] = tim2;
        
        Tim tim3;
        tim3.id = nextIdTim++;
        tim3.namaTim = "Liverpool";
        tim3.stadion = "Anfield";
        tim3.tahunBerdiri = 1892;
        tim3.poin = 70;
        tim3.jumlahPemain = 0;
        daftarTim[jumlahTim++] = tim3;
    }
}

void menuAwal() {
    int pilihan;
    bool programRunning = true;
    User currentUser;
    
  
    inisialisasiDataDefault();
    
    do {
        clearScreen();
        tampilkanHeader("SISTEM MANAJEMEN LIGA PREMIER");
        cout << "Selamat datang di Sistem Manajemen Liga Premier\n\n";
        cout << "1. Registrasi Akun Baru\n";
        cout << "2. Login\n";
        cout << "3. Keluar\n\n";
        
        pilihan = inputAngka("Pilih menu (1-3): ");
        
        switch (pilihan) {
            case 1:
                registrasi();
                break;
            case 2:
                if (login(currentUser)) {
                    
                    if (currentUser.role == "Admin") {
                        menuAdmin(currentUser);
                    } else {
                        menuUser(currentUser);
                    }
                } else {
                    
                    programRunning = false;
                }
                break;
            case 3:
                cout << "\nTerima kasih telah menggunakan program ini!\n";
                programRunning = false;
                break;
            default:
                cout << "\nPilihan tidak valid!\n";
                cout << "Tekan Enter untuk melanjutkan...";
                cin.get();
        }
    } while (programRunning);
}


int main() {
    menuAwal();
    return 0;
}