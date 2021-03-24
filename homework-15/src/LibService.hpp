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
    void addBook(Book book);
    void removeBook(Book book);
    void removeBook(unsigned int index);

    std::vector<Member> getMembers();
    std::optional<Member> getMember(const std::string &name);
    void addMember(Member member);
    void removeMember(Member member);
    void removeMember(unsigned int index);
    std::vector<Book> getMemberBooks(Member member);
    void takeBook(Member member, Book book);
    void returnBook(Member member, Book book);

    static LibService &get() { return s_Instance; }
};
