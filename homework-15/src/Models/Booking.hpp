#pragma once

#include <iostream>
#include <string>

struct Booking {
    unsigned int id;
    unsigned int memberId;
    unsigned int bookId;
};

std::ostream inline &operator<<(std::ostream &output, const Booking &booking) {
    output << booking.id << " " << booking.memberId << " " << booking.bookId;
    return output;
}

std::istream inline &operator>>(std::istream &input, Booking &booking) {
    input >> booking.id >> booking.memberId >> booking.bookId;
    return input;
}