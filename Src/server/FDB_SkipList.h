/*************************************************************************
	> File Name: 1.h
	> Author:Eval 
	> Mail:1040460587@qq.com 
	> Created Time: 2016年04月16日 星期六 12时55分55秒
 ************************************************************************/

#include<stdio.h>  
#include<stdlib.h>  
#include"SkipNode.h"

#define MAX_LEVEL 10 //最大层数 
#define true 1
#define false 0

#ifndef _1_H
#define _1_H
#endif


//跳跃表类
template<class E>
class skiplist
{
public:
    int level;
    nodeStructure<E>* header;

    //成员函数

    int search(skiplist<E> *sl,int key);  
    void printSL(skiplist<E> *sl);  

    int deleteSL(skiplist<E> *sl,E key);  
    skiplist<E>* createSkiplist();  
    nodeStructure<E>* createNode(int level,E key,E value);
    int randomLevel();    
    int insert(skiplist<E> *sl,E key,E value);  
    //nodeStructure<E>* createNode(int level,E key,E value);

};

//创建节点 
template<class E>
nodeStructure<E>* skiplist<E>::createNode(int level,E key,E value)  
{  
    nodeStructure<E> *ns=(nodeStructure<E> *)malloc(sizeof(nodeStructure<E>)+level*sizeof(nodeStructure<E>*));    
    ns->key=key;    
    ns->value=value;    
    return ns;    
}  

//初始化跳表  
template<class E>
skiplist<E>* skiplist<E>::createSkiplist()  
{
    skiplist<E> *sl=(skiplist<E> *)malloc(sizeof(skiplist<E>));    
    sl->level=0;
    sl->header=createNode(MAX_LEVEL-1,0,0);    
    for(int i=0;i<MAX_LEVEL;i++)    
    {    
        sl->header->forward[i]=NULL;    
    }  
    return sl;  
}  
     
//随机产生层数  
template<class E>
int skiplist<E>::randomLevel()    
{
    int k=1;  
    while (rand()%2)    
        k++;    
    k=(k<MAX_LEVEL)?k:MAX_LEVEL;  
    return k;    
}  
        
//插入节点
template<class E>
int skiplist<E>::insert(skiplist<E> *sl,E key,E value)  
{
    nodeStructure<E> *update[MAX_LEVEL];  
    nodeStructure<E> *p, *q = NULL;  
    p=sl->header;  
    int k=sl->level;  
    //从最高层往下查找需要插入的位置  
    //填充update  
    for(int i=k-1; i >= 0; i--){  
        while((q=p->forward[i])&&(q->key<key))  
        {  
            p=q;  
        }  
        update[i]=p;  
    }  
    //不能插入相同的key  
    if(q&&q->key==key)  
    {  
        return false;  
    }  
        
    //产生一个随机层数K  
    //新建一个待插入节点q  
    //一层一层插入  
    k=randomLevel();  
    //更新跳表的level  
    if(k>(sl->level))  
    {
        for(int i=sl->level; i < k; i++){  
            update[i] = sl->header;  
    }  
        sl->level=k;
    }
    
    q=createNode(k,key,value);  
    //逐层更新节点的指针，和普通列表插入一样  
     for(int i=0;i<k;i++)  
    {
        q->forward[i]=update[i]->forward[i];  
        update[i]->forward[i]=q;  
    }
    return true;  
}  

//搜索指定key的value
template<class E>
int skiplist<E>::search(skiplist<E> *sl,int key)  
{
    nodeStructure<E> *p,*q=NULL;  
    p=sl->header;  
    //从最高层开始搜  

    int k=sl->level;  
    for(int i=k-1; i >= 0; i--){  
        while((q=p->forward[i])&&(q->key<=key))  
        {  
            if(q->key == key)  
            {  
                return q->value;  
            }  
            p=q;  
        }
    }
    return 0;

}  


//删除指定的key 

template<class E>
int skiplist<E>::deleteSL(skiplist<E> *sl,E key)  
{
    nodeStructure<E> *update[MAX_LEVEL];
    nodeStructure<E> *p,*q=NULL;  
    p=sl->header;  
    //从最高层开始搜  
    int k=sl->level;  
    for(int i=k-1; i >= 0; i--){  
        while((q=p->forward[i])&&(q->key<key))  
        {  
            p=q;  
        }  
        update[i]=p;  
    }  
    if(q&&q->key==key)  
    {  
        //逐层删除，和普通列表删除一样  

        for(int i=0; i<sl->level; i++){    
            if(update[i]->forward[i]==q){    
                update[i]->forward[i]=q->forward[i];    
            }  
        }   
        free(q);  
        //如果删除的是最大层的节点，那么需要重新维护跳表的  

        for(int i=sl->level - 1; i >= 0; i--){    
            if(sl->header->forward[i]==NULL){    
                sl->level--;    
            }    
        }    
        return true;
    }  
    else{
        return false;
    }  
}  
template<class E>
void skiplist<E>::printSL(skiplist<E> *sl)  
{  
    //从最高层开始打印  
    
    nodeStructure<E> *p,*q=NULL;  
    //从最高层开始搜  

    int k=sl->level;  
    for(int i=k-1; i >= 0; i--)  
    {  
        p=sl->header;  
        while(q=p->forward[i])  
        {
            printf("%d -> ",p->value);  
            p=q;  
        }  
        printf("\n");
    }  
    printf("\n");
}  
