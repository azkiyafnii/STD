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
            cout << "  Ke: " << r->adrS->nama << ", Jarak: " << r->jarak << "KM , Harga: " << r->harga << endl;
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

adrRute findRute(Graph G, adrStasiun pStasiun, string stasiun){
    if (firstStasiun(G) == NULL || pStasiun == NULL ){
        return NULL;
    }else{
        adrRute p = firstRute(pStasiun);
        while(p != NULL && nama(adrS(p)) != stasiun){
            p = nextRute(p);
        }
        return p;
    }
}

void deleteFirstEdge(Graph &G, adrStasiun pStasiun){
    if (firstStasiun(G) == NULL || firstRute(pStasiun) == NULL){
        cout << "Daftar Stasiun atau Rute kosong" << endl;
    }else{
        adrRute p = firstRute(pStasiun);
        firstRute(pStasiun) = nextRute(p);
        p->nextRute = NULL;
    }
}

void deleteLastEdge(Graph &G, adrStasiun pStasiun){
    if (firstStasiun(G) == NULL || firstRute(pStasiun) == NULL){
        cout << "Daftar Stasiun atau Rute kosong" << endl;
    }else{
        adrRute Q = firstRute(pStasiun), prev = NULL;
        while (nextRute(Q) != NULL){
            prev = Q;
            Q = nextRute(Q);
        }
        if (prev == NULL){
            firstRute(pStasiun) = NULL;
        }else{
            nextRute(prev) = NULL;
        }
        Q->nextRute = NULL;
    }
}

void deleteAfterEdge(Graph &G, adrStasiun pStasiun, adrRute prec){
    if (prec != NULL && nextRute(prec) != NULL){
        adrRute p = nextRute(prec);
        nextRute(prec) = nextRute(p);
        p->nextRute = NULL;
    }
}

void deleteRute(Graph &G, adrStasiun pStasiun, adrRute pRute){
    if (pRute == firstRute(pStasiun)){
        deleteFirstEdge(G, pStasiun);
    }else if (nextRute(pRute) == NULL){
        deleteLastEdge(G, pStasiun);
    }else{
        adrRute prec = firstRute(pStasiun);
        while (nextRute(prec) != pRute){
            prec = nextRute(prec);
        }
        deleteAfterEdge(G, pStasiun, prec);
    }
}

void disconnect(Graph &G, string stasiunAsal, string stasiunTujuan){
    adrStasiun s1 = findStasiun(G, stasiunAsal);
    adrStasiun s2 = findStasiun(G, stasiunTujuan);

    if (s1 != NULL && s2 != NULL){
        adrRute r1 = findRute(G, s1, stasiunTujuan);
        adrRute r2 = findRute(G, s2, stasiunAsal);
        if (r1 != NULL && r2 != NULL){
            deleteRute(G, s1, r1);
            deleteRute(G, s2, r2);
        }
        if (r1 == NULL && r2 == NULL){
            cout << "Rute tidak ditemukan" << endl;
        }
    }else{
        cout << "Stasiun tidak ditemukan" << endl;
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
    if (firstStasiun(G)==NULL){
        cout << "Daftar Stasiun kosong" << endl;
        return;
    }

    adrStasiun p = firstStasiun(G), prev = NULL;

    while (p && nama(p) != namaStasiun){
        prev = p;
        p = nextStasiun(p);
    }

    if (p==NULL){
        cout << "Stasiun tidak ditemukan" << endl;
        return;
    }

    // Hapus semua rute yang terhubung ke stasiun
    adrRute r = firstRute(p);
    while (r!=NULL){
        disconnect(G, nama(p), nama(adrS(r)));
        r = firstRute(p);
    }

    if (prev==NULL){
        firstStasiun(G) = nextStasiun(p);
    }else{
        nextStasiun(prev) = nextStasiun(p);
    }
    p->nextStasiun = NULL;
}
/*
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
*/
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
