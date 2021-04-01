#include "MainMenu.hpp"
#include "../LibService.hpp"
#include "../Settings.hpp"
#include "../Utils/Table.hpp"

#include <algorithm>
#include <filesystem>
#include <iostream>
#include <stdexcept>

////////////////////////////////////////////////////////
////////////////////// MAIN MENU ///////////////////////
////////////////////////////////////////////////////////
MainMenu::MainMenu(Context context) : BaseMenu(context, "Главное меню") {
    m_Menu = {"Читатель", "База книг", "База читателей", "Выход"};
}

BaseMenu *MainMenu::update(bool &exit) {
    unsigned int input;
    getInput(input);

    switch (input) {
    case 1:
        return findMember();
    case 2:
        return new BookManagementMenu(m_Context);
    case 3:
        return new MemberManagementMenu(m_Context);
    case 4:
        exit = true;
        return this;

    default:
        throw std::invalid_argument("Неправильный пункт меню");
        break;
    }
}

BaseMenu *MainMenu::findMember() {
    std::string memberName;
    getInput(memberName, "Введите имя читателя:");

    const auto member = LibService::get().getMember(memberName);

    if (!member.has_value()) {
        std::cout << "Читатель не был найден" << std::endl;
        return this;
    }

    m_Context.member = member.value();

    return new MemberBooksMenu(m_Context);
}

////////////////////////////////////////////////////////
//////////////// MEBMER MANAGEMENT MENU ////////////////
////////////////////////////////////////////////////////
MemberManagementMenu::MemberManagementMenu(Context context)
    : BaseMenu(context, "Меню управления читателями") {
    m_Menu = {"Просмотреть все записи", "Добавить читателя", "Удалить читателя",
              "Назад"};
}

BaseMenu *MemberManagementMenu::update(bool &) {
    unsigned int input;
    getInput(input);

    switch (input) {
    case 1:
        printAll();
        return this;
    case 2:
        addEntry();
        return this;
    case 3:
        removeEntry();
        return this;
    case 4:
        return new MainMenu(m_Context);

    default:
        throw std::invalid_argument("Неправильный пункт меню");
        break;
    }
}

void MemberManagementMenu::printAll() {
    const auto &members = LibService::get().getMembers();

    if (members.empty()) {
        std::cout << "В системе нет читателей" << std::endl;
        return;
    }

    Helper::printTable("Таблица читателей: ", members, c_ScreenWidth);
}

void MemberManagementMenu::addEntry() {
    Member member;

    getInput(member.name, "Имя читателя:");

    try {
        LibService::get().addMember(member);
        std::cout << "Читател был успешно добавлен" << std::endl;
    } catch (const char *message) {
        std::cout << message << std::endl;
        std::cout << "Читател не был добавлен" << std::endl;
    }
}

void MemberManagementMenu::removeEntry() {
    unsigned int index;
    getInput(index, "Введите индекс читателя:");

    if (!getConfirmation("Вы действительно хотите удалить запись?")) {
        std::cout << "Читатель не был удален" << std::endl;
        return;
    }

    try {
        LibService::get().removeMember(index - 1);
        std::cout << "Читатель был успешно удален" << std::endl;
    } catch (const char *message) {
        std::cout << message << std::endl;
        std::cout << "Читатель не был удален" << std::endl;
    }
}

////////////////////////////////////////////////////////
///////////////// BOOK MANAGEMENT MENU /////////////////
////////////////////////////////////////////////////////
BookManagementMenu::BookManagementMenu(Context context)
    : BaseMenu(context, "Меню управления книгами") {
    m_Menu = {"Просмотреть все записи", "Добавить книгу", "Удалить книгу",
              "назад"};
}

BaseMenu *BookManagementMenu::update(bool &) {
    unsigned int input;
    getInput(input);

    switch (input) {
    case 1:
        printAll();
        return this;
    case 2:
        addEntry();
        return this;
    case 3:
        removeEntry();
        return this;
    case 4:
        return new MainMenu(m_Context);

    default:
        throw std::invalid_argument("Неправильный пункт меню");
        break;
    }
}

