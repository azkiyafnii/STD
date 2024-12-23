#include "KRL.h"

void createStasiun(string name, adrStasiun &s) {
    s = new Stasiun;
    nama(s) = name;
    nextStasiun(s) = NULL;
    firstRute(s) = NULL;
}

void createRute(string newNamaStasiun, int jarak, int harga, adrRute &r) {
    r = new Rute;
    adrS(r) = new Stasiun;
    nama(adrS(r)) = newNamaStasiun;
    jarak(r) = jarak;
    harga(r) = harga;
    nextRute(r) = NULL;
}

void initGraph(Graph &G) {
    firstStasiun(G) = NULL;
}

void printStasiun(Graph G) {
    cout << "------------------Daftar Stasiun--------------------" << endl;
    adrStasiun p = firstStasiun(G);
    while (p != NULL) {
        cout << "Stasiun: " << nama(p) << endl;
        p = nextStasiun(p);
    }
}

void printRute(Graph G) {
    cout << "-------------------Daftar Rute----------------------\n" ;
    adrStasiun p = firstStasiun(G);
    while (p != NULL) {
        adrRute r = firstRute(p);
        cout << "Rute dari " << nama(p) << ":\n";
        while (r != NULL) {
            cout << "  Ke: " << nama(adrS(r)) << ", Jarak: " << jarak(r) << "KM, Harga: " << harga(r) << endl;
            r = nextRute(r);
        }
        p = nextStasiun(p);
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

void deleteFirstRute(Graph &G, adrStasiun pStasiun){
    if (firstStasiun(G) == NULL || firstRute(pStasiun) == NULL){
        cout << "Daftar Stasiun atau Rute kosong" << endl;
    }else{
        adrRute p = firstRute(pStasiun);
        firstRute(pStasiun) = nextRute(p);
        nextRute(p) = NULL;
    }
}

void deleteLastRute(Graph &G, adrStasiun pStasiun){
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
        nextRute(Q)= NULL;
    }
}

void deleteAfterRute(Graph &G, adrStasiun pStasiun, adrRute prec){
    if (prec != NULL && nextRute(prec) != NULL){
        adrRute p = nextRute(prec);
        nextRute(prec) = nextRute(p);
        nextRute(p) = NULL;
    }
}

void deleteRute(Graph &G, adrStasiun pStasiun, adrRute pRute){
    if (pRute == firstRute(pStasiun)){
        deleteFirstRute(G, pStasiun);
    }else if (nextRute(pRute) == NULL){
        deleteLastRute(G, pStasiun);
    }else{
        adrRute prec = firstRute(pStasiun);
        while (nextRute(prec) != pRute){
            prec = nextRute(prec);
        }
        deleteAfterRute(G, pStasiun, prec);
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
        }else{
            cout << "Rute tidak ditemukan" << endl;
        }
    }else{
        cout << "Stasiun tidak ditemukan" << endl;
    }
}

void addRute(Graph &G, string stasiunAsal, string stasiunTujuan, int jarak, int harga){
    //cari pointer stasiun asal
    adrStasiun p1 = findStasiun(G, stasiunAsal);
    //cari pointer stasiun tujuan
    adrStasiun p2 = findStasiun(G, stasiunTujuan);
    if (p1!=NULL && p2!=NULL){
        //membuat rute dari stasiun asal ke tujuan
        adrRute e1;
        createRute(stasiunTujuan, jarak, harga, e1);
        insertLastRute(G, p1, e1);
        //membuat rute dari stasiun tujuan ke asal
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
    }else{
        adrStasiun p = firstStasiun(G), prev = NULL;

        while (p!=NULL && nama(p) != namaStasiun){
            prev = p;
            p = nextStasiun(p);
        }

        if (p==NULL){
           cout << "Stasiun tidak ditemukan" << endl;
        }else{
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
            nextStasiun(p) = NULL;
        }

    }
}

int degree(Graph &G, adrStasiun v) {
    //mencari rute terbanyak
    int count = 0;
    adrRute r = firstRute(v);
    while (r != NULL) {
        count++;
        r = nextRute(r);
    }
    return count;
}

