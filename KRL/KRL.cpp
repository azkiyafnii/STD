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
    bool ketemu = false;
    adrStasiun p = firstStasiun(G);
    while(p!=NULL && ketemu != true){
        if(nama(p)==nama){
            cout << "Error: Nama stasiun \"" << nama << "\" sudah ada!" << endl;
        }
        p=nextStasiun(p);
    }
    if(!ketemu){
        adrStasiun s;
        createStasiun(nama, s);
        if (firstStasiun(G)==NULL){
            firstStasiun(G) = s;
        }else{
            p = firstStasiun(G);
            while (nextStasiun(p)!=NULL){
                p = nextStasiun(p);
            }
            nextStasiun(p)=s;
        }
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
    //mengapus rute dari dua arah
    adrStasiun s1 = findStasiun(G, stasiunAsal);
    adrStasiun s2 = findStasiun(G, stasiunTujuan);

    if (s1 != NULL && s2 != NULL){
        adrRute r1 = findRute(G, s1, stasiunTujuan);
        adrRute r2 = findRute(G, s2, stasiunAsal);
        if (r1 != NULL && r2 != NULL){
            deleteRute(G, s1, r1);
            deleteRute(G, s2, r2);
            cout << "Rute berhasil dihapus" << endl;
        }else{
            cout << "Rute tidak ditemukan" << endl;
        }
    }else{
        cout << "Stasiun tidak ditemukan " << endl;
    }
}

void addRute(Graph &G, string stasiunAsal, string stasiunTujuan, int jarak, int harga) {
    // Membuat pointer stasiun asal
    adrStasiun p1 = findStasiun(G, stasiunAsal);
    // Membuat pointer stasiun tujuan
    adrStasiun p2 = findStasiun(G, stasiunTujuan);

    if (p1 != NULL && p2 != NULL) {
        // Pengecekan apakah rute
        bool ketemu = false;
        adrRute r = firstRute(p1);
        while (r != NULL && ketemu == false) {
            if (nama(adrS(r)) == stasiunTujuan) {
                cout << "Error: Rute dari \"" << stasiunAsal << "\" ke \"" << stasiunTujuan << "\" sudah ada!" << endl;
                ketemu = true;
            }
            r = nextRute(r);
        }
        if (!ketemu){
            adrRute e1;
            createRute(stasiunTujuan, jarak, harga, e1);
            insertLastRute(G, p1, e1);
            adrRute e2;
            createRute(stasiunAsal, jarak, harga, e2);
            insertLastRute(G, p2, e2);
        }
    } else {
        cout << "Error: Salah satu atau kedua stasiun tidak ditemukan!" << endl;
    }
}

