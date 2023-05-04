//
// Created by Yaman SirajAldeen on 5/1/23.
//

#ifndef URSTACK_URSTACK_H
#define URSTACK_URSTACK_H

#include <string>
#include <iostream>


class URStack {
private:
    /*
     * Node class used in MyStringBuilder class to manage single characters.
     */
    class Node {
    public:
        /*
         * Type alias for the type of data stored in the Nodes class.
         * For the use case in MyStringBuilder, char is the type of the data.
         * Can be accessed outside the class using Node::DataType.
         */
        typedef std::string DataType;

        /*
         * Pre-Conditions:
         *      No preconditions.
         *
         * Post-Conditions:
         *      A default Node instance is created.
         *      next is nullptr.
         *      data is default value of the type.
         *
         * No-arg constructor of the Node class.
         */
        Node();

        /*
         * Pre-Conditions:
         *      A const Reference to a variable of type `DataType` is given.
         *
         * Post-Conditions:
         *      A Node instance with the given data is created.
         *      next is nullptr.
         *      data is a copy of the given value.
         *
         * Parameterized constructor of the Node class,
         * that takes the data to be stored.
         */
        explicit Node(DataType);

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
         */
        Node& operator=(const Node&);

        /*
         * Pre-Conditions:
         *      `this` Node instance is not destroyed.
         *
         * Post-Conditions:
         *      `this` Node instance is destroyed.
         *      next is nullptr.
         *
         * Destructor for the Node class.
         */
        ~Node();

        /*
         * Pre-Conditions:
         *      `this` Node instance is initialized.
         *
         * Post-Conditions:
         *      A Node pointer to the next Node or nullptr is returned.
         *      No changes to this.
         *
         * Returns a copy of the pointer to the next Node instance.
         */
        [[nodiscard]] Node* getNext() const;

        /*
         * Pre-Conditions:
         *      `this` Node instance is initialized.
         *
         * Post-Conditions:
         *      Data of type `DataType` is returned.
         *      No changes to this.
         *
         * Returns a copy of the data stored in the Node instance.
         */
        [[nodiscard]] DataType getData() const;

        /*
         * Pre-Conditions:
         *      `this` Node instance is initialized.
         *
         * Post-Conditions:
         *      A Node pointer to the next Node or nullptr is returned.
         *      No changes to this.
         *
         * Returns a copy of the pointer to the next Node instance.
         */
        [[nodiscard]] Node* getPrev() const;


        /*
         * Pre-Conditions:
         *      `this` Node instance is initialized.
         *      An int is given that represents the number of hops.
         *
         * Post-Conditions:
         *      A pointer to a Node instance (or nullptr) is returned,
         *      points to the instance n-Nodes away.
         *
         * Returns a pointer to a Node,
         * after performing the given number of hops.
         */
        [[nodiscard]] Node* skip(int);

        /*
         * Pre-Conditions:
         *      `this` Node instance is initialized.
         *      An int is given that represents the number of Nodes to delete,
         *      after this.
         *
         * Post-Conditions:
         *      All n-Nodes following `this` are deleted.
         *      next points to the node after the last deleted node.
         *
         * Deletes a given number of Node instances following a Node instance.
         * Returns a pointer to the new next Node instance.
         */
        void unchain(Node*);

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
        void chain(Node*);
    private:
        /*
         * Pointer to the next Node.
         * Initialized to nullptr by default.
         */
        Node *next;

        /*
         * Pointer to the previous Node.
         * Initialized to nullptr by default.
         */
        Node *prev;

        /*
         * Data stored in the Node instance.
         * Initialized to the default value of the type.
         */
        DataType data;
    };

    /*
     * Type alias for Node*.
     * Can be accessed in the implementation using URStack::NodePtr.
     */
    typedef Node* NodePtr;

    /*
     * Pointer to the top Node instance of the URStack instance.
     * Default is nullptr
     */
    NodePtr top;

    /*
     * Pointer to the current Node instance of the URStack instance.
     * Default is a NodePtr with an empty string.
     */
    NodePtr current;

    /*
     * Integer representing the maximum number of actions allowed to be
     * saved in the URStack instance.
     * Default is 20.
     */
    int capacity;

    /*
     * Integer representing the actual number of actions saved in the
     * URStack instance (starting from the current NodePtr).
     * Default is 0.
     */
    int size;

    [[nodiscard]] std::ostream& displayDirectionalFrom(
            NodePtr,
            std::ostream&,
            bool to_right) const;

    [[nodiscard]] inline bool isEmpty() const {
        return not size;
    }
public:
    explicit URStack(int capacity = 20);

    void insertNewAction(const std::string&);
    void undo(std::ostream& out = std::cout);
    void redo(std::ostream& out = std::cout);
    [[nodiscard]] std::ostream& displayAll(std::ostream&) const;
    [[nodiscard]] std::ostream& displayPrevious(std::ostream&) const;
    [[nodiscard]] std::ostream& displayNext(std::ostream&) const;
    [[nodiscard]] int getSize() const;
};


#endif //URSTACK_URSTACK_H