adrStasiun stasiunTeramai(Graph G) {
    adrStasiun p = firstStasiun(G), maxStasiun = NULL;
    int maxDegree = -1;
    while (p != NULL) {
        int temp = degree(G, p);
        if (temp > maxDegree) {
            maxDegree = temp;
            maxStasiun = p;
        }
        p = nextStasiun(p);
    }
    return maxStasiun;
}

void findShortestPath(Graph G, string asal, string tujuan) {
    const int MAX = 100; // Maksimal jumlah stasiun
    const int INF = 1e9; // Representasi tak hingga

    string stasiun[MAX];
    int dist[MAX], cost[MAX], prev[MAX], visited[MAX];
    int numStasiun = 0;
    int asalIdx = -1, tujuanIdx = -1;

    // Inisialisasi
    adrStasiun p = firstStasiun(G);
    while (p != NULL) {
        stasiun[numStasiun] = nama(p);
        if (nama(p) == asal) asalIdx = numStasiun;
        if (nama(p) == tujuan) tujuanIdx = numStasiun;

        dist[numStasiun] = INF;
        cost[numStasiun] = INF;
        prev[numStasiun] = -1;
        visited[numStasiun] = 0;

        p = nextStasiun(p);
        numStasiun++;
    }

    if (asalIdx == -1 || tujuanIdx == -1) {
        cout << "Stasiun asal atau tujuan tidak ditemukan.\n";
        return;
    }

    dist[asalIdx] = 0;
    cost[asalIdx] = 0;

    // Proses Dijkstra
    for (int i = 0; i < numStasiun; i++) {
        int u = -1, minDist = INF;

        // Cari stasiun dengan jarak terpendek yang belum dikunjungi
        for (int j = 0; j < numStasiun; j++) {
            if (!visited[j] && dist[j] < minDist) {
                u = j;
                minDist = dist[j];
            }
        }

        if (u == -1) break;
        visited[u] = 1;

        // Perbarui jarak dan biaya ke tetangga
        adrStasiun currentStasiun = findStasiun(G, stasiun[u]);
        adrRute r = firstRute(currentStasiun);
        while (r != NULL) {
            string neighborName = nama(adrS(r));
            int neighborIdx = -1;

            // Cari indeks tetangga
            for (int k = 0; k < numStasiun; k++) {
                if (stasiun[k] == neighborName) {
                    neighborIdx = k;
                    break;
                }
            }

            if (neighborIdx != -1 && !visited[neighborIdx]) {
                int weight = jarak(r);
                int ticketPrice = harga(r);

                // Perbarui jarak dan biaya jika lebih kecil
                if (dist[u] + weight < dist[neighborIdx] ||
                   (dist[u] + weight == dist[neighborIdx] && cost[u] + ticketPrice < cost[neighborIdx])) {
                    dist[neighborIdx] = dist[u] + weight;
                    cost[neighborIdx] = cost[u] + ticketPrice;
                    prev[neighborIdx] = u;
                }
            }
            r = nextRute(r);
        }
    }

    // Konstruksi jalur
    if (dist[tujuanIdx] == INF) {
        cout << "Tidak ada jalur dari " << asal << " ke " << tujuan << endl;
        return;
    }

    int path[MAX], pathLength = 0;
    for (int at = tujuanIdx; at != -1; at = prev[at]) {
        path[pathLength++] = at;
    }

    // Output jalur dan biaya
    cout << "Jalur terpendek dari " << asal << " ke " << tujuan << ":\n";
    for (int i = pathLength - 1; i >= 0; i--) {
        cout << stasiun[path[i]];
        if (i > 0) cout << " -> ";
    }
    cout << "\nTotal jarak: " << dist[tujuanIdx] << " KM";
    cout << "\nTotal biaya: " << cost[tujuanIdx] << " Rupiah\n";
}

