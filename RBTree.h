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

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////RB tree//////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2 = NULLT>
class RBTree {

private :
	Node<T1, T2> *root;
	int size;
	int(*cmp)(const T1 &a, const T1 &b);

	int calcHeight(const Node<T1, T2> * const node) const;
	int calcSize(const Node<T1, T2> * const node) const;
	Node<T1, T2>* sRotateL(Node<T1, T2> *N1);
	Node<T1, T2>* sRotateR(Node<T1, T2> *N1);
	Node<T1, T2>* rotate(Node<T1, T2> *N1, const T1 &id);
	Node<T1, T2>* plug(Node<T1, T2> *node, const T1 &id);
	Node<T1, T2>* cut(Node<T1, T2> *node, const T1 &id);
	Node<T1, T2>* findRML(const Node<T1, T2>* const node) const;
public :
	// constructors and destructor
	RBTree();
	RBTree(int(*compare)(const T1 &a, const T1 &b));
	RBTree(const Node<T1, T2> &head, int(*compare)(const T1 &a, const T1 &b) = NULL);
	RBTree(const T1 &rootID, const T2 * const rootRcd = NULL, int(*compare)(const T1 &a, const T1 &b) = NULL);
	RBTree(const T1 &rootID, const T2 &rootRcd, int(*compare)(const T1 &a, const T1 &b) = NULL);
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
	cmp = NULL;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: RBTree
// DESCRIPTION: Constructor of RBTree class.
//   ARGUMENTS: int(*compare)(const T1 &a, const T1 &b) = NULL - the compare function
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
//				int(*compare)(const T1 &a, const T1 &b) = NULL - the compare function
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
//				int(*compare)(const T1 &a, const T1 &b) = NULL - the compare function
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
//				int(*compare)(const T1 &a, const T1 &b) = NULL - the compare function
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
	//cout << "Destructor: ";
	//if (root != NULL)
	//	cout << root->getID();
	//cout << endl;
	delete root;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: calcHeight
// DESCRIPTION: To get the height of a node in RB tree.
//   ARGUMENTS: const Node<T1, T2> * const node - the node of which the height we want
// USES GLOBAL: none
// MODIFIES GL: none
//     RETURNS: int
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-10
//							KC 2015-02-10
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
int RBTree<T1, T2>::calcHeight(const Node<T1, T2> * const node) const {
	if (node == NULL)
		return -1;
	return node->getHeight();
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
// DESCRIPTION: To add a root for the RB tree.
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
// DESCRIPTION: To delete all the nodes in the RB tree.
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
// DESCRIPTION: To find a node of a certain ID in RB tree.
//   ARGUMENTS: const T1 &id - the ID of the node that we want to find
// USES GLOBAL: none
// MODIFIES GL: none
//     RETURNS: T2*
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-10
//							KC 2015-02-10
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
T2 *RBTree<T1, T2>::find(const T1 &id) const {
	Node<T1, T2> *p = root;
	while ((p != NULL) && (cmp(p->getID(), id) != 0)) {
		if (cmp(id, p->getID()) > 0)
			p = p->getRgt();
		else
			p = p->getLft();
	}
	if (p == NULL)
		return NULL;
	return p->getRcd();
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: sRotateL
// DESCRIPTION: To find a node of a certain ID in RB tree.
//   ARGUMENTS: const T1 &id - the ID of the node that we want to find
// USES GLOBAL: none
// MODIFIES GL: none
//     RETURNS: T2*
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-10
//							KC 2015-02-10
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
Node<T1, T2>* RBTree<T1, T2>::sRotateL(Node<T1, T2> *N1) {
	
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: sRotateR
// DESCRIPTION: To find a node of a certain ID in RB tree.
//   ARGUMENTS: const T1 &id - the ID of the node that we want to find
// USES GLOBAL: none
// MODIFIES GL: none
//     RETURNS: T2*
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-10
//							KC 2015-02-10
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
Node<T1, T2>* RBTree<T1, T2>::sRotateR(Node<T1, T2> *N1) {

}

////////////////////////////////////////////////////////////////////////////////
//        NAME: rotate
// DESCRIPTION: The single rotation of Red-Black tree.
//   ARGUMENTS: Node<T1, T2> *N1 - the trouble finder node
//				const T1 &id - the id of the target node
// USES GLOBAL: none
// MODIFIES GL: root (possible)
//     RETURNS: Node<T1, T2>*
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-10
//							KC 2015-02-10
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
Node<T1, T2>* RBTree<T1, T2>::rotate(Node<T1, T2> *N1, const T1 &id) {

}

////////////////////////////////////////////////////////////////////////////////
//        NAME: plug
// DESCRIPTION: plug a node into the RB tree.
//   ARGUMENTS: Node<T1, T2> *N1 - the root of the subtree that contains the new node
//				const T1 &id - the id of the new node that is to be plugged in
// USES GLOBAL: none
// MODIFIES GL: root (possible)
//     RETURNS: Node<T1, T2>*
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-10
//							KC 2015-02-10
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
Node<T1, T2>* RBTree<T1, T2>::plug(Node<T1, T2> *node, const T1 &id) {
	if (node == NULL) {
		node = new Node<T1, T2>(id);
		++size;
	}
	else if (cmp(id, node->getID()) > 0) {
		node->AddRgt(this->plug(node->getRgt(), id));
		node = balance(node);
	}
	else if (cmp(id, node->getID()) < 0) {
		node->AddLft(this->plug(node->getLft(), id));
		node = balance(node);
	}
	return node;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: Insert
// DESCRIPTION: The user interface of inserting a node into the RB tree.
//   ARGUMENTS: const T1 &id - the id of the new node that is to be inserted
// USES GLOBAL: none
// MODIFIES GL: root (possible)
//     RETURNS: bool
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-10
//							KC 2015-02-10
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
bool RBTree<T1, T2>::Insert(const T1 &id) {
	root = plug(root, id);
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
template<class T1, class T2>
Node<T1, T2>* RBTree<T1, T2>::findRML(const Node<T1, T2>* const node) const{
	Node<T1, T2>* RML = node->getLft();
	if (RML == NULL)
		return NULL;
	while (RML->getRgt() != NULL)
		RML = RML->getRgt();
	return RML;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: cut
// DESCRIPTION: To cut a Node from the RB tree.
//   ARGUMENTS: Node<T1, T2> *N1 - the root of the subtree that node is deleted from
//				const T1 &id - the id of the new node that is to be deleted
// USES GLOBAL: none
// MODIFIES GL: root (possible)
//     RETURNS: Node<T1, T2>*
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-12
//							KC 2015-02-12
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
Node<T1, T2>* RBTree<T1, T2>::cut(Node<T1, T2> *node, const T1 &id) {
	Node<T1, T2> *tmp;
	if (node == NULL)
		return node;
	if (cmp(id, node->getID()) > 0) {
		tmp = cut(node->getRgt(), id);
		if (tmp == NULL)
			delete node->getRgt();
		node->AddRgt(tmp);
		node = balance(node);
	}
	else if (cmp(id, node->getID()) < 0) {
		tmp = cut(node->getLft(), id);
		if (tmp == NULL)
			delete node->getLft();
		node->AddLft(tmp);
		node = balance(node);
	}
	else {
		int Case;
		Case = 2 * (node->getLft() != NULL) + (node->getRgt() != NULL);

		switch (Case) {
		case 0 :	// node is a leaf
			return NULL;
		case 1 :	// node has no left son
			*node = *(node->getRgt());
			delete node->getRgt();
			node->AddRgt(NULL);
			node = balance(node);
			break;
		default :	// node has a left son, or has both left and right subtree
			Node<T1, T2> *RML = findRML(node);
			*node = *RML;
			tmp = cut(node->getLft(), RML->getID());
			if (tmp == NULL)
				delete node->getLft();
			node->AddLft(tmp);
			node = balance(node);
			break;
		}
	}
	return node;
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
	root = cut(root, id);
	return true;
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
