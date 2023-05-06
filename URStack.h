/*
 * URStack Project
 *
 *
 * URStack.h
 *
 * Date:        05/05/2023
 *
 * Author:      Mahmoud Yaman Seraj Alddin
 *
 * Purpose:     Definition of the URStack<DataType> class
 *              & its nested Node class.
 *
 * List of public Node class Functions nested in URStack<DataType>:
 *      Node()
 *          No-arg constructor of the Node class.
 *
 *      Node(const DataType&)
 *          Parameterized constructor of the Node class.
 *
 *      ~Node()
 *          Destructor for the Node class.
 *
 *      Node* getNext() const
 *          Returns the pointer to the next Node instance.
 *
 *      DataType getData() const
 *          Returns the data stored in the Node instance.
 *
 *      void chain(Node*)
 *          Assigns the next Node instance.
 *
 *      void setData(const DataType&)
 *          Assigns the data field in the Node instance.
 *
 *      void unchain(Node*)
 *          Deletes all nodes from this till (excluding) the given Node.
 *
 *      Node* skip(int)
 *          Returns a pointer to a Node,
 *          after performing a given number of hops.
 *
 *      Node* before(Node*)
 *          Returns a Node pointer to the Node before the given Node.
 *
 *      void cut(int)
 *          Deletes all Nodes after N-hops.
 *
 * List of private URStack<DataType> class Functions:
 *      inline bool isEmpty() const
 *          Used to check if the stack is empty.
 *
 *      inline bool hasNext() const
 *          Used to check if the stack has next actions.
 *
 *      std::ostream& displayDirectional(NodePtr from, NodePtr to,
 *                                       std::ostream&, bool reverse) const
 *          Displays Nodes' data from `from` till `to`
 *
 * List of public URStack<DataType> class Functions:
 *      URStack(int capacity = 20)
 *          Parameterized/Default constructor of the URStack class.
 *
 *      insertNewAction(const DataType&)
 *          Inserts a new action on top of the stack.
 *
 *      void undo(std::ostream&)
 *          Undo the latest action in the stack.
 *
 *      void redo(std::ostream&)
 *          Redo the latest undone action in the stack.
 *
 *      std::ostream& displayAll(std::ostream&) const
 *          Displays all actions in the stack.
 *
 *      std::ostream& displayPrevious(std::ostream&) const
 *          Displays all existing actions in the stack.
 *
 *      std::ostream& displayNext(std::ostream&) const
 *          Displays all deleted actions in the stack.
 *
 *      inline int getSize() const
 *          Returns the number of actions in the stack.
 *
 *      inline int getCapacity() const
 *          Returns the capacity of the stack.
 */

#ifndef URSTACK_URSTACK_H
#define URSTACK_URSTACK_H

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>

#include "CommonIO.h"


/*
 * Stack with redo/undo functionality
 */
template<class DataType>
class URStack {
public:
    /*
     * Pre-Conditions:
     *      Capacity of the URStack (optional, default 20).
     *
     * Post-Conditions:
     *      URStack instance is created.
     *      current is nullptr.
     *      top is nullptr.
     *      size is 0.
     *      capacity is given.
     *
     * Parameterized/Default constructor of the URStack class.
     */
    explicit URStack(int capacity = 20);

    /*
     * Pre-Conditions:
     *      URStack is initialized.
     *      const reference to action to be added.
     *
     * Post-Conditions:
     *      New action is added,
     *      necessary adjustments are made according to the requirements.
     *
     * Inserts a new action on top of the stack.
     */
    void insertNewAction(const DataType&);

    /*
     * Pre-Conditions:
     *      URStack is initialized.
     *      ostream reference to display the output (requirement).
     *
     * Post-Conditions:
     *      Display the data of the latest action to the given ostream,
     *      then undo it (if possible).
     *
     * Undo the latest action in the stack.
     */
    void undo(std::ostream&);

    /*
     * Pre-Conditions:
     *      URStack is initialized.
     *      ostream reference to display the output (requirement).
     *
     * Post-Conditions:
     *      Redo the latest deleted action,
     *      then display its data to the given ostream (if possible).
     *
     * Redo the latest undone action in the stack.
     */
    void redo(std::ostream&);

    /*
     * Pre-Conditions:
     *      URStack is initialized.
     *      ostream reference to display the output.
     *
     * Post-Conditions:
     *      Displays all actions in the stack to the given ostream.
     *      Returns reference to the ostream.
     *
     * Displays all actions in the stack.
     */
    [[nodiscard]] std::ostream& displayAll(std::ostream&) const;

