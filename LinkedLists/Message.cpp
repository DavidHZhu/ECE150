// Title: Linked Link Message Project
// Author: David Zhu
// Description: Message storing class using linked lists
// Updates: Nov.27 Added all methods but needs testing and editing
//          Nov 28 Fixed printing needs marmoset testing.
// To do: Test in marmoset
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
    p_next = nullptr;
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
    bool isPlaced{false};
    // Loop to find position of element: Top if is for if it belongs in the center, else if is for the end
    while (current->p_next){
        if (newNode->identifier < current->p_next->identifier){
            newNode->p_next = current->p_next;
            current->p_next = newNode;
            isPlaced = true;
            break;
        }
        current = current->p_next;
    }
    if (!isPlaced){
        current->p_next = newNode;
    }
}

// NEEDS TO BE EDITED:
void Message::print_message() {


    Node* current = head;
    /*while (current){
        std::cout << "Identifier: " << current->identifier << " Packet: " << current->get_fragment() << std::endl;
        current = current->p_next;
    }*/

    // Special case for empty list and list that doesn't start at 0
    if (head == nullptr){
        std::cout << "???" << std::endl;
    } else if (head->identifier > 0){
        for (int i = 0; i < head->identifier; ++i){
            std::cout << "... ";
        }

    }

    while(current){
        if (current->p_next == nullptr && current->get_fragment() != "EOT"){
            std::cout << current->get_fragment() << " ???" << std::endl;

        } else if (current->p_next == nullptr && current->get_fragment() == "EOT"){
            std::cout << std::endl;
            break;

        } else if (current->p_next->identifier - current->identifier == 1){
            if (current->p_next != nullptr)
                std::cout << current->get_fragment() << " ";
            else
                std::cout << std::endl;

        } else if (current->p_next->identifier - current->identifier > 1){
            for (int i = 1; i < current->p_next->identifier - current->identifier; ++i){
                std::cout << current->get_fragment() << " ... ";
            }

        }
        current = current->p_next;
    }



}

//==============================================================================================================
#ifndef MARMOSET_TESTING
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
#endif