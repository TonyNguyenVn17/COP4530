# Huffman Code Generator
## COP 4530 Programming Project 3

## Overview
This project implements a Huffman code generator to compress strings with no loss of data (lossless compression). The implementation follows David Huffman's algorithm described in his paper "A Method for the Construction of Minimum-Redundancy Codes".

## Implementation Details

### Files Structure
- `HuffmanTree.hpp`: Header file defining the `HuffmanTree` class
- `HuffmanTree.cpp`: Implementation file for the `HuffmanTree` class
- `HuffmanBase.hpp` and `HuffmanBase.cpp`: Base class and utility functions
- `HeapQueue.hpp`: Implementation of a priority queue used for building the Huffman tree
- `TestStrings.hpp`: Test strings for validation
- `PP3Test.cpp`: Test cases for the Huffman code implementation
- `catch.hpp`: Test framework

### HuffmanTree Class Design

#### Class Definition (`HuffmanTree.hpp`)
The `HuffmanTree` class inherits from `HuffmanTreeBase` and implements:
```cpp
class HuffmanTree : public HuffmanTreeBase {
public:
    HuffmanTree();
    ~HuffmanTree();
    
    std::string compress(const std::string inputStr) override;
    std::string serializeTree() const override;
    std::string decompress(const std::string inputCode, const std::string serializedTree) override;
    
private:
    HuffmanNode* root;
    std::map<char, std::string> encodingMap;
    
    // Helper methods
    void destroyTree(HuffmanNode* node);
    void buildEncodingMap(HuffmanNode* node, const std::string& code);
    void serializeTreeHelper(HuffmanNode* node, std::string& result) const;
    HuffmanNode* deserializeTree(const std::string& serializedTree);
};
```

#### Key Instance Variables
- `root`: Pointer to the root node of the Huffman tree
- `encodingMap`: Maps characters to their Huffman codes (binary strings)

### Implementation Details (`HuffmanTree.cpp`)

#### 1. Compression Algorithm
The `compress(const std::string inputStr)` method implements:
1. Calculates frequency of each character in the input string
2. Creates leaf nodes for each character with their frequencies
3. Uses a priority queue to build the Huffman tree:
   - Repeatedly removes the two nodes with lowest frequencies
   - Creates a new internal node with these as children
   - Adds the new node back to the queue
4. Builds the encoding map by traversing the tree (0 for left, 1 for right)
5. Encodes the input string using the generated prefix codes

```cpp
std::string HuffmanTree::compress(const std::string inputStr) {
    // Clear any previous state
    if (root) {
        destroyTree(root);
        root = nullptr;
    }
    encodingMap.clear();
    
    // Calculate character frequencies
    std::map<char, size_t> freqMap;
    for (char c : inputStr) {
        freqMap[c]++;
    }
    
    // Create a priority queue
    HeapQueue<HuffmanNode*, HuffmanNode::Compare> pq;
    
    // Add leaf nodes to the priority queue
    for (const auto& pair : freqMap) {
        HuffmanNode* node = new HuffmanNode(pair.first, pair.second);
        pq.insert(node);
    }
    
    // Build the Huffman tree
    while (pq.size() > 1) {
        // Remove two nodes with lowest frequency
        HuffmanNode* node1 = pq.min();
        pq.removeMin();
        HuffmanNode* node2 = pq.min();
        pq.removeMin();
        
        // Create a new internal node with these two nodes as children
        size_t combinedFreq = node1->getFrequency() + node2->getFrequency();
        HuffmanNode* internalNode = new HuffmanNode('\0', combinedFreq, nullptr, node1, node2);
        
        // Set parent pointers
        node1->parent = internalNode;
        node2->parent = internalNode;
        
        // Add the new node back to the priority queue
        pq.insert(internalNode);
    }
    
    // The remaining node is the root of the Huffman tree
    if (!pq.empty()) {
        root = pq.min();
    }
    
    // Build the encoding map by traversing the tree
    buildEncodingMap(root, "");
    
    // Encode the input string using the encoding map
    std::string compressedStr;
    for (char c : inputStr) {
        compressedStr += encodingMap[c];
    }
    
    return compressedStr;
}
```

