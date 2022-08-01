#include <iostream>

#include <bits/stdc++.h>
using namespace std;

struct heapNode
{
    int node;
    int distance;
};

class Heap
{
    vector<heapNode *> arr;
    int size;

public:
    Heap()
    {
        size = 0;
    }

    void insert(int n, int d)
    {
        heapNode *h;
        h=new heapNode;

        h->node = n;
        h->distance = d;
        if (size == arr.size())
            arr.push_back(NULL);
        arr[size] = h;

        int x = size;
       // printf("a");
        while (x > 0)
        {
            int root = (x - 1) / 2;
            if (arr[x]->distance < arr[root]->distance)
            {
                heapNode *temp = arr[x];
                arr[x] = arr[root];
                arr[root] = temp;
            }
            else
            {
                break;
            }
            x = root;
        }
        size++;
    }
    void pop();
    heapNode *top()
    {
        return arr[0];
    }
    void print()
    {
        for(int i=0;i<size;i++)
        {
            cout<<arr[i]->distance<<" ";
        }
        cout<<"\n";
    }
    int size_()
    {
        return size;
    }
};
void Heap::pop()
{
    size--;
    
    arr[0] = arr[size];
    
    int x=0;
    //cout<<"size "<<size<<" \n";
    while(x<size)
    {
        int c1=2*x+1;
        int c2=2*x+2;
        if(size>c1 || size>c2)
        {
            if(arr[c1]->distance<arr[x]->distance)
            {
                heapNode *temp=arr[c1];
                arr[c1]=arr[x];
                arr[x]=temp;
                continue;
            }
            //if(size<c2)
            //{
              else  if(arr[c2]->distance<arr[x]->distance && size>c2)
                {
                    heapNode *temp=arr[c2];
                    arr[c2]=arr[x];
                    arr[x]=temp;
                }
            //}
            else
                break;
        }
        else{
            break;
        }
    }

}