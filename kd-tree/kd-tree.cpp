/*
Bibliography:
1 https://www.cs.cmu.edu/~ckingsf/bioinfo-lectures/kdtrees.pdf
2 http://www.dcc.fc.up.pt/~pribeiro/aulas/taa1516/rangesearch.pdf

*/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

const int DIM = 5;

const double EPS = 1e-6;

// cd: cutting dimension

class Node{
	double x[DIM];
    friend class kd_tree;
public:

	Node *left, *right;

	Node(){
		left = right = nullptr;
	}

	Node(const double data[]){
		left = right = nullptr;
		for (int i = 0; i < DIM; i++){
			x[i] = data[i];
		}
	}

	~Node(){
	}

	double operator[](int i)const{
		return x[i];
	}


	double distance(const Node &tmp)const{
		double s = 0;
		for (int i = 0; i < DIM; i++){
			s += (x[i] - tmp[i]) * (x[i] - tmp[i]);
		}
		return sqrt(s);
	}

	bool operator==(const Node &tmp)const{
		for (int i = 0; i < DIM; i++){
			if(abs(x[i] - tmp[i]) > EPS){
				return false;
			}
		}
		return true;
	}


	private:
	void set_data(const Node &tmp){
		for (int i = 0; i < DIM; i++){
			x[i] = tmp[i];
		}
	}

};

ostream& operator<<(ostream& os, const Node& node){
	for (int i = 0; i < DIM; i++){
		if(i){
			os<<" " << node[i];
		}else{
			os<<node[i];
		}
	}
	return os;
}

class kd_tree{
	Node *root;

	void clear(Node *&node){
		if (node){
			printf("l\n");
			clear(node->left);
			clear(node->right);
			delete node;
			node = nullptr;
		}
	}
	Node *insert(Node *&node, int cd, Node *data){
		if (node == nullptr){
			node = data;
		}else if(*node == *data){
			cout<<"error! duplicate"<<endl;
		}else if((*data)[cd] < (*node)[cd]){
			node->left = insert(node->left, (cd + 1) % DIM, data);
		}else{
			node->right = insert(node->right, (cd + 1) % DIM, data);
		}
		return node;
	}

	Node *find_min(Node *node, int cd, int dim = 0){
		if(node == nullptr){
			return nullptr;
		}
		int next_cd = (cd + 1) % DIM;

		if(cd == dim){
			if(node->left == nullptr){
				return node;
			}else{
				return find_min(node->left, next_cd, dim);
			}
		}else{
			Node *l = find_min(node->left, next_cd, dim);
			Node *r = find_min(node->right, next_cd, dim);
			if(l && (r == nullptr || ((*l)[dim] <= (*r)[dim])) && (node == nullptr || ((*l)[dim] <= (*node)[dim]))){
				return l;
			}

			if(node && (l == nullptr || ((*node)[dim] <= (*l)[dim])) && (r == nullptr || ((*node)[dim] <= (*r)[dim]))){
				return node;
			}
			// if(r && (l == nullptr || ((*r)[dim] <= (*l)[dim])) && (node == nullptr || ((*r)[dim] <= (*node)[dim]))){
			//just return
			return r;
			// }
		}
	}

	const Node *best;
	double best_dis;


	void find_nn(const Node *node, const Node &data, int cd){
		if(node == nullptr){
			return;
		}

		double dis = node->distance(data);
		if(best_dis < 0 || dis < best_dis){
			best = node;
			best_dis = dis;
		}
		int next_cd = (cd + 1) % DIM;
		// visit subtrees in most promising order
		if (data[cd] < (*node)[cd]){
			find_nn(node->left, data, next_cd);
			find_nn(node->right, data, next_cd);
		}else{
			find_nn(node->right, data, next_cd);
			find_nn(node->left, data, next_cd);
		}

	}


	Node *del_node(Node *&node, const Node &data, int cd){
		if(node == nullptr){
			printf("error while delete empty node\n");
			exit(-1);
		}
		int next_cd = (cd + 1) % DIM;
		// This is the point to delete
		if (*node == data){
			if (node->right){
				node->set_data(*find_min(node->right, next_cd, cd));
				node->right = del_node(node->right, data, next_cd);
			}else if(node->left){
				node->set_data(*find_min(node->left, next_cd, cd));
				node->right = del_node(node->left, data, next_cd);
				node->left = nullptr;
			}else{
				//leaf node
				delete node;
				node = nullptr;
			}
		}else if (data[cd] < (*node)[cd]){
			node->left = del_node(node->left, data, next_cd);
		}else{
			node->right = del_node(node->right, data, next_cd);
		}
		return node;
	}

public:
	kd_tree(){
		root = nullptr;
	}

	~kd_tree(){
		clear(root);
	}

	void insert(const double data[]){
		insert(root, 0, new Node(data));
	}


	const Node *find_min(int dim){
		if(dim < 0 || dim >= DIM){
			printf("error in find_min, dim is not in [0, DIM) \n");
			return nullptr;
		}
		return find_min(root, 0, dim);
	}

	const Node *del_node(const Node &data){
		return del_node(root, data, 0);
	}


	const Node *find_nn(const Node &data){
		best = nullptr;
		best_dis = -1;
		find_nn(root, data, 0);
		return best;
	}
};

double a[DIM] = {1, 4.1, 1340.99, 413, 0};
double b[DIM] = {1, 4.1, -1340.99, 413, -1};
double c[DIM] = {3441, -4, -1340.99, 413, -1};
double d[DIM] = {-3441, -4, -1340.99, 413, -1};

double e[DIM] = {-3441, 4, -1340, 413, 1};

int main(){
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	kd_tree t;
	t.insert(a);
	t.insert(b);
	t.insert(c);
	t.insert(d);
	cout<<(*(t.find_nn(d)))<<endl;
	t.del_node(Node(e));
	return 0;
}
