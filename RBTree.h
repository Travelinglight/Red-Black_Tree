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

	static Node<T1, T2> *X, *T, *P, *GP, *GGP;

	int calcSize(const Node<T1, T2> * const node) const;
	Node<T1, T2>* rotateLL(Node<T1, T2> *N1);
	Node<T1, T2>* rotateRR(Node<T1, T2> *N1);
	Node<T1, T2>* rotateLR(Node<T1, T2> *N1);
	Node<T1, T2>* rotateRL(Node<T1, T2> *N1);
	Node<T1, T2>* iRotateLL(Node<T1, T2> *N1);
	Node<T1, T2>* iRotateRR(Node<T1, T2> *N1);
	Node<T1, T2>* iRotateLR(Node<T1, T2> *N1);
	Node<T1, T2>* iRotateRL(Node<T1, T2> *N1);
	Node<T1, T2>* dRotateLL(Node<T1, T2> *N1);
	Node<T1, T2>* dRotateRR(Node<T1, T2> *N1);
	Node<T1, T2>* dRotateLR(Node<T1, T2> *N1);
	Node<T1, T2>* dRotateRL(Node<T1, T2> *N1);
	bool iHandleReorient();
	bool dHandleReorient(int dir = 0);
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
	bool Delete(const T1 &id);
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
Node<T1, T2>* RBTree<T1, T2>::T = NULL;

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
			iHandleReorient();
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
	return N2;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: rotateLR
// DESCRIPTION: The double rotation LR of Red-Black tree.
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
	N2->AddRgt(N3->getLft());
	N1->AddLft(N3->getRgt());
	N3->AddLft(N2);
	N3->AddRgt(N1);
	return N3;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: rotateRL
// DESCRIPTION: The double rotation RL of RB tree.
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
	N2->AddLft(N3->getRgt());
	N1->AddRgt(N3->getLft());
	N3->AddLft(N1);
	N3->AddRgt(N2);
	return N3;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: iRotateLL
