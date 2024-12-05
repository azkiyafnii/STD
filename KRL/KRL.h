#ifndef KRL_H_INCLUDED
#define KRL_H_INCLUDED
#define nama(s) s->nama
#define nextStasiun(s) s->nextStasiun
#define firstRute(s) s->firstRute
#define namaStasiun(r) r->namaStasiun
#define jarak(r) r->jarak
#define harga(r) r->harga
#define nextRute(r) r->nextRute
#define firstStasiun(G) G.firstStasiun

#include <iostream>

using namespace std;

typedef struct Stasiun* adrStasiun;
typedef struct Rute* adrRute;

struct Stasiun{
    string nama;
    adrStasiun nextStasiun;
    adrRute firstRute;
};

struct Rute {
    string namaStasiun;
    int jarak;
    int harga;
    adrRute nextRute;
};

struct Graph{
    adrStasiun firstStasiun;
};

void createStasiun(string nama , adrStasiun &s);
void addStasiun(Graph &G, string nama);
void initGraph(Graph &G);
void buildGraph(Graph &G);
void createRute(string newNamaStasiun, int jarak, int harga, adrRute &r);
void addRute(adrRute &r, string namaStasiun, int jarak, int harga);
void print(Graph G);
void addStasiun(Graph &G, string namaStasiun);
void addRute(Graph &G, string namaStasiun, string namaStasiunTujuan, int jarak, int harga);
void deleteStasiun(Graph &G, string namaStasiun);
void deleteRute(Graph &G, string namaStasiun, string namaStasiunTujuan);

#endif // KRL_H_INCLUDED
