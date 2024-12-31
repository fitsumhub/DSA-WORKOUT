#include <iostream>
using namespace std;

// Node structure for the Circular Doubly Linked List
struct Node {
    int data; // Data held by the node
    Node* next; // Pointer to the next node
    Node* prev; // Pointer to the previous node

    Node(int value) : data(value), next(nullptr), prev(nullptr) {} // Constructor to initialize a node
};

class CircularDoublyLinkedList {
private:
    Node* head; // Pointer to the head of the list

public:
    // Constructor
    CircularDoublyLinkedList() : head(nullptr) {}

    // Destructor to free memory
    ~CircularDoublyLinkedList() {
        while (head) { // Continue until the list is empty
            deleteAtBeginning(); // Delete nodes one by one from the beginning
        }
    }

    // Insert at the beginning
    void insertAtBeginning(int value) {
        Node* newNode = new Node(value); // Create a new node
        if (!head) { // If the list is empty
            head = newNode;
            head->next = head; // Point to itself
            head->prev = head; // Point to itself
        } else {
            Node* tail = head->prev; // Get the tail node
            newNode->next = head; // New node points to current head
            newNode->prev = tail; // New node points to tail
            head->prev = newNode; // Current head points back to new node
            tail->next = newNode; // Tail points to new node
            head = newNode; // Update head to new node
        }
    }

    // Insert at the end
    void insertAtEnd(int value) {
        if (!head) { // If the list is empty
            insertAtBeginning(value); // Insert as the first node
        } else {
            Node* newNode = new Node(value); // Create a new node
            Node* tail = head->prev; // Get the tail node
            newNode->next = head; // New node points to head
            newNode->prev = tail; // New node points to tail
            tail->next = newNode; // Tail points to new node
            head->prev = newNode; // Head points back to new node
        }
    }

    // Insert at a specific position
    void insertAtPosition(int value, int position) {
        if (position <= 0) { // Check for invalid position
            cout << "Invalid position!" << endl;
            return;
        }
        if (position == 1 || !head) { // Insert at beginning if position is 1
            insertAtBeginning(value);
            return;
        }
        Node* temp = head;
        for (int i = 1; i < position - 1 && temp->next != head; ++i) {
            temp = temp->next; // Traverse to the desired position
        }
        Node* newNode = new Node(value); // Create a new node
        newNode->next = temp->next; // New node points to next node
        newNode->prev = temp; // New node points to current node
        temp->next->prev = newNode; // Next node points back to new node
        temp->next = newNode; // Current node points to new node
    }

    // Delete at the beginning
    void deleteAtBeginning() {
        if (!head) return; // If the list is empty, do nothing
        if (head->next == head) { // If only one node exists
            delete head; // Delete the node
            head = nullptr; // Update head to null
        } else {
            Node* tail = head->prev; // Get the tail node
            Node* temp = head; // Temporarily store the current head
            head = head->next; // Move head to the next node
            head->prev = tail; // Update head's previous pointer
            tail->next = head; // Update tail's next pointer
            delete temp; // Delete the old head
        }
    }

    // Delete at the end
    void deleteAtEnd() {
        if (!head) return; // If the list is empty, do nothing
        if (head->next == head) { // If only one node exists
            deleteAtBeginning(); // Delete the only node
        } else {
            Node* tail = head->prev; // Get the tail node
            tail->prev->next = head; // Update the second-last node's next pointer
            head->prev = tail->prev; // Update head's previous pointer
            delete tail; // Delete the tail node
        }
    }

    // Delete by value
    void deleteByValue(int value) {
        if (!head) return; // If the list is empty, do nothing
        Node* temp = head;
        do {
            if (temp->data == value) { // If value matches
                if (temp == head) { // If it's the head
                    deleteAtBeginning();
                } else if (temp->next == head) { // If it's the tail
                    deleteAtEnd();
                } else {
                    temp->prev->next = temp->next; // Update previous node's next pointer
                    temp->next->prev = temp->prev; // Update next node's previous pointer
                    delete temp; // Delete the current node
                }
                return;
            }
            temp = temp->next; // Move to the next node
        } while (temp != head); // Loop until we return to head
        cout << "Value not found!" << endl; // Value not found
    }

    // Delete at a specific position
    void deleteAtPosition(int position) {
        if (position <= 0 || !head) { // Check for invalid position or empty list
            cout << "Invalid position!" << endl;
            return;
        }
        if (position == 1) { // Delete the first node
            deleteAtBeginning();
            return;
        }
        Node* temp = head;
        for (int i = 1; i < position && temp->next != head; ++i) {
            temp = temp->next; // Traverse to the desired position
        }
        if (temp == head) { // Position out of range
            cout << "Position out of range!" << endl;
            return;
        }
        temp->prev->next = temp->next; // Update previous node's next pointer
        temp->next->prev = temp->prev; // Update next node's previous pointer
        delete temp; // Delete the current node
    }

    // Traverse forward
    void traverseForward() {
        if (!head) { // If the list is empty
            cout << "List is empty!" << endl;
            return;
        }
        Node* temp = head;
        do {
            cout << temp->data << " "; // Print the data
            temp = temp->next; // Move to the next node
        } while (temp != head); // Loop until we return to head
        cout << endl;
    }

    // Traverse backward
    void traverseBackward() {
        if (!head) { // If the list is empty
            cout << "List is empty!" << endl;
            return;
        }
        Node* tail = head->prev; // Get the tail node
        Node* temp = tail;
        do {
            cout << temp->data << " "; // Print the data
            temp = temp->prev; // Move to the previous node
        } while (temp != tail); // Loop until we return to tail
        cout << endl;
    }

    // Search for a value
    bool search(int value) {
        if (!head) return false; // If the list is empty, return false
        Node* temp = head;
        do {
            if (temp->data == value) return true; // If value is found
            temp = temp->next; // Move to the next node
        } while (temp != head); // Loop until we return to head
        return false; // Value not found
    }
};

int main() {
    CircularDoublyLinkedList list;

    // Demonstration of insertion operations
    list.insertAtBeginning(10);
    list.insertAtEnd(20);
    list.insertAtEnd(30);
    list.insertAtPosition(25, 3);
    cout << "List after insertions: ";
    list.traverseForward();

    // Demonstration of deletion operations
    list.deleteAtBeginning();
    cout << "List after deleting at beginning: ";
    list.traverseForward();

    list.deleteAtEnd();
    cout << "List after deleting at end: ";
    list.traverseForward();

    list.deleteByValue(25);
    cout << "List after deleting by value 25: ";
    list.traverseForward();

    // Demonstration of traversal methods
    list.insertAtEnd(40);
    list.insertAtEnd(50);
    cout << "List forward traversal: ";
    list.traverseForward();

    cout << "List backward traversal: ";
    list.traverseBackward();

    // Demonstration of search functionality
    cout << "Search for 50: " << (list.search(50) ? "Found" : "Not Found") << endl;
    cout << "Search for 100: " << (list.search(100) ? "Found" : "Not Found") << endl;

    return 0;
}
