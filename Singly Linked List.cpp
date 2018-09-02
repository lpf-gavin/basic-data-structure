//http://www.cnblogs.com/IMGavin/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <exception>
#include <cstdlib>
#include <list>
using namespace std;


template<typename T>
class LinkedList{


	class Node{
		public:
		T data;
		Node *next;
		Node(){
			next = NULL;
		}

		Node(const T &t){
			data = t;
			next = NULL;
		}
	};

	Node *head = NULL;


public:
	LinkedList(){
		
	}

	~LinkedList(){
		if(head == NULL){
			return;
		}
		Node *p = head;
		while(1){
			Node *p_next = p -> next;
			delete p;
			if(p_next){
				p = p_next;
			}else{
				break;
			}

		}
		head = NULL;
	}

	void reverse(){
		Node *p = head, *l = NULL;
		while(p){
			Node *r = p->next;
			p->next = l;
			l = p;
			p = r;
		}
		head = l;
	}

	void print(){
		Node *p = head;
		while(p){
			cout<<p->data<<endl;
			p = p -> next;
		}

	}


	T get_front(){
		if(head == NULL){
			throw new exception();
		}
		return head->data;
	}

	T get_back(){
		if(head == NULL){
			throw new exception();
		}
		Node *p = head;
		while(1){
			if(p -> next){
				p = p -> next;
			}else{
				break;
			}
		}
		return p->data;
	}

	void push_back(const T &t){
		Node *new_p = new Node(t);
		if(new_p == NULL){
			throw new exception();
		}
		if(head == NULL){
			head = new_p;
		}else{
			Node *p = head;
			while(1){
				if(p->next){
					p = p->next;
				}else{
					break;
				}
			}
			p->next = new_p;
		}
	}

	void push_front(const T &t){
		Node *new_p = new Node(t);
		if(new_p == NULL){
			throw new exception();
		}
		if(head == NULL){
			head = new_p;
		}else{
			new_p -> next = head;
			head = new_p;
		}

	}

	void remove_front(){
		if(head == NULL){
			throw new exception();
		}
		Node *p = head->next;
		delete head;
		head = p;
	}

	void remove_back(){
		if(head == NULL){
			return;
		}
		Node *p = head, *fa = NULL;
		while(1){
			if(p -> next){
				fa = p;
				p = p -> next;
			}else{
				break;
			}
		}
		delete p;
		if(fa){
			fa -> next = NULL;
		}else{
			head = NULL;
		}
	}

	void remove_at(unsigned int k){
		if(head == NULL){
			throw new exception();
		}
		unsigned int i = 0;
		Node *p = head, *fa = NULL;
		while(1){
			if(i == k){
				break;
			}
			i++;
			if(p -> next){
				fa = p;
				p = p -> next;
			}else{
				break;
			}
		}
		if(i == k){
			if(fa){
				fa -> next = p -> next;
				delete p;
			}else{
				remove_front();
			}

		}else{
			throw new exception();
		}

	}

	bool empty(){
		return head == NULL;
	}

	unsigned int count(){
		
		if(head == NULL){
			return 0;
		}else{
			unsigned int cnt = 0;
			Node *p = head;
			while(1){
				cnt ++;
				if(p -> next){
					p = p -> next;
				}else{
					break;
				}
			}

			return cnt;
		}
	}

	
};

void test(){
	LinkedList<int>	 ll;
	list<int> ls;
	int n ;
	cin >> n;
	for(int i = 0; i < n; i++){
		unsigned int x = rand();
		if(x % 2){
			ll.push_back(x);
			ls.push_back(x);
		}else{
			ll.push_front(x);
			ls.push_front(x);
		}
		if(x % 211 == 0){
			cout<<x<<endl;
		}
		
		
		if(x % 5 == 0){
			if(!ls.empty()){
				int a = *ls.begin();
				int b = ll.get_front();
				if(a != b){
					cout<<"error"<<endl;
				}
				// cout<<a<<"\t"<<b<<endl;

				ls.erase(ls.begin());
				ll.remove_at(0);
			}
		}

		// cout<<"b"<<endl;
		if(x % 17 == 0){
			ll.push_front(x);
			ls.push_front(x);

			if(ls.size() > 10){
				for(int i = 0; i < 10; i++){
					ls.erase(ls.begin());
				}
				for(int i = 9; i >= 0; i--){
					ll.remove_at(i);
				}
				
			}
		}
		// cout<<"c"<<endl;

	}
}
int main(){
	test();
	return 0;
}
