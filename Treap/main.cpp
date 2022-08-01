#include<iostream>
#include"treap.h"
#include"bst.h"
#include"avl.h"
#include<string.h>
using namespace std;

int main()
{
    
    srand(time(0));   
    char filename[]="data.csv";
    
    FILE *f_in=fopen(filename,"w");
    fprintf(f_in,"filename,tree_type,total_operation,insert,count_node,hight,comparision,rotation,average_hight\n");
    
   // test file name  
    char test[]="test1.txt";
    for(int x=0;x<5;x++)
    {
        // modify file name according to input file
        /*  file0.txt for x=0
            file1.txt for x=1
            file2.txt for x=2
            file3.txt for x=3
            file4.txt for x=4
        */

        test[4]='0'+x;
        cout<<"------------------------------------------------------------------------------------------------\n";
        cout<<test<<"File reading....\n";
        Treap T;                // create treap object
        BST B;                  // create BST object
        AVL_Tree A;             // create AVL object
        // opening test file 
        FILE *f=fopen(test,"r");
        char c[100];
        int d;
        int insert_count=0,delete_count=0;      // Variable for insert count and delete count 
              
        while(!feof(f))
        {
            //cout<<"a ";
            // read entry from file 
            fscanf(f,"%s\t%d\n",c,&d);
            /*
                input 500  => then insert 
                delete 200 => then delete 
            */
            if(strcmp(c,"insert")==0)
            {
                // insert in Treap
                T.insert(d);
                // insert in BST
                B.insert(d);
                // insert in AVL
                A.AVL_Insert(d);
                // increase insert count 
                insert_count++;

			}
            else{
                // delete from Treap
                T.Delete(d);
                // delete from BST
                B.Delete(d);
                // delete from AVL
                A.AVL_Delete(d);
                // increase delete count 
                delete_count++;
            }
            
        }
        int t=T.count_node();       // count number of node in Treap
        int a=A.count_node();       // count number of node in BST
        int b=B.count_node();       // count number of node in AVL
        float ht=float(T.average_node_height())/t;  // average height of Treap
        float ha=float(A.average_node_height())/a;  // average height of BST
        float hb=float(B.average_node_height())/b;  // average height of TAVL
        // insert treap data in data.txt
        fprintf(f_in,"%s,traep,%d,%d,%d,%d,%d,",test,insert_count+delete_count,insert_count,t,T.treap_height(),T.treap_comparision_count());
        fprintf(f_in,"%d,%f\n",T.treap_rotation_count(),ht);
        // insert BST data in data.txt
        fprintf(f_in,"%s,avl,%d,%d,%d,%d,%d,",test,insert_count+delete_count,insert_count,a,A.height(),A.comparision());
        fprintf(f_in,"%d,%f\n",A.rotation(),ha); 
        // insert AVL data in data.txt
        fprintf(f_in,"%s,bst,%d,%d,%d,%d,%d,",test,insert_count+delete_count,insert_count,b,B.height(),B.comparision());
        fprintf(f_in,"%d,%f\n",B.rotation(),hb); 
        
        int pri=12;

        cout.width(pri);
        cout<<"Type";
        cout.width(pri);
        cout<<"node count";
        cout.width(pri);
        cout<<"Height :";
        cout.width(pri);
        cout<<"comparision";
        cout.width(pri);
        cout<<"rotation";
        cout.width(25);
        cout<<"average_node_height";
        cout<<"\n";
      cout<<"=================================================================================================\n";
        
        cout.width(pri);
        cout<<"Treap";
        cout.width(pri);
        cout<<t;
        cout.width(pri);
        cout<<T.treap_height();
        cout.width(pri);
        cout<<T.treap_comparision_count();
        cout.width(pri);
        cout<<T.treap_rotation_count();
        cout.width(25);
        cout<<ht;
        cout<<"\n";
        
        cout.width(pri);
        cout<<"AVL";
        cout.width(pri);
        cout<<a;
        cout.width(pri);
        cout<<A.height();
        cout.width(pri);
        cout<<A.comparision();
        cout.width(pri);
        cout<<A.rotation();
        cout.width(25);
        cout<<ha;
        cout<<"\n";
        
        cout.width(pri);
        cout<<"BST";
        cout.width(pri);
        cout<<b;
        cout.width(pri);
        cout<<B.height();
        cout.width(pri);
        cout<<B.comparision();
        cout.width(pri);
        cout<<B.rotation();
        cout.width(25);
        cout<<hb;
        cout<<"\n\n";
        cout<<"Total Number of Insetrion : "<<insert_count<<"\n";
        cout<<"Total Number of Deletion : "<<delete_count<<"\n";
        cout<<"Total Operation :"<< insert_count+delete_count<<"\n";

    
     fclose(f);
    }
    fclose(f_in);
 
}
