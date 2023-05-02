//
// Created by yaman on 5/2/2023.
//

#ifndef URSTACK_CUSTOMIO_H
#define URSTACK_CUSTOMIO_H

#include <string>
#include <iostream>
#include <exception>

void displayInvalidMessage(const std::string&, std::ostream&);

void displayDataMessage(const std::string&, std::ostream&);

void displaySeparator(std::ostream&);

std::string get(const std::string&, std::ostream&, std::istream&);

int getInt(const std::string&, std::ostream&, std::istream&,
           int lower = -1,
           int upper = -1,
           int default_val = -1);

#endif //URSTACK_CUSTOMIO_H
