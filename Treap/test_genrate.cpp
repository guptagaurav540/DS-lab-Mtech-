#include<iostream>
using namespace std;

#include <bits/stdc++.h>
#include <cstdlib> 
#include <ctime>
int main()
{
    char test[]="test1.txt";
    srand(time(0));
    int key_value;
    for(int x=0;x<5;x++)
    {
        cout<<"Number of Operations :";
        int total;

        cin>>total;
        if(total>20000)
        {
            cout<< "please try below 20000 oprations :\n";
            x--;
            continue;
        }
        set<int> key;     
       
        test[4]='0'+x;
        printf("percentage of input as a insert :");
        FILE *f=fopen(test,"w");
        int p1;
        cin>>p1;
        int count=0;
        while(count<total)
        {
            if((count%100)<p1*100/100){
                key_value=rand()%(total);

                if(key.count(key_value)==0){
                 
                    fprintf(f,"insert\t%d\n",key_value);
                    count++;
                    key.insert(key_value);

                }
            }
            else{
                key_value=rand()%(total);
                 if(key.count(key_value)!=0){
                 
                    fprintf(f,"delete\t%d\n",key_value);
                    count++;
                    key.erase(key_value);
                }
            }
        }
        fclose(f);
        
    }

}