/*
 * StringBuilder Project
 *
 *
 * *.cpp
 *
 * Date:        13/04/2023
 *
 * Author:      Mahmoud Yaman Seraj Alddin
 *
 * Purpose:     Implementation of the Node class, described in Node.h
 *
 * List of public Functions:
 *      Node()
 *          No-arg constructor of the Node class.
 *
 *      Node(const DataType&)
 *          Parameterized constructor of the Node class.
 *
 *      Node& operator=(const Node&)
 *          Assignment operator for the Node class.
 *
 *      ~Node()
 *          Destructor for the Node class.
 *
 *      NodePtr getNext() const
 *          Returns the pointer to the next Node instance.
 *
 *      DataType getData() const
 *          Returns the data stored in the Node instance.
 *
 *      void chain(NodePtr)
 *          Assigns the next Node instance.
 *
 *      void setData(const DataType&)
 *          Assigns the data field in the Node instance.
 *
 *      NodePtr unchain(int)
 *          Deletes a given number of Node instances following a Node instance.
 *          Returns a pointer to the new next Node instance.
 *
 *      NodePtr skip(int)
 *          Returns a pointer to a Node,
 *          after performing a given number of hops.
 */


#include "URStack.h"
#include "CustomIO.h"

#include <utility>
#include <iostream>
#include <exception>

using std::string, std::ostream,
        std::min, std::max, std::invalid_argument;

/*
 * Pre-Conditions:
 *      No preconditions.
 *
 * Post-Conditions:
 *      A default Node instance is created.
 *      next is initialized to nullptr.
 *      data is initialized to default value of the type.
 *
 * No-arg constructor of the Node class.
 */
URStack::Node::Node(): data{}, next{nullptr}, prev{nullptr} {}

/*
 * Pre-Conditions:
 *      A const Reference to a variable of type `DataType` is given.
 *
 * Post-Conditions:
 *      A Node instance with the given data is created.
 *      next is initialized to nullptr.
 *      data is initialized to the given value.
 *
 * Marked explicit to prevent implicit conversions from char* to string.
 * Parameterized constructor of the Node class,
 * that takes the data to be stored.
 */
URStack::Node::Node(DataType data): data{std::move(data)},
                                    next{nullptr}, prev{nullptr} {}

/*
 * Pre-Conditions:
 *      `this` Node instance & the given Node instance are initialized.
 *      A const Reference to a Node instance is given from which to copy.
 *
 * Post-Conditions:
 *      data is a copy of the given Node's data.
 *      next is a copy of the given Node's next.
 *      Returns a reference to this.
 *
 * Assignment operator for the Node class that copies the data fields of
 * the given Node to this.
 * data & next data fields are copied using their assignment operators.
 * If the pointer to other is the same as this, no copying is performed,
 * prevents self assignment & needles copying.
 */
URStack::Node& URStack::Node::operator=(const Node& other) {
    /* Self-assignment test */
    if (this == &other) {
        return *this;
    }

    data = other.data;
    next = other.next;
    prev = other.prev;

    return *this;
}

/*
 * Pre-Conditions:
 *      `this` Node instance is not destroyed.
 *
 * Post-Conditions:
 *      `this` Node instance is destroyed.
 *      next is nullptr
 *
 * Destructor for the Node class.
 * Deletes all the following Node instances, till it reaches a nullptr.
 */
URStack::Node::~Node() {
    if (prev) {
        prev->chain(nullptr);
    }

    /* Deleting nullptr has no effect */
    delete next;

    /* Provides protection against illegal access */
    next = nullptr;

    /* Provides protection against illegal access */
    prev = nullptr;
}

/*
 * Pre-Conditions:
 *      `this` Node instance is initialized.
 *
 * Post-Conditions:
 *      A Node pointer to the next Node or nullptr is returned.
 *      No changes to this.
 *
 * Marked [[nodiscard]] to allow the compiler to issue warnings in case of
 * wasteful calls. For example `node.getNext();`.
 * Returns a copy of the pointer to the next Node instance.
 */
URStack::NodePtr URStack::Node::getNext() const {
    return next;
}

/*
 * Pre-Conditions:
 *      `this` Node instance is initialized.
 *
 * Post-Conditions:
 *      Data of type `DataType` is returned.
 *      No changes to this.
 *
 * Marked [[nodiscard]] to allow the compiler to issue warnings in case of
 * wasteful calls. For example `node.getData();`.
 * Returns a copy of the data stored in the Node instance.
 */
URStack::Node::DataType URStack::Node::getData() const {
    return data;
}

/*
 * Pre-Conditions:
 *      `this` Node instance is initialized.
 *
 * Post-Conditions:
 *      A Node pointer to the next Node or nullptr is returned.
 *      No changes to this.
 *
 * Marked [[nodiscard]] to allow the compiler to issue warnings in case of
 * wasteful calls. For example `node.getNext();`.
 * Returns a copy of the pointer to the next Node instance.
 */
