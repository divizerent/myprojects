#include <iostream>
#include <functional>
#include "hash.h"

using namespace std;

int main(){
    Hash_procession<int, int> *h = new Hash_procession<int, int>();
    h->Add(15, 4);
    h->Add(1, 90);
    h->Add(56, 2);
    h->Add(11, 213);
    h->Add(13, 532);
    h->Add(41, 661);
    h->Add(65, 761);
    h->Add(89, 311);
    h->Add(10, 721);
    
    h->Search(100);
    h->Search(1);
    h->Print();
    return 0;
}

