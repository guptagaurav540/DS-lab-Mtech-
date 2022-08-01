#include<iostream>
using namespace std;

#include <bits/stdc++.h>
#include <cstdlib> 
#include <ctime>
int main()
{
    char file_name[]="data.csv";
    FILE *f_in=fopen(file_name,"w");
    fprintf(f_in,"filename,tree_type,total_operation,insert,count_node,hight,comparision,rotation,average_hight\n");
    fclose(f_in);
    char test[]="test1.txt";
    srand(time(0));
    int key_value;
    for(int x=0;x<5;x++)
    {
        cout<<"Number of Operations :";
        int total;

        cin>>total;
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