#include "BaseMenu.hpp"
#include "../Settings.hpp"
#include "../Utils/String.hpp"

#include <iostream>
#include <limits>

BaseMenu::BaseMenu(Context context, std::string title)
    : m_Context(context), m_Title(title) {}
BaseMenu::~BaseMenu() {}

void BaseMenu::render() {
    const int freeSpace = c_ScreenWidth - Utils::stringLength(m_Title);
    const int paddingLeft = freeSpace / 2;
    const int paddingRight = freeSpace - paddingLeft;

    std::cout << std::endl;

    for (int i = 0; i < paddingLeft - 1; i++) {
        std::cout << "-";
    }

    std::cout << " " << m_Title << " ";

    for (int i = 0; i < paddingRight - 1; i++) {
        std::cout << "-";
    }

    std::cout << std::endl;

    for (size_t i = 0; i < m_Menu.size(); i++) {
        std::cout << i + 1 << ". " << m_Menu[i] << std::endl;
    }
}

void BaseMenu::handleInputError() {
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<int>::max(), '\n');
    }
}

bool BaseMenu::getConfirmation(const std::string &message) {
    int selection;
    do {
        handleInputError();

        std::cout << message << std::endl;
        std::cout << "1. Да" << std::endl;
        std::cout << "2. Нет" << std::endl;

        std::cin >> selection;
    } while (std::cin.fail() || selection < 1 || selection > 2);

    return selection == 1;
}
