#include "KRL.h"

int main() {
    Graph G;
    initGraph(G);
    int pilihan = 0;
    string nama, tujuan;
    int jarak, harga;
    adrStasiun asal = NULL, ramai = NULL;

    while (pilihan != 8) {
        menu();
        cout << "Pilih opsi: ";
        cin >> pilihan;
        switch (pilihan) {
            case 1:
                buildGraph(G);
                break;
            case 2:
                cout << "Masukkan nama stasiun asal: ";
                cin >> nama;
                cout << "Masukkan nama stasiun tujuan: ";
                cin >> tujuan;
                cout << "Masukkan jarak: ";
                cin >> jarak;
                cout << "Masukkan harga: ";
                cin >> harga;
                asal = G.firstStasiun;
                while (asal != NULL && asal->nama != nama) asal = asal->nextStasiun;
                if (asal != NULL) addRute(asal->firstRute, tujuan, jarak, harga);
                break;
            case 3:
                cout << "Masukkan nama stasiun yang akan dihapus: ";
                cin >> nama;
                deleteStasiun(G, nama);
                break;
            case 4:
                cout << "Masukkan nama stasiun asal: ";
                cin >> nama;
                cout << "Masukkan nama stasiun tujuan: ";
                cin >> tujuan;
                deleteRute(G, nama, tujuan);
                break;
            case 5:
                printStasiun(G);
                break;
            case 6:
                printRute(G);
                break;
            case 7:
                ramai = stasiunTeramai(G);
                if (ramai != NULL) cout << "Stasiun teramai: " << ramai->nama << endl;
                else cout << "Tidak ada stasiun." << endl;
                break;
            case 8:
                cout << "Keluar dari program." << endl;
                break;
            default:
                cout << "Opsi tidak valid!" << endl;
        }
    }
    return 0;
}
