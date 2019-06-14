#include <iostream>
#include <algorithm>
#include<stdio.h>
#include<windows.h>

using namespace std;
/// Global function
void gotoxy(int x, int y)
{
    static HANDLE h = NULL;
    if(!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = { x, y };
    SetConsoleCursorPosition(h,c);

}
int gety()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int y;
    if(GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
    {
        y = csbi.dwCursorPosition.Y;
    }
    return y;
}

template <class T>
class BSTnode
{
public:
    T data;
    BSTnode<T>* left;
    BSTnode<T>* right;
    BSTnode()
    {
        left = right = NULL;
    }
    BSTnode(T value)
    {
        data = value;
        left = right = NULL;
    }
};
template <class T>
class BSTFCI
{
public:
    BSTnode<T>* root;
    BSTFCI();
    BSTnode<T>* Insert(BSTnode<T>*& node,T value);
    void print_inorder(BSTnode<T>* node);
    void add(T value);
    int hieght(BSTnode<T>* current);
    bool isBalance(BSTnode<T>* current);
    friend bool issub(BSTnode<T>* original,BSTnode<T>* Totest);
    friend bool Equal(BSTnode<T>* root1,BSTnode<T>* root2);
    void print_range(BSTnode<T>* node,int start,int End);
    void flip(BSTnode<T>* node);
/// TO PLOT.
    void plottree(BSTnode<T> *root,int h,int H,int mid,int Y);
};
template <class T>
BSTFCI<T>::BSTFCI()
{
    root = NULL;
}
template <class T>
void BSTFCI<T>::print_inorder(BSTnode<T>* node)
{
    if(node != NULL)
    {
        if(node->left != NULL)
        {
            print_inorder(node->left);
        }

        cout << node->data << " ";
        if(node->right != NULL)
        {
            print_inorder(node->right);
        }

    }
    else
    {
        cout << "The tree is empty!" << endl;
    }
}
template <class T>
BSTnode<T>* BSTFCI<T>::Insert(BSTnode<T>*& node,T value)
{
/// If the tree still empty.
    if(node == NULL)
    {
        return new BSTnode<T>(value);
    }
    if(value < node->data)
    {
        node->left = Insert(node->left, value);
    }
    else if(value > node->data)
    {
        node->right = Insert(node->right,value);
    }

    return node;
}
template <class T>
void BSTFCI<T>::add(T value)
{
    root = Insert(root,value);
}
template <class T>
int BSTFCI<T>::hieght(BSTnode<T>* current)
{
/// if the tree is empty
    if(current == NULL)
    {
        return 0;
    }
    else  /// if the tree contains data.
    {
        int HightOfLeft = hieght(current->left);
        int HightOfright = hieght(current->right);

        return max(HightOfLeft,HightOfright) + 1;
    }
}
template <class T>
bool BSTFCI<T>::isBalance(BSTnode<T>* current)
{
    int HightOfLeft;
    int HightOfright;

    if(current == NULL)
        return true;

    HightOfLeft = hieght(current->left);
    HightOfright = hieght(current->right);

    if(abs(HightOfLeft - HightOfright) <= 1 && isBalance(current->left) && isBalance(current->right))
    {
        return true;
    }
    return false;
}
template <class T>
bool Equal(BSTnode<T>* root1,BSTnode<T>* root2)
{
/// if the two nodes not points to anything,that's my goal.
    if(root1 == NULL && root2 == NULL)
        return true;
/// if one of the nodes not point to anything and the other points to other node -> it's false.
    if(root1 == NULL || root2 == NULL)
        return false;

/// check if the data of both roots is same and data of the left and right subtree are also same.

    return(root1->data == root2->data && Equal(root1->left,root2->left) && Equal(root1->right,root2->right));
}

template <class T>
bool issub(BSTnode<T>* original,BSTnode<T>* Totest)
{
/// if the second tree has no values then it's also subtree.

    if(Totest == NULL)
        return true;

/// if the first tree has no values so there is no matching elements.

    if(original == NULL)
        return false;

/// check from the current node at each tree to see if there is a matching elements.

    if(Equal(original,Totest))
        return true;

/// Try the left node of the original tree ,if it's fail, try the right node.

    return issub(original->left,Totest) || issub(original->right,Totest);
}
template <class T>
void BSTFCI<T>::print_range(BSTnode<T>* node,int start,int End)
{

    /*********************************************************************************************
     The algorithm goes like this:                                                               *
                                                                                                 *
     1- if the value of root is greater than start value we will go to the left of tree          *
     2- if the value of root is less than End value we will go to the right                      *
     3- if the value of root fall in the range between start and end , we will print this value  *
                                                                                                 *
    *********************************************************************************************/

    if(node == NULL)
    {
        return;
    }
    if(node->data > start)
    {
        print_range(node->left,start,End);
    }
    if(node->data >= start && node->data <= End)
    {
        cout << node->data << " ";
    }
    if(node->data < End)
    {
        print_range(node->right,start,End);
    }
}
template <class T>
void BSTFCI<T>::flip(BSTnode<T>* node)
{
    /*****************************************************************************************************************************
     The algorithm goes like this:                                                                                               *
                                                                                                                                 *
     1- go to the left part of the tree until reach null , after this return and back to the previous node.                      *
     2- go to the right part of the tree from the current node until reach null , after this return and back to the previous node*
     3- swap the two child with each other                                                                                       *
                                                                                                                                 *
    *****************************************************************************************************************************/

    if(node == NULL)
    {
        return;
    }
    else
    {
        flip(node->left);
        flip(node->right);

        BSTnode<T>* temp = new BSTnode<T>();
        temp = root->left;
        root->left = root->right;
        root->right = temp;
    }
}
template <class T>
void BSTFCI<T>::plottree(BSTnode<T> *root,int h,int H,int mid,int Y)
{
    if(root==NULL)
    {
        return;
    }

    int x = mid;
    int y=Y+1+(H*(H+1))/2 - (h*(h+1))/2;
    gotoxy(x,y);
    printf("%d",root->data);
    if(root->right!=NULL)
    {
        for(int i=1; i<=(h-1); i++)
        {
            gotoxy(mid+i,y+i);
            printf("\\");
        }
        plottree(root->right,h-1,H,mid+h,Y);
    }
    if(root->left!=NULL)
    {
        for(int i=1; i<=(h-1); i++)
        {
            gotoxy(mid-i,y+i);
            printf("/");
        }
        plottree(root->left,h-1,H,mid-h,Y);
    }
}

int main()
{
    BSTFCI<int> o;
    BSTFCI<int> h;
    char choice;
    int entered_value;
    /**while(true)
    {
        cout << endl;
        cout<<"\n\t\t*********************************   Menu   ***************************************"<<endl;
        cout<<"\t\t*                                                                                  *";
        cout<<"\n\t\t*          1- To add to BST                                                        *";
        cout<<"\n\t\t*          2- To print In order                                                    *";
        cout<<"\n\t\t*          3- To print specific range.                                             *";
        cout<<"\n\t\t*          4- To flip the tree and print it.                                       *";
        cout<<"\n\t\t*          5- To check if the tree is balanced                                     *";
        cout<<"\n\t\t*          6- To plot the tree.                                                    *";
        cout<<"\n\t\t*          7- Enter tree to check if it's a subtree                                *";
        cout<<"\n\t\t*          8- To terminate the program                                             *";

        cout << endl;
        cin >> choice;
        switch(choice)
        {
        case '1':
        {
            cout << "Enter values for tree and if you finish , enter ctrl+z" << endl;
            while(true)
            {
                if(cin.eof())
                {
                    cin.clear();
                    break;
                }
                cin >> entered_value;
                o.add(entered_value);
            }

        }
        break;
        case '2':
        {
            cout << "The o tree contain: " << endl;
            o.print_inorder(o.root);
            cout << endl;
        }
        break;
        case '3':
        {
            int start;
            int End;
            cout << "Enter the start of the range: " << endl;
            cin >> start;
            cout << "Enter the end of the range: " << endl;
            cin >> End;

            o.print_range(o.root,start,End);

        }
        break;
        case '4':
        {
            o.flip(o.root);
            o.print_inorder(o.root);
        }
        break;
        case '5':
        {
            if(o.isBalance(o.root))
            {
                cout << "The tree is balanced!" << endl;
            }
            else
            {
                cout << "The tree is not balanced!" << endl;
            }
        }
        break;
        case '6':
        {
            int j;
            cout << "\nGraphical Plot of the Tree: " << endl;
            j = o.hieght(o.root);
            o.plottree(o.root,j,j,j*(j+1)/2,gety());
            cout << endl;
            cout << endl;
        }
        break;
        case '7':
        {
            cout << "Enter values for tree and if you finish , enter ctrl+z" << endl;
            while(true)
            {
                if(cin.eof())
                {
                    cin.clear();
                    break;
                }
                cin >> entered_value;
                h.add(entered_value);
            }
                if(issub(o.root,h.root))
                {
                    cout << "The new tree is a subtree of original tree" << endl;
                }
                else
                {
                    cout << "The new tree is not a subtree of original tree" << endl;
                }
            }break;
        case '8':
        {
            cout << "Thanks for using the program :)" << endl;
            exit(0);
        }break;
            default:
            {
                cout << "Error! , invalid input :(" << endl;
            }
            break;
        }
        }**/


        return 0;
    }
