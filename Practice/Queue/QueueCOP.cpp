#include <iostream>

class QueueEmpty : public std::runtime_error {
public:
    QueueEmpty() : std::runtime_error("Queue is empty") {}
};

template <typename E>
class Queue {
public:
    int size() const;
    bool empty();
    const E& front() const throw(QueueEmpty);
    void enqueue (const E& e);
    void dequee() throw(QueueEmpty);
};