void deleteStasiun(Graph &G, string namaStasiun) {
    //mengecek graph kosong atau tidak
    if (firstStasiun(G)==NULL){
        cout << "Daftar Stasiun kosong" << endl;
    }else{
        //mencari stasiun
        adrStasiun p = firstStasiun(G), prev = NULL;
        while (p!=NULL && nama(p) != namaStasiun){
            prev = p;
            p = nextStasiun(p);
        }
        //mengecek stasiun yang akan dihapus ada atau tidak
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
            cout << "Stasiun " << namaStasiun <<" berhasil dihapus" << endl;
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
    //return alamat stasiun Teramai
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

void mencariJalurTerpendek(Graph G, string asal, string tujuan) {
    string stasiun[MAX]; // Array untuk menyimpan nama-nama stasiun
    int dist[MAX], cost[MAX], prev[MAX], visited[MAX]; // Array untuk jarak, biaya, jalur sebelumnya, dan status kunjungan
    int numStasiun = 0;
    int asalIdx = -1, tujuanIdx = -1;

    // Inisialisasi array dan mencari indeks stasiun asal dan tujuan
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
    }else{
        dist[asalIdx] = 0;
        cost[asalIdx] = 0;
        int unvisitedCount = numStasiun; // Hitung jumlah stasiun yang belum dikunjungi
        // Proses Dijkstra
        while (unvisitedCount > 0) {
            int u = -1, minDist = INF;

            // Cari stasiun dengan jarak terpendek yang belum dikunjungi
            for (int j = 0; j < numStasiun; j++) {
                if (!visited[j] && dist[j] < minDist) {
                    u = j;
                    minDist = dist[j];
                }
            }

            // Jika tidak ada stasiun yang dapat dijangkau, keluar dari loop
            if (u == -1) {
                unvisitedCount = 0;
                continue;
            }

            // Tandai stasiun ini telah dikunjungi
            visited[u] = 1;
            unvisitedCount--;

            // Perbarui jarak dan biaya ke tetangga-tetangga stasiun saat ini
            adrStasiun currentStasiun = findStasiun(G, stasiun[u]);
            adrRute r = firstRute(currentStasiun);
            while (r != NULL) {
                string neighborName = nama(adrS(r));
                int neighborIdx = -1;

                // Cari indeks stasiun tetangga
                int k =0;
                while(k<numStasiun && neighborIdx == -1){
                    if (stasiun[k]==neighborName){
                        neighborIdx = k;
                    }
                    k++;
                }

                // Jika tetangga belum dikunjungi, perbarui jarak dan biaya
                if (neighborIdx != -1 && !visited[neighborIdx]) {
                    int weight = jarak(r);
                    int ticketPrice = harga(r);

                    // Periksa apakah jarak lebih kecil atau jika sama, biaya lebih kecil
                    if (dist[u] + weight < dist[neighborIdx] || (dist[u] + weight == dist[neighborIdx] && cost[u] + ticketPrice < cost[neighborIdx])) {
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
        }else{
            // menyimpan indeks stasiun dalam jalur
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
    }

}

void mencariJalurAlternatif(Graph G, string asal, string tujuan, string problemFrom, string problemTo) {
    string stasiun[MAX]; // Array untuk menyimpan nama stasiun
    int dist[MAX], cost[MAX], prev[MAX], visited[MAX]; // Array untuk menyimpan jarak, biaya, jalur sebelumnya, dan status kunjungan
    int numStasiun = 0;
    int asalIdx = -1, tujuanIdx = -1;

    // Inisialisasi semua data stasiun dalam graf
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
    // mengecek apakah stasiun asal dan tujuan ditemukan
    if (asalIdx == -1 || tujuanIdx == -1) {
        cout << "Stasiun asal atau tujuan tidak ditemukan.\n";
    }else{
        dist[asalIdx] = 0;
        cost[asalIdx] = 0;
        int unvisitedCount = numStasiun;
        // Proses Dijkstra
        while (unvisitedCount > 0) {
            int u = -1, minDist = INF;

            // Mencari stasiun dengan jarak terpendek yang belum dikunjungi
            for (int j = 0; j < numStasiun; j++) {
                if (!visited[j] && dist[j] < minDist) {
                    u = j;
                    minDist = dist[j];
                }
            }

            // Jika tidak ada stasiun yang dapat dijangkau, keluar dari loop
            if (u == -1) {
                unvisitedCount = 0;
                continue;
            }

            // Tandai stasiun ini telah dikunjungi
            visited[u] = 1;
            unvisitedCount--;

            // Perbarui jarak dan biaya ke tetangga-tetangga stasiun saat ini
            adrStasiun currentStasiun = findStasiun(G, stasiun[u]);
            adrRute r = firstRute(currentStasiun);
            while (r != NULL) {
                string neighborName = nama(adrS(r));
                int neighborIdx = -1;

                // Cari indeks stasiun tetangga
                int k=0;
                while(k<numStasiun && neighborIdx == -1){
                    if (stasiun[k]==neighborName){
                        neighborIdx = k;
                    }
                    k++;
                }

                // Abaikan rute bermasalah
                if ((nama(currentStasiun) == problemFrom && neighborName == problemTo) ||
                    (nama(currentStasiun) == problemTo && neighborName == problemFrom)) {
                    r = nextRute(r);
                    continue;
                }

                if (neighborIdx != -1 && !visited[neighborIdx]) {
                    int weight = jarak(r);
                    int price = harga(r);

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

        if (dist[tujuanIdx] == INF) {
            cout << "Tidak ada jalur alternatif dari " << asal << " ke " << tujuan << endl;
        }else{
            // Membuat jalur
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
    }
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
