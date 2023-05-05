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
std::ostream& displayDataMessage(const std::string&, std::ostream& out);


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
void get(const std::string&, std::ostream&,
         std::istream&, std::string&);

int getInt(const std::string&, std::ostream&, std::istream&,
           int lower = -1,
           int upper = -1,
           int default_val = -1);

#endif //URSTACK_CUSTOMIO_H
