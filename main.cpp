/*
 * URStack Project
 *
 *
 * main.cpp
 *
 * Date:        06/05/2023
 *
 * Author:      Mahmoud Yaman Seraj Alddin
 *
 * Purpose:     File containing the main function & other vital functions.
 *
 * List of Functions:
 *      template<class T>
 *      void clear(URStack<T>&, ostream&, istream&)
 *          Assigns a new URStack<T> to the given reference.
 *
 *      int displayMenu(ostream&)
 *          Displays the option menu.
 *
 *       template<class T>
 *       void insertNewAction(URStack<T>&, ostream&, istream&)
 *          Handles all the necessary input and output to
 *          insert a new action to the URStack
 *          using its insertNewAction function.
 *          If T is string, a different variant of the function is called.
 *
 *       void insertNewAction(URStack<string>&, ostream&, istream&)
 *          Handles all the necessary input and output to
 *          insert a new action string to the URStack,
 *          using its insertNewAction function.
 *          Takes the whole line as input for the action string.
 *
 *       template<class T>
 *       void undo(URStack<T>&, ostream&)
 *           Handles all the necessary output
 *           to undo an action in the URStack,
 *           using the undo function.
 *
 *       template<class T>
 *       void redo(URStack<T>&, ostream&)
 *          Handles all the necessary output
 *          to redo an action in the URStack,
 *          using the redo function.
 *
 *       template<class T>
 *       ostream& displayAll(URStack<T>&, ostream&)
 *          Handles all the necessary output
 *          to display all actions in the URStack,
 *          using the displayAll function.
 *
 *       template<class T>
 *       ostream& displayPrevious(URStack<T>&, ostream&)
 *          Handles all the necessary output to display all previous
 *          actions in the URStack, using the displayPrevious function.
 *
 *       template<class T>
 *       ostream& displayNext(URStack<T>&, ostream&)
 *          Handles all the necessary output to display all next
 *          actions in the URStack, using the displayNext function.
 *
 *      template<class T>
 *      void displayStackInfo(URStack<T>&, ostream&)
 *          Handles all the necessary output to display
 *          the current size, capacity, & whether the type
 *          stored in the URStack is string or not.
 *
 *      int main()
 *          Main function of the program
 */

#include <iostream>
#include <type_traits>
#include <vector>

#include "CommonIO.h"
#include "URStack.cpp"


using namespace std;

/*
 * Pre-Conditions:
 *      ostream reference to display a prompt.
 *      istream reference read user input.
 *      Reference to the URStack in use by the program.
 *
 * Post-Conditions:
 *      Given reference refers to a new URStack of the given, or default,
 *      capacity.
 *
 * Assigns a new URStack<T> to the given reference.
 */
template<class T>
void clear(URStack<T>& result, ostream& out, istream& in) {
    /* Default is -1 */
    int new_capacity = getInt("Enter Stack capacity", out,
                              in, 1);

    /* Display new line, flush buffer */
    out << endl;

    /* Use default capacity in the constructor (presumably unknown) */
    result = new_capacity < 0 ? URStack<T>() : URStack<T>(new_capacity);
}

/*
 * Pre-Conditions:
 *      ostream reference to display a prompt..
 *
 * Post-Conditions:
 *      Displays the option menu.
 *      Returns the number of options in the menu as an int.
 *
 * Displays the option menu.
 */
int displayMenu(ostream& out) {
    vector<string> options{
            "Insert a new action",
            "Undo action",
            "Redo action",
            "Display all actions",
            "Display all previous actions",
            "Display all next actions",
            "Clear stack",
            "Exit",
    };

    /* Loop over all options */
    for (int i = 0; i < options.size(); i++) {
        displayDataMessage(to_string(i + 1) + '-', out)
            << string(4, '\t')
            << options[i]
            << '\n';
    }

    displaySeparator(out);

    /* cast from vector<string>::size_t to int */
    return (int) options.size();
}

/*
 * Pre-Conditions:
 *      Reference to the URStack<T> in use by the program.
 *      Type T must have operator>>(istream&, T&) defined or be a string.
 *      ostream reference to display a prompt.
 *      istream reference read user input.
 *
 * Post-Conditions:
 *      An action of type T is created using user input & inserted
 *      to the given URStack.
 *
 * Handles all the necessary input and output to
 * insert a new action to the URStack using its insertNewAction function.
 * If T is string, a variant of the function is called.
 */
template<class T>
void insertNewAction(URStack<T>& stack, ostream& out, istream& in) {
    T new_action;

    /* use operator>> defined in T */
    get("Enter a new action", out, in, new_action);

    stack.insertNewAction(new_action);

    /* Display new line, flush buffer */
    out << endl;
}

/*
 * Pre-Conditions:
 *      Reference to the URStack<string> in use by the program.
 *      ostream reference to display a prompt.
 *      istream reference read user input.
 *
 * Post-Conditions:
 *      An action of type string is created using user input & inserted
 *      to the given URStack.
 *
 * Handles all the necessary input and output to
 * insert a new action string to the URStack using its insertNewAction function.
 * Takes the whole line as input for the action string.
 */
void insertNewAction(URStack<string>& stack, ostream& out, istream& in) {
    string new_action = getString("Enter a new action", out, in);

    stack.insertNewAction(new_action);

    /* Display new line, flush buffer */
    out << endl;
}

