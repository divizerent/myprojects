#include <iostream>
#include <iterator>
#include <functional>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <list>

using namespace std;
template<class K>



class Comparator{
    public: int operator()(K a, K b){
        if(a > b)
            return 1;
        if(a < b)
            return -1;
        if(a == b)
            return 0;
    }

};


template<class K, class D>


class Hash_procession{
    public:
    Comparator<int> c;
    int lists;
    int elements;
    float k;
    int flag;
    vector<list<pair<K, D>>> v;
    list<pair<K, D>> l;
    hash<K> hash_func;
    Hash_procession(){
        elements = 0;
        lists = 1;
        flag=0;
    }
    void Add(K key, D value){
        if(this->v.size()==0){//если это начало работы программы
            size_t res_hash = hash_func(key) % lists;
            this->l.push_back(make_pair(key, value));
            this->v.push_back(l);
            this->l.clear();
            elements++;
            
        }
        else{
            k =  elements / lists;
            if(k>=2.0){//если коэфф перегруженности больше 2
                int oldsize = this->v.size();//текущая загруженность вектора(количество списков)
                lists = 2 * lists + 1;
                v.resize(lists);
                vector<pair<K, D>> buff1;
                for(int j=0; j<oldsize; j++){
                    for(auto m : this->v[j]){
                        buff1.push_back(make_pair(m.first, m.second));

                    }
                }

                this->v.clear();
                v.resize(lists);
                Rehashing(buff1); 

                        
            }


            flag=0;

            size_t res_hash = hash_func(key) % lists;
            for(int i=0; i<v.size(); i++){//идем по вектору



                if(res_hash == i){
                    for(auto m1 : v[i]){
                        this->l.push_back(make_pair(m1.first, m1.second));
                    }
                    this->l.push_back(make_pair(key, value));
                    this->v.erase(this->v.begin()+i);
                    this->v.insert(this->v.begin()+i, l);
                    this->l.clear();

                    elements++;
                    flag=1;
                    break;
                }
            }
            if(flag!=1){
                this->l.push_back(make_pair(key, value));
                this->v.insert(this->v.begin()+res_hash, l);
                this->l.clear();
                flag=0;
                elements++;
            }
            
        }
        flag = 0;

    }
    
    D Search(K key){
        size_t poy = hash_func(key) % lists;
        if(this->v[poy].size()!=0){
            for(auto iter : v[poy]){
                if(c(iter.first, key)==0){
                    cout<<"+"<<endl;
                    return iter.second;//теперь возвращает значение
                }
            }
        }
        cout<<"-"<<endl;
        return -1;

    }


    void Print(){
        for(int l=0; l<this->v.size(); l++){
            cout<<"Хэш "<<l<<endl;
            for(auto a : v[l]){
                cout<<" Ключ "<<a.first<<endl;
            }
        }
        cout<<"//////////////////////////"<<endl;
    }
//////////////////////////////////////    
    
    private:

    void Rehashing(vector<pair<K, D>> buff1){ 
        for(int x=0; x<buff1.size(); x++){
                size_t res_hash = hash_func(buff1[x].first) % lists;
                for(int i1=0; i1<v.size(); i1++){//идем по вектору

                    flag = 0;
                    if(res_hash == i1){
                        for(auto m2 : v[i1]){
                            this->l.push_back(make_pair(m2.first, m2.second));
                        }
                        this->l.push_back(make_pair(buff1[x].first, buff1[x].second));
                        this->v.erase(this->v.begin()+i1);
                        this->v.insert(this->v.begin()+i1, l);
                        this->l.clear();

                        flag=1;
                        break;
                    }
                }
                if(flag!=1){
                    this->l.push_back(make_pair(buff1[x].first, buff1[x].second));
                    this->v.insert(this->v.begin()+res_hash, l);
                    this->l.clear();
                    flag=0;
                }
        }
    }
    
};


