#include "KRL.h"

int main() {
    Graph G;
    initGraph(G);
    int pilihan = -1;
    string nama, tujuan, problemFrom, problemTo;
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
    addRute(G, "Tangerang", "Duri", 23, 3000);
    addRute(G, "Duri", "Tanah_Abang", 4, 3000);
    addRute(G, "Tanah_Abang", "Kampung_Bandan", 9, 3000);
    addRute(G, "Tanah_Abang", "Manggarai", 4, 3000);
    addRute(G, "Tanah_Abang", "Rangkas_Bitung", 72, 8000);
    addRute(G, "Manggarai", "Bogor", 48, 5000);
    addRute(G, "Manggarai", "Jatinegara", 4, 3000);
    addRute(G, "Manggarai", "Kampung_Bandan", 11, 3000);
    addRute(G, "Jatinegara", "Cikarang", 25, 5000);
    addRute(G, "Jatinegara", "Kampung_Bandan", 21, 3000);
    addRute(G, "Kampung_Bandan", "Tanjung_Priok", 9, 3000);



    while (pilihan != 0) {
        menu();
        cout << "Pilih opsi: ";
        cin >> pilihan;
        switch (pilihan) {
            case 1:
                cout << "Masukkan nama stasiun baru: ";
                cin >> nama;
                addStasiun(G, nama);
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
                disconnect(G, nama, tujuan);
                break;
            case 5:
                printStasiun(G);
                break;
            case 6:
                printRute(G);
                break;
            case 7:
                ramai = stasiunTeramai(G);
                if (ramai != NULL) {
                    cout << "Stasiun teramai: " << nama(ramai) << endl;
                }else{
                    cout << "Tidak ada stasiun." << endl;
                }
                break;
            case 8:
                cout << "Masukkan stasiun asal: ";
                cin >> nama;
                cout << "Masukkan stasiun tujuan: ";
                cin >> tujuan;
                mencariJalurTerpendek(G, nama, tujuan);
                break;
            case 9:
                cout << "Masukkan stasiun asal: ";
                cin >> nama;
                cout << "Masukkan stasiun tujuan: ";
                cin >> tujuan;
                cout << "Masukkan stasiun awal rute bermasalah: ";
                cin >> problemFrom;
                cout << "Masukkan stasiun tujuan rute bermasalah: ";
                cin >> problemTo;
                mencariJalurAlternatif(G, nama, tujuan, problemFrom, problemTo);
                break;
            case 0:
                cout << "Keluar dari program." << endl;
                break;
            default:
                cout << "Opsi tidak valid!" << endl;
        }
    }
    return 0;
}
