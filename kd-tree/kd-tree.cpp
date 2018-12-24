#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#include <vector>
#include <map>
#include <stack>
#include <set>
#include <bitset>
#include <algorithm>
using namespace std;

const int DIM = 2;

const double EPS = 1e-6;

// cd: cutting dimension

class Node{
	double x[N];
public:
	Node(){

	}

	Node(const double data[]){
		for (int i = 0; i < DIM; i++){
			x[i] = data[i];
		}
	}

	~Node(){

	}

	bool operator==(const Node &tmp)const{
		for (int i = 0; i < DIM; i++){
			if(abs(x[i] - tmp.x[i]) > EPS){
				return false;
			}
		}
		return true;
	}

	int& operator[](int cd){
		return x[cd];
	}
	
};

class kd_tree{
	Node *root;

	Node *insert(Node *data_node, Node *&node, int cd){
		if (node == NULL){
			node = data_node;
		}else if(*node == *data_node){
			cout<<"error! duplicate"<<endl;
		}else if(*data_node[cd] < *node[cd]){
			node->left = insert(data_node, node->left, (cd + 1) % DIM);
		}else{
			node->right = insert(data_node, node->right, (cd + 1) % DIM);
		}
		return node;
	}

	Node *find_min(int cd, Node *node = root, int dim = 0){
		if(node == NULL){
			return NULL;
		}

		if(cd == dim){
			if(node->left == NULL){
				return node;
			}else{
				return find_min(cd, node->left, (cd + 1) % DIM);
			}
		}else{
			return 
		}

	}
public:
	kd_tree(){
		head = NULL;
	}

	~kd_tree(){

	}

	void insert(const double data[]){
		insert(new Node(data), root, 0);

	}

	
	Node *find_min(int cd){
		return find_min(cd, root, 0);
	}
};


int main(){
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);

	return 0;
}
