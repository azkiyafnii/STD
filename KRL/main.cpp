#include "KRL.h"

int main() {
    Graph G;
    initGraph(G);
    int pilihan = 0;
    string nama, tujuan;
    int jarak, harga;
    adrStasiun asal = NULL, ramai = NULL;
    addStasiun(G, "Tangerang");
    addStasiun(G, "Duri");
    addStasiun(G, "Tanah_Abang");
    addStasiun(G, "Rangkas_Bitung");
    addStasiun(G, "Tanjung_Priok");
    addStasiun(G, "Kampung_Bandan");
    addStasiun(G, "Manggarai");
    addStasiun(G, "Bogor");
    addStasiun(G, "Jatinegara");
    addStasiun(G, "Cikarang");
    addRute(G, "Tangerang", "Duri", 50, 3000);


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
                addRute(G, nama, tujuan, jarak, harga);
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
