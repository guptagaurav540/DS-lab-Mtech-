#include"heap.h"
using namespace std;
class Node{
        int node;                           // node store the detination vertices 
        int weight;                         // weight of edge 
        int edge_type;                      // type of edge 0 for tree edge 1 forward 2 cross edge 3 back edge 
        int  entry_time;                    // entry time of node during dfs 
        int exit_time;                      // remove time of node during dfs
        Node *next;                         // used for linklist adjacency list implementation
        
    public: 
        Node()                              // contructor 
        {
            node=-1;                        
            weight=0;
            next=NULL;
            edge_type=-1;
        }
        Node(int n)                          // constructor
        {
            node=n;
            weight=0;
            next=NULL;

            edge_type=-1;
        }

        // node contructor
        Node(int u,int v,int d)
        {
            node=v;
            weight=d;
            next=NULL;
            
            edge_type=-1;
        }
        // weight update 
        void Weight_update(int d);
       
        void next_update(Node *temp)
        {
            next=temp;
        }
       
        int edge();
        friend class Graph;
        
        
};
int Node::edge()
{
    return edge_type;
}
void Node::Weight_update(int d)
{
    weight=d;
}

class Graph{

    // store the adjacency list of vertices 
    vector<Node*> adjacency_list;           
    int n;                          // number of vertices 
    int m;                          // number of edged 
    int i,clock;                    
    int *low;                       

        bool *visited;
        int *num;
    public:

        Graph()
        {
            
        }
        Graph(int n,int m);                             // constructor for creating the graph
        void add_edge(int u,int v,int distance);        //
        void print_graph();                             
        void DFS(int start_node);                       
        void DFS2(int start_node,bool *sta,int *low2,vector<vector<int>> &scc_vector,stack<int> &stack_scc,int *i_t,int *visited_order,bool *visited_vertex);

        void DFS_S();
        void print_DFS(const char *filename );
        void print_Graph(const char *filename);
        void DFS3(int start_node,bool *visi);
        void dijkstra(int start_node);
        vector<vector<int>> tarjan();
        bool semi_connected();                          
        int* count_in_degree();
        int in_degree(int v)
        {
        	int count=0;
        	for(int x=1;x<=n;x++)
        	{
        		Node *temp=adjacency_list[x];
        		temp=temp->next;
				while(temp!=NULL)
				{
					if(temp->node==v)
						count++;
					temp=temp->next;
				}
			}
			return count;
		}
        
        int out_degree(int v)
        {
        	Node *temp=adjacency_list[v];
        	temp=temp->next;
        	int count=0;
			while(temp!=NULL)
        	{
        		count++;
        		temp=temp->next;
			}
			return count;
		}
        int no_of_node()
        {
            return n;
        }
        int visited_count()
        {
            int x=0;
            for(int i=1;i<=n;i++)
            {
                if(visited[i]==true)
                    x++;
            }
            return x;
        }
        int edge_delete(int u,int v);
        void min_graph();
        int helper(int start_node,int dest);
      
        
};

int Graph::helper(int start_node,int dest)
{
    bool *vis=new bool[n+1];
    for(int i=0;i<=n;i++)
        vis[i]=false;
    DFS3(start_node,vis);
    if(vis[dest]==true)
        return 1;
    return 0;
}


void Graph::DFS3(int start_node,bool *vis)
{
    // store the adjacency list
    Node *temp=adjacency_list[start_node];    
    temp=temp->next;
    // trsvese the graph
    vis[start_node]=true;
    while(temp!=NULL)
    {
        if(vis[temp->node]==false)
        {
            DFS3(temp->node,vis);
        }
        temp=temp->next;
    }
}

