#pragma once

#include <iostream>
#include <string>

struct Member {
    unsigned int id;
    std::string name;
};

std::ostream inline &operator<<(std::ostream &output, const Member &member) {
    output << member.id << " " << member.name;
    return output;
}

std::istream inline &operator>>(std::istream &input, Member &member) {
    input >> member.id >> member.name;
    return input;
}