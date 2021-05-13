#include <iostream>
#include<algorithm>
#include<list>
#include<vector>
#include<iomanip>
#include<climits>
#include<time.h>
#include<stdio.h>
using namespace std;
const int minn=4;
const int maxx=32;
const int N=320;
int ins[2*N];
double hit_num=0;
const int max_add=32766;//32k-2
struct node{
      int id;
      int num;
};

void get_input(){
      int cnt=0;
      srand(time(0));
      while(cnt<N){
            int m=rand()%max_add+1;
            ins[cnt++]=m;
            if(cnt>=N)break;
            ins[cnt++]=m+1;
            if(cnt>=N)break;
            int m1=rand()%m;
            ins[cnt++]=m1;
            if(cnt>=N)break;
            ins[cnt++]=m1+1;
            if(cnt>=N)break;
            int m2=rand()%(max_add-1-m1)+(m1+2);
            ins[cnt++]=m2;
            if(cnt>=N)break;
            ins[cnt++]=m2+1;
            if(cnt>=N)break;
      }
      for(int i=0;i<N;i++){
            ins[i]=ins[i]/1024;//得到所在的
      }
//      for(int i=0;i<N;i++){
//            cout<<ins[i]<<"   ";
//      }
}

double FIFO(int page){
      hit_num=0;
      list<int>temp;
      for(int i=0;i<page;i++){
            temp.push_back(-1);
      }
      for(int i=0;i<N;i++){
            list<int>::iterator it=find(temp.begin(),temp.end(),ins[i]);
            if(it==temp.end()){
                  temp.pop_front();
                  temp.push_back(ins[i]);
            }else{
                  hit_num++;
            }
      }
      hit_num=hit_num/N;
      hit_num*=100;
      return hit_num;
}

double LRU(int page){
      hit_num=0;
      list<node>temp;
      for(int i=0;i<page;i++){
            temp.push_back(node{-1,0});
      }
      list<node>::iterator it;
      for(int i=0;i<N;i++){
            for(it=temp.begin();it!=temp.end();it++){
                  it->num++;
            }
            bool flag=false;
             for(it=temp.begin();it!=temp.end();it++){
                  if(it->id==ins[i]){
                        flag=true;
                        it->num=0;
                        hit_num++;
                        break;
                  }
             }
             if(!flag){
                  //找到一个最大的
                   list<node>::iterator max_it=temp.begin();
                   for(it=temp.begin();it!=temp.end();it++){
                        if(it->num>max_it->num){
                              max_it=it;
                        }
                   }
                   temp.erase(max_it);
                   temp.push_back(node{ins[i],0});
             }
      }
      hit_num=hit_num*1.0/N;
      hit_num*=100;
      return hit_num;
}

double OPT(int page){
      list<int>temp;
      hit_num=0;
      for(int i=0;i<page;i++){
            temp.push_back(-1);
      }
      for(int i=0;i<N;i++){
            list<int>::iterator it=find(temp.begin(),temp.end(),ins[i]);
            if(it==temp.end()){
                  int max_id=-1;

                  list<int>::iterator ans;
                  for(it=temp.begin();it!=temp.end();it++){
                  //初始化
                        int cur=0x3f3f3f3f;
                        for(int j=i+1;j<N;j++){
                            if(ins[j]==*it){
                              cur=j;
                              break;
                            }
                        }
                        if(cur>max_id){
                              max_id=cur;
                              ans=it;
                        }
                  }
                  temp.erase(ans);
                  temp.push_back(ins[i]);

            }else{
                  hit_num++;
            }
      }
      hit_num=hit_num*1.0/N;
      hit_num*=100;
      return hit_num;
}

int main()
{
   get_input();
   cout<<"          三种算法命中率比较表格           "<<endl;
   cout<<"内存页块           FIFO             LRU               OPT"<<endl;
   for(int i=minn;i<=maxx;i++){
   printf("%d               %.2f             %.2f          %.2f\n",i,FIFO(i),LRU(i),OPT(i));
   }
    return 0;
}