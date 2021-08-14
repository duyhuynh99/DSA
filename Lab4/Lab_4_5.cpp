#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
using namespace std;

template<class K, class V>
class BinaryTree {
public:
	class Node;

private:
	Node *root;

public:
	BinaryTree() : root(nullptr) {}
	~BinaryTree() {
		// You have to delete all Nodes in BinaryTree. However in this task, you can ignore it.
	}

	class Node {
	private:
		K key;
		V value;
		Node *pLeft, *pRight;
		friend class BinaryTree<K, V>;

	public:
		Node(K key, V value) : key(key), value(value), pLeft(NULL), pRight(NULL) {}
		~Node() {}
	};

	void addNode(string posFromRoot, K key, V value) {
		if (posFromRoot == "") {
			this->root = new Node(key, value);
			return;
		}

		Node* walker = this->root;
		int l = posFromRoot.length();
		for (int i = 0; i < l - 1; i++) {
			if (!walker)
				return;
			if (posFromRoot[i] == 'L')
				walker = walker->pLeft;
			if (posFromRoot[i] == 'R')
				walker = walker->pRight;
		}
		if (posFromRoot[l - 1] == 'L')
			walker->pLeft = new Node(key, value);
		if (posFromRoot[l - 1] == 'R')
			walker->pRight = new Node(key, value);
	}
	/*
		Given class BinaryTree, you need to finish methods isBST() to determine if a tree is a binary search tree (BST)
	*/
	bool isBST(Node* root, Node* trai=NULL, Node* phai=NULL) { 
    // Base condition 
    if (root == NULL) 
        return true; 
    if (trai != NULL && root->value <= trai->value) 
        return false; 
    // if right node exist then check it has 
    // correct data or not i.e. right node's data 
    // should be greater than root's data 
    if (phai != NULL && root->value >= phai->value) 
        return false; 
    // check recursively for every node. 
    return isBST(root->pLeft, trai, root) && isBST(root->pRight, root, phai); 
} 
	bool isBST() {
		return isBST(this->root,NULL,NULL);
	}
};

int main() {
    BinaryTree<int, int> binaryTree;
    binaryTree.addNode("", 2, 4); // Add to root
    binaryTree.addNode("L", 3, 2); // Add to root's pLeft node
    binaryTree.addNode("R", 5, 9); // Add to root's right node
    cout << binaryTree.isBST();
	return 0;
}