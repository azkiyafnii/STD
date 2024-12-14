#include "KRL.h"

void createStasiun(string name, adrStasiun &s) {
    s = new Stasiun;
    nama(s) = name;
    nextStasiun(s) = nullptr;
    firstRute(s) = nullptr;
}

void createRute(string newNamaStasiun, int jarak, int harga, adrRute &r) {
    r = new Rute;
    r->adrS = new Stasiun;
    nama(r->adrS) = newNamaStasiun;
    r->jarak = jarak;
    r->harga = harga;
    nextRute(r) = nullptr;
}

void initGraph(Graph &G) {
    firstStasiun(G) = nullptr;
}

void buildGraph(Graph &G) {
    initGraph(G);
    // Implementasi pembuatan graph sesuai kebutuhan
}

void printStasiun(Graph G) {
    adrStasiun p = firstStasiun(G);
    while (p != nullptr) {
        cout << "Stasiun: " << nama(p) << endl;
        p = nextStasiun(p);
    }
}

void printRute(Graph G) {
    adrStasiun p = firstStasiun(G);
    while (p != nullptr) {
        adrRute r = firstRute(p);
        cout << "Rute dari " << nama(p) << ":\n";
        while (r != nullptr) {
            cout << "  Ke: " << namaStasiun(r->adrS) << ", Jarak: " << jarak(r) << ", Harga: " << harga(r) << endl;
            r = nextRute(r);
        }
        p = nextStasiun(p);
    }
}

void addStasiun(Graph &G, string nama) {
    adrStasiun s;
    createStasiun(nama, s);
    nextStasiun(s) = firstStasiun(G);
    firstStasiun(G) = s;
}

void addRute(adrRute &r, string namaStasiun, int jarak, int harga) {
    adrRute newR;
    createRute(namaStasiun, jarak, harga, newR);
    nextRute(newR) = r;
    r = newR;
}

void deleteStasiun(Graph &G, string namaStasiun) {
    adrStasiun p = firstStasiun(G), q = nullptr;
    while (p != nullptr && nama(p) != namaStasiun) {
        q = p;
        p = nextStasiun(p);
    }
    if (p != nullptr) {
        if (q == nullptr) firstStasiun(G) = nextStasiun(p);
        else nextStasiun(q) = nextStasiun(p);
        delete p;
    }
}

void deleteRute(Graph &G, string namaStasiun, string namaStasiunTujuan) {
    adrStasiun p = firstStasiun(G);
    while (p != nullptr && nama(p) != namaStasiun) {
        p = nextStasiun(p);
    }
    if (p != nullptr) {
        adrRute r = firstRute(p), prev = nullptr;
        while (r != nullptr && namaStasiun(r->adrS) != namaStasiunTujuan) {
            prev = r;
            r = nextRute(r);
        }
        if (r != nullptr) {
            if (prev == nullptr) firstRute(p) = nextRute(r);
            else nextRute(prev) = nextRute(r);
            delete r;
        }
    }
}

int degree(Graph &G, adrStasiun v) {
    int count = 0;
    adrRute r = firstRute(v);
    while (r != nullptr) {
        count++;
        r = nextRute(r);
    }
    return count;
}

adrStasiun stasiunTeramai(Graph G) {
    adrStasiun p = firstStasiun(G), maxStasiun = nullptr;
    int maxDegree = -1;
    while (p != nullptr) {
        int d = degree(G, p);
        if (d > maxDegree) {
            maxDegree = d;
            maxStasiun = p;
        }
        p = nextStasiun(p);
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
