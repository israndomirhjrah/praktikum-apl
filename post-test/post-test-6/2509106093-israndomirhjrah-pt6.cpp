#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>

using namespace std;

const size_t MAX_STREAM_SIZE = 1000;
const int INT_MIN_VALUE = -2147483648;
const int INT_MAX_VALUE = 2147483647;

void clearInputBuffer() {
    cin.ignore(MAX_STREAM_SIZE, '\n');
}

void clearScreenManual() {
    for (int i = 0; i < 50; i++) {
        cout << endl;
    }
}

int Integer(string pesan, int minValue, int maxValue) {
    int angka;
    bool valid = false;

    while (!valid) {
        cout << pesan;
        cin >> angka;

        if (cin.fail()) {
            cin.clear();
            clearInputBuffer();
            cout << "Input harus berupa angka! Silakan coba lagi.\n";
        } else if (angka < minValue || angka > maxValue) {
            cout << "Input harus antara " << minValue << " - " << maxValue << "! Silakan coba lagi.\n";
            clearInputBuffer();
        } else {
            clearInputBuffer();
            valid = true;
        }
    }
    return angka;
}

int Integer(string pesan) {
    return Integer(pesan, INT_MIN_VALUE, INT_MAX_VALUE);
}

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

struct UserNode {
    User data;
    UserNode* next;
};

class UserDatabase {
private:
    UserNode* head;
    int size;

public:
    UserDatabase() : head(nullptr), size(0) {}

    ~UserDatabase() {
        UserNode* current = head;
        while (current != nullptr) {
            UserNode* temp = current;
            current = current->next;
            delete temp;
        }
    }

    bool addUser(User user) {
        if (findUser(user.username) != nullptr) {
            return false;
        }

        UserNode* newNode = new UserNode;
        newNode->data = user;
        newNode->next = head;
        head = newNode;
        size++;
        return true;
    }

    User* findUser(string username) {
        UserNode* current = head;
        while (current != nullptr) {
            if (current->data.username == username) {
                return &(current->data);
            }
            current = current->next;
        }
        return nullptr;
    }

    int getSize() { return size; }
};

const int MAKS_TIM = 20;
UserDatabase databaseUsers;

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

void tambahPoinTim(Tim* tim, int poin) {
    (*tim).poin += poin;
}

void updateStatistikPemain(Pemain* pemain, int golBaru, int assistBaru) {
    pemain->gol += golBaru;
    pemain->assist += assistBaru;
}

void tambahPemainKeTim(Tim* tim, Pemain* pemainBaru, bool* berhasil) {
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
    if (indeks >= jumlahPemain) return 0;
    return skuad[indeks].gol + hitungTotalGol(skuad, indeks + 1, jumlahPemain);
}

int hitungTotalAssist(Pemain* skuad, int indeks, int jumlahPemain) {
    if (indeks >= jumlahPemain) return 0;
    return skuad[indeks].assist + hitungTotalAssist(skuad, indeks + 1, jumlahPemain);
}

void tampilkanPemain(Pemain* skuad, int indeks, int jumlahPemain) {
    if (indeks >= jumlahPemain) return;

    cout << left
         << setw(5)  << indeks + 1
         << setw(25) << skuad[indeks].namaPemain.substr(0, 24)
         << setw(15) << skuad[indeks].nomorPunggung
         << setw(15) << skuad[indeks].posisi.substr(0, 14)
         << setw(10) << skuad[indeks].gol
         << setw(10) << skuad[indeks].assist
         << "\n";

    tampilkanPemain(skuad, indeks + 1, jumlahPemain);
}

void clearScreen() {
    clearScreenManual();
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
        if (daftarTim[i].id == idTim) return i;
    }
    return -1;
}

int cariTim(string namaTim, int jumlahTim, Tim daftarTim[]) {
    for (int i = 0; i < jumlahTim; i++) {
        if (daftarTim[i].namaTim == namaTim) return i;
    }
    return -1;
}

void sortTimById(Tim* daftarTim, int jumlahTim) {

    for (int i = 1; i < jumlahTim; i++) {
        Tim key = daftarTim[i];
        int j   = i - 1;
        while (j >= 0 && daftarTim[j].id > key.id) {
            daftarTim[j + 1] = daftarTim[j];
            j--;
        }
        daftarTim[j + 1] = key;
    }
}

