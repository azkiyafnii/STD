#ifndef KRL_H_INCLUDED
#define KRL_H_INCLUDED
#include <iostream>
#define nama(s) s->nama
#define nextStasiun(s) s->nextStasiun
#define firstRute(s) s->firstRute
#define adrS(r) r->adrS
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
void deleteStasiun(Graph &G, string namaStasiun);
void menu();
int degree(Graph &G, adrStasiun v);
adrStasiun stasiunTeramai(Graph G);
adrStasiun findStasiun(Graph G, string data);
void insertLastRute(Graph &G, adrStasiun stasiunP, adrRute ruteP);
void addRute(Graph &G, string stasiunAsal, string stasiunTujuan, int jarak, int harga);
adrRute findRute(Graph G, adrStasiun pStasiun, string stasiun);
void deleteFirstRute(Graph &G, adrStasiun pStasiun);
void deleteLastRute(Graph &G, adrStasiun pStasiun);
void deleteAfterRute(Graph &G, adrStasiun pStasiun, adrRute prec);
void deleteRute(Graph &G, adrStasiun pStasiun, adrRute pRute);
void disconnect(Graph &G, string stasiunAsal, string stasiunTujuan);
void mencariJalurTerpendek(Graph G, string asal, string tujuan);
void mencariJalurAlternatif(Graph G, string asal, string tujuan, string problemFrom, string problemTo);

#endif // KRL_H_INCLUDED
