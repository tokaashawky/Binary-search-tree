#include <iostream>
using namespace std;

class Exception {
public:
    int code;
    string name;
    Exception(int code_, string name_) {
        code = code_;
        name = name_;
    }
};

class Node {
public:
    Node* right;
    Node* left;
    int data;
    Node(int _data) {
        right = NULL;
        left = NULL;
        data = _data;
    }
};

class tree {
public:
    Node* root;
    tree() { root = NULL; }
    ~tree() {}

    //-----------------------------------------------------------
    void add_data(int data) {
        Node* newnode = new Node(data);
        Node* parent = NULL;
        if (root == NULL) {
            root = newnode;
        } else {
            Node* current = root;
            while (current != NULL) {
                parent = current;
                if (data > current->data) {
                    current = current->right;
                } else {
                    current = current->left;
                }
            }
            if (data > parent->data) {
                parent->right = newnode;
            } else {
                parent->left = newnode;
            }
        }
    }
    //---------------------------------------------------------------
    void remove_node(int data) {
        Node* current = getNodeByData(data);
        if (current == NULL) {
            cout << "Node not found.\n";
            return;
        }
        if (current == root) { // Delete root
            if (current->right == NULL && current->left == NULL) {
                root = NULL;
            } else if (current->right == NULL) {
                root = root->left;
            } else if (current->left == NULL) {
                root = root->right;
            } else {
                Node* leftNode_root = root->left;
                Node* MRN = getMaxRight(leftNode_root);
                MRN->right = root->right;
                root = leftNode_root;
            }
        } else { // Delete non-root node
            Node* parent = getParent(current);
            Node* newChild = NULL;

            if (current->left == NULL && current->right == NULL) { // No children
                newChild = NULL;
            } else if (current->left == NULL) { // One child (right)
                newChild = current->right;
            } else if (current->right == NULL) { // One child (left)
                newChild = current->left;
            } else { // Two children
                Node* newparent = current->left;
                Node* maxLeft = getMaxRight(newparent);
                maxLeft->right = current->right;
                newChild = newparent;
            }

            if (parent->right == current) {
                parent->right = newChild;
            } else {
                parent->left = newChild;
            }
        }
        delete current;
    }

    //---------------------------------------------------------------
    int Max() {
        if (root == NULL) throw Exception(101, "Tree is empty");
        Node* node = getMaxRight(root);
        return node->data;
    }

    int Min() {
        if (root == NULL) throw Exception(101, "Tree is empty");
        Node* current = root;
        while (current->left != NULL) {
            current = current->left;
        }
        return current->data;
    }

    void DisplayAll() { Display(root); }

private:
    Node* getNodeByData(int data) {
        Node* Nod = root;
        while (Nod != NULL) {
            if (data > Nod->data) {
                Nod = Nod->right;
            } else if (data < Nod->data) {
                Nod = Nod->left;
            } else {
                return Nod;
            }
        }
        return NULL;
    }

    Node* getParent(Node* node) {
        Node* pNod = root;
        while (pNod != NULL) {
            if (pNod->right == node || pNod->left == node) {
                return pNod;
            } else if (node->data > pNod->data) {
                pNod = pNod->right;
            } else {
                pNod = pNod->left;
            }
        }
        return NULL;
    }

    Node* getMaxRight(Node* node) {
        Node* nod = node;
        while (nod->right != NULL) {
            nod = nod->right;
        }
        return nod;
    }

    void Display(Node* node) {
        if (node == NULL) return;
        Display(node->left);
        cout << node->data << "\t";
        Display(node->right);
    }
};

int main() {
    tree t1, t2;
    try {
        cout << "1st Tree Max: " << t1.Max() << endl; // Tree is empty
    } catch (Exception e) {
        cout << e.name << " (Code: " << e.code << ")" << endl;
    }

    t1.add_data(60);
    t1.add_data(80);
    t1.add_data(50);
    t1.add_data(55);
    t1.add_data(40);
    t1.add_data(70);
    t1.add_data(90);
    t1.add_data(30);
    t1.add_data(45);
    t1.add_data(95);
    t1.add_data(92);
    t1.add_data(91);
    cout << "Display All Tree:\n";
    t1.DisplayAll();
    cout << endl;

    cout << "Remove Leaf Node (45):\n";
    t1.remove_node(45);
    t1.DisplayAll();
    cout << endl;

    cout << "Remove Node with Right Child Only (80):\n";
    t1.remove_node(80);
    t1.DisplayAll();
    cout << endl;

    cout << "Remove Node with Left Child Only (95):\n";
    t1.remove_node(95);
    t1.DisplayAll();
    cout << endl;

    cout << "Remove Node with Two Children (50):\n";
    t1.remove_node(50);
    t1.DisplayAll();
    cout << endl;

    cout << "Remove Root Node (60):\n";
    t1.remove_node(60);
    t1.DisplayAll();
    cout << endl;

    cout << "********************************************************************************************\n";

    t2.add_data(55);
    t2.add_data(50);
    t2.add_data(40);

    cout << "Display All Tree 2:\n";
    t2.DisplayAll();
    cout << endl;

    cout << "Remove Root Node with Left Child Only (55):\n";
    t2.remove_node(55);
    t2.DisplayAll();
    cout << endl;

    cout << "1st Tree Max: " << t1.Max() << endl;
    cout << "1st Tree Min: " << t1.Min() << endl;

    cout << "2nd Tree Max: " << t2.Max() << endl;
    cout << "2nd Tree Min: " << t2.Min() << endl;

    cout << "Remove Nonexistent Node (1000): ";
    t1.remove_node(1000);
    t1.DisplayAll();
    cout << endl;

    return 0;
}
