#pragma once

#include "../Models/Member.hpp"

#include <string>
#include <vector>

struct Context {
    Member member;
};

class BaseMenu {
  protected:
    Context m_Context;
    std::string m_Title;
    std::vector<std::string> m_Menu;

  public:
    BaseMenu(Context context, std::string title);
    virtual ~BaseMenu();

    void render();
    BaseMenu virtual *update(bool &exit) = 0;

    void handleInputError();
    bool getConfirmation(const std::string &message);

    template <typename T>
    void getInput(T &input, const std::string &label = "") {
        if (!label.empty()) {
            std::cout << label << std::endl;
        }
        std::cin >> input;
        handleInputError();
    }
};
