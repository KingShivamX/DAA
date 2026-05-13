// Practical 2.4 - Huffman Coding (Greedy)
// Build a binary tree by repeatedly merging the two lowest-frequency nodes.
// Characters with higher frequency get shorter codes. Time: O(n log n)

#include <bits/stdc++.h>
using namespace std;

struct Node {
    char ch;
    int freq;
    Node *left, *right;
    Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

// Min-heap comparator: lower frequency = higher priority
struct Compare {
    bool operator()(Node* a, Node* b) { return a->freq > b->freq; }
};

void printCodes(Node* root, string code) {
    if (!root) return;
    // Leaf node: print the character and its code
    if (!root->left && !root->right) {
        cout << root->ch << " : " << code << "\n";
        return;
    }
    printCodes(root->left,  code + "0");
    printCodes(root->right, code + "1");
}

void deleteTree(Node* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    int n;
    cout << "Enter number of characters: ";
    cin >> n;

    priority_queue<Node*, vector<Node*>, Compare> pq;
    for (int i = 0; i < n; i++) {
        char c; int f;
        cout << "Char freq: ";
        cin >> c >> f;
        pq.push(new Node(c, f));
    }

    // Merge two smallest nodes until one root remains
    while (pq.size() > 1) {
        Node* l = pq.top(); pq.pop();
        Node* r = pq.top(); pq.pop();
        Node* parent = new Node('-', l->freq + r->freq);
        parent->left  = l;
        parent->right = r;
        pq.push(parent);
    }

    cout << "Huffman Codes:\n";
    printCodes(pq.top(), "");
    deleteTree(pq.top());
    return 0;
}
