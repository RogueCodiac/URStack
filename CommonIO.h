/*
 * URStack Project
 *
 *
 * CommonIO.h
 *
 * Date:        02/05/2023
 *
 * Author:      Mahmoud Yaman Seraj Alddin
 *
 * Purpose:     Definitions for shared input & output functions
 *              used in the project.
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

#ifndef URSTACK_COMMONIO_H
#define URSTACK_COMMONIO_H

#include <exception>
#include <iostream>
#include <string>

#include "GenericIO.cpp"


/*
 * Pre-Conditions:
 *      ostream reference to display the output.
 *
 * Post-Conditions:
 *      Displays a separator of width 70 to the given ostream.
 *
 * Displays a separator of width 70.
 */
std::ostream& displaySeparator(std::ostream&);

/*
 * Pre-Conditions:
 *      const reference to a message to be displayed.
 *      ostream reference to display the output.
 *
 * Post-Conditions:
 *      Displays an error message in red color to the user.
 *
 * Displays an error message.
 */
std::ostream& displayInvalidMessage(const std::string&,
                                    std::ostream&);

/*
 * Pre-Conditions:
 *      const reference to a message to be displayed.
 *      ostream reference to display the output.
 *
 * Post-Conditions:
 *      Displays a message in cyan color to the user.
 *
 * Displays a message.
 */
std::ostream& displayDataMessage(const std::string&,
                                 std::ostream& out);

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
 */
std::string getString(const std::string&,
                      std::ostream&,
                      std::istream&);

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
int getInt(const std::string&,
           std::ostream&, std::istream&,
           int lower = -1,
           int upper = -1,
           int default_val = -1);

#endif //URSTACK_COMMONIO_H
