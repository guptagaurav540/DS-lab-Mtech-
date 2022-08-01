#include<iostream>
#include<vector>
#include<stack>
#include<stdlib.h>
#include <bits/stdc++.h>
#include"Graph.h"

int main()
{

    char file_name[100];
    printf("Enter Graph File name :");
    cin>>file_name;
    FILE *f=fopen(file_name,"r");
        
    int n,m;        // numnber of vertex and edge 
    
    fscanf(f,"%d %d\n",&n,&m);
    Graph G(n,m);
    while(!feof(f))
    {
        int v1,v2,w;
        fscanf(f,"%d %d %d\n",&v1,&v2,&w);
        G.add_edge(v1,v2,w);
    }
    
   
   
    cout<<"1. DFS sequence :\n";
    cout<<"2. Tarjan Algorithm \n";
    cout<<"3. Find minimum Graph :\n";
    cout<<"4. Semi-connected :\n";
    cout<<"5. Dijkstra :\n";
    cout<<"6. Print original graph :\n";
    cout<<"0 for exit:\n";
    int option;
        
    do{
        char dfs_image_name[100]="DFS_graph_image";;
        char graph_image_name[100]="graph_image";
        cout<<"Choose options :";
        cin>>option;
        int node;
        int *dfs_seq;
        vector<vector<int>> scc,scc2;
        switch (option)
        {
            case 1:
                G.DFS_S();
                G.print_DFS(dfs_image_name);
                cout<<"PNG Image file name \""<<dfs_image_name<<".png\" created :\n";
                cout<<"\n";
                break;
            case 2:
                cout<<"Tarjan algo :\n";
                G.tarjan();
                break;
            case 3:
                G.min_graph();
                break;
            case 4:
                cout<<"Semi connected find :\n";
                G.semi_connected();
                break;
            case 5:
                cout<<"Dijstra algo: \nEnter Starting Node :";
                cin>>node;
                if(node<=n)
                G.dijkstra(node);
                else
                cout<<"Node not exist \n";
                break;
            case 6:
                G.print_Graph(graph_image_name);
                cout<<"Graph image \""<<graph_image_name<<".png\" Created\n";
                break;
    
            default:
                cout<<"Wrong Choice :\n";

        }
    }
    while(option>0);
}