/*
 * Pre-Conditions:
 *      Reference to the URStack<T> in use by the program.
 *      Type T must have operator<<(ostream&, const T&) defined.
 *      ostream reference to display a prompt.
 *
 * Post-Conditions:
 *      The latest action in the URStack is undone & displayed,
 *      if possible.
 *
 * Handles all the necessary output to undo an action in the URStack,
 * using the undo function.
 */
template<class T>
void undo(URStack<T>& stack, ostream& out) {
    /* Display empty line */
    out << '\n';

    stack.undo(out);

    /* Display two new lines, flush buffer */
    out << '\n' << endl;
}

/*
 * Pre-Conditions:
 *      Reference to the URStack<T> in use by the program.
 *      Type T must have operator<<(ostream&, const T&) defined.
 *      ostream reference to display a prompt.
 *
 * Post-Conditions:
 *      The latest action in the URStack is redone & displayed,
 *      if possible.
 *
 * Handles all the necessary output to redo an action in the URStack,
 * using the redo function.
 */
template<class T>
void redo(URStack<T>& stack, ostream& out) {
    /* Display empty line */
    out << '\n';

    stack.redo(out);

    /* Display two new lines, flush buffer */
    out << '\n' << endl;
}

/*
 * Pre-Conditions:
 *      Reference to the URStack<T> in use by the program.
 *      Type T must have operator<<(ostream&, const T&) defined.
 *      ostream reference to display a prompt.
 *
 * Post-Conditions:
 *      Displays all the actions in the given URStack.
 *
 * Handles all the necessary output to display all actions in the URStack,
 * using the displayAll function.
 */
template<class T>
ostream& displayAll(URStack<T>& stack, ostream& out) {
    /* Display empty line */
    out << '\n';

    /* Display the actions followed by two new lines */
    return stack.displayAll(out) << '\n' << endl;
}

/*
 * Pre-Conditions:
 *      Reference to the URStack<T> in use by the program.
 *      Type T must have operator<<(ostream&, const T&) defined.
 *      ostream reference to display a prompt.
 *
 * Post-Conditions:
 *      Displays all the previous actions in the given URStack.
 *
 * Handles all the necessary output to display all previous
 * actions in the URStack, using the displayPrevious function.
 */
template<class T>
ostream& displayPrevious(URStack<T>& stack, ostream& out) {
    /* Display empty line */
    out << '\n';

    /* Display the actions followed by two new lines */
    return stack.displayPrevious(out) << '\n' << endl;
}

/*
 * Pre-Conditions:
 *      Reference to the URStack<T> in use by the program.
 *      Type T must have operator<<(ostream&, const T&) defined.
 *      ostream reference to display a prompt.
 *
 * Post-Conditions:
 *      Displays all the next actions in the given URStack.
 *
 * Handles all the necessary output to display all next
 * actions in the URStack, using the displayNext function.
 */
template<class T>
ostream& displayNext(URStack<T>& stack, ostream& out) {
    /* Display empty line */
    out << '\n';

    /* Display the actions followed by two new lines */
    return stack.displayNext(out) << '\n' << endl;
}

/*
 * Pre-Conditions:
 *      Reference to the URStack<T> in use by the program.
 *      Type T must have operator<<(ostream&, const T&) defined.
 *      ostream reference to display a prompt.
 *
 * Post-Conditions:
 *      Displays information about the given URStack.
 *
 * Handles all the necessary output to display the current size, capacity, &
 * whether the type stored in the URStack is string or not.
 */
template<class T>
void displayStackInfo(URStack<T>& stack, ostream& out) {
    /* Display empty line */
    out << '\n';

    /* Displays {size} / {capacity} */
    displayDataMessage(
            "Stack size:\t\t" + to_string(stack.getSize())
                            + " / " + to_string(stack.getCapacity()),
            out) << '\n';

    displayDataMessage("Datatype:\t\t", out);

    /* Displays "String" or "Custom" based on the type of T */
    displayDataMessage(is_same_v<T, string> ? "String" : "Custom",
            out) << '\n';
}

/*
 * Pre-Conditions:
 *      No code-related preconditions.
 *
 * Post-Conditions:
 *      Program startup.
 */
int main() {
    int selected_option;
    int options_num;
    ostream& out = cout;
    istream& in = cin;

    /* Change DataType only here */
    URStack<string> stack;

    displaySeparator(out);

    /* Create a new stack with a size given by the user */
    clear(stack, out, in);

    /* Process user input till exit is triggered */
    while (true) {
        displayStackInfo(stack, out);
        options_num = displayMenu(out);

        /* Get selected option */
        selected_option = getInt("Choose an option", out, in,
                                 1, options_num);

        switch (selected_option) {
            case 1:
                insertNewAction(stack, out, in);
                break;
            case 2:
                undo(stack, out);
                break;
            case 3:
                redo(stack, out);
                break;
            case 4:
                displayAll(stack, out);
                break;
            case 5:
                displayPrevious(stack, out);
                break;
            case 6:
                displayNext(stack, out);
                break;
            case 7:
                clear(stack, out, in);
                break;
            case 8:
                return 0;
            default:
                displayInvalidMessage("Invalid option!", out)
                << '\n' << endl;
        }
    }
}
