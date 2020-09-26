#include <iostream>
#include <cstdlib>
#include "btree.h"
using namespace std;


int main(){
    srand(static_cast<unsigned int>(time(0)));
    int node_size;
    int amount;
    int num;//
    cout<<"ENTER NODE SIZE (>2): ";
    cin>>node_size;
    while(node_size<2){    
        cout<<"ENTER NODE SIZE (>2): ";
        cin>>node_size;
    }
    cout<<"ENTER THE AMOUNT OF DATA(unsigned int): ";
    cin>>amount;
    Btree<int, int> *bt = new Btree<int, int>(node_size);


    for(int i=0; i<amount; i++){
        num = i;
        bt->Add(num, i);
    }
/*    for(int i=0; i<amount; i++){
        num = rand()%amount;
        bt->Add(num, i);
    }*/
    cout<<"KEY ROOT:";
    bt->Print();
    int key_search;
    cout<<"ENTER THE KEY TO DISPLAY ITS VALUE:";
    cin>>key_search;
    bt->Search(key_search);
    return 0;
}
