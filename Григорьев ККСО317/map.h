#include <iostream>
#include <cmath>

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


class map{
    public:
        struct node{
            K k;
            D data;
            int height;
            node *left;//указатель на левый элемент
            node *right;//указатель на правый элемент
            node *parent;

            node(){
                left=right=parent=0;
                height = 0;//новый элемент не имеет изначально соседей
            }
        
        }n;
        Comparator<int> c;//
        node* p;//указатель на корень
        
        map(){
            p = NULL;
        }

        void Add(K k, D data){
            int b = 10;
            node* element = new node;
            element->k = k;
            element->data = data;
            node* currElement = p;
            node* constp = p;
            if(p == NULL){ p = currElement = element;}
            else{ //currElement != NULL{
                while(b==10){
                    
                    if(c(element->k,currElement->k)==1){
                        if(currElement->right==0){
                            currElement-> right = element;
                            element->parent = currElement;
                            break;
                        }
                        else{
                            currElement = currElement->right;
                            continue;
                        }
                    }
                    if(c(element->k, currElement->k)==-1){//(element->k < currElement->k){
                        if(currElement->left==0){
                            currElement->left = element;
                            element-> parent = currElement;
                            break;
                        }
                        else{
                            currElement = currElement->left;
                            continue;
                        }
                    }
                    if(c(element->k, currElement->k)==0){
                        break;
                    }
                }
                checker(element);
                while(1){
                    if(p->parent!=0){
                        p=p->parent;
                    }
                    else{
                        break;
                    }
                }

                
            }

        }


        int putheight(int hl, int hr){
            return (hl>hr?hl:hr)+1;
        }

        void checker(node* p){
            int hl=0, hr=0;
            if(p->left!=0){
                
                hl = p->left->height;
            }
            if(p->right!=0){
                hr = p->right->height;
            }
            p->height = putheight(hl, hr);
            swaper(p);    
            if(p->parent!=0){

                checker(p->parent);
            }
            
            
        }


        void swaper(node* p){
            if(delta(p)==-2){
               
                if(delta(p->left)>0){
                    p->left= swapleft(p->left);
                }
                p=swapright(p);
                p=(p->parent?foo(p->parent, p):p);
                
            }

            if(delta(p)==2){
                if(delta(p->right)<0){
                    p->right=swapright(p->right);
                }
                p=swapleft(p);
                p=(p->parent?foo(p->parent, p):p);
            }
            
        }
            
            int delta(node* p){
                return (p->right?p->right->height:0) - (p->left?p->left->height:0);
            }


            node* swapright(node* p){
                node* q = p->left;
                p->left = q->right;
                
                q->right = p;
                q->parent = p->parent;//
                p->parent = q;//
                int hl = (p->left? p->left->height:0);
                int hr = (p->right?p->right->height:0);
                p->height = putheight(hl, hr);
                hl = (q->left?q->left->height:0);
                hr = (q->right?q->right->height:0);
                q->height = putheight(hl, hr);
                
                if(p->left!=0){
                    p->left = bar(p->left, p);
                }

                return q;
            }
            
            node* foo(node* p, node* q){
                if(c(q->k, p->k)==-1){
                    p->left = q;
                    return p->left;
                }
                if(c(q->k, p->k)==1){
                    p->right = q;
                return p->right;
                }
            }

            node* bar(node*p, node* q){
                p->parent = q;

                return p;
            }

        
            node* rab(node*p, node* q){
                p->parent = q;

                return p;
            }


            node* swapleft(node* q){
                node* p = q->right;
                q->right = p->left;
                p->left = q;
                p->parent = q->parent;
                q->parent = p;
                int hl = (q->left?q->left->height:0);
                int hr = (q->right?q->right->height:0);
                q->height = putheight(hl,hr);
                hl = (p->left?p->left->height:0);
                hr = (p->right?p->right->height:0);
                p->height = putheight(hl,hr);
                
                
                if(q->right!=0){
                    q->right = rab(q->right, q);
                }
                
                return p;
            }

            void print(){
                cout<<"print "<<p->k<<endl;;
            }



            void WhereElement(K k){
                int b = 10;
                node* currElement = p;
                node* constp = p;
                if(p == NULL){cout<<"Nothing"<<endl;}
                else{ //currElement != NULL{
                    while(b==10){
                    
                        if(c(k, currElement->k) == 1){
                            if(currElement->right==0){
                                break;
                            }
                            else{
                                currElement = currElement->right;
                                continue;
                            }
                        }
                        if(c(k, currElement->k) == -1){
                            if(currElement->left==0){
                                break;
                            }
                            else{
                                currElement = currElement->left;
                                continue;
                            }
                        }
                        if(c(k, currElement->k) == 0){
                            break;
                        }
                    }
                }
            }

            void check(int quan){
                int h = p->height;
                float d1 = 1.44*log2(quan+2)- 0.328;
                float d2 = log2(quan+1);
                cout<<"QUANTITY "<<d2<<" "<<d1<<" "<<h<<endl;
            }
                


};

