//http://www.cnblogs.com/IMGavin/
#include <iostream>
#include <stdio.h>
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

struct Node{
	Node *next, *pre;
	int val;

	Node(){
		next = pre = NULL;
	}

	Node(int v){
		next = pre = NULL;
		val = v;
	}
};

class LinkedList{
	Node *head, *rear;

public:
	LinkedList(){
		head = rear = NULL;
	}

	~LinkedList(){
		clear();
	}

	friend void mergeList(LinkedList &a, LinkedList &b);

	void pushFront(int val){
		Node *p = new Node(val);
		if(head == NULL){
			rear = head = p;
		}else{
			p -> next = head;
			head -> pre = p;
			head = p;
		}
	}

	void pushBack(int val){
		Node *p = new Node(val);
		if(head == NULL){
			rear = head = p;
		}else{
			rear -> next = p;
			p -> pre = rear;
			rear = p;
		}
	}

	int getFront(){
		if(head == NULL){
			return -1;
		}else{
			return head->val;
		}
	}

	int getBack(){
		if(head == NULL){
			return -1;
		}else{
			return rear->val;
		}
	}

	void removeBack(){
		if(head == NULL){

		}else{
			Node *pre = rear->pre;
			delete rear;
			rear = pre;
			if(rear){
				rear -> next = NULL;
			}else{
				head = NULL;
			}

		}
	}

	void removeFront(){
		if(head == NULL){

		}else{
			Node *next = head -> next;
			delete head;
			head = next;

			if(head){
				head -> pre = NULL;
			}else{
				rear = NULL;
			}
		}
	}

	void reverse(){
		if(head == NULL){
			return;
		}

		Node *p = head, *l = NULL;
		while(p){
			Node *r = p -> next;
			p -> next = l;
			p -> pre = r;
			l = p;
			p = r;
		}
		swap(head, rear);
	}

	void clear(){
		Node *p = head;
		while(p){
			Node *p_nxt = p -> next;
			delete p;
			p = p_nxt;
		}
		head = rear = NULL;
	}

	void print(){
		Node *p = head;
		while(p){
			cout<<p->val<<endl;
			p = p -> next;
		}
	}

};

void mergeList(LinkedList &a, LinkedList &b){
	if(b.head == NULL){
		return;
	}
	if(a.head){
		a.rear -> next = b.head;
		b.head -> pre = a.rear;
		a.rear = b.rear;
	}else{
		a.head = b.head;
		a.rear = b.rear;
	}

	b.head = b.rear = NULL;
}

int main(){
	LinkedList ls;
	for(int i = 0; i < 100; i++){
		ls.pushFront(i);
	}
	ls.print();
	return 0;
}