// finding the minimum number of edges in graph 
void Graph::min_graph()
{
    // create new graph with sa/
    Graph G_new(this->n,this->m);
    // copying the graph
    for(int i=1;i<=n;i++)
    {
        Node *temp=this->adjacency_list[i];
        temp=temp->next;
        while(temp!=NULL)
        {
            G_new.add_edge(i,temp->node,temp->weight);
            temp=temp->next;
        }
        
    }
    // find SCC for the graph
    cout<<"Original Graph SCC :\n";
    vector<vector<int>> scc_vector=this->tarjan();
    int scc_node_map[n+1];
    // map vertices with scc index
    for(int x=0;x<scc_vector.size();x++)
    {
        for(int j=0;j<scc_vector[x].size();j++)
        {
            scc_node_map[scc_vector[x][j]]=x;
   //         cout<<scc_vector[x][j]<<" "<<scc_node_map[scc_vector[x][j]]<<"\n";
        }
    }
    // create a boolean matrix of scc by scc size and initiaize all to false 
    // scc[i][j]=true means one vertex is included for scc i to scc j
    bool c[scc_vector.size()][scc_vector.size()];
    for (int i=0;i<scc_vector.size();i++)
    {
        for (int j=0;j<scc_vector.size();j++){
            c[i][j]=false;
        }
    }
    // traversing the all edge and removing one by one 
    for(int x=1;x<n+1;x++)
    {   
        Node *temp=adjacency_list[x];
        temp=temp->next;
        int count=0;
        while(temp!=NULL)
        {
            if(scc_node_map[x]==scc_node_map[temp->node])
            {
                // cout<<"same_compo"<<x<<" "<<temp->node<<"\n"
             //   cout<<G_new.in_degree(x)<<" "<<G_new.out_degree(temp->node)<<"\n";
                
			//	if(G_new.out_degree(x)>1 && G_new.in_degree(temp->node)>1){
				
					G_new.edge_delete(x,temp->node);
                
					if(G_new.helper(x,temp->node)==0 ||G_new.helper(temp->node,x)==0)
                	      G_new.add_edge(x,temp->node,temp->weight);
			///	}	

                
            }
            else
            {
                // edge between component
                if(c[scc_node_map[x]][scc_node_map[temp->node]]==false)
                {
                    c[scc_node_map[x]][scc_node_map[temp->node]]=true;
                 //   cout<<"leave"<<x<<" "<<temp->node<<"\n";
                
                }
                else{
                    G_new.edge_delete(x,temp->node);
                   // cout<<"removed"<<x<<" "<<temp->node<<"\n";
                }
            }
            temp=temp->next;
        }

    }
    // after removing we get minimize tree 
    cout<<"New minimized graph :\n";
    G_new.print_graph();
    cout<<"Mimimized Graph SCC :\n";
    // printing scc 
    G_new.tarjan();
    char minimized_graph[100]="minimized_graph";
    G_new.print_Graph(minimized_graph);
    cout<<"minimized Graph PNG image \""<<minimized_graph<<".txt\" created :\n";
    
}
/*

Graph Graph::min_graph2()
{
    Graph G_new(n,m);
    vector<vector<int>> scc_vector=this->tarjan();
    map<int,int> scc_node_map;
    for(int i=0;i<scc_vector.size();i++)
    {
        for(int j=0;j<scc_vector[i].size();j++)
        {
            scc_node_map.insert(pair<int,int>(scc_vector[i][j],i));
        }
    }
   

    bool c[scc_vector.size()][scc_vector.size()];
    for (int i=0;i<scc_vector.size();i++)
    {
        for (int j=0;j<scc_vector.size();j++){
            c[i][j]=false;
        }
    }
    for(int x=1;x<n+1;x++)
    {   
        Node *temp=this->adjacency_list[x];
        temp=temp->next;
        int count=0;
        while(temp!=NULL)
        {
            if(scc_node_map[x]==scc_node_map[temp->node])
            {
                G_new.add_edge(x,temp->node,temp->weight);
            }
            else
            {
                // edge between component
                if(c[scc_node_map[x]][scc_node_map[temp->node]]==false)
                {
                    G_new.add_edge(x,temp->node,temp->weight);
                    c[scc_node_map[x]][scc_node_map[temp->node]]=true;
                }
            }
            temp=temp->next;
        }

    }
    return G_new;
}
*/
// delete a edge from graph
int Graph::edge_delete(int u,int v)
{
    Node *temp=adjacency_list[u];
    Node *prev=temp;
    temp=temp->next;
    while(temp!=NULL)
    {
        if(temp->node==v)
        {
            prev->next=temp->next;
            return 1;
        }
        prev=temp;
        temp=temp->next;
    }
    return 0;
}

