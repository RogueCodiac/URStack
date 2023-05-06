/*
 * URStack Project
 *
 *
 * URStack.cpp
 *
 * Date:        05/05/2023
 *
 * Author:      Mahmoud Yaman Seraj Alddin
 *
 * Purpose:     Implementation of the functions defined in URStack.h
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

#include "URStack.h"


/* Used std utilities */
using std::string, std::ostream,
        std::min, std::max, std::invalid_argument;

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
template<class DataType>
URStack<DataType>::Node::Node(): data{}, next{nullptr} {}

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
template<class DataType>
URStack<DataType>::Node::Node(DataType data): data{data}, next{nullptr} {}

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
template<class DataType>
URStack<DataType>::Node::~Node() {
    /* Deleting nullptr has no effect */
    delete next;

    /* Provides protection against illegal access */
    next = nullptr;

    /* Data released automatically */
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
template<class DataType>
typename URStack<DataType>::NodePtr
    URStack<DataType>::Node::before(NodePtr end_node) {
    Node *result = this;

    /*
     * Keep on iterating until we reach the end of the chain,
     * or the next Node is the end_node
     */
    while (result and result->getNext() != end_node) {
        result = result->getNext();
    }

    return result;
}

/*
 * Pre-Conditions:
 *      `this` Node instance is initialized.
 *      A pointer to a Node located N-hops after `this`.
 *
 * Post-Conditions:
 *      All n-Nodes from `this` are deleted.
 *      In case the given pointer is equal to `this`,
 *      nothing occurs.
 *
 * Deletes all nodes from this till (excluding) the given Node.
 */
template<class DataType>
void URStack<DataType>::Node::unchain(Node *chain_end) {
    if (this == chain_end) {
        return;
    }

    /*
     * Chain the node before the last node to nullptr,
     * to keep the rest of the chain starting from chain_end
     */
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
void URStack<DataType>::Node::chain(Node *new_next) {
    next = new_next;
}

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
template<class DataType>
void URStack<DataType>::Node::cut(int after_distance) {
    /* Node (N-1) hops away */
    NodePtr before_last = skip(after_distance - 1);

    /* Delete all Nodes after N-hops */
    delete before_last->getNext();

    /* Allows for delete of next in the future */
    before_last->chain(nullptr);
}

/*
 * Pre-Conditions:
 *      Capacity of the URStack (optional, default 20).
 *
 * Post-Conditions:
 *      URStack instance is created.
 *      current initialized to nullptr.
 *      top initialized to nullptr.
 *      size initialized to 0.
 *      capacity initialized to given value or default 20.
 *
 * Parameterized/Default constructor of the URStack class.
 */
template<class DataType>
URStack<DataType>::URStack(int capacity): size{0}, top{nullptr},
                                          current{nullptr},
                                          capacity{capacity} {
    if (capacity <= 0) {
        throw invalid_argument("\nCapacity must be a positive integer.\n");
    }
}

/*
 * Pre-Conditions:
 *      URStack is initialized.
 *      const reference for action to be added.
 *
 * Post-Conditions:
 *      If the stack is empty:
 *          The new action is added to the top of the stack.
 *          size becomes 1.
 *      Otherwise:
 *          If top & current are the same:
 *              In case the stack is not full:
 *                  The new action is added to the top of the stack,
 *                  both top & current point to the new action.
 *                  size incremented by 1.
 *              Otherwise:
 *                  The oldest action is discarded & continue the
 *                  same as the previous case, but no incrementation of size.
 *          If they are not the same:
 *              Delete all the actions from top (inclusive)
 *              till current (exclusive) & then continue as
 *              the previous case.
 *
 * Inserts a new action on top of the stack.
 */
template<class DataType>
void URStack<DataType>::insertNewAction(const DataType& action) {
    auto new_action = new Node{action};

    if (isEmpty()) {
        current = new_action;
        size = 1;

        /*
         * Deletes all actions in the stack, if any.
         * (Deleting nullptr is safe).
         */
        delete top;
        top = current;

        return;
    }

    /*
     * Stack not empty, top cannot be nullptr.
     * Deletes any nodes from top till current, if any.
     */
    top->unchain(current);

    /* New action added on top of the stack */
    new_action->chain(current);

    /* Adjust top & current to proper value */
    top = current = new_action;

    if (size == capacity) {
        /* Delete the oldest action Node, no change on size */
        current->cut(size);
    } else {
        size++;
    }
}

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
template<class DataType>
void URStack<DataType>::undo(ostream& out) {
    /* Check if there are actions to undo */
    if (not isEmpty()) {
        display("Undoing: ", out);
        display(current->getData(), out);

        /*
         * Keeps the value of current non-null, as next is nullptr.
         * Allows us to undo & redo all actions in the stack.
         * An alternative solution is using a trailing Node, but this approach
         * makes good use of the size data field in this & other functions.
         */
        if (size != 1) {
            current = current->getNext();
        }

        size--;
    } else {
        displayInvalidMessage("No actions\a", out);
    }
}

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
template<class DataType>
void URStack<DataType>::redo(ostream &out) {
    /* Check if there are actions to redo */
    if (hasNext()) {
        /*
         * Allows us to undo & redo all actions in the stack.
         * In case the stack is empty,
         * current is actually the last Node in the stack (see undo).
         */
        if (not isEmpty()) {
            current = top->before(current);
        }

        display("Redoing: ", out);
        display(current->getData(), out);

        size++;
    } else {
        displayInvalidMessage("No previous actions\a", out);
    }
}

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
 * Displays Nodes' data from `from` till `to`.
 * Uses recursion to achieve the reversal of nodes without wasting space.
 */
template<class DataType>
ostream& URStack<DataType>::displayDirectional(
        NodePtr from,
        NodePtr to,
        ostream& out,
        bool reverse) const {
    /* Separator between Nodes data in ostream */
    static const string& kSep = ", ";

    /* Base case */
    if (not from or (from == to and not isEmpty())) {
        return out;
    }

    if (reverse) {
        /* Display the rest of the Nodes */
        displayDirectional(from->getNext(), to,
                           out, reverse);

        /* Display the `from` node */
        display(from->getData(), out);

        /* No separator for last Node (which is actually the first) */
        if (from != top) {
            display(kSep, out);
        }
    } else {
        /* Display the `from` node  */
        display(from->getData(),out);

        /* No separator for last Node */
        if (from->getNext()) {
            display(kSep, out);
        }

        /* Display the rest of the Nodes */
        return displayDirectional(from->getNext(), to,
                                  out, reverse);
    }

    return out;
}

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
 * Marked [[nodiscard]] to allow the compiler to issue warnings in case of
 * wasteful calls. For example `stack.displayAll(cout);`.
 * Depends on displayDirectional.
 */
template<class DataType>
ostream& URStack<DataType>::displayAll(ostream& out) const {
    if (not top) {
        /* There are truly no actions */
        return displayInvalidMessage("No actions", out);
    }

    /* Display all nodes from top till the end of the chain */
    return displayDirectional(top, nullptr,
                              out, false);
}

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
 * Effectively displays all nodes to the right of current,
 * including current.
 * Marked [[nodiscard]] to allow the compiler to issue warnings in case of
 * wasteful calls. For example `stack.displayPrevious(cout);`.
 * Depends on displayDirectional.
 */
template<class DataType>
ostream& URStack<DataType>::displayPrevious(ostream& out) const {
    if (isEmpty()) {
        /* No actions to undo */
        return display("No previous actions", out);
    }

    /* Display all the nodes from current to the end of the chain */
    return displayDirectional(current, nullptr,
                              out, false);
}

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
 * Effectively displays all the nodes to the right of current,
 * from closest to furthest.
 * Marked [[nodiscard]] to allow the compiler to issue warnings in case of
 * wasteful calls. For example `stack.displayNext(cout);`.
 * Depends on displayDirectional.
 */
template<class DataType>
ostream& URStack<DataType>::displayNext(ostream& out) const {
    if (not hasNext()) {
        /* No undone actions */
        return display("No next actions", out);
    }

    /* Display all the nodes from current to top in reverse */
    return displayDirectional(top, current, out, true);
}
