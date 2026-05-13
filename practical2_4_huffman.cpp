/*
 * Huffman Encoding (Greedy Algorithm)
 *
 * ---------------------------------------------------------------
 * Builds an optimal prefix-free binary code for a set of characters
 * based on their frequencies. Characters with higher frequency get
 * shorter codes, minimizing total encoded message length.
 *
 * Algorithm:
 *   1. Insert each character as a leaf node in a min-heap.
 *   2. Repeatedly extract the two lowest-frequency nodes and
 *      merge them into a new internal node.
 *   3. The last remaining node is the root of the Huffman tree.
 *   4. Traverse the tree: left = '0', right = '1'.
 *
 * Time  : O(n log n)  — n heap operations, each O(log n)
 * Space : O(n)        — the tree has 2n - 1 nodes
 * ---------------------------------------------------------------
 */

#include <iostream>
#include <vector>
#include <queue>
#include <chrono>

using namespace std;

// ---- Huffman Tree Node -----------------------------------------------

struct HuffmanNode {
    char ch;           // character ('\0' for internal nodes)
    int  freq;         // frequency
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char c, int f)
        : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

// Min-heap comparator: lower frequency = higher priority
struct Compare {
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        return a->freq > b->freq;
    }
};

// ---- Build Tree ------------------------------------------------------

HuffmanNode* buildHuffmanTree(const vector<char>& chars, const vector<int>& freqs) {
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> minHeap;

    // Insert every character as a leaf node
    for (int i = 0; i < (int)chars.size(); i++)
        minHeap.push(new HuffmanNode(chars[i], freqs[i]));

    // Merge the two least frequent nodes until only one tree remains
    while (minHeap.size() > 1) {
        HuffmanNode* left  = minHeap.top(); minHeap.pop();
        HuffmanNode* right = minHeap.top(); minHeap.pop();

        // Internal node carries the combined frequency; no character
        HuffmanNode* merged = new HuffmanNode('\0', left->freq + right->freq);
        merged->left  = left;
        merged->right = right;

        minHeap.push(merged);
    }

    return minHeap.top();
}

// ---- Print Codes -----------------------------------------------------

// Traverse the tree and print each character's binary code
void printCodes(HuffmanNode* node, vector<int>& code) {
    if (!node)
        return;

    // Leaf node: print the character and the accumulated path as its code
    if (!node->left && !node->right) {
        cout << "  " << node->ch << "  :  ";
        for (int bit : code)
            cout << bit;
        cout << endl;
        return;
    }

    // Go left (bit = 0)
    code.push_back(0);
    printCodes(node->left, code);
    code.pop_back();

    // Go right (bit = 1)
    code.push_back(1);
    printCodes(node->right, code);
    code.pop_back();
}

// ---- Memory Cleanup --------------------------------------------------

void deleteTree(HuffmanNode* node) {
    if (!node) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

// ---- Main ------------------------------------------------------------

int main() {
    int n;
    cout << "Enter number of characters: ";
    cin >> n;

    vector<char> chars(n);
    vector<int>  freqs(n);

    cout << "Enter each character and its frequency:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "  Character " << i + 1 << " (char freq): ";
        cin >> chars[i] >> freqs[i];
    }

    auto start = chrono::high_resolution_clock::now();

    HuffmanNode* root = buildHuffmanTree(chars, freqs);

    auto stop     = chrono::high_resolution_clock::now();
    long long dur = chrono::duration_cast<chrono::microseconds>(stop - start).count();

    cout << "\nHuffman Codes:" << endl;
    cout << "  Char  :  Code" << endl;
    cout << "  -----------" << endl;

    vector<int> code;
    printCodes(root, code);

    cout << "\nTime: " << dur << " microseconds" << endl;

    deleteTree(root);
    return 0;
}