// constructore for graph it take number of verices(n) and number of edge(m) as a input 
Graph::Graph(int n,int m)
{
    this->n=n;          // initalize number of vertices
    this->m=m;          // initalize number of edges 
    visited=new bool[n+1];
    // create  a adjecency vector which store the node 
    adjacency_list.push_back(NULL);
    for(int i=1;i<n+1;i++)
    {
        Node *temp=new Node(i);
        adjacency_list.push_back(temp);
        visited[i]=false;
        
    }
    // initialize num
    num=(int *)malloc(sizeof(int)*(n+1));
    clock=0;
    // initialize low 
    low=(int *)malloc(sizeof(int )*(n+1));
    // initialize visited =0 initially no node is visited 
    for(int j=1;j<=n;j++)
    {
       visited[j]=false;
       num[j]=0;
    }
}

// count in degree of verices 
int* Graph::count_in_degree()
{
    int *count_d;
    // create a array of size of # of vertices 
    count_d=new int[n+1];
    // initialize count_node as 0 for every node 
    for(int i=0;i<n+1;i++)
        count_d[i]=0;
    // traverse adjacency list and increase the in degee for node 
    // if there is a node from u to v then in degree of v increase by one 
    for(int i=1;i<=n;i++)
    {
        Node *temp=adjacency_list[i];
        temp=temp->next;
        while(temp!=NULL)
        {
            count_d[temp->node]++;
            temp=temp->next;
        }
    }
    // return the count array
    return count_d;
}


/* check graph is semi-connected or not 
For checking semiconnected following steps are involved
    1.  calculate SCC
    2.  create a new graph by take one scc as a one vertices 
    3.  find the oth degree vertices for new created graph
    4.  assign it as root node 
    5.  implement dfs on root node 
    6.  If every node is reachable from root node then graph is semi connected 
*/
bool Graph::semi_connected()
{
    // finding Semi-Connected 

    cout<<"Testing semi connected :\n";
    cout<<"Finding strongly connected component :\n";
    // create new graph 
    vector<vector<int>> scc_com1=this->tarjan();
    Graph component_graph(scc_com1.size(),0);       // create new graph by taking a scc as a vertes
    // scc_vector contain the verices which belong to  same component 
    vector<int> scc_vector;
    // map vertices with component number 
    map<int,int> component_map;
    for(int i=0;i<scc_com1.size();i++)
    {
        for(int j=0;j<scc_com1[i].size();j++){
            component_map.insert(pair<int,int>(scc_com1[i][j],i+1));
        }
    }
    //cout<<"Create new graph of by taking a componet as vertex \n";
    for(int i=1;i<n;i++)
    {
        Node *temp=adjacency_list[i];
        int node=low[temp->node];
        temp=temp->next;
        while(temp!=NULL)
        {
    //        cout<<component_map[i]<<" "<<component_map[temp->node]<<"\n";
            component_graph.add_edge(component_map[i],component_map[temp->node],0);
            temp=temp->next;
        }
    }
    //char ss[100]="comp_graph";
    //component_graph.print_Graph(ss);
   // component_graph.print_graph();
    // count the in-degree of all verices in new graph
    int *count_degree=component_graph.count_in_degree();
    
    int dfs_node=-1,zero_count=0;
    // find the verices which have indegree as 0
    for(int vertex=1;vertex<=component_graph.no_of_node();vertex++)
    {
        //cout<<count_degree[vertex];
        if(count_degree[vertex]==0)
        {
            dfs_node=vertex;
            zero_count++;
        }
    }
    cout<<"Component Graph \"shrink_scc_graph.png\""<<"\n";
    char aa[]="shrink_scc_graph";
    component_graph.print_Graph(aa);
   
   // cout<<"dfs_node"<<dfs_node;
    if(zero_count!=1)
    {
        printf("Graph is not Semi-connected connected\n");
        return false;
    }
    component_graph.DFS(dfs_node);
    // check all verices visited or not if noyt then return graph is not semiconnected
    if(component_graph.visited_count()!=component_graph.n)
    {
        printf("Graph is not Semi-connected connected\n");       
        return false;
    }
    cout<<"Graph is Semi-Connected\n";
    return true;
}

