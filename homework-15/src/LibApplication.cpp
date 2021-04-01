#include "LibApplication.hpp"
#include "Menu/MainMenu.hpp"

#include <exception>
#include <iostream>

LibApplication::LibApplication() { m_Menu = new MainMenu({}); }

LibApplication::~LibApplication() { delete m_Menu; }

void LibApplication::run() {
    bool exit = false;
    while (!exit) {
        m_Menu->render();

        try {
            auto *nextMenu = m_Menu->update(exit);

            if (nextMenu != m_Menu) {
                delete m_Menu;
                m_Menu = nextMenu;
            }
        } catch (const std::exception &e) {
            std::cout << e.what() << std::endl;
        } catch (...) {
            std::cout << "Произошла неизвестная ошибка" << std::endl;
        }
    }
}
