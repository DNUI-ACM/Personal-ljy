#include<stdio.h>
#include<cstring>
#include<stdlib.h>
typedef struct {
    int * _base;
    int _len;
    int _capacity;
}Vector;

void init(Vector * v);
void destroy(Vector * v);
void push_back(Vector * v,int value);
int get_value(Vector * ,int );
int size(Vector *);

int get_value(Vector * v,int i)
{
    return v -> _base[i];
}
void expand_capacity(Vector * v){
    if(v -> _capacity == 0){
        v -> _base = (int*)malloc(sizeof(int) * 1);
        v -> _capacity = 1;
    }else{
        int * address = (int*)malloc(sizeof(int) * (v -> _capacity) * 2);
        memcpy(address , v -> _base , sizeof(int) * (v -> _capacity));
        free(v -> _base);
        v -> _base = address;
        v -> _capacity *= 2;
    }
}
void init(Vector * v){
    v -> _base = NULL;
    v -> _len = 0;
    v -> _capacity = 0;
}
void destroy(Vector * v){
    if(v -> _base){
        free(v -> _base);
    }
}
void push_back(Vector * v,int value){
    if(v ->_len < v -> _capacity){
        v -> _base[v -> _len] = value;
        v -> _len ++;
    }else{
        expand_capacity(v);
        v -> _base[v -> _len] = value;
        v -> _len ++;
    }
}
int size(Vector * v){
    return v -> _len;
}
int _capacity(Vector * v){
        return v->_capacity;
}
void * getValue(Vector * v,int pos)
{
    return &v->_base[pos];
}
void pop_back(Vector * v)
{
    v -> _len--;
}
void erase(Vector * v,int pos)
{
    int i=pos;
    for(i;i<v->_len-1;i++)
    {
        v->_base[i]=v->_base[i+1];
    }
    v->_len--;
}
void insert(Vector * v,int pos,int a)
{
    if(v->_len < v->_capacity){
        ;
    }
    else{
        expand_capacity(v);
    }
    int i=v->_len-1;
    for(i;i>=pos;i--)
    {
        v->_base[i+1]=v->_base[i];
    }
    v->_base[pos]=a;
}
int main(){
    Vector v;
    init(&v);
    for(int j = 0;j != 100;j++){
        push_back(&v , j);
    }

    for(int i=0;i<50;i++)
        erase(&v,0);
    for(int i=0;i<70;i++)
        printf("%d ",v._base[i]);
    destroy(&v);
    return 0;
}

