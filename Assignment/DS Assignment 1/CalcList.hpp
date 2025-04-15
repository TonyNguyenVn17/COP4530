#ifndef CALCLIST_H
#define CALCLIST_H

#include "CalcListInterface.hpp"
#include <string>

// Node structure for the linked list
struct Node {
    FUNCTIONS func;
    double operand;
    double totalSoFar;  // Total after this operation
    Node* prev;
    int step;           // Operation number
};

class CalcList: 
    public CalcListInterface {
    public:
        CalcList();  // Constructor
        ~CalcList(); // Destructor

    // Virtual functions from CalcListInterface
        double total() const;
        void newOperation(const FUNCTIONS func, const double operand);
        void removeLastOperation();
        std::string toString(unsigned short precision) const;


    private:
        Node* tail;          // Pointer to the last node
        double currentTotal; // Current total value
        int numOperations;   // Number of operations performed
};

#endif // CALCLIST_H
