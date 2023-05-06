/*
 * URStack Project
 *
 *
 * CommonIO.cpp
 *
 * Date:        03/05/2023
 *
 * Author:      Mahmoud Yaman Seraj Alddin
 *
 * Purpose:     Implementation of the functions described in CommonIO.h
 *
 * List of Functions:
 *      void displaySeparator(ostream&)
 *          Displays a separator of width 70.
 *
 *     void displayInvalidMessage(const string&, ostream&)
 *          Displays an error message to the user.
 *
 *     void displayDataMessage(const string&, ostream&)
 *          Displays information to the user.
 *
 *     void getString(const string&, ostream&, istream&, string&)
 *          Displays the given prompt, places user string input into a
 *          given variable
 *
 *     int getInt(const string&, ostream&, istream&,
 *                  int lower = -1,
 *                  int upper = -1,
 *                  int defaultValue = -1)
 *          Displays the given prompt, keeps on trying to take int
 *          input from the user until a valid value is given.
 */

#include "CommonIO.h"


/* Used std features in the file, shortens typing */
using std::string, std::endl, std::ostream,
        std::istream, std::to_string, std::invalid_argument;

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
 *      const reference to a message to be displayed.
 *      ostream reference to display the output.
 *
 * Post-Conditions:
 *      Displays an error message in red color to the user.
 *
 * Displays an error message.
 * This method of coloring text is not supported by Windows 10 cmd;
 * use a terminal simulator.
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
 *      ostream reference to display the output.
 *
 * Post-Conditions:
 *      Displays a message in cyan color to the user.
 *
 * Displays a message.
 * This method of coloring text is not supported by Windows 10 cmd;
 * use a terminal simulator.
 */
ostream& displayDataMessage(const string& msg, ostream& out) {
    return out << "\033[36;1;1m"   /* Text becomes cyan, bold */
               << msg
               << "\033[0m";        /* Text becomes normal */
}

/*
 * Pre-Conditions:
 *      const string reference to the prompt.
 *      ostream reference to display the prompt.
 *      istream reference read user input.
 *
 * Post-Conditions:
 *      Returns user input as a string.
 *
 * Displays the given prompt, takes string input from the user.
 * This method of coloring text is not supported by Windows 10 cmd;
 * use a terminal simulator.
 */
string getString(const string& prompt, ostream& out,
               istream& in) {
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
 *      ostream reference to display the prompt.
 *      istream reference read user input.
 *      int minimum input value. Default disables bound.
 *      int maximum input value. Default disables bound.
 *      int default input value. Default is -1.
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

    /* Insure istream is blank */
    in.clear();

    /* Take input until user gives a valid value */
    while (true) {
        try {
            response = getString(prompt, out, in);

            /* No input */
            if (not response.length()) {
                return default_val;
            }

            /* Try to convert string response to int */
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