// implement dijkstra algorithm 
// input is starting node 
/*
    steps-
    1.  initialize all vertices distance as infinity
    2.  distance of starting node is 0
    3.  create a min heap 
    4.  insert the staring node 
    5.  rum a loop untill the min-heap is not empty
        1.  remove veritices from heap which is at min distance
        2.  find distance of all adjacent elements
        3.  push adjacent nodes in heap 

*/
void Graph::dijkstra(int start_node)
{
    int *distance=new int[n+1];         // strore final distance of vertices 
    // initialization as infinite 
    for(int i=1;i<=n;i++)
    {
        distance[i]=INT_MAX;
    }
    // initialize distance of start node 
    distance[start_node]=0;
    // maintain a priority heap 
    Heap h;
    // insert the starting vertices 
    h.insert(start_node,0);

    while(h.size_()!=0)
    {
        // removing the minimum distance node 
        heapNode *min_node=h.top();
        h.pop();  
        int node=min_node->node;
        int dist=min_node->distance;
        Node *temp = adjacency_list[node];
        temp=temp->next;
        // find the adjecent nodes and update the distance 
        while(temp!=NULL)
        {
            if(distance[temp->node]>dist+temp->weight)
            {
                distance[temp->node]=dist+temp->weight;
                h.insert(temp->node,dist+temp->weight);
            }
            temp=temp->next;
        }
    }
    // print the distance table 
    cout<<"\n";

    cout<<"distance of diffrent nodes from "<<start_node<<":\n";
        cout<<"Node"<<setw(10)<<"distance"<<setw(15)<<"\n";
    int max=10000;
    for(int i=1;i<=n;i++)
    {
        if(distance[i]<max)
        cout<<i<<setw(10)<<distance[i]<<setw(15)<<"\n";
        else
        cout<<i<<setw(10)<<"infinity"<<setw(15)<<"\n";
        
    }   


}


// implement tarjan for finding the SCC components in graph 
vector<vector<int>> Graph::tarjan()
{

    // num is used as id
    int i_t=0;
    int count=0;
    bool *visited_vertex=new bool[n+1];


    bool *sta= new bool[n+1];       // stack is used for containing the circles node during dfs 
    int *low2=new int[n+1];         // use for assign the scc value 
    int *visited_order=new int[n+1];// contain the order of visited vertices 
    vector<vector<int >> scc_vector;       // contain the SCC components vericeas 

    stack<int> stack_scc;

    for(int j=0;j<=n;j++)
    {
        visited_vertex[j]=false;
        visited_order[j]=0;
        sta[j]=false;
        low2[i]=0;
    }
    // implement DFS on nodes from 1 to n
    // only in unvisited nodes 
    for(int j=1;j<=n;j++)
    {
        if(!visited_vertex[j]){
            DFS2(j,sta,low2,scc_vector,stack_scc,&i_t,visited_order,visited_vertex);
        }
    }
    
    // print the SCC nodes 
    cout<<"Number of SCC in Graph : " <<scc_vector.size()<<"\n";
    for(int i=0;i<scc_vector.size();i++)
    {
        cout<<"SCC :"<<i+1<<" : ";
        for(int j=0;j<scc_vector[i].size();j++)
        {
            cout<<scc_vector[i][j]<<" ";
        }
        cout<<"\n";
    }
            
    // return the SCC vector

    return scc_vector;
}

// find the minimum between two numbers 
int min(int a,int b)
{
    if(a<b)
        return a;
    return b;

}


