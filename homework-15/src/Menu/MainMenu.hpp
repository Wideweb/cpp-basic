#pragma once

#include "BaseMenu.hpp"

class MainMenu : public BaseMenu {
  public:
    MainMenu(Context context);

    BaseMenu *update(bool &exit);

    BaseMenu *findMember();
};

class MemberManagementMenu : public BaseMenu {
  public:
    MemberManagementMenu(Context context);

    BaseMenu *update(bool &exit);

    void printAll();
    void addEntry();
    void removeEntry();
};

class BookManagementMenu : public BaseMenu {
  public:
    BookManagementMenu(Context context);

    BaseMenu *update(bool &exit);

    void printAll();
    void addEntry();
    void removeEntry();
};

class MemberBooksMenu : public BaseMenu {
  public:
    MemberBooksMenu(Context context);

    BaseMenu *update(bool &exit);

    void printAll();
    void takeBook();
    void returnBook();
};