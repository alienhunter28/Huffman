#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class HuffmanNode {
public:
    char data;
    int freq;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char c, int f) : data(c), freq(f), left(nullptr), right(nullptr) {}
};

struct CompareNodes {
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        return a->freq > b->freq;
    }
};

HuffmanNode* buildHuffmanTree(vector<char>& S, vector<int>& f) {
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, CompareNodes> minHeap;

    for (int i = 0; i < S.size(); ++i) {
        minHeap.push(new HuffmanNode(S[i], f[i]));
    }

    while (minHeap.size() > 1) {
        HuffmanNode* left = minHeap.top();
        minHeap.pop();
        HuffmanNode* right = minHeap.top();
        minHeap.pop();

        HuffmanNode* internalNode = new HuffmanNode('\0', left->freq + right->freq);
        internalNode->left = left;
        internalNode->right = right;

        minHeap.push(internalNode);
    }

    return minHeap.top();
}

void printHuffmanCodes(HuffmanNode* root, string code, vector<string>& result) {
    if (root == nullptr) {
        return;
    }

    if (root->data != '\0') {
        result.push_back(code + ": " + root->data);
        return;
    }

    printHuffmanCodes(root->left, code + '0', result);
    printHuffmanCodes(root->right, code + '1', result);
}

vector<string> huffmanCodes(vector<char>& S, vector<int>& f) {
    HuffmanNode* root = buildHuffmanTree(S, f);
    vector<string> result;
    printHuffmanCodes(root, "", result);
    return result;
}

int main() {
    vector<char> S = {'a', 'b', 'c', 'd', 'e', 'f'};
    vector<int> f = {5, 9, 12, 13, 16, 45};

    vector<string> codes = huffmanCodes(S, f);

    for (const string& code : codes) {
        cout << code << endl;
    }

    return 0;
}
