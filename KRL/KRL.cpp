#include "KRL.h"

void createStasiun(string name, adrStasiun &s) {
    s = new Stasiun;
    s->nama = name;
    s->nextStasiun = NULL;
    s->firstRute = NULL;
}

void createRute(string newNamaStasiun, int jarak, int harga, adrRute &r) {
    r = new Rute;
    r->adrS = new Stasiun;
    r->adrS->nama = newNamaStasiun;
    r->jarak = jarak;
    r->harga = harga;
    r->nextRute = NULL;
}

void initGraph(Graph &G) {
    G.firstStasiun = NULL;
}

void buildGraph(Graph &G) {
    string namaStasiun;
    cout << "Masukkan 0 untuk berhenti" << endl;
    cin >> namaStasiun;
    while (namaStasiun != "0") {
        bool isDuplicate = false;
        adrStasiun temp = G.firstStasiun;
        while (temp != NULL) {
            if (temp->nama == namaStasiun) {
                isDuplicate = true;
                break;
            }
            temp = temp->nextStasiun;
        }
        if (!isDuplicate) {
            addStasiun(G, namaStasiun);
        }
        cin >> namaStasiun;
    }
}

void printStasiun(Graph G) {
    adrStasiun p = G.firstStasiun;
    while (p != NULL) {
        cout << "Stasiun: " << p->nama << endl;
        p = p->nextStasiun;
    }
}

void printRute(Graph G) {
    adrStasiun p = G.firstStasiun;
    while (p != NULL) {
        adrRute r = p->firstRute;
        cout << "Rute dari " << p->nama << ":\n";
        while (r != NULL) {
            cout << "  Ke: " << r->adrS->nama << ", Jarak: " << r->jarak << ", Harga: " << r->harga << endl;
            r = r->nextRute;
        }
        p = p->nextStasiun;
    }
}

void addStasiun(Graph &G, string nama) {
    adrStasiun s;
    createStasiun(nama, s);
    if (firstStasiun(G)==NULL){
        firstStasiun(G) = s;
    }else{
        adrStasiun p = firstStasiun(G);
        while (nextStasiun(p)!=NULL){
            p = nextStasiun(p);
        }
        nextStasiun(p)=s;
    }
}

adrStasiun findStasiun(Graph G, string data){
    adrStasiun p;
    if (firstStasiun(G)==NULL){
        return NULL;
    }else{
        p = firstStasiun(G);
        while (nama(p) != data && nextStasiun(p)!=NULL){
            p = nextStasiun(p);
        }
        if (nama(p)==data){
            return p;
        }else{
            return NULL;
        }
    }
}

void insertLastRute(Graph &G, adrStasiun stasiunP, adrRute ruteP){
    adrRute p;
    if (stasiunP==NULL){
        cout << "Stasiun tidak ditemukan" << endl;
    }else if(firstRute(stasiunP)==NULL){
        firstRute(stasiunP) = ruteP;
    }else{
        p = firstRute(stasiunP);
        while (nextRute(p)!=NULL){
            p=nextRute(p);
        }
        nextRute(p)=ruteP;
    }
}

void addRute(Graph &G, string stasiunAsal, string stasiunTujuan, int jarak, int harga){
    adrStasiun p1 = findStasiun(G, stasiunAsal);
    adrStasiun p2 = findStasiun(G, stasiunTujuan);
    if (p1!=NULL && p2!=NULL){
        adrRute e1;
        createRute(stasiunTujuan, jarak, harga, e1);
        insertLastRute(G, p1, e1);
        adrRute e2;
        createRute(stasiunAsal, jarak, harga, e2);
        insertLastRute(G, p2, e2);
    }else{
        cout << "Stasiun tidak ditemukan" << endl;
    }
}

void deleteStasiun(Graph &G, string namaStasiun) {
    adrStasiun p = G.firstStasiun, q = NULL;
    while (p != NULL && p->nama != namaStasiun) {
        q = p;
        p = p->nextStasiun;
    }
    if (p != NULL) {
        if (q == NULL) G.firstStasiun = p->nextStasiun;
        else q->nextStasiun = p->nextStasiun;
        delete p;
    }
}

void deleteRute(Graph &G, string namaStasiun, string namaStasiunTujuan) {
    adrStasiun p = G.firstStasiun;
    while (p != NULL && p->nama != namaStasiun) {
        p = p->nextStasiun;
    }
    if (p != NULL) {
        adrRute r = p->firstRute, prev = NULL;
        while (r != NULL && r->adrS->nama != namaStasiunTujuan) {
            prev = r;
            r = r->nextRute;
        }
        if (r != NULL) {
            if (prev == NULL) p->firstRute = r->nextRute;
            else prev->nextRute = r->nextRute;
            delete r;
        }
    }
}

int degree(Graph &G, adrStasiun v) {
    int count = 0;
    adrRute r = v->firstRute;
    while (r != NULL) {
        count++;
        r = r->nextRute;
    }
    return count;
}

adrStasiun stasiunTeramai(Graph G) {
    adrStasiun p = G.firstStasiun, maxStasiun = NULL;
    int maxDegree = -1;
    while (p != NULL) {
        int d = degree(G, p);
        if (d > maxDegree) {
            maxDegree = d;
            maxStasiun = p;
        }
        p = p->nextStasiun;
    }
    return maxStasiun;
}

void menu() {
    cout << "Menu Graph KRL:\n";
    cout << "1. Tambah Stasiun\n";
    cout << "2. Tambah Rute\n";
    cout << "3. Hapus Stasiun\n";
    cout << "4. Hapus Rute\n";
    cout << "5. Cetak Stasiun\n";
    cout << "6. Cetak Rute\n";
    cout << "7. Stasiun Teramai\n";
    cout << "8. Keluar\n";
}
