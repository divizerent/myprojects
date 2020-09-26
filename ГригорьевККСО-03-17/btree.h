#include<iostream>
#include <utility>
#include <cstdlib>
#include <vector>
#include <algorithm>
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


class Btree{
    struct node{
        vector<pair<K, D>> v;
        vector<node*> v1;
        node* parent;
        int key_count=0;
        int son_count=0;
        node(){
            parent=0;
            key_count = son_count = 0;
        }
    }n;
    public:
    Comparator<int> c;
    int size;
    char pause_of_work;//нужна для демонстр. пауз 
    node* p;//корень
    Btree(int s){
        size = s;
        p = NULL;
    }

    ~Btree(){//без деструктора все точно работает корректно 
        clear(p);
    }


    void Add(K x, D y){
        node* currElement = new node;
        currElement = p;
            //char stop1;
            //cin>>stop1;
        if(currElement==NULL) {
            node* element = new node; 
            currElement = element; 
            currElement->v.push_back(make_pair(x, y));
            currElement->key_count = currElement->key_count+1;
            p = currElement;
        }
        else{
           
            if(currElement!=NULL && currElement->v1.size()==0 && currElement->parent==0){
                for(int j=0; j<p->v.size(); j++){
                    if(c(x, p->v[j].first)==0){
                        //cout<<"ENTER ANY KEY"<<endl;
                        //cin>>pause_of_work;
                        return;
                    }
                }
                if(currElement->v.size()<size-1){
                    currElement->v.push_back(make_pair(x, y));
                    currElement->key_count = currElement->key_count +1;
                    sort(currElement->v.begin(), currElement->v.end());
                    p = currElement;
                }
                else{
                    currElement->v.push_back(make_pair(x, y));
                    currElement->key_count = currElement->key_count +1;
                    sort(currElement->v.begin(), currElement->v.end());
                    p = currElement;
                    p = Insert(p);
                
                }
            }
            else if(currElement->v1.size()!=0){


                while(1){
                    if(currElement->v1.size()!=0){
                        for(int i=0; i<currElement->v.size(); i++){
                            if(currElement->v.size()==1){
                                if(c(x, currElement->v[i].first)==1){//if(x>currElement->v[i].first){
                                    node* q = new node;
                                    q = currElement;

                                    currElement = currElement->v1[i+1];
                                    currElement->parent = q;
                                    break;
                                }
                                if(c(x, currElement->v[i].first)==0){
                                    //cout<<"ENTER ANY KEY"<<endl;
                                    //cin>>pause_of_work;
                                    return;
                                }
                                if(c(x, currElement->v[i].first)==-1){//else{
                                    node* q = new node;
                                    q = currElement;
                                    currElement = currElement->v1[i];
                                    currElement->parent = q;
                                    break;
                                }
                            }
                            if(i<=currElement->v.size()-1){
                                if(c(x, currElement->v[i].first)==0 || c(x, currElement->v[i+1].first)==0){
                                    //cout<<"ENTER ANY KEY"<<endl;
                                    //cin>>pause_of_work;
                                    return;
                                }
                                if(c(x, currElement->v[i].first)==1 && c(x, currElement->v[i+1].first)==-1){
                                    node* q = new node;
                                    q = currElement;
                                    currElement = currElement->v1[i+1];
                                    currElement->parent = q;
                                    break;
                                }
                                if(c(x, currElement->v[0].first)==-1){//if(x<currElement->v[0].first){//если x меньш самого левого, то ему сюда
                                    node* q = new node;
                                    q = currElement;
                                    currElement = currElement->v1[i];//&
                                    currElement->parent = q;
                                    break;

                                }
                                int len, len1;
                                len = currElement->v.size();
                                len1 = currElement->v1.size();

                                
                                if(c(x, currElement->v[len-1].first)==0){
                                    //cout<<"ENTER ANY KEY"<<endl;
                                    //cin>>pause_of_work;
                                    return;
                                }
                                if(c(x, currElement->v[len-1].first)==1){
                                    node* q = new node;
                                    q = currElement;
                                    currElement = currElement->v1[len1-1];
                                    currElement->parent = q;
                                    break;
                                }
                            }
                        }
                        continue;
                    }
                    else{
                        break;
                    }
                }//внизу дерева


                for(int j1=0; j1<currElement->v.size(); j1++){
                    if(c(x, currElement->v[j1].first)==0){
                        //cout<<"ENTER ANY KEY"<<endl;
                        //cin>>pause_of_work;
                        return;
                    }
                }
                if(currElement->v.size()!=size-1){
                    currElement->v.push_back(make_pair(x, y));
                    currElement->key_count = currElement->key_count +1;
                    sort(currElement->v.begin(), currElement->v.end());
                }
                else{
                    currElement->v.push_back(make_pair(x, y));
                    currElement->key_count = currElement->key_count +1;
                    sort(currElement->v.begin(), currElement->v.end());
                    while(1){
                        if(currElement->parent==0){
                            p = Insert(currElement);
                            break;
                        }

                        else{
                            node* s = new node;
                            s = Insert(currElement);
                            
                            
                            
                            
                            currElement = currElement->parent;
                            K point_key = s->v[0].first;
                            currElement->v.push_back(make_pair(s->v[0].first, s->v[0].second));
                            sort(currElement->v.begin(), currElement->v.end());
                            int position;
                            for(int i=0; i<currElement->v.size(); i++){
                                if(c(point_key, currElement->v[i].first)==0){//if(point_key == currElement->v[i].first){
                                    position = i;
                                    break;
                                }
                            }
                            currElement->v1.erase(currElement->v1.begin()+position);

                            currElement->v1.insert(currElement->v1.begin()+position, s->v1.begin(), s->v1.end());

                            currElement->son_count += 2;
                            if(currElement->v.size()!=size){
                                break;
                            }
                            
                        }
                    }
                }
            }
        }

    }
    node* Insert(node* n){
        int mid = size / 2;

        auto iter = n->v.begin();
        node* left = new node;
        node* right = new node;
        for(int i=0; i<n->v.size(); i++){
            if(i<mid){
                left->v.push_back(make_pair(iter->first, iter->second));

                sort(left->v.begin(), left->v.end());
                left->key_count++;
            }
            if(i>mid){
                right->v.push_back(make_pair(iter->first, iter->second));
                sort(right->v.begin(), right->v.end());
                right->key_count++;
            }
            iter++;
        }
        
        pair<K, D> buff_pair = make_pair(n->v[mid].first, n->v[mid].second);
        n->v.clear();
        n->key_count = 1;
        n->son_count = 0;
        n->v.push_back(make_pair(buff_pair.first, buff_pair.second));

        if(n->v1.size()!=0){ //если у n есть потомки
            for(int i=0; i<n->v1.size(); i++){//раскидать потомков в массивы двух новых потомков 
                if(i<=mid){
                    left->v1.push_back(n->v1[i]);
                    left->son_count++;
                }
                if(i>mid){
                    right->v1.push_back(n->v1[i]);
                    right->son_count++;
                }

            }
            n->v1.clear();
        }
        n->v1.push_back(left);
        n->v1.push_back(right);//у n теперь два новых потомка
        left->parent = right->parent = n;//n теперь является родителем ДЛЯ двух своих новых потомков
        n->son_count+=2;
        return n;

    }   
    
