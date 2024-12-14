#include <iostream>
#include "KRL.h"

using namespace std;

int main()
{
    Graph G;
    initGraph(G);

    buildGraph(G);
    printStasiun(G);
    return 0;
}
