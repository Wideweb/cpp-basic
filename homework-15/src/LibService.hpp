#pragma once

#include "DataBase.hpp"
#include "Models/Book.hpp"
#include "Models/Booking.hpp"
#include "Models/Member.hpp"
#include "Settings.hpp"

#include <optional>
#include <vector>

class LibService {
  private:
    static LibService s_Instance;

    DataBase<Member> m_MemberDb = DataBase<Member>(c_MemberDataFile);
    DataBase<Book> m_BookDb = DataBase<Book>(c_BookDataFile);
    DataBase<Booking> m_BookingDb = DataBase<Booking>(c_BookingDataFile);

    LibService();

  public:
    virtual ~LibService();

    LibService(LibService &other) = delete;
    void operator=(const LibService &) = delete;

    std::vector<Book> getBooks();
    std::vector<Book> getAvailableBooks();
    void addBook(const Book &book);
    void removeBook(const Book &book);
    void removeBook(unsigned int index);

    std::vector<Member> getMembers();
    std::optional<Member> getMember(const std::string &name);
    void addMember(const Member &member);
    void removeMember(const Member &member);
    void removeMember(unsigned int index);
    std::vector<Book> getMemberBooks(const Member &member);
    void takeBook(const Member &member, const Book &book);
    void returnBook(const Member &member, const Book &book);

    static LibService &get() { return s_Instance; }
};
