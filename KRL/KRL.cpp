#include "KRL.h"

void createStasiun(string name, adrStasiun &s){
    s = new Stasiun;
    nama(s) = name;
    nextStasiun(s) = NULL;
    firstRute(s) = NULL;

}

void addStasiun(Graph &G, string nama){
    adrStasiun newStasiun;
    createStasiun(name, newStasiun);

    if (firstStasiun(s) == NULL) {
        firstStasiun(s) = newStasiun;
    } else {
        adrStasiun temp = firstStasiun(s);
        while (nextStasiun(temp) != NULL) {
            temp = nextStasiun(temp);
        }
        nextStasiun(temp) = newStasiun;
    }

}

void initGraph(Graph &G){
    firstStasiun(G) = NULL;

}

void createRute(string newNamaStasiun, int jarak, int harga, adrRute &r){
    r = new Rute;
    namaStasiun(v) = newNamaStasiun;
    jarak(r) = jarak;
    harga(r) = harga;
    nextRute(r) = NULL;
}

void addRute(adrRute &r, string namaStasiun, int jarak, int harga){
    adrRute p;
    createRute(namaStasiun, jarak, harga, p);
    if (firstRute(r) == NULL){
        firstRute(r) = p;
    }else{
        adrRute temp = firstRute(r);
        while (nextRute(temp) != NULL){
            temp = nextRute(temp);
        }
        nextRute(temp) = p;
    }

}

int degree(Graph &G, adrStasiun v){
    int count = 0;
    adrStasiun p = firstStasiun(G);
    while(p!=NULL){
        adrRute temp = firstRute(p);
        while(temp!=NULL){
            if (nama(v)==namaStasiun(temp)){
                count++;
            }
            temp = nextRute(temp);
        }
        p = nextStasiun(p);
    }

    adrRute e = firstRute(v);
    while(e!=NULL){
        count++;
        e = nextRute(e);
    }
    return count;
}

adrStasiun stasiunTeramai(G Graph){
    adrStasiun p = firstStasiun(G);
    adrStasiun pmaks = NULL;
    int temp, maks;
    maks = -1;
    while(p!=NULL){
        temp = degree(G,p);
        if (temp>maks){
            pmaks = p;
            maks = temp;
        }
        p = nextStasiun(p);
    }
    return pmaks;
}

void buildGraph(Graph &G);
void printStasiun(Graph G);
void printRute(Graph G);
void deleteStasiun(Graph &G, string namaStasiun);
void deleteRute(Graph &G, string namaStasiun, string namaStasiunTujuan);

void menu(){
    int input;
    while(input != 8){
            cout << "---------------------------------------------------" << endl;
            cout << "                       menu                        " << endl;
            cout << "---------------------------------------------------" << endl;
            cout << "1. menambahkan stasiun                             " << endl;
            cout << "2. tampilkan semua daftar stasiun                  " << endl;
            cout << "3. menambahkan rute                                " << endl;
            cout << "4. tampilkan rute stasiun                          " << endl;
            cout << "5. tampilkan rute termurah                         " << endl;
            cout << "6. tampilkan stasiun paling ramai                  " << endl;
            cout << "7. mencari jalur alternatif                        " << endl;
            cout << "8. keluar                                          " << endl;
            cout << "---------------------------------------------------" << endl;
            cout << "input : ";
            cin >> input;

        switch(input){
        case 1:{
            string nama;
            cout <<"masukan nama stasiun : " << endl;
            cin >> nama;
            addStasiun(G, nama);
            cout << "data telah ditambahkan ! ";
        }
        case 2:{
            printStasiun(G);
            cout << "semua data stasiun telah di tampilkan !";
        }
        case 3:{
            string nama, int jarak, int harga;
            cout << "masukan rute : " << endl;
            cout << "masukan jarak : " << endl;
            cout << "masukan harga : " << endl;
            cin >> nama;
            cin >> jarak;
            cin >> harga;
        }
        case 4:{
            printRute(G);
            cout << "semua data  rute telah di tampilkan !";
        }
        case 5:{

        }
        case 6:{

        }
        case 7:{

        }
        case 8:{
            break;
        }

        }
    }
}