int binarySearchTimById(Tim* daftarTim, int* jumlahTim, int* targetId) {

    Tim* timSorted = new Tim[*jumlahTim];
    for (int i = 0; i < *jumlahTim; i++) {
        timSorted[i] = daftarTim[i];
    }
    sortTimById(timSorted, *jumlahTim);

    int kiri   = 0;
    int kanan  = *jumlahTim - 1;
    int hasil  = -1;

    while (kiri <= kanan) {
        int tengah = kiri + (kanan - kiri) / 2;

        if (timSorted[tengah].id == *targetId) {

            for (int i = 0; i < *jumlahTim; i++) {
                if (daftarTim[i].id == *targetId) {
                    hasil = i;
                    break;
                }
            }
            break;
        } else if (timSorted[tengah].id < *targetId) {
            kiri = tengah + 1;
        } else {
            kanan = tengah - 1;
        }
    }

    delete[] timSorted;
    return hasil;
}

string toLower(string str) {
    string hasil = str;
    transform(hasil.begin(), hasil.end(), hasil.begin(), ::tolower);
    return hasil;
}

int sequentialSearchTimByNama(Tim* daftarTim, int* jumlahTim, string* keyword, int* hasilIndeks) {
    string keyLower = toLower(*keyword);
    int jumlahHasil = 0;

    for (int i = 0; i < *jumlahTim; i++) {
        string namaLower = toLower(daftarTim[i].namaTim);

        if (namaLower.find(keyLower) != string::npos) {
            hasilIndeks[jumlahHasil] = i;
            jumlahHasil++;
        }
    }
    return jumlahHasil;
}

void menuCariTimById(Tim* daftarTim, int* jumlahTim, int* nextIdTim) {
    clearScreen();
    tampilkanHeader("CARI TIM BERDASARKAN ID");
    tampilkanGaris('-', 50);

    if (*jumlahTim == 0) {
        tampilkanPesan("Belum ada tim terdaftar.", true);
        return;
    }

    cout << "\nID Tim yang tersedia: ";
    for (int i = 0; i < *jumlahTim; i++) {
        cout << daftarTim[i].id;
        if (i < *jumlahTim - 1) cout << ", ";
    }
    cout << "\n\n";

    int targetId = Integer("Masukkan ID Tim yang dicari: ", 1, INT_MAX_VALUE);
    int* pTargetId = &targetId;

    cout << "\nMencari tim dengan ID = " << targetId << " ...\n";
    tampilkanGaris('-', 50);

    int indeks = binarySearchTimById(daftarTim, jumlahTim, pTargetId);

    if (indeks == -1) {
        cout << "\n[TIDAK DITEMUKAN] Tim dengan ID " << targetId << " tidak ada dalam database.\n";
    } else {
        cout << "\n[DITEMUKAN] Tim dengan ID " << targetId << " berhasil ditemukan!\n\n";
        cout << left
             << setw(5)  << "ID"
             << setw(25) << "Nama Tim"
             << setw(25) << "Stadion"
             << setw(15) << "Tahun"
             << setw(10) << "Poin"
             << setw(15) << "Pemain"
             << "\n";
        tampilkanGaris('-', 95);
        cout << left
             << setw(5)  << daftarTim[indeks].id
             << setw(25) << daftarTim[indeks].namaTim.substr(0, 24)
             << setw(25) << daftarTim[indeks].stadion.substr(0, 24)
             << setw(15) << daftarTim[indeks].tahunBerdiri
             << setw(10) << daftarTim[indeks].poin
             << setw(15) << daftarTim[indeks].jumlahPemain
             << "\n";
        tampilkanGaris('=', 95);
    }

    cout << "\nTekan Enter untuk kembali...";
    cin.get();
}

