﻿#pragma once

#include <iostream>
#include <string>

struct Book {
    unsigned int id;
    std::string name;
};

std::ostream inline &operator<<(std::ostream &output, const Book &book) {
    output << book.id << " " << book.name;
    return output;
}

std::istream inline &operator>>(std::istream &input, Book &book) {
    input >> book.id >> book.name;
    return input;
}