// DFS function for tarjan algorithm 
void Graph::DFS2(int start_node,bool *sta,int *low2,vector<vector<int>> &scc_vector,stack<int> &stack_scc,int *i_t,int *visited_order,bool *visited_vertex)
{
    // push starting node in stack
    stack_scc.push(start_node);
    // mave sta[start_node]=true means this node is in stack
    sta[start_node]=true;

    // increment the  i values which is used as time 
    (*i_t)++;
    visited_order[start_node]=*i_t;              // contain the order of visted vertex
    low2[start_node]=*i_t;
    // visited of start_node is true 
    visited_vertex[start_node]=true;
    
    Node *temp=adjacency_list[start_node];
    temp=temp->next;
    // travese the list for node i (means find the adjacent elements of start node )
    while(temp!=NULL)
    {
        // if visited order is 0 means veritices is not visited yet so apply DFS on vertices 
        if(visited_order[temp->node]==0)
        {
            // apply DFS o vertex
            DFS2(temp->node,sta,low2,scc_vector,stack_scc,i_t,visited_order,visited_vertex);
        }   
        // if node is in stack means we are current traversing a SCC so low value of verext should be tne minimum vertex index of the SCC 
        if(sta[temp->node]==true)
        {
            
            low2[start_node]=min(low2[start_node],low2[temp->node]);
        }
        temp=temp->next;
    }
    // if visited order is same as low value then it belongs to same SCC component 
    if(visited_order[start_node]==low2[start_node])
    {
        // create a vector and store the verices which is belonging to same SCC 
        vector<int > vertices;
        while(stack_scc.size()!=0)
        {
            int x=stack_scc.top();
       //     cout<<x<<" ";
            
            stack_scc.pop();
            sta[x]=false;
            low2[x]=visited_order[start_node];
            vertices.push_back(x);
            if(x==start_node)
            {
                break;
            }
            
        }
        scc_vector.push_back(vertices);
    }
}

// print the graph   
void Graph::print_Graph(const char *filename)
{
    string dot_file_name="";
    dot_file_name=dot_file_name+filename+".dot";
    FILE *fp = fopen(dot_file_name.c_str(), "w");
    if (fp == NULL)
    {
        cout << "File creating Error :";
        return;
    }
    if(adjacency_list.size()!=0)
    {
        fprintf(fp, "digraph g{\n");
    }
    if(adjacency_list.size()!=0){
        for(int x=1;x<=n;x++)
        {
            Node *temp2=this->adjacency_list[x];        
            temp2=temp2->next;
            while(temp2!=NULL)
            {
                fprintf(fp, "%d->%d\n",x, temp2->node);           
                temp2=temp2->next;
            }
        
        }
        fprintf(fp, "}");
        fclose(fp);
        string png_file="";
        png_file=png_file+filename+".png";
        string s="dot -Tpng ";
        s=s+dot_file_name+" -o "+png_file;
        const char *command=s.c_str();
        system(command);
    }
    else
        fclose(fp);

}




void Graph::print_DFS(const char *filename)
{
    string dot_file_name="";
    dot_file_name=dot_file_name+filename+".dot";
    FILE *fp = fopen(dot_file_name.c_str(), "w");
    if (fp == NULL)
    {
        cout << "File creating Error :";
        return;
    }
    if(adjacency_list.size()!=0)
    {
        fprintf(fp, "digraph g{\n");
        fprintf(fp,"node [shape=record, height=0.1];\n");
        fprintf(fp, "label=\"T => Tree edge\nB => Back Edge \nF => forward edge\nC=> Cross edge\"\n\"entry_time|node|exit_time\"");
        
    	
            
	}
    if(adjacency_list.size()!=0){
        for(int i=1;i<=n;i++)
        {
            Node *temp=adjacency_list[i];
            Node *x=temp;
            fprintf(fp,"%d [label=\"<f0>%d|<f1>%d|<f2>%d\"];\n",temp->node,temp->entry_time,temp->node,temp->exit_time);
            
            temp=temp->next;
                 
            while(temp!=NULL)
            {
                if(temp->edge_type==0)
                {
                //    printf("Tree edge %d -> %d\n",i,temp->node);
                    fprintf(fp, "%d:f1->%d:f1[label=\"T\"]\n",i, temp->node);
            
                }
                else if(temp->edge_type==1)
                {
            //        printf("forward edge %d -> %d\n",i,temp->node);
                    fprintf(fp, "%d:f1->%d:f1[style=dotted][label=\"F\"]\n",i, temp->node);
            
              
                }
                else //if(temp->edge_type==2)
                {
                	if(adjacency_list[x->node]->entry_time > adjacency_list[temp->node]->entry_time &&adjacency_list[x->node]->exit_time > adjacency_list[temp->node]->exit_time )
                   	 fprintf(fp, "%d:f1->%d:f1[style=dotted][label=\"C\"]\n",i, temp->node);
                	else{
                		  fprintf(fp, "%d:f1->%d:f1[style=dotted][label=\"B\"]\n",i, temp->node);
					}
				}/*
                else if(temp->edge_type==3)
                {
                
                    //printf("Back edge %d -> %d\n",i,temp->node);
                    fprintf(fp, "%d:f1->%d:f1[style=dotted][label=\"B\"]\n",i, temp->node);
                }*/
                temp=temp->next;
            }
        
        }
        fprintf(fp, "}");
        fclose(fp);
        string png_file="";
        png_file=png_file+filename+".png";
        string stack_scc="dot -Tpng ";
        stack_scc=stack_scc+dot_file_name+" -o "+png_file;
        const char *command=stack_scc.c_str();
        system(command);

    }
    else{
        fclose(fp);
    }
}

