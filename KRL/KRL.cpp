#include "KRL.h"

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