void findAlternatePath(Graph G, string asal, string tujuan, string problemFrom, string problemTo) {
    const int MAX = 100; // Maksimal jumlah stasiun
    const int INF = 1e9; // Representasi tak hingga

    string stasiun[MAX];
    int dist[MAX], cost[MAX], prev[MAX], visited[MAX];
    int numStasiun = 0;
    int asalIdx = -1, tujuanIdx = -1;

    // Inisialisasi
    adrStasiun p = firstStasiun(G);
    while (p != NULL) {
        stasiun[numStasiun] = nama(p);
        if (nama(p) == asal) asalIdx = numStasiun;
        if (nama(p) == tujuan) tujuanIdx = numStasiun;

        dist[numStasiun] = INF;
        cost[numStasiun] = INF;
        prev[numStasiun] = -1;
        visited[numStasiun] = 0;

        p = nextStasiun(p);
        numStasiun++;
    }

    if (asalIdx == -1 || tujuanIdx == -1) {
        cout << "Stasiun asal atau tujuan tidak ditemukan.\n";
        return;
    }

    dist[asalIdx] = 0;
    cost[asalIdx] = 0;

    // Proses Dijkstra
    for (int i = 0; i < numStasiun; i++) {
        int u = -1, minDist = INF;

        // Cari stasiun dengan jarak terpendek yang belum dikunjungi
        for (int j = 0; j < numStasiun; j++) {
            if (!visited[j] && dist[j] < minDist) {
                u = j;
                minDist = dist[j];
            }
        }

        if (u == -1) break;
        visited[u] = 1;

        // Perbarui jarak dan biaya ke tetangga
        adrStasiun currentStasiun = findStasiun(G, stasiun[u]);
        adrRute r = firstRute(currentStasiun);
        while (r != NULL) {
            string neighborName = nama(adrS(r));
            int neighborIdx = -1;

            // Cari indeks tetangga
            for (int k = 0; k < numStasiun; k++) {
                if (stasiun[k] == neighborName) {
                    neighborIdx = k;
                    break;
                }
            }

            // Abaikan rute bermasalah
            if (nama(currentStasiun) == problemFrom && neighborName == problemTo) {
                r = nextRute(r);
                continue;
            }

            if (neighborIdx != -1 && !visited[neighborIdx]) {
                int weight = jarak(r);
                int price = harga(r); // Biaya tambahan

                // Perbarui jarak dan biaya jika lebih kecil
                if (dist[u] + weight < dist[neighborIdx]) {
                    dist[neighborIdx] = dist[u] + weight;
                    cost[neighborIdx] = cost[u] + price;
                    prev[neighborIdx] = u;
                }
            }
            r = nextRute(r);
        }
    }

    // Konstruksi jalur
    if (dist[tujuanIdx] == INF) {
        cout << "Tidak ada jalur alternatif dari " << asal << " ke " << tujuan << endl;
        return;
    }

    int path[MAX], pathLength = 0;
    for (int at = tujuanIdx; at != -1; at = prev[at]) {
        path[pathLength++] = at;
    }

    // Output jalur
    cout << "Jalur alternatif dari " << asal << " ke " << tujuan << ":\n";
    for (int i = pathLength - 1; i >= 0; i--) {
        cout << stasiun[path[i]];
        if (i > 0) cout << " -> ";
    }
    cout << "\nTotal jarak: " << dist[tujuanIdx] << " KM\n";
    cout << "Total biaya: Rp" << cost[tujuanIdx] << endl;
}

void menu() {
    cout << "-----------------Menu Aplikasi KRL------------------\n";
    cout << "1. Tambah Stasiun\n";
    cout << "2. Tambah Rute\n";
    cout << "3. Hapus Stasiun\n";
    cout << "4. Hapus Rute\n";
    cout << "5. Info Stasiun\n";
    cout << "6. Info Rute\n";
    cout << "7. Cek Stasiun Teramai\n";
    cout << "8. Mencari jalur terpendek\n";
    cout << "9. Mencari jalur alternatif\n";
    cout << "0. Keluar\n";
    cout << "----------------------------------------------------\n";
}
