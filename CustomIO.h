//
// Created by yaman on 5/2/2023.
//

#ifndef URSTACK_CUSTOMIO_H
#define URSTACK_CUSTOMIO_H

#include <string>
#include <iostream>
#include <exception>


std::ostream& displayInvalidMessage(const std::string&, std::ostream&);

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
template<class T>
std::ostream& displayDataMessage(const T& msg, std::ostream& out) {
    return
            out << "\033[36;1;1m"   /* Text becomes cyan, bold */
                << msg
                << "\033[0m";        /* Text becomes normal */
}

std::ostream& displaySeparator(std::ostream&);

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
template<class T>
void get(const std::string& prompt, std::ostream& out,
         std::istream& in, T& result) {
    out << prompt
        << ": "
        << "\033[36;1;1m";   /* Text becomes cyan, bold */

    getline(in, result);

    out << "\033[0m";  /* Text becomes normal */
}

int getInt(const std::string&, std::ostream&, std::istream&,
           int lower = -1,
           int upper = -1,
           int default_val = -1);

#endif //URSTACK_CUSTOMIO_H