URStack::NodePtr URStack::Node::getPrev() const {
    return prev;
}

/*
 * Pre-Conditions:
 *      `this` Node instance is initialized.
 *      An int is given that represents the number of hops.
 *
 * Post-Conditions:
 *      A pointer to a Node instance (or nullptr) is returned,
 *      points to the instance n-Nodes away.
 *
 * Marked [[nodiscard]] to allow the compiler to issue warnings in case of
 * wasteful calls. For example `node.skip(5);`.
 * If the number of hops exceeds the number of Nodes nullptr is returned.
 * If the number of hops is 0 or less, `this` is returned.
 * Returns a pointer to a Node,
 * after performing the given number of hops.
 */
URStack::NodePtr URStack::Node::skip(int n) {
    Node *result = this;

    if (n < 0) {
        n *= -1;

        /* Perform n-hops */
        while (result and 0 < n--) {
            result = result->getPrev();
        }
    } else {
        /* Perform n-hops */
        while (result and 0 < n--) {
            result = result->getNext();
        }
    }

    return result;
}

/*
 * Pre-Conditions:
 *      `this` Node instance is initialized.
 *      The given chain end is guaranteed to be present.
 *
 * Post-Conditions:
 *      All n-Nodes following `this` are deleted.
 *      next points to the node after the last deleted node.
 *
 * If the count is 0 or less, no changes occur, next is returned.
 * Deletes a given number of Node instances following a Node instance.
 * Returns a pointer to the new next Node instance.
 */
void URStack::Node::unchain(Node *chain_end) {
    if (this == chain_end) {
        return;
    }

    if (chain_end) {
        chain_end->getPrev()->chain(nullptr);
        chain_end->prev = nullptr;
    }

    delete this;
}

/*
 * Pre-Conditions:
 *      `this` Node instance is initialized.
 *      A pointer to a Node is given.
 *
 * Post-Conditions:
 *      next points to the Node represented by the given pointer.
 *
 * Assigns the given pointer to next.
 */
void URStack::Node::chain(Node *newNext) {
    next = newNext;

    if (newNext) {
        newNext->prev = this;
    }
}

URStack::URStack(int capacity): size{0}, top{nullptr}, current{nullptr} {
    if (capacity <= 0) {
        throw invalid_argument("\nCapacity must be a positive integer.\n");
    }

    this->capacity = capacity;
}

void URStack::insertNewAction(const string& action) {
    auto new_action = new Node{action};

    if (isEmpty()) {
        current = new_action;
        size = 1;

        delete top;
        top = new_action;

        return;
    }

    if (top) {
        top->unchain(current);
    }

    new_action->chain(current);
    top = current = new_action;

    if (size == capacity) {
        delete current->skip(size);
    } else {
        size++;
    }
}

void URStack::undo(ostream& out) {
    if (not isEmpty()) {
        displayDataMessage("Undoing: " + current->getData(), out);

        if (size != 1) {
            current = current->skip(1);
        }

        size--;
    } else {
        displayInvalidMessage("No actions\a", out);
    }
}

void URStack::redo(std::ostream &out) {
    if (top and (current->getPrev() or isEmpty())) {
        if (not isEmpty()) {
            current = current->skip(-1);
        }

        displayDataMessage("Redoing: " + current->getData(), out);
        size++;
    } else {
        displayInvalidMessage("No previous actions\a", out);
    }
}

ostream& URStack::displayDirectional(std::ostream& out, bool to_prev) const {
    NodePtr current_cpy = to_prev or isEmpty() ? current : current->getPrev();

    displayDataMessage(current_cpy->getData(), out);
    current_cpy = to_prev ? current_cpy->getNext() : current_cpy->getPrev();

    while (current_cpy) {
        displayDataMessage(" | " + current_cpy->getData(), out);
        current_cpy = to_prev ? current_cpy->getNext() : current_cpy->getPrev();
    }

    return out;
}

ostream& URStack::displayAll(std::ostream& out) const {
    if (not top) {
        return displayInvalidMessage("No actions", out);
    }

    NodePtr top_cpy = top;

    displayDataMessage(top_cpy->getData(), out);
    top_cpy = top_cpy->getNext();

    while (top_cpy) {
        displayDataMessage(" | " + top_cpy->getData(), out);
        top_cpy = top_cpy->getNext();
    }

    return out;
}

ostream& URStack::displayPrevious(std::ostream& out) const {
    if (not current or isEmpty()) {
        return displayDataMessage("No previous actions", out);
    }

    return displayDirectional(out, true);
}

ostream& URStack::displayNext(std::ostream& out) const {
    if (not current or not (current->getPrev() or isEmpty())) {
        return displayDataMessage("No next actions", out);
    }

    return displayDirectional(out, false);
}

int URStack::getSize() const {
    return size;
}
