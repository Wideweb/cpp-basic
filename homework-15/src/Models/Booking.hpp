#pragma once

#include "../DataBase.hpp"

#include <iostream>
#include <string>

struct Booking : public Entity {
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