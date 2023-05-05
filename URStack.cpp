/*
 * StringBuilder Project
 *
 *
 * URStack.cpp
 *
 * Date:        04/05/2023
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


#include "CustomIO.h"
#include "URStack.h"

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
template<class DataType>
URStack<DataType>::Node::Node(): data{}, next{nullptr} {}

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
template<class DataType>
URStack<DataType>::Node::Node(DataType data): data{data},
                                    next{nullptr} {}

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
template<class DataType>
typename URStack<DataType>::Node& URStack<DataType>::Node::operator=(const Node& other) {
    /* Self-assignment test */
    if (this == &other) {
        return *this;
    }

    data = other.data;
    next = other.next;

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
template<class DataType>
URStack<DataType>::Node::~Node() {
    /* Deleting nullptr has no effect */
    delete next;

    /* Provides protection against illegal access */
    next = nullptr;
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
template<class DataType>
typename URStack<DataType>::NodePtr URStack<DataType>::Node::getNext() const {
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
template<class DataType>
DataType URStack<DataType>::Node::getData() const {
    return data;
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
template<class DataType>
typename URStack<DataType>::NodePtr URStack<DataType>::Node::skip(int n) {
    Node *result = this;

    /* Perform n-hops */
    while (result and 0 < n--) {
        result = result->getNext();
    }

    return result;
}

template<class DataType>
typename URStack<DataType>::NodePtr URStack<DataType>::Node::before(NodePtr node) {
    Node *result = this;

    while (result and result->getNext() != node) {
        result = result->getNext();
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
template<class DataType>
void URStack<DataType>::Node::unchain(Node *chain_end) {
    if (this == chain_end) {
        return;
    }

    before(chain_end)->chain(nullptr);

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
template<class DataType>
void URStack<DataType>::Node::chain(Node *newNext) {
    next = newNext;
}

template<class DataType>
void URStack<DataType>::Node::cut(int after_distance) {
    NodePtr before_last = skip(after_distance - 1);
    delete before_last->getNext();
    before_last->chain(nullptr);
}

template<class DataType>
URStack<DataType>::URStack(int capacity): size{0}, top{nullptr},
current{nullptr}, capacity{capacity} {
    if (capacity <= 0) {
        throw invalid_argument("\nCapacity must be a positive integer.\n");
    }
}

template<class DataType>
void URStack<DataType>::insertNewAction(const DataType& action) {
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
        current->cut(size);
    } else {
        size++;
    }
}

template<class DataType>
void URStack<DataType>::undo(ostream& out) {
    if (not isEmpty()) {
        displayDataMessage("Undoing: " + current->getData(), out);

        if (size != 1) {
            current = current->getNext();
        }

        size--;
    } else {
        displayInvalidMessage("No actions\a", out);
    }
}

template<class DataType>
void URStack<DataType>::redo(std::ostream &out) {
    if (hasNext()) {
        if (not isEmpty()) {
            current = top->before(current);
        }

        displayDataMessage("Redoing: " + current->getData(), out);
        size++;
    } else {
        displayInvalidMessage("No previous actions\a", out);
    }
}

template<class DataType>
ostream& URStack<DataType>::displayDirectional(
        NodePtr from,
        NodePtr to,
        std::ostream& out,
        bool reverse) const {
    static const string& k_sep = ", ";

    if (not from or (from == to and not isEmpty())) {
        return out;
    }

    if (reverse) {
        displayDirectional(from->getNext(), to, out, reverse);
        return displayDataMessage(from->getData() + (from != top ? k_sep : ""), out);
    } else {
        displayDataMessage(
                from->getData() + (from->getNext() ? k_sep : ""),out
        );

        return displayDirectional(from->getNext(), to, out, reverse);
    }
}

template<class DataType>
ostream& URStack<DataType>::displayAll(std::ostream& out) const {
    if (not top) {
        return displayInvalidMessage("No actions", out);
    }

    return displayDirectional(top, nullptr, out, false);
}

template<class DataType>
ostream& URStack<DataType>::displayPrevious(std::ostream& out) const {
    if (isEmpty()) {
        return displayDataMessage("No previous actions", out);
    }

    return displayDirectional(current, nullptr, out, false);
}

template<class DataType>
ostream& URStack<DataType>::displayNext(std::ostream& out) const {
    if (not hasNext()) {
        return displayDataMessage("No next actions", out);
    }

    return displayDirectional(top, current, out, true);
}

template<class DataType>
int URStack<DataType>::getSize() const {
    return size;
}