void menuCariTimByNama(Tim* daftarTim, int* jumlahTim) {
    clearScreen();
    tampilkanHeader("CARI TIM BERDASARKAN NAMA");
    tampilkanGaris('-', 50);

    if (*jumlahTim == 0) {
        tampilkanPesan("Belum ada tim terdaftar.", true);
        return;
    }

    cout << "Masukkan nama tim (atau sebagian nama): ";
    string keyword;
    getline(cin, keyword);
    string* pKeyword = &keyword;

    int hasilIndeks[MAKS_TIM];
    int jumlahHasil = sequentialSearchTimByNama(daftarTim, jumlahTim, pKeyword, hasilIndeks);

    cout << "\nMencari tim dengan kata kunci \"" << keyword << "\" ...\n";
    tampilkanGaris('-', 95);

    if (jumlahHasil == 0) {
        cout << "\n[TIDAK DITEMUKAN] Tidak ada tim dengan nama yang mengandung \"" << keyword << "\".\n";
    } else {
        cout << "\n[DITEMUKAN] " << jumlahHasil << " tim ditemukan:\n\n";
        cout << left
             << setw(5)  << "ID"
             << setw(25) << "Nama Tim"
             << setw(25) << "Stadion"
             << setw(15) << "Tahun"
             << setw(10) << "Poin"
             << setw(15) << "Pemain"
             << "\n";
        tampilkanGaris('-', 95);

        for (int i = 0; i < jumlahHasil; i++) {
            int idx = hasilIndeks[i];
            cout << left
                 << setw(5)  << daftarTim[idx].id
                 << setw(25) << daftarTim[idx].namaTim.substr(0, 24)
                 << setw(25) << daftarTim[idx].stadion.substr(0, 24)
                 << setw(15) << daftarTim[idx].tahunBerdiri
                 << setw(10) << daftarTim[idx].poin
                 << setw(15) << daftarTim[idx].jumlahPemain
                 << "\n";
        }
        tampilkanGaris('=', 95);
    }

    cout << "\nTekan Enter untuk kembali...";
    cin.get();
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
        if (tim.skuad[i].nomorPunggung == nomor) return false;
    }
    return true;
}

int inputAngka(string pesan, int minValue, int maxValue) {
    return Integer(pesan, minValue, maxValue);
}

int inputAngka(string pesan) {
    return Integer(pesan);
}

bool registrasi(User* userBaru) {
    if (databaseUsers.findUser(userBaru->username) != nullptr) return false;
    if (userBaru->password.length() < 6) return false;

    userBaru->role = "User";
    return databaseUsers.addUser(*userBaru);
}

bool loginUser(string username, string password, User* currentUser) {
    User* user = databaseUsers.findUser(username);
    if (user != nullptr && user->password == password) {
        *currentUser = *user;
        return true;
    }
    return false;
}

bool tambahTimBaru(Tim* daftarTim, int* jumlahTim, int* nextId, Tim* timBaru) {
    if (*jumlahTim >= MAKS_TIM) return false;

    timBaru->id            = (*nextId)++;
    timBaru->jumlahPemain  = 0;
    timBaru->kapasitasPemain = 11;
    timBaru->skuad         = new Pemain[timBaru->kapasitasPemain];

    daftarTim[*jumlahTim]  = *timBaru;
    (*jumlahTim)++;
    return true;
}

bool tambahPemainBaru(Tim* tim, Pemain* pemainBaru) {
    if (tim->jumlahPemain >= tim->kapasitasPemain) return false;
    tim->skuad[tim->jumlahPemain] = *pemainBaru;
    tim->jumlahPemain++;
    return true;
}

bool hapusTimDariLiga(Tim* daftarTim, int* jumlahTim, int idTim) {
    int indeks = cariTim(idTim, *jumlahTim, daftarTim);
    if (indeks == -1) return false;

    delete[] daftarTim[indeks].skuad;
    daftarTim[indeks].skuad = nullptr;

    for (int i = indeks; i < *jumlahTim - 1; i++) {
        daftarTim[i] = daftarTim[i + 1];
    }
    daftarTim[*jumlahTim - 1].skuad = nullptr;
    (*jumlahTim)--;
    return true;
}

void tampilkanStatistikTim(Tim* tim) {
    cout << "\n=== STATISTIK TIM: " << tim->namaTim << " ===\n";
    cout << "Total Gol Semua Pemain    : " << hitungTotalGol(tim->skuad, 0, tim->jumlahPemain) << endl;
    cout << "Total Assist Semua Pemain : " << hitungTotalAssist(tim->skuad, 0, tim->jumlahPemain) << endl;

    if (tim->jumlahPemain > 0) {
        Pemain* topScorer = &(tim->skuad[0]);
        for (int i = 1; i < tim->jumlahPemain; i++) {
            if (tim->skuad[i].gol > topScorer->gol) {
                topScorer = &(tim->skuad[i]);
            }
        }
        cout << "Top Scorer                : " << topScorer->namaPemain
             << " (" << topScorer->gol << " gol)" << endl;
    }
}

