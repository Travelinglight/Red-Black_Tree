#include "RBTree.h"

// define a class
class A {
public :
	int x;
	A(int id = 0) { x = id; }
	friend ostream &operator<<(ostream &out, A a);
	friend bool operator<(const A &a, const A &b);
	friend bool operator>(const A &a, const A &b);
};

ostream &operator<<(ostream &out, A a) {
	cout << a.x;
	return out;
}

bool operator<(const A &a, const A &b) {
	return (a.x < b.x);
}

bool operator>(const A &a, const A &b) {
	return (a.x > b.x);
}

// the compare function
int cmp(const A &a, const A &b) {
	if (a.x > b.x)
		return 1;
	if (a.x < b.x)
		return -1;
	return 0;
}

int main() {
	{ // RBTree();	RBTree(const RBTree<T1, T2> &New);	bool setCmp(int(*compare)(const T1 &a, const T1 &b));
	  // bool addRoot(const T1 &id, const T2 * const rcd = NULL);	bool addRoot(const T1 &id, const T2 &rcd);
	  // bool addRoot(const Node<T1, T2> &New);
	  	cout << "========================================" << endl;
		RBTree<int> RBT1;
		RBT1.addRoot(1);
		RBTree<A> RBT2;
		RBT2.setCmp(cmp);
		Node<A> Nd2(2);
		RBT2.addRoot(Nd2);
		RBTree<A, int>RBT3;
		RBT3.addRoot(3, 6);
		RBTree<A> RBT4(RBT2);
	}
	{ // RBTree(int(*compare)(const T1 &a, const T1 &b));
		cout << "========================================" << endl;
		RBTree<A> RBT1(cmp);
		for (int i = 1; i < 8; i++)
			RBT1.Insert(i);
		RBT1.print();
		cout << "----------------------------------------" << endl;
		RBT1.empty();
		RBT1.Insert(10);
		RBT1.Insert(85);
		RBT1.Insert(15);
		RBT1.Insert(70);
		RBT1.Insert(20);
		RBT1.Insert(60);
		RBT1.Insert(30);
		RBT1.Insert(50);
		RBT1.Insert(65);
		RBT1.Insert(80);
		RBT1.Insert(90);
		RBT1.Insert(40);
		RBT1.Insert(5);
		RBT1.Insert(55);
		//RBT1.Insert(64);
		//RBT1.Insert(66);
		//RBT1.Insert(67);
		RBT1.print();
		cout << "------------------delete----------------" << endl;
		RBT1.Delete(30);
		RBT1.print();
	}
	{
		cout << "==============deletion==================" << endl;
		RBTree<A> RBT1(cmp);
		for (int i = 1; i < 8; i++)
			RBT1.Insert(i);
		//RBT1.Delete(7);
		//RBT1.Delete(5);
		//RBT1.Delete(6);
		//RBT1.Delete(4);
		RBT1.print();
		cout << "----------------------------------------" << endl;
		RBTree<A> RBT2(cmp);
		for (int i = 7; i > 0; i--)
			RBT2.Insert(i);
		//RBT2.print();
		//RBT2.Delete(1);
		//RBT2.Delete(2);
		RBT2.Delete(4);
		//RBT2.Delete(6);
		RBT2.print();
	}
	{ // RBTree(const Node<T1, T2> &head, int(*compare)(const T1 &a, const T1 &b) = dCmp);
	  	cout << "========================================" << endl;
		Node<A> Nd1(1);
		RBTree<A> RBT1(Nd1);
		RBTree<A> RBT2(Nd1, cmp);
	}
	{ // RBTree(const T1 &rootID, const T2 * const rootRcd = NULL, int(*compare)(const T1 &a, const T1 &b) = dCmp);
	  	cout << "========================================" << endl;
		int a = 1, b = 2;
		RBTree<A, int> RBT1(1, &a, cmp);
		RBTree<A, int> RBT3(3, NULL, cmp);
		RBTree<A, int> RBT4(4, &b);
		RBTree<A, int> RBT5(5);
	}
	{ // RBTree(const T1 &rootID, const T2 &rootRcd, int(*compare)(const T1 &a, const T1 &b) = dCmp);
	  	cout << "========================================" << endl;
		RBTree<A, int> RBT1(1, 2, cmp);
		RBTree<A, int> RBT2(2, 3);
	}
	system("pause");
}
