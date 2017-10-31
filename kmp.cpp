#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>

using namespace std;



//My first thought, the easiest way.
//Get the next[] table.
//O(n^2)
//It's too slow for some situation,
//so we need to figure out another way.
void getNext(char ptr[], int next[], int l)
{
    int i,j,k,t;
    char *p,*q;
    bool flag;
    for(i=0;i<l;i++) next[i]=-1;
    for(i=1;i<l;i++)
    {
        p = ptr;
        t = 0;
        flag = true;
        for(j=1;j<=i;j++)
        {
            p=ptr;
            q=ptr+j;
            t=0;
            while(t+j<l && *p==*q && next[t+j]<=t)
            {
                q++;
                p++;
                next[t+j]=t;
                t++;                
            }
        }
    }
    return;
}



//another way to get the next[] table.
//seems like dp
void getNext(char ptr[], int next[])
{
    int i,j,k=-1;
    next[0]=-1;
    int l = strlen(ptr);
    for(i=1;i<l;i++)
    {
        while(k>-1 && ptr[k+1]!=ptr[i])
            k=next[k];
        
        if(ptr[k+1]==ptr[i])
            k++;

        next[i]=k;

    }

    return;
}



//The matching peroid
//Use the next[] table that we just created.
//When the matching is failed,
//We don't have to fallback to the fist char if the next[k]>0;
void KMP(char str[], char ptr[], int next[])
{
    int slen = strlen(str);
    int plen = strlen(ptr);
    int i;
    int k = -1;
    for(i=0;i<slen;i++)
    {
        //fallback when the matching is failed
        while(k>-1 && ptr[k+1]!=str[i])  
            k = next[k];

        //matching
        if(ptr[k+1]==str[i])
            k++;
        
        //a pattern string is matched.
        //do something.
        if(k==plen-1) 
        {
            cout<<"matched:"<<i-plen+1<<endl;;
            i=i-plen+1;
            k=-1;
        }
    }
    return;
}


int main()
{
    char str[]="ddabcabcacabcabcacab";
    char ptr[]="abcabcacab";
    int next[20]={};
    int l = strlen(ptr);
    getNext(ptr,next);
    int i;
    cout<<ptr<<endl;
    cout<<str<<endl;
    for(i=0;i<l;i++) cout<<next[i]<<" ";
    cout<<endl;
    
    KMP(str,ptr,next);
	return 0;
}



