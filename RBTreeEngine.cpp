#include "RBTree.h"
#include "Student.h"
#include <iostream>
using namespace std;

int menu()
{
    int response = 0;
    
    cout << endl << "Menu:" << endl;
    cout << "1. insert" << endl;
    cout << "2. delete" << endl;
    cout << "3. print rbt" << endl;
    cout << "4. quit" << endl;
    cout << "Please input the option you would like: ";
    cin >> response;
    cout << "---------------------------------------" << endl;
    return response;
}
template <class T>
bool validateInput(int response, RBTree<T>* rbt, bool clearScreen)
/* returns a bool determining if the program should quit or not, 
 * true if the program should quit
*/
{
    bool quit = false;
    if(response >= 1 && response <= 5)
    {
        switch(response)
        {
            case 1:
            {
				rbt->rbtInsert();
                cout << (clearScreen?string(100, '\n'):"");
                break;
            }
            case 2:
            {
                cout << (clearScreen?string(100, '\n'):"");
				cout << "what would you like to delete?" << endl;
				int key = 0;
				cin >> key;
				T del = T(key);
                rbt->rbtDelete(rbt->rbtSearch(del));
                break;
            }
            case 3:
            {
                cout << (clearScreen?string(100, '\n'):"");
				cout << "How would you like to print it?" << endl;
				cout << "1. Inorder" << endl << "2. Preorder" << endl << "3. Postorder" << endl;
				int printChoice = 0;
				cin >> printChoice;
               	
				switch(printChoice)
				{
					case 1:
						rbt->inOrder();
						break;
					case 2:
						rbt->preOrder();
						break;
					case 3:
						rbt->postOrder();
						break;
				}
                break;
            }
            case 4:
            {
                //cout << "back";
                quit = true;
                break;
            }
            
        }//end switch
    }
    else
	{
        cout << (clearScreen?string(100, '\n'):"");
		cout << "Please enter a valid integer" << endl << endl;
	}
      return quit;          
}

int main()
{
    RBTree<int>* iRBTree = new RBTree<int>();
    RBTree<Student>* sRBTree = new RBTree<Student>();
    
    cout << "Choose a RBTree type" << endl << "0. Student" << endl << "1. Integer" << endl;
    bool isIRBTree = 0;
    cin >> isIRBTree;
    cout << "Clear screen?" << endl;
	bool clear = true;
	cin >> clear;
    cout << (clear?string(100, '\n'):"");
    bool quit = false;
    while(!quit)//menu asks for which option, which returns the choice into validateInput, which returns if the program should quit
    {
        if(isIRBTree)
            quit = validateInput<int>(menu(), iRBTree, clear);
        else
            quit = validateInput<Student>(menu(), sRBTree, clear);
        //RBTree->printRBTree();
    }
    return 0;
}
