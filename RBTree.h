/*
RBTree.h

Copyright (C) 2015-2019 Kingston Chan

This source code is provided 'as-is', without any express or implied
warranty. In no event will the author be held liable for any damages
arising from the use of this code.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this source code must not be misrepresented; you must not
claim that you wrote the original source code. If you use this source code
in a product, an acknowledgment in the product documentation would be
appreciated but is not required.

2. Altered source versions must be plainly marked as such, and must not be
misrepresented as being the original source code.

3. This notice may not be removed or altered from any source distribution.

Kingston Chan

*/

#ifndef RBTREE_H
#define RBTREE_H

#include "TreeNode.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

template<typename T1>
int dCmp(const T1 &a, const T1 &b) {
	if (a > b)
		return 1;
	if (a < b)
		return -1;
	return 0;
}

class RBERR {
public :
	std::string error;
	RBERR();
	RBERR(std::string info) {
		error = info;
	}
};

////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////RB tree//////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2 = NULLT>
class RBTree {

private :
	Node<T1, T2> *root;
	int size;
	int(*cmp)(const T1 &a, const T1 &b);

	static Node<T1, T2> *X, *P, *GP, *GGP;

	int calcSize(const Node<T1, T2> * const node) const;
	Node<T1, T2>* rotateLL(Node<T1, T2> *N1);
	Node<T1, T2>* rotateRR(Node<T1, T2> *N1);
	Node<T1, T2>* rotateLR(Node<T1, T2> *N1);
	Node<T1, T2>* rotateRL(Node<T1, T2> *N1);
	bool handleReorient();
	//Node<T1, T2>* findRML(const Node<T1, T2>* const node) const;
public :
	// constructors and destructor
	RBTree();
	RBTree(int(*compare)(const T1 &a, const T1 &b));
	RBTree(const Node<T1, T2> &head, int(*compare)(const T1 &a, const T1 &b) = dCmp);
	RBTree(const T1 &rootID, const T2 * const rootRcd = NULL, int(*compare)(const T1 &a, const T1 &b) = dCmp);
	RBTree(const T1 &rootID, const T2 &rootRcd, int(*compare)(const T1 &a, const T1 &b) = dCmp);
	RBTree(const RBTree<T1, T2> &New);
	~RBTree();

	bool setCmp(int(*compare)(const T1 &a, const T1 &b));
	bool addRoot(const T1 &id, const T2 * const rcd = NULL);
	bool addRoot(const T1 &id, const T2 &rcd);
	bool addRoot(const Node<T1, T2> &New);

	bool Insert(const T1 &id);
	//bool Delete(const T1 &id);
	bool empty();

	int getSize() const { return size; }
	int getHeight() const { return root->getHeight(); }
	T2 *find(const T1 &id) const;
	T1 rootID() const { return root->getID(); }
	bool print() const;
};

template<class T1, class T2>
Node<T1, T2>* RBTree<T1, T2>::X = NULL;

template<class T1, class T2>
Node<T1, T2>* RBTree<T1, T2>::P = NULL;

template<class T1, class T2>
Node<T1, T2>* RBTree<T1, T2>::GP = NULL;

template<class T1, class T2>
Node<T1, T2>* RBTree<T1, T2>::GGP = NULL;

