//Name and Unumber: Thien Minh Nguyen (U11796783) & Phong Thanh Lu (U89713042)

/*
    A Huffman Tree optimizes data compression by translating characters into binary codes.
    It works by analyzing character frequencies: common symbols get compact codes, while rare ones
    receive longer sequences. Built using a priority queue (min-heap), the tree merges nodes
    starting with the least frequent, creating an efficient hierarchy. Once constructed, the tree
    can be serialized for compact storage or reused to decode compressed data with minimal overhead
 */

#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#include "HuffmanBase.hpp"
#include "HeapQueue.hpp"
#include <map>
#include <string>
#include <vector>
#include <stack>

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
    
    void destroyTree(HuffmanNode* node);
    void buildEncodingMap(HuffmanNode* node, const std::string& code);
    void serializeTreeHelper(HuffmanNode* node, std::string& result) const;
    HuffmanNode* deserializeTree(const std::string& serializedTree);
};

#endif 