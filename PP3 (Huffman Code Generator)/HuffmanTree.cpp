// Name and Unumber: Thien Minh Nguyen (U11796783) & Phong Thanh Lu (U89713042)

/* 
    This program compresses and decompresses text using Huffman Coding. First, t analyzes input
    to build a frequency-weighted binary tree, assigning shorter codes to recurring characters.
    Then the compressed output pairs these codes with a serialized tree, enabling lossless reconstruction
    of the original data. This would make it ideal for balancing compression ratios with processing speed.
 */
#include "HuffmanTree.hpp"
#include <map>
#include <string>
#include <vector>
#include <stack>

HuffmanTree::HuffmanTree() : root(nullptr) {}

// Cleans up the memory by destroying the Huffman tree
HuffmanTree::~HuffmanTree() {
    destroyTree(root);
    root = nullptr;
}

// Recursively deletes all nodes in the tree to free memory
void HuffmanTree::destroyTree(HuffmanNode* node) {
    if (node == nullptr) return;

    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
}

// Compresses the input string using Huffman coding and returns a binary string
std::string HuffmanTree::compress(const std::string inputStr) {
    if (inputStr.empty()) {
        return "";  // Return an empty string if there's nothing to compress
    }

    // Clean up previous tree and state
    destroyTree(root);
    root = nullptr;
    encodingMap.clear();

    // Count frequency of each character in the input string
    std::map<char, size_t> freqMap;
    for (char c : inputStr) {
        freqMap[c]+=1;
    }

    // Create a min-heap (priority queue) for HuffmanNode pointers
    HeapQueue<HuffmanNode*, HuffmanNode::Compare> pq;
    for (auto it = freqMap.begin(); it != freqMap.end(); ++it) {
        pq.insert(new HuffmanNode(it->first, it->second));  // Create a leaf node
    }

    // Build the Huffman tree using the priority queue
    while (pq.size() > 1) {
        HuffmanNode* left = pq.min(); pq.removeMin();
        HuffmanNode* right = pq.min(); pq.removeMin();

        size_t sumFreq = left->getFrequency() + right->getFrequency();
        HuffmanNode* parent = new HuffmanNode('\0', sumFreq, nullptr, left, right); // Internal node

        left->parent = parent;
        right->parent = parent;

        pq.insert(parent);
    }

    // Set the root to the last remaining node
    if (!pq.empty()) {
        root = pq.min();
    }

    // Build the encoding map (char → binary string) from the tree
    buildEncodingMap(root, "");

    // Encode the input string using the encoding map
    std::string compressed;
    for (char c : inputStr) {
        compressed += encodingMap[c];
    }

    return compressed;
}

// Helper function to build a map from characters to Huffman binary codes
void HuffmanTree::buildEncodingMap(HuffmanNode* node, const std::string& code) {
    if (node == nullptr) return;

    if (node->isLeaf()) {
        encodingMap[node->getCharacter()] = code;
    } else {
        buildEncodingMap(node->left, code + "0");  // Traverse left with '0'
        buildEncodingMap(node->right, code + "1"); // Traverse right with '1'
    }
}

// Serializes the Huffman tree into a post-order string representation
std::string HuffmanTree::serializeTree() const {
    std::string result;
    serializeTreeHelper(root, result);
    return result;
}

// Helper function for post-order tree serialization
void HuffmanTree::serializeTreeHelper(HuffmanNode* node, std::string& result) const {
    if (node == nullptr) return;

    serializeTreeHelper(node->left, result);
    serializeTreeHelper(node->right, result);

    if (node->isLeaf()) {
        result += "L";
        result += node->getCharacter();
    } else {
        result += "B";
    }
}

// Decompresses a binary string using a serialized Huffman tree
std::string HuffmanTree::decompress(const std::string inputCode, const std::string serializedTree) {
    // Reconstruct the Huffman tree from its serialized string
    HuffmanNode* treeRoot = deserializeTree(serializedTree);
    if (treeRoot == nullptr) {
        return "";  // If tree reconstruction fails, return empty string
    }

    std::string output;
    HuffmanNode* current = treeRoot;

    // Traverse the tree based on each bit in the input string
    for (char bit : inputCode) {
        if (bit == '0') {
            current = current->left;
        } else if (bit == '1') {
            current = current->right;
        }

        // If a leaf is reached, append the character and reset to root
        if (current && current->isLeaf()) {
            output += current->getCharacter();
            current = treeRoot;
        }
    }

    destroyTree(treeRoot);
    return output;
}

// Deserializes the tree from a post-order serialized string and reconstructs the Huffman tree
HuffmanNode* HuffmanTree::deserializeTree(const std::string& serializedTree) {
    std::stack<HuffmanNode*> stack;
    size_t i = 0;

    while (i < serializedTree.length()) {
        char symbol = serializedTree[i];

        if (symbol == 'L') {
            // Leaf node - next character is the value
            i+=1;
            if (i >= serializedTree.length()) return nullptr;

            char c = serializedTree[i++];
            HuffmanNode* leaf = new HuffmanNode(c, 0);
            stack.push(leaf);
        } else if (symbol == 'B') {
            // Branch node - pop two nodes and create a parent
            i+=1;
            if (stack.size() < 2) return nullptr;

            HuffmanNode* right = stack.top(); stack.pop();
            HuffmanNode* left = stack.top(); stack.pop();

            HuffmanNode* branch = new HuffmanNode('\0', 0, nullptr, left, right);
            left->parent = branch;
            right->parent = branch;

            stack.push(branch);
        } else {
            // Skip any invalid symbols
            i+=1;
        }
    }

    // Return the final tree root 
    if (stack.empty()) {
        return nullptr;
    } else {
        return stack.top();
    }
}
