#ifndef KRL_H_INCLUDED
#define KRL_H_INCLUDED
#include <iostream>
#define nama(s) s->nama
#define nextStasiun(s) s->nextStasiun
#define firstRute(s) s->firstRute
#define adrS(r) r->adrS
#define namaStasiun(r) r->namaStasiun
#define jarak(r) r->jarak
#define harga(r) r->harga
#define nextRute(r) r->nextRute
#define firstStasiun(G) G.firstStasiun

using namespace std;

typedef struct Stasiun* adrStasiun;
typedef struct Rute* adrRute;

struct Stasiun{
    string nama;
    adrStasiun nextStasiun;
    adrRute firstRute;
};

struct Rute {
    adrStasiun adrS;
    int jarak;
    int harga;
    adrRute nextRute;
};

struct Graph{
    adrStasiun firstStasiun;
};

void createStasiun(string name , adrStasiun &s);
void createRute(string newNamaStasiun, int jarak, int harga, adrRute &r);
void initGraph(Graph &G);
void buildGraph(Graph &G);
void printStasiun(Graph G);
void printRute(Graph G);
void addStasiun(Graph &G, string nama);
void addRute(adrRute &r, string namaStasiun, int jarak, int harga);
void deleteStasiun(Graph &G, string namaStasiun);
void deleteRute(Graph &G, string namaStasiun, string namaStasiunTujuan);
void menu();
int degree(Graph &G, adrStasiun v);
adrStasiun stasiunTeramai(Graph G);
#endif // KRL_H_INCLUDED