////////////////////////////////////////////////////////////////////////////////
//        NAME: RBTree
// DESCRIPTION: Constructor of RBTree class.
//   ARGUMENTS: none
// USES GLOBAL: none
// MODIFIES GL: root, size, cmp;
//     RETURNS: none
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-10
//							KC 2015-02-10
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
RBTree<T1, T2>::RBTree() {
	root = NULL;
	size = 0;
	cmp = dCmp;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: RBTree
// DESCRIPTION: Constructor of RBTree class.
//   ARGUMENTS: int(*compare)(const T1 &a, const T1 &b) = dCmp - the compare function
// USES GLOBAL: none
// MODIFIES GL: root, size, cmp;
//     RETURNS: none
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-10
//							KC 2015-02-10
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
RBTree<T1, T2>::RBTree(int(*compare)(const T1 &a, const T1 &b)) {
	root = NULL;
	size = 0;
	cmp = compare;
}
////////////////////////////////////////////////////////////////////////////////
//        NAME: RBTree
// DESCRIPTION: Constructor of RBTree class.
//   ARGUMENTS: const Node<T1, T2> &head - the root node of the RB tree
//				int(*compare)(const T1 &a, const T1 &b) = dCmp - the compare function
// USES GLOBAL: none
// MODIFIES GL: root, size, cmp;
//     RETURNS: none
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-10
//							KC 2015-02-10
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
RBTree<T1, T2>::RBTree(const Node<T1, T2> &head, int(*compare)(const T1 &a, const T1 &b)) {
	root = new Node<T1, T2>(head);
	size = calcSize(root);
	cmp = compare;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: RBTree
// DESCRIPTION: Constructor of RBTree class.
//   ARGUMENTS: const T1 &rootID - the ID of the root node
//				const T2 * const rootRcd = NULL - the initial root record
//				int(*compare)(const T1 &a, const T1 &b) = dCmp - the compare function
// USES GLOBAL: none
// MODIFIES GL: root, size, cmp;
//     RETURNS: none
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-10
//							KC 2015-02-10
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
RBTree<T1, T2>::RBTree(const T1 &rootID, const T2 * const rootRcd, int(*compare)(const T1 &a, const T1 &b)) {
	root = new Node<T1, T2>(rootID, rootRcd);
	size = 1;
	cmp = compare;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: RBTree
// DESCRIPTION: Constructor of RBTree class.
//   ARGUMENTS: const T1 &rootID - the ID of the root node
//				const T2 &rootRcd - the initial root record
//				int(*compare)(const T1 &a, const T1 &b) = dCmp - the compare function
// USES GLOBAL: none
// MODIFIES GL: root, size, cmp;
//     RETURNS: none
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-10
//							KC 2015-02-10
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
RBTree<T1, T2>::RBTree(const T1 &rootID, const T2 &rootRcd, int(*compare)(const T1 &a, const T1 &b)) {
	root = new Node<T1, T2>(rootID, rootRcd);
	size = 1;
	cmp = compare;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: RBTree
// DESCRIPTION: Copy constructor of RBTree class.
//   ARGUMENTS: const RBTree<T1, T2> &Old - the RBTree that is to be copied
// USES GLOBAL: none
// MODIFIES GL: root, size, cmp;
//     RETURNS: none
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-10
//							KC 2015-02-10
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
RBTree<T1, T2>::RBTree(const RBTree<T1, T2> &Old) {
	size = Old.size;
	cmp = Old.cmp;
	root = new Node<T1, T2>;
	root->copy(Old.root);
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: RBTree
// DESCRIPTION: Destructor of RBTree class.
//   ARGUMENTS: none
// USES GLOBAL: none
// MODIFIES GL: root, size, cmp;
//     RETURNS: none
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-10
//							KC 2015-02-10
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
RBTree<T1, T2>::~RBTree() {
	cout << "Destructor: ";
	if (root != NULL)
		cout << root->getID();
	cout << endl;
	delete root;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: calcSize
// DESCRIPTION: To calculate the size of the tree with the root "node".
//   ARGUMENTS: const Node<T1, T2> * const node - the root the of tree
// USES GLOBAL: none
// MODIFIES GL: none
//     RETURNS: int
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-10
//							KC 2015-02-10
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
int RBTree<T1, T2>::calcSize(const Node<T1, T2> * const node) const {
	if (node == NULL)
		return 0;
	else
		return calcSize(node->getLft()) + calcSize(node->getRgt()) + 1;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: setCmp
// DESCRIPTION: To assign the compare function to the member function pointer.
//   ARGUMENTS: int(*compare)(const T1 &a, const T1 &b) - the compare function
// USES GLOBAL: none
// MODIFIES GL: cmp
//     RETURNS: bool
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-10
//							KC 2015-02-10
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
bool RBTree<T1, T2>::setCmp(int(*compare)(const T1 &a, const T1 &b)) {
	cmp = compare;
	return true;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: addRoot
// DESCRIPTION: To add a root for the RB tree.
//   ARGUMENTS: const T1 &id - the id of the root node
//				const T2 * const rcd - the record of the root node with default value NULL
// USES GLOBAL: none
// MODIFIES GL: root, size
//     RETURNS: bool
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-10
//							KC 2015-02-10
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
bool RBTree<T1, T2>::addRoot(const T1 &id, const T2 * const rcd) {
	if (root != NULL) {
		throw RBERR("root already exists");
	}
	root = new Node<T1, T2>(id, rcd);
	size = calcSize(root);
	return true;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: addRoot
// DESCRIPTION: To add a root for the RB tree.
//   ARGUMENTS: const T1 &id - the id of the root node
//				const T2 &rcd - the record of the root node
// USES GLOBAL: none
// MODIFIES GL: root, size
//     RETURNS: bool
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-10
//							KC 2015-02-10
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
bool RBTree<T1, T2>::addRoot(const T1 &id, const T2 &rcd) {
	if (root != NULL) {
		throw RBERR("root already exists");
	}
	root = new Node<T1, T2>(id, rcd);
	size = calcSize(root);
	return true;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: addRoot
// DESCRIPTION: To add a root for the Red-Black tree.
//   ARGUMENTS: const Node<T1, T2> &New - the copy of the root node
// USES GLOBAL: none
// MODIFIES GL: root, size
//     RETURNS: bool
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-10
//							KC 2015-02-10
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
bool RBTree<T1, T2>::addRoot(const Node<T1, T2> &New) {
	if (root != NULL) {
		throw RBERR("root already exists");
	}
	root = new Node<T1, T2>(New);
	size = calcSize(root);
	return true;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: empty
// DESCRIPTION: To delete all the nodes in the Red-Black tree.
//   ARGUMENTS: none
// USES GLOBAL: none
// MODIFIES GL: root, size
//     RETURNS: bool
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-10
//							KC 2015-02-10
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
bool RBTree<T1, T2>::empty() {
	if (root == NULL)
		return true;
	delete root;
	root = NULL;
	size = 0;
	return true;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: find
// DESCRIPTION: To find a node of a certain ID in Red-Black tree.
//   ARGUMENTS: const T1 &id - the ID of the node that we want to find
// USES GLOBAL: none
// MODIFIES GL: none
//     RETURNS: T2*
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-24
//							KC 2015-02-24
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
T2 *RBTree<T1, T2>::find(const T1 &id) const {
	X = P = GP = GGP = root;
	while ((X != NULL) && (cmp(X->getID(), id) != 0)) {
		GGP = GP;
		GP = P;
		P = X;
		if (cmp(id, X->getID()) > 0)
			X = X->getRgt();
		else
			X = X->getLft();
		flag = false;
		if (((X->getLft() != NULL) && (X->getLft()->getColor() == 1)) && ((X->getRgt() != NULL) && (X->getRgt()->getColor() == 1)))
			handleReorient();
	}
	if (X == NULL)
		return NULL;
	return X->getRcd();
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: rotateLL
// DESCRIPTION: The single rotation LL of Red-Black tree.
//   ARGUMENTS: Node<T1, T2> *N1 - the trouble finder node
// USES GLOBAL: none
// MODIFIES GL: root (possible)
//     RETURNS: Node<T1, T2>*
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-21
//							KC 2015-02-21
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
Node<T1, T2>* RBTree<T1, T2>::rotateLL(Node<T1, T2> *N1) {
	Node<T1, T2> *N2 = N1->getLft();
	N1->AddLft(N2->getRgt());
	N2->AddRgt(N1);
	N1->setColor(1 - N1->getColor());
	N2->setColor(2 - N2->getColor());
	return N2;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: rotateRR
// DESCRIPTION: The single rotation RR of Red-Black tree.
//   ARGUMENTS: Node<T1, T2> *N1 - the trouble finder node
// USES GLOBAL: none
// MODIFIES GL: root (possible)
//     RETURNS: Node<T1, T2>*
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-21
//							KC 2015-02-21
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
Node<T1, T2>* RBTree<T1, T2>::rotateRR(Node<T1, T2> *N1) {
	Node<T1, T2> *N2 = N1->getRgt();
	N1->AddRgt(N2->getLft());
	N2->AddLft(N1);
	N1->setColor(1 - N1->getColor());
	N2->setColor(1 - N2->getColor());
	return N2;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: rotateLR
// DESCRIPTION: The single rotation LR of Red-Black tree.
//   ARGUMENTS: Node<T1, T2> *N1 - the trouble finder node
// USES GLOBAL: none
// MODIFIES GL: root (possible)
//     RETURNS: Node<T1, T2>*
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-21
//							KC 2015-02-21
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
Node<T1, T2>* RBTree<T1, T2>::rotateLR(Node<T1, T2> *N1) {
	Node<T1, T2> *N2 = N1->getLft();
	Node<T1, T2> *N3 = N2->getRgt();
	N1->setColor(1 - N1->getColor());
	N3->setColor(1 - N3->getColor());
	N2->AddRgt(N3->getLft());
	N1->AddLft(N3->getRgt());
	N3->AddLft(N2);
	N3->AddRgt(N1);
	return N3;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: rotateRL
// DESCRIPTION: The single rotation RL of RB tree.
//   ARGUMENTS: Node<T1, T2> *N1 - the trouble finder node
// USES GLOBAL: none
// MODIFIES GL: root (possible)
//     RETURNS: Node<T1, T2>*
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-21
//							KC 2015-02-21
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
Node<T1, T2>* RBTree<T1, T2>::rotateRL(Node<T1, T2> *N1) {
	Node<T1, T2> *N2 = N1->getRgt();
	Node<T1, T2> *N3 = N2->getLft();
	N1->setColor(1 - N1->getColor());
	N3->setColor(1 - N3->getColor());
	N2->AddLft(N3->getRgt());
	N1->AddRgt(N3->getLft());
	N3->AddLft(N1);
	N3->AddRgt(N2);
	return N3;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: handleReorient
// DESCRIPTION: handle the reorientation including recoloring and rotation.
//   ARGUMENTS: none 
// USES GLOBAL: none
// MODIFIES GL: root (possible)
//     RETURNS: Node<T1, T2>*
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-23
//							KC 2015-02-23
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
bool RBTree<T1, T2>::handleReorient() {

	// recoloring
	X->setColor(1);
	if (X->getLft() != NULL)
		X->getLft()->setColor(0);
	if (X->getRgt() != NULL)
		X->getRgt()->setColor(0);

	if (P->getColor() == 1) {	// rotation
		int Case = (cmp(X->getID(), P->getID()) < 0) + ((cmp(P->getID(), GP->getID()) < 0) << 1);
		switch(Case) {
		case 0:	// single rotate with right
			if (GP == GGP)
				GGP = GP = rotateRR(GP);
			else if (cmp(GP->getID(), GGP->getID()) < 0)
				GGP->AddLft(rotateRR(GP));
			else
				GGP->AddRgt(rotateRR(GP));
			break;
		case 1:	// double rotate right-left
			if (GP == GGP)
				GGP = GP = rotateRL(GP);
			if (cmp(GP->getID(), GGP->getID()) < 0)
				GGP->AddLft(rotateRL(GP));
			else
				GGP->AddRgt(rotateRL(GP));
			break;
		case 2: // double rotate left-right
			if (GP == GGP)
				GGP = GP = rotateLR(GP);
			if (cmp(GP->getID(), GGP->getID()) < 0)
				GGP->AddLft(rotateLR(GP));
			else
				GGP->AddRgt(rotateLR(GP));
			break;
		case 3: // single rotate with right
			if (GP == GGP)
				GGP = GP = rotateRR(GP);
			if (cmp(GP->getID(), GGP->getID()) < 0)
				GGP->AddLft(rotateLL(GP));
			else
				GGP->AddRgt(rotateLL(GP));
			break;
		default:
			throw RBERR("Case out of range");
			return false;
		}
	}

	root->setColor(0);
	return true;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: Insert
// DESCRIPTION: Inserting a node into the RB tree.
//   ARGUMENTS: const T1 &id - the id of the new node that is to be inserted
// USES GLOBAL: none
// MODIFIES GL: root (possible)
//     RETURNS: bool
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-23
//							KC 2015-02-23
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
bool RBTree<T1, T2>::Insert(const T1 &id) {
	// special case (NULL tree) handling
	if (root == NULL) {
		root = new Node<T1, T2>(id);
		if (root == NULL) {
			throw RBERR("Out of space");
			return false;
		}
		++size;
		return true;
	}

	// find the right place to insert
	X = P = GP = GGP = root;
	while ((X != NULL) && (cmp(X->getID(), id) != 0)) {
		if (((X->getLft() != NULL) && (X->getLft()->getColor() == 1)) && ((X->getRgt() != NULL) && (X->getRgt()->getColor() == 1)))
			handleReorient();
		GGP = GP;
		GP = P;
		P = X;
		if (cmp(X->getID(), id) > 0)
			X = X->getLft();
		else
			X = X->getRgt();
	}

	// if the Node already exists
	if (X != NULL)
		return true;

	// create a new Node and concatenate it on the tree
	X = new Node<T1, T2>(id);
	if (X == NULL) {
		throw RBERR("Out of space");
		return false;
	}
	X->setColor(1);
	++size;
	if (cmp(id, P->getID()) < 0)
		P->AddLft(X);
	else
		P->AddRgt(X);
	if (P->getColor() == 1)
		handleReorient();

	return true;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: findRML
// DESCRIPTION: To find the rightmost posterity of a node in its left sub-tree.
//   ARGUMENTS: Node<T1, T2>* node - the top node
// USES GLOBAL: none
// MODIFIES GL: none
//     RETURNS: Node<T1, T2>*
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-11
//							KC 2015-02-11
////////////////////////////////////////////////////////////////////////////////
/*template<class T1, class T2>
Node<T1, T2>* RBTree<T1, T2>::findRML(const Node<T1, T2>* const node) const{
	Node<T1, T2>* RML = node->getLft();
	if (RML == NULL)
		return NULL;
	while (RML->getRgt() != NULL)
		RML = RML->getRgt();
	return RML;
}*/

////////////////////////////////////////////////////////////////////////////////
//        NAME: Delete
// DESCRIPTION: The user interface of deleting a node into the RB tree.
//   ARGUMENTS: const T1 &id - the id of the new node that is to be deleted
// USES GLOBAL: none
// MODIFIES GL: root (possible)
//     RETURNS: bool
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-10
//							KC 2015-02-10
////////////////////////////////////////////////////////////////////////////////
/*template<class T1, class T2>
bool RBTree<T1, T2>::Delete(const T1 &id) {
	root = cut(root, id);
	return true;
}*/

////////////////////////////////////////////////////////////////////////////////
//        NAME: print
// DESCRIPTION: print a tree with inorder traversal.
//   ARGUMENTS: none
// USES GLOBAL: none
// MODIFIES GL: none
//     RETURNS: bool
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-11
//							KC 2015-02-11
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
bool RBTree<T1, T2>::print() const {
	if (root != NULL) {
		root->print();
		return true;
	}
	else
		return false;
}

#endif
