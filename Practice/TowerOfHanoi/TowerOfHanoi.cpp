#include "iostream"
#include <stack>
#include <map>
#include <string>

using namespace std;

stack<int> A;
stack<int> B;
stack<int> C;

map<stack<int> *, string>names;

int countPush = 0;
int countPop;

void outputMove(int diskNum, string stackFrom, string stackTo) {
    std::cout << "Moving disk " << diskNum << " from post " << stackFrom << " to " << stackTo << std::endl;
}

void StacksOfHanoi  (
    int n, stack<int>& stackFrom, stack<int>& stackTo, stack<int>& stackAux) {
        if (n == 1){
            // calls outputMove with the top disk (stackFrom.top()) and the names of the source and destination stacks (names[&stackFrom] 
            // and names[&stackTo])
            stackTo.push(stackFrom.top()); countPush++;
            stackFrom.pop(); countPop++;
        } else {
            StacksOfHanoi(n - 1, stackFrom, stackAux, stackTo);
            outputMove(stackFrom.top(), names[&stackFrom], names[&stackTo]);
            stackTo.push(stackFrom.top()); countPush++;
            stackFrom.pop(); countPop++;

            StacksOfHanoi (n - 1, stackAux, stackTo, stackFrom);
        }
    }



int main(){
    names[&A] = "A";
    names[&B] = "B";
    names[&C] = "C";

    int n = 3;

    for (int i = n; i >= 1; i--){
        A.push(i);
    }

    StacksOfHanoi(n, A, C, B);

    // Stack C from top down
    while (!C.empty()) {
        cout << C.top() << " ";
        C.pop();
    }
    cout << endl;

    cout << "Push Ops: " << countPush << endl;
    cout << "Pop Ops: " << countPush << endl;

    return 0;
};