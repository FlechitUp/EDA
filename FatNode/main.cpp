#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<vector>

using namespace std;

class node
{
    public:
        //int NrVersion ;///key
        int posFromFather ;
        vector<int> history;
        node *left = NULL;
        node *right = NULL;

        node(int nV){//NrVersion = nV;
                    posFromFather =nV;
                    history.push_back(nV);}
        void update(int a){ history.push_back(a);}
        bool newVersion(int pos){
            if (left == NULL){
                left = new node(pos);
                return true;
            }
            if (right == NULL){
                right = new node(pos);
                return true;
            }
            return false;
        }

};


bool newVersion(node *mynode, int pos){
    if(pos>mynode->history.size() ){return false;}
    if (mynode->left == NULL){
        mynode->left = new node(mynode->history[pos]);
        return true;
    }
    if (mynode->right == NULL){
        mynode->right = new node(mynode->history[pos]);
        return true;
    }
    return false;
}


void printVect(vector<int> myvect){
    cout<<"[";
    for (int i=0; i< myvect.size() ; i++){
        cout<<myvect[i];
    }
    cout<<"]"<<endl;
}


void inorder(struct node *root)
{
	if (root != NULL)
	{
        inorder(root->left);
		printVect(root->history);
		inorder(root->right);
	}
}


int main()
{
	/*
			50
		/	 \
		30	 70
		/ \ / \
	20 40 60 80 */
	node *root = new node(4);

	root->update(8);
	root->update(6);
	root->update(9);

	newVersion(root,2);
	newVersion(root,1);
	//newVersion(root,0);
	inorder(root);

	return 0;
}
