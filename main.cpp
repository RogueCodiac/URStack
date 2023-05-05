#include "URStack.cpp"
#include "CommonIO.h"
#include <iostream>
#include <vector>

using namespace std;

/*
 * Pre-Conditions:
 *      const string reference to a prompt.
 *      ostream reference to display a prompt.
 *      istream reference read user input.
 *      Reference to a type T that has operator>>(istream&, T&) defined, or
 *      a reference to a string.
 *
 * Post-Conditions:
 *      Reads user input into the given variable reference of type T.
 *
 * Displays the given prompt, takes string input from the user.
 *
 * This method of coloring text is not supported by Windows 10 cmd;
 * use a terminal simulator.
 */
template<class T>
void get(const string& prompt, ostream& out,
         istream& in, T& result) {
    out << prompt
        << ":\n\n"
        << "\033[36;1;1m";   /* Text becomes cyan, bold */

    in >> result;

    out << "\033[0m";  /* Text becomes normal */
}

/*
 * Pre-Conditions:
 *      ostream reference to display a prompt.
 *      istream reference read user input.
 *      Reference to the URStack in use by the program.
 *
 * Post-Conditions:
 *      Given reference refers to a new URStack of the given, or default,
 *      capacity.
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
            << "\t\t"
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
 * If T is string, the whole line of input is taken.
 */
template<class T>
void insertNewAction(URStack<T>& stack, ostream& out, istream& in) {
    T new_action;

    if (is_same_v<T, string>) {
        /* T is string, take whole line as input */
        new_action = getString("Enter a new action", out, in);
    } else {
        /* T is not string, use its operator>> */
        get("Enter a new action", out, in, new_action);
    }

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
 * Handles all the necessary output to display the current size & capacity
 * of the URStack.
 */
template<class T>
void displayStackInfo(URStack<T>& stack, ostream& out) {
    out << '\n';

    displayDataMessage(
            "Stack size:\t" + to_string(stack.getSize())
                            + " / " + to_string(stack.getCapacity()),
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
    displaySeparator(cout);

    int selected_option;
    int options_num;
    URStack<string> stack;

    /* Create a new stack with a size given by the user */
    clear(stack, cout, cin);

    /* Process user input till exit is triggered */
    while (true) {
        displayStackInfo(stack, cout);
        options_num = displayMenu(cout);

        /* Get selected option */
        selected_option = getInt("Choose an option", cout, cin,
                                 1, options_num);

        switch (selected_option) {
            case 1:
                insertNewAction(stack, cout, cin);
                break;
            case 2:
                undo(stack, cout);
                break;
            case 3:
                redo(stack, cout);
                break;
            case 4:
                displayAll(stack, cout);
                break;
            case 5:
                displayPrevious(stack, cout);
                break;
            case 6:
                displayNext(stack, cout);
                break;
            case 7:
                clear(stack, cout, cin);
                break;
            case 8:
                return 0;
            default:
                displayInvalidMessage("Invalid option!", cout)
                << '\n' << endl;
        }
    }
}