void Graph::DFS_S()
{
    i=0;                    // using for visited sequence 
    cout<<"DFS Sequence :";
   
    for(int j=1;j<=n;j++)
    {
        num[i]=-1;                  // num[i] store the sequence of cisited node 
        visited[i]=false;
    }

    for(int j=1;j<=n;j++)
    {
        // apply dfs forom node 1 to n if node is unvisited 
        if(!visited[j]){
            DFS(j);
        }
    }
    // print the dfs sequence 
   /* for(int i=1;i<=n;i++)
    {
        cout<<num[i]<<" ";
    }*/  
    cout<<"\n";
}
void Graph::DFS(int start_node)
{
    // increase the i
    cout<<start_node<<" ";
    i++;
    // num[start_node] visited at ith number 
    num[start_node]=i;
    // visited of node is true 
    visited[start_node]=true;
    // store the adjacency list
    Node *temp=adjacency_list[start_node];

    // insert insert time of vertex in stack  
    adjacency_list[start_node]->entry_time=clock++;

    
    temp=temp->next;
    // trsvese the graph
    while(temp!=NULL)
    {
        if(num[temp->node]==0)
        {
            DFS(temp->node);
            // edge tyoe 0 means tree edge 
            temp->edge_type=0;
        }
        else if(num[temp->node]>num[start_node])
        {
            // edge type 1 menns  forward edge 
            temp->edge_type=1;
        }
        else if(visited[temp->node]==false)
        {
            // edge type 2 menas cross edge 
            temp->edge_type=2;
        }
        else
        {
            // edge type 3 means back edge 
            temp->edge_type=3;
        }
        temp=temp->next;
    }
    // put exit time of node 
    adjacency_list[start_node]->exit_time=clock++;
    
   
}

// add the edge(u,v) which have weight w
void Graph::add_edge(int u,int v,int w)
{
    if(u==v){
        return;
    }
    // store the list of u
    Node *temp=adjacency_list[u];
    
    while(temp->next!=NULL)
    {
        // finding the correct position of new inserted edge in linklist 
        if(temp->node==v)
        {
     //       printf("Edge already present\n");
            return;
        }
        temp=temp->next;
    }
    if(temp->node==v)
        return;
    Node *temp1=new Node(u,v,w);
    temp1->next=NULL;
    temp->next=temp1;
}


void Graph::print_graph()
{
    for(int i=1;i<=n;i++)
    {
        Node *temp=adjacency_list[i];
        cout<<"Node -> "<<temp->node<<"->";
      //  cout<<"entry_time "<<temp->entry_time<<" exit_time"<<temp->exit_time<<"\n";
        temp=temp->next;
        while(temp!=NULL)
        {
            cout<<temp->node<<" ";
            temp=temp->next;
        }
        printf("\n");
    }
}

