//
// Created by yaman on 5/2/2023.
//

#include "CustomIO.h"

using std::string, std::endl, std::ostream,
        std::istream, std::to_string, std::invalid_argument;

/*
 * Pre-Conditions:
 *      const reference to a message to be displayed.
 *      ostream reference (optional), default is cout.
 *
 * Post-Conditions:
 *      Displays an error message.
 *
 * Displays an error message.
 */
ostream& displayInvalidMessage(const string& msg, ostream& out) {
    return
        out << "\033[31;1;1m"   /* Text color becomes red, underlined, bold */
            << msg
            << "\033[0m";       /* Text color becomes normal */
}

/*
 * Pre-Conditions:
 *      const reference to a message to be displayed.
 *      ostream reference (optional), default is cout.
 *
 * Post-Conditions:
 *      Displays an information message.
 *
 * Displays an information message.
 */
ostream& displayDataMessage(const string& msg, ostream& out) {
    return
        out << "\033[36;1;1m"   /* Text becomes cyan, bold */
            << msg
            << "\033[0m";        /* Text becomes normal */
}

/*
 * Pre-Conditions:
 *      ostream reference (optional), default is cout.
 *
 * Post-Conditions:
 *      Displays a separator of width 70 to the given ostream.
 *
 * Displays a separator of width 70.
 */
ostream& displaySeparator(ostream& out) {
    return out << '\n' << string(70, '-') << endl;
}

/*
 * Pre-Conditions:
 *      const string reference to the prompt.
 *      ostream reference (optional), default is cout.
 *      istream reference (optional), default is cin.
 *
 * Post-Conditions:
 *      Returns user string input.
 *
 * Displays the given prompt, takes string input from the user.
 */
string get(const string& prompt, ostream& out, istream& in) {
    string result;

    out << prompt
        << ": "
        << "\033[36;1;1m";   /* Text becomes cyan, bold */

    getline(in, result);

    out << "\033[0m";  /* Text becomes normal */

    return result;
}

/*
 * Pre-Conditions:
 *      const string reference to the prompt.
 *      ostream reference (optional), default is cout.
 *      istream reference (optional), default is cin.
 *      int minimum input value. Default disables bound.
 *      int maximum input value. Default disables bound.
 *      int default input value. Default disables default.
 *
 * Post-Conditions:
 *      Returns user int input.
 *
 * Displays the given prompt, keeps on trying to take int
 * input from the user until a given value is given.
 */
int getInt(const string& prompt, ostream& out, istream& in,
           int lower, int upper, int default_val) {
    string response;

    /* Take input until user gives a default value */
    while (true) {
        try {
            if (default_val < 0) {
                response = get(prompt, out, in);
            } else {
                response = get(prompt
                               + " (Default is " + to_string(default_val) + ")",
                               out, in);
            }

            /* No input */
            if (not response.length()) {
                return default_val;
            }

            /* Convert string response to int */
            const int result = stoi(response);

            if (lower != -1 and result < lower) {
                /* Lower than minimum */
                displayInvalidMessage(
                        "Invalid integer must be >= "
                        + to_string(lower),
                        out
                ) << '\n' << endl;
                continue;
            } else if (upper != -1 and upper < result) {
                /* Higher than maximum */
                displayInvalidMessage(
                        "Invalid integer must be between "
                        + to_string(lower) + " & " + to_string(upper),
                        out
                ) << '\n' << endl;
                continue;
            }

            return result;
        } catch (invalid_argument& ignored) {
            displayInvalidMessage("Invalid integer input!", out)
            << '\n' << endl;
        }
    }
}