void BookManagementMenu::printAll() {
    const auto &books = LibService::get().getBooks();

    if (books.empty()) {
        std::cout << "В системе нет книг" << std::endl;
        return;
    }

    Helper::printTable("Таблица книг: ", books, c_ScreenWidth);
}

void BookManagementMenu::addEntry() {
    Book book;
    getInput(book.name, "Название:");

    try {
        LibService::get().addBook(book);
        std::cout << "Книга была успешно добавлена" << std::endl;
    } catch (const char *message) {
        std::cout << message << std::endl;
        std::cout << "Книга не была добавлена" << std::endl;
    }
}

void BookManagementMenu::removeEntry() {
    unsigned int index;
    getInput(index, "Введите индекс книги:");

    if (!getConfirmation("Вы действительно хотите удалить книгу?")) {
        std::cout << "Книга не была удалена" << std::endl;
        return;
    }

    try {
        LibService::get().removeBook(index - 1);
        std::cout << "Книга была успешно удалена" << std::endl;
    } catch (const char *message) {
        std::cout << message << std::endl;
        std::cout << "Книга не была удалена" << std::endl;
    }
}

////////////////////////////////////////////////////////
///////////////// MEMBER BOOKS MENU ////////////////////
////////////////////////////////////////////////////////
MemberBooksMenu::MemberBooksMenu(Context context)
    : BaseMenu(context, "Меню читателя") {
    m_Menu = {"Книги читателя", "Взять книгу", "Вернуть книгу", "Назад"};
}

BaseMenu *MemberBooksMenu::update(bool &) {
    unsigned int input;
    getInput(input);

    switch (input) {
    case 1:
        printAll();
        return this;
    case 2:
        takeBook();
        return this;
    case 3:
        returnBook();
        return this;
    case 4:
        return new MainMenu(m_Context);

    default:
        throw std::invalid_argument("Неправильный пункт меню");
        break;
    }
}

void MemberBooksMenu::printAll() {
    const auto memberBooks = LibService::get().getMemberBooks(m_Context.member);

    if (memberBooks.empty()) {
        std::cout << "У читателя нет книг" << std::endl;
        return;
    }

    Helper::printTable("Таблица книг читателя: ", memberBooks, c_ScreenWidth);
}

void MemberBooksMenu::takeBook() {
    const auto availableBooks = LibService::get().getAvailableBooks();

    if (availableBooks.empty()) {
        std::cout << "Книг нет в наличии" << std::endl;
        return;
    }

    Helper::printTable("Таблица доступных книг: ", availableBooks,
                       c_ScreenWidth);

    unsigned int index;
    getInput(index, "Введите индекс книги:");

    if (index < 1 || index > availableBooks.size()) {
        std::cout << "Книга не была найден" << std::endl;
        return;
    }

    try {
        LibService::get().takeBook(m_Context.member, availableBooks[index - 1]);
        std::cout << "Данные о книге были успешно обновлены" << std::endl;
    } catch (const char *message) {
        std::cout << message << std::endl;
        std::cout << "Книга не была обнавлена" << std::endl;
    }
}

void MemberBooksMenu::returnBook() {
    auto &member = m_Context.member;

    const auto memberBooks = LibService::get().getMemberBooks(m_Context.member);

    if (memberBooks.empty()) {
        std::cout << "У читателя нет книг" << std::endl;
        return;
    }

    Helper::printTable("Таблица книг читателя: ", memberBooks, c_ScreenWidth);

    unsigned int index;
    getInput(index, "Введите индекс книги:");

    if (index < 1 || index > memberBooks.size()) {
        std::cout << "Книга не была найден" << std::endl;
        return;
    }

    try {
        LibService::get().returnBook(member, memberBooks[index - 1]);
        std::cout << "Данные о книге были успешно обновлены" << std::endl;
    } catch (const char *message) {
        std::cout << message << std::endl;
        std::cout << "Книга не была возвращена" << std::endl;
    }
}