#### 2. Tree Serialization
The `serializeTree()` method:
- Serializes the Huffman tree using post-order traversal
- Adds 'L' followed by the character for leaf nodes
- Adds 'B' for branch (internal) nodes

```cpp
std::string HuffmanTree::serializeTree() const {
    std::string result;
    serializeTreeHelper(root, result);
    return result;
}

void HuffmanTree::serializeTreeHelper(HuffmanNode* node, std::string& result) const {
    if (node) {
        // Perform post-order traversal (left, right, node)
        serializeTreeHelper(node->left, result);
        serializeTreeHelper(node->right, result);
        
        // Add node information to result
        if (node->isLeaf()) {
            result += "L" + std::string(1, node->getCharacter());
        } else {
            result += "B";
        }
    }
}
```

#### 3. Decompression
The `decompress(const std::string inputCode, const std::string serializedTree)` method:
1. Deserializes the tree from the given serialized tree string
2. Uses the tree to decode the Huffman codes back to characters
3. For each bit in the input code:
   - Navigates left for '0', right for '1'
   - When a leaf node is reached, adds its character to the result and resets to the root

```cpp
std::string HuffmanTree::decompress(const std::string inputCode, const std::string serializedTree) {
    // First, deserialize the tree
    HuffmanNode* decompressRoot = deserializeTree(serializedTree);
    
    // Use the tree to decode the Huffman code
    std::string decompressedStr;
    HuffmanNode* current = decompressRoot;
    
    for (char bit : inputCode) {
        // Navigate the tree based on the bit
        if (bit == '0') {
            current = current->left;
        } else { // bit == '1'
            current = current->right;
        }
        
        // If we reach a leaf node, add its character to the result
        if (current && current->isLeaf()) {
            decompressedStr += current->getCharacter();
            // Reset to the root for the next character
            current = decompressRoot;
        }
    }
    
    // Clean up the temporary tree
    destroyTree(decompressRoot);
    
    return decompressedStr;
}
```

#### 4. Tree Deserialization
The `deserializeTree(const std::string& serializedTree)` method:
- Processes the serialized tree string character by character
- Uses a stack to build the tree
- For 'L', creates a leaf node and pushes it onto the stack
- For 'B', pops two nodes from the stack, creates a branch node with them as children, and pushes it back

```cpp
HuffmanNode* HuffmanTree::deserializeTree(const std::string& serializedTree) {
    std::stack<HuffmanNode*> nodeStack;
    
    size_t i = 0;
    while (i < serializedTree.length()) {
        if (serializedTree[i] == 'L') {
            // Leaf node: create a new node with the character
            i++; // Skip 'L'
            char c = serializedTree[i++];
            // Frequency doesn't matter for decompression, so we use 0
            HuffmanNode* leafNode = new HuffmanNode(c, 0);
            nodeStack.push(leafNode);
        } else if (serializedTree[i] == 'B') {
            // Branch node: pop two nodes and create a new internal node
            i++; // Skip 'B'
            
            if (nodeStack.size() < 2) {
                // Error handling: malformed serialized tree
                return nullptr;
            }
            
            // The right child was pushed most recently
            HuffmanNode* rightChild = nodeStack.top();
            nodeStack.pop();
            
            // The left child was pushed before that
            HuffmanNode* leftChild = nodeStack.top();
            nodeStack.pop();
            
            // Create internal node with these two nodes as children
            HuffmanNode* branchNode = new HuffmanNode('\0', 0, nullptr, leftChild, rightChild);
            
            // Set parent pointers
            leftChild->parent = branchNode;
            rightChild->parent = branchNode;
            
            // Push the branch node back onto the stack
            nodeStack.push(branchNode);
        } else {
            // Skip unexpected characters
            i++;
        }
    }
    
    // The final node on the stack is the root of the tree
    return nodeStack.empty() ? nullptr : nodeStack.top();
}
```

## Memory Management
Memory management is handled through:
- Constructor and destructor for proper initialization and cleanup
- The `destroyTree` method for recursively deleting all nodes in the tree

## How to Run the Tests
To compile and run the tests:
```bash
g++ -std=c++17 -Wall *.cpp -o pp3_test
./pp3_test -s
```

The test cases verify the implementation with four different strings (turing, dijkstra, wikipedia, and constitution) for:
1. Compression (encoding)
2. Tree serialization
3. Decompression (decoding) 