#include <iostream>
#include "map.h"
#include <cstdlib>

using namespace std;


int main(){
    srand(static_cast<unsigned int>(time(0)));
    int num;
    int val;
    cout<<"Enter size:"<<endl;
    cin>>val;
    map<int, int> *mp = new map<int, int>();//map
    //map<int, int> mp();
    //mp.Add(58, 2);
    //mp.Add(58, 2);
    //mp.Add(58, 2);
    for(int i=0; i<val; i++){
        num = rand()%val;
        mp->Add(num, i);
    }
    /*mp->Add(44, 1);
    mp->Add(58, 2);
    mp->Add(12, 3);
    mp->Add(12, 12);
    mp->Add(12, 23);*/
    mp->check(val);
    
    
  /*  
    mp->Add(44, 131);
    mp->Add(22, 121231);
    mp->Add(50, 53);
    mp->Add(12, 73);
    mp->Add(10, 4);
*/
   /* mp->Add(44, 12);
    mp->Add(52, 121);
    mp->Add(51, 23);
    mp->Add(55, 124);
    mp->Add(53, 124);

    mp->Add(59, 124);

    mp->Add(58, 124);
    mp->Add(112, 124);
    mp->Add(65, 124);
    
    mp->Add(67, 124);
    mp->Add(66, 124);

    mp->Add(100, 124);

    mp->Add(45, 1);
    mp->Add(84, 124);
    mp->Add(22, 5);
    mp->Add(13, 6);
    mp->Add(70, 213);
    mp->Add(14, 131);
    mp->Add(46, 131);
    
    mp->Add(47, 131);
    mp->Add(48, 131);
    mp->Add(413, 13);
    mp->Add(102, 131);
    mp->Add(94, 131);
    mp->Add(670, 131);
    mp->Add(456, 131);
    mp->Add(555, 131);
    mp->Add(543, 131);
    mp->Add(777, 131);

    mp->Add(786, 131);
    mp->Add(999, 131);
    mp->print();
    mp->Delete(51);*/
/*
    mp->Add(4, 131);
    mp->Add(6, 131);
    mp->Add(49, 7);
    mp->Add(51, 8);
    mp->Add(123, 9);
    mp->Add(31, 10);*/
    //mp->Add(111, 9);
    cout<<"main"<<endl;
    //mp->print(44);
    //mp->print(9);
    //mp->print(13);
    return 0;
}
