#include "CalcList.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

CalcList::CalcList() : tail(nullptr), currentTotal(0.0), numOperations(0) {
}

CalcList::~CalcList() {
    // Delete all nodes
    while (tail != nullptr) {
        Node* temp = tail;
        tail = tail->prev;
        delete temp;
    }
}

double CalcList::total() const {
    return currentTotal;
}

void CalcList::newOperation(const FUNCTIONS func, const double operand) {
    // Check for division by zero
    if (func == DIVISION && operand == 0.0) {
        throw std::string("Division by zero");
    }

    // Compute new total
    double newTotal;
    switch (func) {
        case ADDITION:
            newTotal = currentTotal + operand;
            break;
        case SUBTRACTION:
            newTotal = currentTotal - operand;
            break;
        case MULTIPLICATION:
            newTotal = currentTotal * operand;
            break;
        case DIVISION:
            newTotal = currentTotal / operand;
            break;
        default:
            throw std::string("Invalid operation");
    }

    // Create new node
    Node* newNode = new Node;
    newNode->func = func;
    newNode->operand = operand;
    newNode->totalSoFar = newTotal;
    newNode->prev = tail;
    newNode->step = numOperations + 1;

    // Update tail and currentTotal
    tail = newNode;
    currentTotal = newTotal;
    numOperations++;
}

void CalcList::removeLastOperation() {
    if (tail == nullptr) {
        throw std::string("No operations to remove");
    }

    // Update currentTotal to the total before this operation
    if (tail->prev != nullptr) {
        currentTotal = tail->prev->totalSoFar;
    } else {
        currentTotal = 0.0;
    }

    // Remove last node
    Node* temp = tail;
    tail = tail->prev;
    delete temp;
    numOperations--;
}

std::string CalcList::toString(unsigned short precision) const {
    std::ostringstream oss;
    Node* current = tail;

    // Create an array to store the nodes
    int n = numOperations;
    Node** nodes = new Node*[n];
    int i = n - 1; // Start from the end of the array
    while (current != nullptr) {
        nodes[i--] = current;
        current = current->prev;
    }

    // Set the precision and fixed format once
    oss << std::fixed << std::setprecision(precision);

    // Now, output in reverse order
    for (int j = n - 1; j >= 0; --j) {
        Node* node = nodes[j];
        oss << node->step << ": ";

        // Get the total before this operation
        double prevTotal = (node->prev != nullptr) ? node->prev->totalSoFar : 0.0;

        // Output prevTotal
        oss << prevTotal;

        // Output operation
        switch (node->func) {
            case ADDITION:
                oss << " + ";
                break;
            case SUBTRACTION:
                oss << " - ";
                break;
            case MULTIPLICATION:
                oss << " * ";
                break;
            case DIVISION:
                oss << " / ";
                break;
        }

        // Output operand and result
        oss << node->operand << " = " << node->totalSoFar << "\n";
    }

    delete[] nodes;

    return oss.str();
}

int main() {
    try{
        CalcList calcList;
        calcList.newOperation(ADDITION, 10); 
        calcList.newOperation(MULTIPLICATION, 5);
        calcList.newOperation(SUBTRACTION, 15);
        calcList.newOperation(DIVISION, 7);
        calcList.removeLastOperation();
        calcList.newOperation(SUBTRACTION, 30);
        calcList.newOperation(ADDITION, 5);
        calcList.removeLastOperation();
        std::cout << calcList.toString(2) << std::endl;

        calcList.removeLastOperation();
        std::cout << calcList.toString(2) << std::endl;
    }
    catch(std::string& e){
        std::cout << "Error: " << e << std::endl;
    }

    return 0;
}