// DESCRIPTION: The single rotation LL and recoloring of RB tree used for Insertion.
//   ARGUMENTS: Node<T1, T2> *N1 - the trouble finder node
// USES GLOBAL: none
// MODIFIES GL: root (possible)
//     RETURNS: Node<T1, T2>*
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-28
//							KC 2015-02-28
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
Node<T1, T2>* RBTree<T1, T2>::iRotateLL(Node<T1, T2> *N1) {
	Node<T1, T2> *N2 = N1->getLft();
	N1->setColor(1 - N1->getColor());
	N2->setColor(1 - N2->getColor());
	return rotateLL(N1);
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: iRotateRR
// DESCRIPTION: The single rotation RR and recoloring of RB tree used for Insertion.
//   ARGUMENTS: Node<T1, T2> *N1 - the trouble finder node
// USES GLOBAL: none
// MODIFIES GL: root (possible)
//     RETURNS: Node<T1, T2>*
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-28
//							KC 2015-02-28
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
Node<T1, T2>* RBTree<T1, T2>::iRotateRR(Node<T1, T2> *N1) {
	Node<T1, T2> *N2 = N1->getRgt();
	N1->setColor(1 - N1->getColor());
	N2->setColor(1 - N2->getColor());
	return rotateRR(N1);
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: iRotateLR
// DESCRIPTION: The double rotation LR and recoloring of RB tree used for Insertion.
//   ARGUMENTS: Node<T1, T2> *N1 - the trouble finder node
// USES GLOBAL: none
// MODIFIES GL: root (possible)
//     RETURNS: Node<T1, T2>*
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-28
//							KC 2015-02-28
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
Node<T1, T2>* RBTree<T1, T2>::iRotateLR(Node<T1, T2> *N1) {
	Node<T1, T2> *N2 = N1->getLft();
	Node<T1, T2> *N3 = N2->getRgt();
	N1->setColor(1 - N1->getColor());
	N3->setColor(1 - N3->getColor());
	return rotateLR(N1);
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: iRotateRL
// DESCRIPTION: The double rotation RL and recoloring of RB tree used for Insertion.
//   ARGUMENTS: Node<T1, T2> *N1 - the trouble finder node
// USES GLOBAL: none
// MODIFIES GL: root (possible)
//     RETURNS: Node<T1, T2>*
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-28
//							KC 2015-02-28
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
Node<T1, T2>* RBTree<T1, T2>::iRotateRL(Node<T1, T2> *N1) {
	Node<T1, T2> *N2 = N1->getRgt();
	Node<T1, T2> *N3 = N2->getLft();
	N1->setColor(1 - N1->getColor());
	N3->setColor(1 - N3->getColor());
	return rotateRL(N1);
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: iRotateLL
// DESCRIPTION: The single rotation LL and recoloring of RB tree used for Deletion.
//   ARGUMENTS: Node<T1, T2> *N1 - the trouble finder node
// USES GLOBAL: none
// MODIFIES GL: root (possible)
//     RETURNS: Node<T1, T2>*
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-28
//							KC 2015-02-28
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
Node<T1, T2>* RBTree<T1, T2>::dRotateLL(Node<T1, T2> *N1) {
	Node<T1, T2> *NL = N1->getLft();
	Node<T1, T2> *NR = N1->getRgt();
	Node<T1, T2> *NRR = NR->getRgt();

	N1->setColor(1 - N1->getColor());
	if (NL != NULL)
		NL->setColor(1 - NL->getColor());
	if (NR != NULL)
		NR->setColor(1 - NR->getColor());
	if (NRR != NULL)
		NRR->setColor(1 - NRR->getColor());
	return rotateLL(N1);
}


////////////////////////////////////////////////////////////////////////////////
//        NAME: iRotateRR
// DESCRIPTION: The single rotation RR and recoloring of RB tree used for Deletion.
//   ARGUMENTS: Node<T1, T2> *N1 - the trouble finder node
// USES GLOBAL: none
// MODIFIES GL: root (possible)
//     RETURNS: Node<T1, T2>*
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-28
//							KC 2015-02-28
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
Node<T1, T2>* RBTree<T1, T2>::dRotateRR(Node<T1, T2> *N1) {
	Node<T1, T2> *NL = N1->getLft();
	Node<T1, T2> *NR = N1->getRgt();
	Node<T1, T2> *NLL = NL->getLft();

	N1->setColor(1 - N1->getColor());
	if (NL != NULL)
		NL->setColor(1 - NL->getColor());
	if (NR != NULL)
		NR->setColor(1 - NR->getColor());
	if (NLL != NULL)
		NLL->setColor(1 - NLL->getColor());
	return rotateRR(N1);
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: iRotateLR
// DESCRIPTION: The double rotation LR and recoloring of RB tree used for Deletion.
//   ARGUMENTS: Node<T1, T2> *N1 - the trouble finder node
// USES GLOBAL: none
// MODIFIES GL: root (possible)
//     RETURNS: Node<T1, T2>*
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-28
//							KC 2015-02-28
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
Node<T1, T2>* RBTree<T1, T2>::dRotateLR(Node<T1, T2> *N1) {
	Node<T1, T2> *N2 = N1->getRgt();
	N1->setColor(1 - N1->getColor());
	if (N2 != NULL)
		N2->setColor(1 - N2->getColor());
	return rotateLR(N1);
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: iRotateRL
// DESCRIPTION: The double rotation RL and recoloring of RB tree used for Deletion.
//   ARGUMENTS: Node<T1, T2> *N1 - the trouble finder node
// USES GLOBAL: none
// MODIFIES GL: root (possible)
//     RETURNS: Node<T1, T2>*
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-28
//							KC 2015-02-28
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
Node<T1, T2>* RBTree<T1, T2>::dRotateRL(Node<T1, T2> *N1) {
	Node<T1, T2> *N2= N1->getLft();
	N1->setColor(1 - N1->getColor());
	if (N2 != NULL)
		N2->setColor(1 - N2->getColor());
	return rotateRL(N1);
}


////////////////////////////////////////////////////////////////////////////////
//        NAME: iHandleReorient
// DESCRIPTION: handle the reorientation including recoloring and rotation for insertion
//   ARGUMENTS: none 
// USES GLOBAL: none
// MODIFIES GL: root (possible)
//     RETURNS: Node<T1, T2>*
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-23
//							KC 2015-02-23
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
bool RBTree<T1, T2>::iHandleReorient() {

	// recoloring
	X->setColor(1);
	if (X->getLft() != NULL)
		X->getLft()->setColor(0);
	if (X->getRgt() != NULL)
		X->getRgt()->setColor(0);

	if ((P != X) && (P->getColor() == 1)) {	// rotation
		int Case = (cmp(X->getID(), P->getID()) < 0) + ((cmp(P->getID(), GP->getID()) < 0) << 1);
		switch(Case) {
		case 0:	// single rotate with right
			cout << "rotateRR" << endl;
			if (GP == GGP)
				root = iRotateRR(GP);
			else if (cmp(GP->getID(), GGP->getID()) < 0)
				GGP->AddLft(iRotateRR(GP));
			else
				GGP->AddRgt(iRotateRR(GP));
			break;
		case 1:	// double rotate right-left
			cout << "rotateRL" << endl;
			if (GP == GGP)
				root = iRotateRL(GP);
			else if (cmp(GP->getID(), GGP->getID()) < 0)
				GGP->AddLft(iRotateRL(GP));
			else
				GGP->AddRgt(iRotateRL(GP));
			break;
		case 2: // double rotate left-right
			cout << "rotateLR" << endl;
			if (GP == GGP)
				root = iRotateLR(GP);
			else if (cmp(GP->getID(), GGP->getID()) < 0)
				GGP->AddLft(iRotateLR(GP));
			else
				GGP->AddRgt(iRotateLR(GP));
			break;
		case 3: // single rotate with right
			cout << "rotateLL" << endl;
			if (GP == GGP)
				root = iRotateLL(GP);
			else if (cmp(GP->getID(), GGP->getID()) < 0)
				GGP->AddLft(iRotateLL(GP));
			else
				GGP->AddRgt(iRotateLL(GP));
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
			iHandleReorient();
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
		iHandleReorient();

	return true;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: dHandleReorient
// DESCRIPTION: handle the reorientation including recoloring and rotation for deletion
//   ARGUMENTS: int dir - indicate the direction X is moving towards 
// USES GLOBAL: none
// MODIFIES GL: root (possible)
//     RETURNS: Node<T1, T2>*
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-26
//							KC 2015-02-26
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
bool RBTree<T1, T2>::dHandleReorient(int dir) {
	int Case = 0;

	// decide the cases
	if (((X->getLft() != NULL) && (X->getLft()->getColor() == 1)) || ((X->getRgt() != NULL) && (X->getRgt()->getColor() == 1))) {
		Case |= 4;
		if ((dir == -1) && (X->getLft() != NULL) && (X->getLft()->getColor() == 1))
			Case |= 1;
		if ((dir == 1) && (X->getRgt() != NULL) && (X->getRgt()->getColor() == 1))
			Case |= 1;
	}
	else {
		if ((T->getLft() != NULL) && (T->getLft()->getColor() == 1))
			Case |= 1;
		else if ((T->getRgt() != NULL) && (T->getRgt()->getColor() == 1))
			Case |= 2;
	}

	// execute with respect to case
	switch(Case) {
	case 0:	// case 2A1
		P->setColor(0);
		X->setColor(1);
		T->setColor(1);
		return true;
	case 1:	// case 2A2
		if (cmp(X->getID(), P->getID()) < 0) {	// T is on the right, double rotation
			if (cmp(P->getID(), GP->getID()) < 0)
				GP->AddLft(dRotateRL(P));
			else
				GP->AddRgt(dRotateRL(P));
		}
		else {	// T is on the left, single rotation
			T->getLft()->setColor(0);
			if (cmp(P->getID(), GP->getID()) < 0)
				GP->AddLft(dRotateLL(P));
			else
				GP->AddRgt(dRotateLL(P));
		}
		X->setColor(1);
		return true;
	case 2:	// case 2A3
		if (cmp(X->getID(), P->getID()) < 0) {	// T is on the right, single rotation
			T->getRgt()->setColor(0);
			if (cmp(P->getID(), GP->getID()) < 0)
				GP->AddLft(dRotateRR(P));
			else
				GP->AddRgt(dRotateRR(P));
		}
		else {	// T is on the left, double rotation
			if (cmp(P->getID(), GP->getID()) < 0)
				GP->AddLft(dRotateLR(P));
			else
				GP->AddRgt(dRotateLR(P));
		}
		X->setColor(1);
		return true;
	case 4:	// case 2B2
		// move down
		GP = P;
		P = X;
		if (dir < 0) {
			X = P->getLft();
			T = P->getRgt();
			// rotate
			if (cmp(P->getID(), GP->getID()) < 0)
				GP->AddLft(dRotateRR(P));
			else
				GP->AddRgt(dRotateRR(P));

			// roll back
			X = P;
			P = T;
			T = P->getRgt();
		}
		else {
			X = P->getRgt();
			T = P->getLft();
			// rotate
			if (cmp(P->getID(), GP->getID()) < 0)
				GP->AddLft(dRotateLL(P));
			else
				GP->AddRgt(dRotateLL(P));

			// roll back
			X = P;
			P = T;
			T = P->getLft();
		}
		return true;
	case 5:	// case 2B1
		return true;
	default:
		throw RBERR("case out of range");
		return false;
	}
}

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
template<class T1, class T2>
bool RBTree<T1, T2>::Delete(const T1 &id) {
	int Case = -1;
	Node<T1, T2> *dp = NULL; // pointer to the target node's father

	if (root == NULL)
		return true;
	
	// find the Node
	GP = P = X = T = root;
	while ((X != NULL) && (cmp(id, X->getID()) != 0)) {
		if (X->getColor() == 0)
			dHandleReorient(cmp(id, X->getID()));
		GP = P;
		P = X;
		if (cmp(id, X->getID()) < 0) {
			X = X->getLft();
			T = P->getRgt();
		}
		else {
			X = X->getRgt();
			T = P->getLft();
		}
	}

	// not found
	if (X == NULL)
		return true;
	
	dp = X;	// mark the target's father
	
	// delete
	Case = ((X->getRgt() != NULL) << 1) + (X->getLft() != NULL);
	switch(Case) {
	case 0: // X is a leaf
		// reorientation
		if (X->getColor() == 0)
			dHandleReorient(0);
		// delete the node
		if (cmp(X->getID(), P->getID()) < 0)
			P->AddLft(NULL);
		else
			P->AddRgt(NULL);
		// release the space
		delete X;
		X = NULL;
		return true;
	case 1: // X has a left son
		// reorientation
		if (X->getColor() == 0)
			dHandleReorient(-1);
		// delete the root
		if (cmp(X->getID(), P->getID()) < 0)
			P->AddLft(X->getLft());
		else
			P->AddRgt(X->getLft());
		// release the space
		X->AddLft(NULL);
		delete X;
		X = NULL;
		return true;
	case 2: // X has a right son
		// reorientation
		if (X->getColor() == 0)
			dHandleReorient(1);
		// delete the root
		if (cmp(X->getID(), P->getID()) < 0)
			P->AddLft(X->getRgt());
		else
			P->AddRgt(X->getRgt());
		// release the space
		X->AddRgt(NULL);
		delete X;
		X = NULL;
		return true;
	case 3: // X has both left and right son
		// reorientation
		if (X->getColor() == 0)
			dHandleReorient(-1);
		// find the in-order predecessor
		GP = P;
		P = X;
		X = X->getLft();
		T = P->getRgt();
		if (X->getColor() == 0)
			dHandleReorient(1);
		while (X->getRgt() != NULL) {
			GP = P;
			P = X;
			X = X->getRgt();
			T = P->getLft();
			if (X->getColor() == 0)
				dHandleReorient(1);
		}
		// delete
		if (cmp(X->getID(), P->getID()) < 0)
			P->AddLft(X->getLft());
		else
			P->AddRgt(X->getLft());
		X->AddLft(NULL);
		*dp = *X;
		delete X;
		return true;
	default:
		throw RBERR("Case out of range");
		return false;
	}

}

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