    /*
     * Pre-Conditions:
     *      URStack is initialized.
     *      ostream reference to display the output.
     *
     * Post-Conditions:
     *      Displays all currently existing actions in the stack
     *      to the given ostream.
     *      Returns reference to the ostream.
     *
     * Displays all existing actions in the stack.
     */
    [[nodiscard]] std::ostream& displayPrevious(std::ostream&) const;

    /*
     * Pre-Conditions:
     *      URStack is initialized.
     *      ostream reference to display the output.
     *
     * Post-Conditions:
     *      Displays all previously deleted actions in the stack
     *      to the given ostream.
     *      Returns reference to the ostream.
     *
     * Displays all deleted actions in the stack.
     */
    [[nodiscard]] std::ostream& displayNext(std::ostream&) const;

    /*
     * Pre-Conditions:
     *      URStack is initialized.
     *
     * Post-Conditions:
     *      Number of actions in the stack is returned.
     *
     * Returns the number of actions in the stack.
     */
    [[nodiscard]] inline int getSize() const {
        return size;
    };

    /*
     * Pre-Conditions:
     *      URStack is initialized.
     *
     * Post-Conditions:
     *      Capacity of the stack is returned.
     *
     * Returns the capacity of the stack.
     */
    [[nodiscard]] inline int getCapacity() const {
        return capacity;
    };

private:
    /*
     * Node class used in URStack to manage actions
     */
    class Node {
    public:
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
         *      Data of `DataType` type is given.
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
         *      `this` Node instance is not destroyed.
         *
         * Post-Conditions:
         *      `this` Node instance is destroyed.
         *      All following nodes in the chain are destroyed.
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
         *      `this` Node instance is linked to the given Node
         *      after N-hops.
         *
         * Post-Conditions:
         *      The node before the given Node
         *      (i.e. the one which has next pointing to it) is returned.
         *
         * Returns a Node pointer to the Node before the given Node.
         */
        [[nodiscard]] Node* before(Node*);

        /*
         * Pre-Conditions:
         *      `this` Node instance is initialized.
         *      A pointer to a Node located N-hops after `this`.
         *
         * Post-Conditions:
         *      All n-Nodes from `this` are deleted.
         *      In case the given pointer is equal to this,
         *      nothing occurs.
         *
         * Deletes all nodes from this till (excluding) the given Node.
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

        /*
         * Pre-Conditions:
         *      `this` is initialized.
         *
         * Post-Conditions:
         *      All nodes after N-hops are deleted.
         *      The Node (N-1) hops away points to nullptr.
         *
         * Deletes all Nodes after N-hops.
         */
        void cut(int);
    private:
        /*
         * Pointer to the next Node.
         * Initialized to nullptr by default.
         */
        Node *next;

        /*
         * Data stored in the Node instance.
         * Initialized to the default value of the type.
         */
        DataType data;
    };

    /*
     * Type alias for Node*.
     * Can be accessed in the implementation file using URStack::NodePtr.
     */
    typedef Node* NodePtr;

    /*
     * Pointer to the top Node instance of the URStack instance.
     * Default is nullptr.
     */
    NodePtr top;

    /*
     * Pointer to the current Node instance of the URStack instance.
     * Default is nullptr.
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

    /*
     * Pre-Conditions:
     *      URStack<DataType> is initialized.
     *      ostream to display the output.
     *      The stack is not empty.
     *      Current must have a Node before it, if reverse is true.
     *      The given from pointer is before to.
     *      reverse, true displays the Nodes' data in reverse.
     *      DataType must have an operator<< implementation.
     *
     * Post-Conditions:
     *      The data in the Nodes is displayed into the given ostream&
     *
     * Displays Nodes' data from `from` till `to`
     */
    std::ostream& displayDirectional(
            NodePtr /* from */,
            NodePtr /* to */,
            std::ostream&,
            bool /* reverse */) const;

    /*
     * Pre-Conditions:
     *      URStack<DataType> is initialized.
     *
     * Post-Conditions:
     *      True if stack is empty, otherwise false.
     *
     * Used to check if the stack is empty.
     */
    [[nodiscard]] inline bool isEmpty() const {
        return not size;
    }

    /*
     * Pre-Conditions:
     *      URStack<DataType> is initialized.
     *
     * Post-Conditions:
     *      True if stack has next actions, otherwise false.
     *
     * Used to check if the stack has next actions.
     */
    [[nodiscard]] inline bool hasNext() const {
        return top and (top != current or isEmpty());
    }
};

#endif //URSTACK_URSTACK_H
