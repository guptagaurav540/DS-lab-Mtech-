#include"treap.h"
using namespace std;
int main()
{
    cout << "Gaurav Kumar \nRoll-Number- 214101018\nMain Menu :\n";
    Treap tree1;

    int choice;
   
    cout << "1. Insert\n";
    cout << "2. Delete\n";
    cout << "3. Search\n";
    cout << "4. Print the tree :\n";
    cout << "5. Hight of Tree :\n";
    
    cout << "0. Exit\n";
    do
    {
        char name[]="abc";
        cout << "Enter your choice :";
        cin >> choice;
        int number, n;
        bool a = 0;
        char filename[20];
        switch (choice)
        {
        case 1:
            cout << "Enter inserted element :";
            cin >> number;
            tree1.insert(number);
            //tree1.Treap_Print(filename);
            
            cout << "New tree sequence is :";
            tree1.inorderprint();
            cout << "\n";

            break;
        case 2:
            tree1.inorderprint();
            cout << "Delete Number :";
            cin >> number;
            tree1.Delete(number);
            cout << "After deletion Nodes available in Tree :";
            tree1.inorderprint();
            cout << "\n";

            break;
        case 3:
            cout << "Search Element :";
            cin >> number;
            a = tree1.search(number);
            if (a == true)
            {
                cout << "Element is found in tree :\n";
            }
            else
            {
                cout << "Element Not found in tree :\n";
            }
            break;
        case 4:
            cout << "Enter File name :";
            cin >> filename;
            tree1.Treap_Print(filename);
            cout << "png file created :\n";

            break;
        case 5:
            cout<< "Height of Tree is "<<tree1.treap_height()<<"\n";
            break;
        default:

            break;
        }

    } while (choice != 0);
}
