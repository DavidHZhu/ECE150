// Title: Linked Link Message Project
// Author: David Zhu
// Description: Message storing class using linked lists
// Updates: Nov.27 Added all methods but needs testing and editing
// To do: Fix printing and continue testing
//
//===============================================================================================================
#include <iostream>
#include "Message.h"
#ifndef MARMOSET_TESTING
int main();
#endif
//===============================================================================================================

// Class definitions for Node
Node* Node::get_next() {
    return p_next;
}

std::string Node::get_fragment() {
    return fragment;
}

Node::Node(unsigned int id, std::string frag) {
    identifier = id;
    fragment = frag;
}

// Class definitions for Linked List
Message::Message() {
    head = nullptr;
}

Message::~Message() {}

void Message::insert(unsigned int id, std::string fragment) {

    // Creates node and pointer to keep track of placement
    Node* current = nullptr;
    Node* newNode = new Node(id,fragment);
    newNode->p_next = nullptr;

    // Checks if the head exists
    if (head == nullptr) {
        head = newNode;
        return;
    }
    // Checks if the node should be the new head.
    if (newNode->identifier < head->identifier){
        newNode->p_next = head;
        head = newNode;
        return;
    }

    // Set current to the top of the list
    current = head;
    // Loop to find position of element: Top if is for if it belongs in the center, else if is for the end
    while (current->p_next){
        if (current->identifier < newNode->identifier && newNode->identifier < current->p_next->identifier){
            newNode->p_next = current->p_next;
            current->p_next = newNode;
        } else if (current->p_next == nullptr){
            current->p_next = newNode;
            // newNode was already nullptr here;
        }
        current = current->p_next;
    }

}

// NEEDS TO BE EDITED:
void Message::print_message() {

    Node* current = head;
    while (current){
        std::cout << "Number: " << current->identifier << std::endl;
        current = current->p_next;
    }

}

//==============================================================================================================

int main() {

    // Linked list object
    Message userMessage;

    // Variables for id and frag
    int command = 0;
    std::string data = "";

    // Runs until user enters -2:
    while (command != -2){
        // User inputs a command number
        std::cin >> command;
        if (command > -1){
            std::cin >> data;
            userMessage.insert(command, data);
        } else if (command == -1){
            userMessage.print_message();
        }
    }
    return 0;
}