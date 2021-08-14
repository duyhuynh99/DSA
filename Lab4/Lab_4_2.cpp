#include<iostream>
#include<string>
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
		int bek = posFromRoot.length();
		for (int i = 0; i < bek - 1; i++) {
			if (!walker)
				return;
			else if (posFromRoot[i] == 'R')
				walker = walker->pRight;				
			else if (posFromRoot[i] == 'L')
				walker = walker->pLeft;
		}
		if (posFromRoot[bek - 1] == 'R')
			walker->pRight = new Node(key, value);
		else if (posFromRoot[bek - 1] == 'L')
			walker->pLeft = new Node(key, value);

	}
	
	int countTwoChildrenNode() { 
		return countTwoChildren(this->root);
		}
	int countTwoChildren(Node* root) {
		if (root == NULL)
		 return 0; 
		else if (root->pLeft != NULL && root->pRight != NULL) { return countTwoChildren(root->pLeft) + countTwoChildren(root->pRight) + 1; }
		return countTwoChildren(root->pLeft) + countTwoChildren(root->pRight);
	}
};

int main() {
	BinaryTree<int, int> binaryTree;
	binaryTree.addNode("", 2, 4); // Add to root
	binaryTree.addNode("L", 3, 6); // Add to root's left node
	binaryTree.addNode("R", 5, 9); // Add to root's right node
	cout << binaryTree.countTwoChildrenNode();
	return 0;
}