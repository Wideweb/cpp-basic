#pragma once

#include "Menu/BaseMenu.hpp"

class LibApplication {
  private:
    BaseMenu *m_Menu;

  public:
    LibApplication();
    ~LibApplication();

    void run();
};
