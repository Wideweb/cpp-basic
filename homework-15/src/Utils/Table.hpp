#pragma once

#include "../Models/Book.hpp"
#include "../Models/Booking.hpp"
#include "../Models/Member.hpp"
#include "String.hpp"

#include <iostream>
#include <numeric>
#include <string>
#include <vector>

class Table {
  private:
    std::vector<int> m_ColumnWidth;
    std::vector<std::vector<std::string>> m_Rows;
    const int m_CellPadding = 4;

  public:
    void addRow(std::vector<std::string> row) {
        if (m_ColumnWidth.empty()) {
            m_ColumnWidth.resize(row.size());
        }

        for (unsigned int i = 0; i < row.size(); i++) {
            const int size = Utils::stringLength(row[i]) + m_CellPadding;
            if (m_ColumnWidth[i] < size) {
                m_ColumnWidth[i] = size;
            }
        }

        m_Rows.push_back(row);
    }

    void print(int minWidth = 0) {
        int rowWidth =
            std::accumulate(m_ColumnWidth.begin(), m_ColumnWidth.end(), 0) +
            m_ColumnWidth.size() + 1;

        int columnAddWidth = 0;
        if (rowWidth < minWidth) {
            columnAddWidth = (minWidth - rowWidth) / m_ColumnWidth.size();
            rowWidth += columnAddWidth * m_ColumnWidth.size();
        }

        const int remainingSpace = minWidth - rowWidth;
        rowWidth = minWidth;

        std::cout << std::string(rowWidth, '-');
        std::cout << std::endl;

        for (const auto &row : m_Rows) {
            std::cout << "|";
            for (unsigned int i = 0; i < row.size(); i++) {
                int columnWidth = m_ColumnWidth[i] + columnAddWidth;
                columnWidth += (i == row.size() - 1) ? remainingSpace : 0;
                printText(row[i], columnWidth);
                std::cout << "|";
            }
            std::cout << std::endl;
            std::cout << std::string(rowWidth, '-');
            std::cout << std::endl;
        }
    }

  private:
    void printText(std::string text, int width) {
        const int freeSpace = width - Utils::stringLength(text);
        const int paddingLeft = freeSpace / 2;
        const int paddingRight = freeSpace - paddingLeft;

        for (int i = 0; i < paddingLeft; i++) {
            std::cout << " ";
        }

        std::cout << text;

        for (int i = 0; i < paddingRight; i++) {
            std::cout << " ";
        }
    }
};

class Helper {
  public:
    void static printTable(const std::string &title,
                           const std::vector<Book> &books, int minWidth) {
        std::cout << std::endl;
        std::cout << title << std::endl;

        if (books.empty()) {
            std::cout << "По Вашему запросу ничего не найдено." << std::endl;
            return;
        }

        Table table;
        table.addRow({"N", "Название"});

        int index = 0;
        for (const auto &book : books) {
            index++;
            std::vector<std::string> row;
            row.push_back(Utils::toString(index));
            row.push_back(book.name);
            table.addRow(row);
        }
        table.print(minWidth);
        std::cout << std::endl;
    }

    void static printTable(const std::string &title,
                           const std::vector<Member> &members, int minWidth) {
        std::cout << std::endl;
        std::cout << title << std::endl;

        if (members.empty()) {
            std::cout << "По Вашему запросу ничего не найдено." << std::endl;
            return;
        }

        Table table;
        table.addRow({"N", "Имя"});

        int index = 0;
        for (const auto &member : members) {
            index++;
            std::vector<std::string> row;
            row.push_back(Utils::toString(index));
            row.push_back(member.name);
            table.addRow(row);
        }

        table.print(minWidth);
        std::cout << std::endl;
    }
};