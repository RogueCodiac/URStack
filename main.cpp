#include "URStack.cpp"
#include "CustomIO.h"
#include <iostream>
#include <vector>

using namespace std;

template<class T>
void clear(ostream& out, istream& in, URStack<T>& result) {
    int new_capacity = getInt("Enter Stack capacity", out,
                              in, 1);

    out << endl;

    result = new_capacity < 0 ? URStack<T>() : URStack<T>(new_capacity);
}

int displayMenu(ostream& out) {
    vector<string> options{
            "Insert a new action",
            "Undo action",
            "Redo action",
            "Display all actions",
            "Display all previous actions",
            "Display all next actions",
            "Clear stack",
            "Stack size",
            "Exit",
    };

    for (int i = 0; i < options.size(); i++) {
        displayDataMessage(to_string(i + 1) + '-', out)
            << "\t\t"
            << options[i]
            << '\n';
    }

    displaySeparator(out);
    return (int) options.size();
}

template<class T>
void insertNewAction(URStack<T>& stack, istream& in, ostream& out) {
    T new_action;
    get("Enter a new action", out, in, new_action);
    stack.insertNewAction(new_action);
    out << endl;
}

template<class T>
void undo(URStack<T>& stack, ostream& out) {
    out << '\n';
    stack.undo(out);
    out << '\n' << endl;
}

template<class T>
void redo(URStack<T>& stack, ostream& out) {
    out << '\n';
    stack.redo(out);
    out << '\n' << endl;
}

template<class T>
ostream& displayAll(URStack<T>& stack, ostream& out) {
    return stack.displayAll(out) << '\n' << endl;
}

template<class T>
ostream& displayPrevious(URStack<T>& stack, ostream& out) {
    return stack.displayPrevious(out) << '\n' << endl;
}

template<class T>
ostream& displayNext(URStack<T>& stack, ostream& out) {
    return stack.displayNext(out) << '\n' << endl;
}

template<class T>
void displaySize(URStack<T>& stack, ostream& out) {
    out << '\n';
    displayDataMessage(
            "Stack size is: " + to_string(stack.getSize()),
            out) << '\n' << endl;
}

int main() {
    displaySeparator(cout);

    int selected_option;
    int options_num;
    URStack<string> stack;

    clear(cout, cin, stack);

    while (true) {
        options_num = displayMenu(cout);

        selected_option = getInt("Choose an option", cout, cin,
                                 1, options_num);

        switch (selected_option) {
            case 1:
                insertNewAction(stack, cin, cout);
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
                clear(cout, cin, stack);
                break;
            case 8:
                displaySize(stack, cout);
                break;
            case 9:
                return 0;
            default:
                displayInvalidMessage("Invalid option!", cout) << '\n' << endl;
        }
    }
}
