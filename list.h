#ifndef LIST_H
#define LIST_H
template<typename T> struct node{
    T data;
    node *pnext;

};
template<typename T> struct NODE{
    node<T>* p=new node<T>();
    NODE(){
        p=NULL;
    }
    NODE(T x){
        p->data=x;
        p->pnext=NULL;
    }

    bool operator!=(NODE<T> x) {return p != x.p;}
    T& operator*() {return p->data;}
    void operator++() {p=p->pnext; }
};
template<typename T> node<T>* makenode(T x){
    node<T>* p=new node<T>();
    p->data=x;
    p->pnext=NULL;
    return p;
}
template <typename T> struct list{
    NODE<T> phead;
    NODE<T> ptail;
    NODE<T> pnull;

    int vsize=0;
    T first(){
        return *phead;
    }
    T last(){
        return *ptail;
    }

    NODE<T> begin(){
        return phead;
    }
    NODE<T> end(){

        node<T> *pointersub=makenode(*ptail);
        ptail.p->pnext=pointersub;
        pnull.p=pointersub;
        return pnull;

    }
    void append(T x){
        node<T>* pointer=makenode(x);
        if (phead.p==NULL) {
            phead.p=ptail.p=pointer;

        } else {
            ptail.p->pnext=pointer; ptail.p=pointer;

        }
        vsize++;
    }

    T & operator[](int i){
        int j=0;
        static T nullvalue;
        for (node<T> *k=phead.p;k!=ptail.p->pnext;k=k->pnext) {
            if (j==i) return k->data;

            j++;
        }

        return nullvalue;
    }
    const list<T> &operator =(const list<T> & a){
        for (node<T> *k=a.phead.p;k!=a.ptail.p->pnext;k=k->pnext){
            append(k->data);
        }
    }
    int size(){
        return this->vsize;
    }
};
#endif // LIST_H
