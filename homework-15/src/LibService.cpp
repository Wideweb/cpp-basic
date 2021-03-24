#include "LibService.hpp"

#include <stdexcept>

LibService LibService::s_Instance;

LibService::LibService() {}

LibService::~LibService() {}

std::vector<Book> LibService::getBooks() { return m_BookDb.getAll(); }

std::vector<Book> LibService::getAvailableBooks() {
    auto books = getBooks();
    auto bookings = m_BookingDb.getAll();

    std::vector<Book> availableBooks;
    for (const auto &book : books) {
        auto bookingIt = std::find_if(
            bookings.begin(), bookings.end(),
            [&book](const auto &booking) { return booking.bookId == book.id; });

        if (bookingIt == bookings.end()) {
            availableBooks.push_back(book);
        }
    }

    return availableBooks;
}

void LibService::addBook(Book book) { m_BookDb.add(book); }

void LibService::removeBook(Book book) {
    auto bookings = m_BookingDb.getAll();

    std::vector<Booking> bookBookings;
    std::copy_if(
        bookings.begin(), bookings.end(), std::back_inserter(bookBookings),
        [&book](const auto &booking) { return booking.bookId == book.id; });

    for (const auto &booking : bookBookings) {
        m_BookingDb.remove(booking);
    }

    if (m_BookDb.remove(book)) {
        throw std::invalid_argument("Ошибка при удалении книги");
    }
}

void LibService::removeBook(unsigned int index) {
    if (index < 0 || index >= getBooks().size()) {
        throw std::invalid_argument("Книга не найден");
    }

    removeBook(getBooks()[index]);
}

std::vector<Member> LibService::getMembers() { return m_MemberDb.getAll(); }

std::optional<Member> LibService::getMember(const std::string &name) {
    auto members = m_MemberDb.getAll();

    auto it = std::find_if(
        members.begin(), members.end(),
        [&name](const auto &member) { return member.name == name; });

    if (it == members.end()) {
        return std::nullopt;
    }

    return std::make_optional(*it);
}

void LibService::addMember(Member member) {
    if (getMember(member.name).has_value()) {
        throw std::invalid_argument(
            "Читатель с таким именем уже был зарегистрирован");
    }
    m_MemberDb.add(member);
}

void LibService::removeMember(Member member) {
    auto bookings = m_BookingDb.getAll();

    auto it = std::find_if(bookings.begin(), bookings.end(),
                           [&member](const auto &booking) {
                               return booking.memberId == member.id;
                           });

    if (it != bookings.end()) {
        throw std::invalid_argument("У читателя остались книги");
    }

    if (!m_MemberDb.remove(member)) {
        throw std::invalid_argument("Ошибка при удалении читателя");
    }
}

void LibService::removeMember(unsigned int index) {
    if (index < 0 || index >= getMembers().size()) {
        throw std::invalid_argument("Читатель не найден");
    }

    removeMember(getMembers()[index]);
}

std::vector<Book> LibService::getMemberBooks(Member member) {
    auto bookings = m_BookingDb.getAll();

    std::vector<Booking> memberBookings;
    std::copy_if(bookings.begin(), bookings.end(),
                 std::back_inserter(memberBookings),
                 [&member](const auto &booking) {
                     return booking.memberId == member.id;
                 });

    auto books = getBooks();

    std::vector<Book> memberBooks;
    for (const auto &booking : memberBookings) {
        auto bookIt = std::find_if(
            books.begin(), books.end(),
            [&booking](const auto &book) { return booking.bookId == book.id; });

        memberBooks.push_back(*bookIt);
    }

    return memberBooks;
}

void LibService::takeBook(Member member, Book book) {
    Booking booking;
    booking.memberId = member.id;
    booking.bookId = book.id;

    m_BookingDb.add(booking);
}

void LibService::returnBook(Member member, Book book) {
    auto bookings = m_BookingDb.getAll();

    auto bookingIt = std::find_if(bookings.begin(), bookings.end(),
                                  [&member, &book](const auto &booking) {
                                      return booking.memberId == member.id &&
                                             booking.bookId == book.id;
                                  });

    if (bookingIt == bookings.end()) {
        throw std::invalid_argument("Бронирование не найдено");
    }

    m_BookingDb.remove(*bookingIt);
}