    void Print(){
        cout<<"____________________________________________________"<<endl;
        node* pr;
        pr = p;
        cout<<"КОРЕНЬ ИМЕЕТ "<<pr->v.size()<<" КЛЮЧЕЙ, "<<pr->v1.size()<<" ПОТОМКОВ"<<endl;
        cout<<"КЛЮЧИ:";
        for(int i=0; i<pr->v.size(); i++){
            cout<<pr->v[i].first<<" ";
        }
        cout<<"____________________________________________________"<<endl;
    }

    int Search(K x){
        node* r = new node;
        r = p;
        
            while(1){
                if(r->v1.size()!=0){
                    for(int i=0; i<r->v.size(); i++){
                        if(r->v.size()==1){
                            if(binary_search(r, x)==1){
                                cout<<"ОН БЫЛ НАЙДЕН "<<endl;
                                return 0;
                            }
                            if(c(x, r->v[i].first)==1){//if(x>currElement->v[i].first){
                                node* q1 = new node;
                                q1 = r;

                                r = r->v1[i+1];
                                r->parent = q1;
                                break;
                            }
                            else{
                                node* q1 = new node;
                                q1 = r;
                                r = r->v1[i];
                                r->parent = q1;
                                break;
                            }
                        }

                            if(binary_search(r, x)==1){
                                cout<<"ОН БЫЛ НАЙДЕН "<<endl;
                                return 0;
                            }
                        if(i<=r->v.size()-1){
                            if(c(x, r->v[i].first)==1 && c(x, r->v[i+1].first)==-1){
                                node* q1 = new node;
                                q1 = r;
                                r = r->v1[i+1];
                                r->parent = q1;
                                break;
                            }
                            if(c(x, r->v[0].first)==-1){//if(x<currElement->v[0].first){//если x меньш самого левого, то ему сюда
                                node* q1 = new node;
                                q1 = r;
                                r = r->v1[i];//&
                                r->parent = q1;
                                break;

                            }
                            int len, len1;
                            len = r->v.size();
                            len1 = r->v1.size();

                            
                            if(c(x, r->v[len-1].first)==1){
                                node* q1 = new node;
                                q1 = r;
                                r = r->v1[len1-1];
                                r->parent = q1;
                                break;
                            }
                        }
                    }
                    continue;
                }
                else{

                    if(binary_search(r, x)==1){
                        cout<<"ОН БЫЛ НАЙДЕН "<<endl;
                        return 0;
                    }
                    break;
                }
            }//внизу дерева
    cout<<"ТАКОГО КЛЮЧА ЗДЕСЬ НЕТ"<<endl;
    return 0;

    } 
    
    int binary_search(node* z, K key){
        bool flag = false;
        int l = 0;
        int r = z->v.size()-1;
        int middle;
        while((l<=r) && (flag!=true)){
            middle = (l+r)/2;
            if(c(z->v[middle].first,key)==0) flag = true;//
            if(c(z->v[middle].first,key)==1) r = middle-1;
            else l = middle +1;
        }
        if(flag){cout<<"ЗНАЧЕНИЕ С ЭТИМ КЛЮЧОМ "<<z->v[middle].second<<endl; return 1;}
        else return 0;
        return 0;
    }
            

};


