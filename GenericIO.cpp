/*
 * URStack Project
 *
 *
 * GenericIO.cpp
 *
 * Date:        03/05/2023
 *
 * Author:      Mahmoud Yaman Seraj Alddin
 *
 * Purpose:     Implementation of generic input/output functions.
 *
 * List of Functions:
 *      template<class T>
 *      std::ostream& display(const T&, std::ostream&)
 *          Displays the given instance of type T, using its operator<<
 *
 *      template<class T>
 *      void get(const std::string&, std::ostream&, std::istream&, T&)
 *          Displays the given prompt, writes user input into the given
 *          reference of T.
 */

#ifndef URSTACK_GENERICIO_CPP
#define URSTACK_GENERICIO_CPP

#include <climits>
#include <iostream>
#include <string>


/*
 * Pre-Conditions:
 *      const T reference to a value.
 *      ostream reference to display a prompt.
 *      Reference to a type T that has operator<<(ostream&, const T&) defined.
 *
 * Post-Conditions:
 *      Displays the given reference into the given ostream.
 *
 * Displays the given prompt, takes string input from the user.
 *
 * This method of coloring text is not supported by Windows 10 cmd;
 * use a terminal simulator.
 */
template<class T>
std::ostream& display(const T& val, std::ostream& out) {
    return out << "\033[36;1;1m"   /* Text becomes cyan, bold */
               << val
               << "\033[0m";       /* Text becomes normal */
}

/*
 * Pre-Conditions:
 *      const string reference to a prompt.
 *      ostream reference to display a prompt.
 *      istream reference read user input.
 *      Reference to a type T that has operator>>(istream&, T&) defined.
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
void get(const std::string& prompt, std::ostream& out,
         std::istream& in, T& result) {
    out << prompt
    << ": "
    << "\033[36;1;1m"   /* Text becomes cyan, bold */
    << std::endl;

    in >> result;

    /* Ignore all unused input */
    in.ignore(LLONG_MAX, '\n');

    out << "\033[0m";  /* Text becomes normal */
}

#endif //URSTACK_GENERICIO_CPP