void NamaAscending(Tim* daftarTim, int jumlahTim) {
    for (int i = 0; i < jumlahTim - 1; i++) {
        for (int j = 0; j < jumlahTim - i - 1; j++) {
            if (daftarTim[j].namaTim > daftarTim[j + 1].namaTim) {
                Tim temp        = daftarTim[j];
                daftarTim[j]    = daftarTim[j + 1];
                daftarTim[j + 1] = temp;
            }
        }
    }
}

void PoinDescending(Tim* daftarTim, int jumlahTim) {
    for (int i = 0; i < jumlahTim - 1; i++) {
        int maxIdx = i;
        for (int j = i + 1; j < jumlahTim; j++) {
            if (daftarTim[j].poin > daftarTim[maxIdx].poin) {
                maxIdx = j;
            }
        }
        if (maxIdx != i) {
            Tim temp          = daftarTim[i];
            daftarTim[i]      = daftarTim[maxIdx];
            daftarTim[maxIdx] = temp;
        }
    }
}

void TahunAscending(Tim* daftarTim, int jumlahTim) {
    for (int i = 1; i < jumlahTim; i++) {
        Tim key = daftarTim[i];
        int j   = i - 1;
        while (j >= 0 && daftarTim[j].tahunBerdiri > key.tahunBerdiri) {
            daftarTim[j + 1] = daftarTim[j];
            j--;
        }
        daftarTim[j + 1] = key;
    }
}

void tampilkanTim(Tim* daftarTim, int jumlahTim, string metode) {
    clearScreen();
    tampilkanHeader("DAFTAR TIM - " + metode);

    if (jumlahTim == 0) {
        tampilkanPesan("Belum ada tim terdaftar.", true);
        return;
    }

    cout << left
         << setw(5)  << "ID"
         << setw(25) << "Nama Tim"
         << setw(25) << "Stadion"
         << setw(15) << "Tahun"
         << setw(10) << "Poin"
         << setw(15) << "Pemain"
         << "\n";
    tampilkanGaris('-', 95);

    for (int i = 0; i < jumlahTim; i++) {
        cout << left
             << setw(5)  << daftarTim[i].id
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

void registrasiMenu() {
    clearScreen();
    tampilkanHeader("REGISTRASI AKUN BARU");

    User userBaru;

    cout << "Masukkan Username: ";
    getline(cin, userBaru.username);
    cout << "Masukkan Password (minimal 6 karakter): ";
    getline(cin, userBaru.password);
    cout << "Masukkan Nama Lengkap: ";
    getline(cin, userBaru.namaLengkap);

    if (registrasi(&userBaru)) {
        cout << "\n==========================================\n";
        cout << "         REGISTRASI BERHASIL!\n";
        cout << "==========================================\n";
        cout << "Username    : " << userBaru.username << "\n";
        cout << "Nama        : " << userBaru.namaLengkap << "\n";
        cout << "Role        : User\n";
        cout << "==========================================\n";
        cout << "Silakan login menggunakan akun Anda.\n";
    } else {
        cout << "\n==========================================\n";
        cout << "           REGISTRASI GAGAL!\n";
        cout << "==========================================\n";
        if (databaseUsers.findUser(userBaru.username) != nullptr) {
            cout << "Username '" << userBaru.username << "' sudah digunakan!\n";
        } else if (userBaru.password.length() < 6) {
            cout << "Password harus minimal 6 karakter!\n";
        } else {
            cout << "Terjadi kesalahan saat registrasi.\n";
        }
        cout << "==========================================\n";
    }
    cout << "\nTekan Enter untuk melanjutkan...";
    cin.get();
}

bool loginMenu(User* currentUser) {
    string username, password;
    int percobaan     = 0;
    const int maxPercobaan = 3;

    while (percobaan < maxPercobaan) {
        clearScreen();
        tampilkanHeader("MENU LOGIN");
        cout << "Username: ";
        getline(cin, username);
        cout << "Password: ";
        getline(cin, password);

        if (loginUser(username, password, currentUser)) {
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
    cout << "\nAnda telah gagal login sebanyak " << maxPercobaan << " kali.\n";
    cout << "Tekan Enter untuk kembali ke menu utama...";
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
         << setw(5)  << "ID"
         << setw(25) << "Nama Tim"
         << setw(25) << "Stadion"
         << setw(15) << "Tahun"
         << setw(10) << "Poin"
         << setw(15) << "Pemain"
         << "\n";
    tampilkanGaris('-', 95);

    for (int i = 0; i < *jumlahTim; i++) {
        cout << left
             << setw(5)  << daftarTim[i].id
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
        tampilkanGaris('-', 80);
        cout << left
             << setw(5)  << "No"
             << setw(25) << "Nama Pemain"
             << setw(15) << "No Punggung"
             << setw(15) << "Posisi"
             << setw(10) << "Gol"
             << setw(10) << "Assist"
             << "\n";
        tampilkanGaris('-', 80);
        tampilkanPemain(daftarTim[indeksTim].skuad, 0, daftarTim[indeksTim].jumlahPemain);
        tampilkanGaris('=', 80);
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
    timBaru.skuad = nullptr;

    cout << "Nama Tim: ";
    getline(cin, timBaru.namaTim);
    cout << "Stadion: ";
    getline(cin, timBaru.stadion);

    do {
        timBaru.tahunBerdiri = inputAngka("Tahun Berdiri (1800-2024): ", 1800, 2024);
    } while (!validasiTahunBerdiri(timBaru.tahunBerdiri));

    timBaru.poin = inputAngka("Poin Awal (0-100): ", 0, 100);

    if (tambahTimBaru(daftarTim, jumlahTim, nextIdTim, &timBaru)) {
        tampilkanPesan("\nTim " + timBaru.namaTim + " berhasil ditambahkan! ID Tim: " +
                       to_string(daftarTim[*jumlahTim - 1].id), true);
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
        tampilkanPesan("Tim sudah mencapai kapasitas maksimal (" +
                       to_string(daftarTim[indeksTim].kapasitasPemain) + " pemain)!", true);
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
    pemainBaru.gol    = inputAngka("Jumlah Gol: ", 0, 999);
    pemainBaru.assist = inputAngka("Jumlah Assist: ", 0, 999);

    bool berhasil = false;
    tambahPemainKeTim(&daftarTim[indeksTim], &pemainBaru, &berhasil);

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
    cout << "Nama Tim      : " << daftarTim[indeksHapus].namaTim << "\n";
    cout << "Stadion       : " << daftarTim[indeksHapus].stadion << "\n";
    cout << "Jumlah Pemain : " << daftarTim[indeksHapus].jumlahPemain << " pemain\n\n";
    cout << "Yakin ingin menghapus tim ini? (y/n): ";

    char konfirmasi;
    cin >> konfirmasi;
    clearInputBuffer();

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

void menuSearching(Tim* daftarTim, int* jumlahTim, int* nextIdTim) {
    int pilihan;
    bool running = true;

    do {
        clearScreen();
        tampilkanHeader("MENU PENCARIAN TIM");
        cout << "Pilih metode pencarian:\n\n";
        cout << "1. Cari Tim berdasarkan ID\n";
        cout << "2. Cari Tim berdasarkan Nama\n";
        cout << "3. Kembali\n\n";

        pilihan = inputAngka("Pilih menu (1-3): ", 1, 3);

        switch (pilihan) {
            case 1: menuCariTimById(daftarTim, jumlahTim, nextIdTim);  break;
            case 2: menuCariTimByNama(daftarTim, jumlahTim);           break;
            case 3: running = false;                                    break;
        }
    } while (running);
}

void menuAdmin(User* currentUser, Tim* daftarTim, int* jumlahTim, int* nextIdTim) {
    int  pilihan;
    bool running = true;
    Tim  timTemp[MAKS_TIM];

    do {
        clearScreen();
        tampilkanHeader("MENU ADMIN");
        cout << "User: " << currentUser->username << " | " << currentUser->namaLengkap << "\n\n";
        cout << "1. Tambah Pemain ke Tim\n";
        cout << "2. Lihat Semua Tim\n";
        cout << "3. Tambah Tim Baru\n";
        cout << "4. Hapus Tim dari Liga\n";
        cout << "5. Lihat Detail Tim dan Pemain\n";
        cout << "6. Cari Tim\n";
        cout << "7. Logout\n\n";

        pilihan = inputAngka("Pilih menu (1-7): ", 1, 7);

        switch (pilihan) {
            case 1: tambahPemainMenu(daftarTim, jumlahTim, nextIdTim);  break;
            case 2: lihatSemuaTim(daftarTim, jumlahTim);                break;
            case 3: tambahTimMenu(daftarTim, jumlahTim, nextIdTim);     break;
            case 4: hapusTimMenu(daftarTim, jumlahTim, nextIdTim);      break;
            case 5: lihatDetailTim(daftarTim, jumlahTim, nextIdTim);    break;
            case 6:
                menuSearching(daftarTim, jumlahTim, nextIdTim);
                break;
            case 7:
                cout << "\nLogout berhasil!\n";
                running = false;
                break;
        }
    } while (running);
}

void menuUser(User* currentUser, Tim* daftarTim, int* jumlahTim, int* nextIdTim) {
    int  pilihan;
    bool running = true;
    Tim  timTemp[MAKS_TIM];

    do {
        clearScreen();
        tampilkanHeader("MENU USER");
        cout << "User: " << currentUser->username << " | " << currentUser->namaLengkap << "\n\n";
        cout << "1. Lihat Semua Tim\n";
        cout << "2. Lihat Detail Tim dan Pemain\n";
        cout << "3. Cari Tim\n";
        cout << "4. Logout\n\n";

        pilihan = inputAngka("Pilih menu (1-4): ", 1, 4);

        switch (pilihan) {
            case 1: lihatSemuaTim(daftarTim, jumlahTim);              break;
            case 2: lihatDetailTim(daftarTim, jumlahTim, nextIdTim);  break;
            case 3:
                menuSearching(daftarTim, jumlahTim, nextIdTim);
                break;
            case 4:
                cout << "\nLogout berhasil!\n";
                running = false;
                break;
        }
    } while (running);
}

void inisialisasiData(Tim* daftarTim, int* jumlahTim, int* nextIdTim) {
    User admin;
    admin.username    = "rando";
    admin.password    = "2509106093";
    admin.namaLengkap = "Administrator";
    admin.role        = "Admin";
    databaseUsers.addUser(admin);

    User user;
    user.username    = "rando1";
    user.password    = "093";
    user.namaLengkap = "User";
    user.role        = "User";
    databaseUsers.addUser(user);

    if (*jumlahTim == 0) {
        inisialisasiTim(&daftarTim[*jumlahTim], (*nextIdTim)++,
                        "Manchester City", "Etihad Stadium", 1880, 73);
        (*jumlahTim)++;

        inisialisasiTim(&daftarTim[*jumlahTim], (*nextIdTim)++,
                        "Arsenal", "Emirates Stadium", 1886, 71);
        (*jumlahTim)++;

        inisialisasiTim(&daftarTim[*jumlahTim], (*nextIdTim)++,
                        "Liverpool", "Anfield", 1892, 70);
        (*jumlahTim)++;
    }
}

void cleanupData(Tim* daftarTim, int* jumlahTim) {
    for (int i = 0; i < *jumlahTim; i++) {
        delete[] daftarTim[i].skuad;
        daftarTim[i].skuad = nullptr;
    }
    *jumlahTim = 0;
}

int main() {
    Tim daftarTim[MAKS_TIM];
    int jumlahTim = 0;
    int nextIdTim = 1;

    for (int i = 0; i < MAKS_TIM; i++) {
        daftarTim[i].skuad = nullptr;
    }

    inisialisasiData(daftarTim, &jumlahTim, &nextIdTim);

    int  pilihan;
    bool appRunning = true;

    while (appRunning) {
        clearScreen();
        tampilkanHeader("SISTEM MANAJEMEN LIGA SEPAK BOLA");
        cout << "1. Login\n";
        cout << "2. Registrasi\n";
        cout << "3. Keluar\n\n";

        pilihan = inputAngka("Pilih menu (1-3): ", 1, 3);

        switch (pilihan) {
            case 1: {
                User currentUser;
                if (loginMenu(&currentUser)) {
                    if (currentUser.role == "Admin") {
                        menuAdmin(&currentUser, daftarTim, &jumlahTim, &nextIdTim);
                    } else {
                        menuUser(&currentUser, daftarTim, &jumlahTim, &nextIdTim);
                    }
                }
                break;
            }
            case 2:
                registrasiMenu();
                break;
            case 3:
                cout << "\nTerima kasih! Sampai jumpa.\n";
                appRunning = false;
                break;
        }
    }

    cleanupData(daftarTim, &jumlahTim);
    return 0;
}