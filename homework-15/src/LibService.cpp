#include "LibService.hpp"

#include <stdexcept>

LibService LibService::s_Instance;

LibService::LibService() {}

LibService::~LibService() {}

std::vector<Book> LibService::getBooks() { return m_BookDb.getAll(); }

std::vector<Book> LibService::getAvailableBooks() {
    const auto &books = getBooks();
    const auto &bookings = m_BookingDb.getAll();

    std::vector<Book> availableBooks;
    for (const auto &book : books) {
        const auto bookingIt = std::find_if(
            bookings.cbegin(), bookings.cend(),
            [&book](const auto &booking) { return booking.bookId == book.id; });

        if (bookingIt == bookings.cend()) {
            availableBooks.push_back(book);
        }
    }

    return availableBooks;
}

void LibService::addBook(const Book &book) { m_BookDb.add(book); }

void LibService::removeBook(const Book &book) {
    const auto &bookings = m_BookingDb.getAll();

    std::vector<Booking> bookBookings;
    std::copy_if(
        bookings.cbegin(), bookings.cend(), std::back_inserter(bookBookings),
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
    const auto &members = m_MemberDb.getAll();

    const auto it = std::find_if(
        members.cbegin(), members.cend(),
        [&name](const auto &member) { return member.name == name; });

    if (it == members.cend()) {
        return std::nullopt;
    }

    return std::make_optional(*it);
}

void LibService::addMember(const Member &member) {
    if (getMember(member.name).has_value()) {
        throw std::invalid_argument(
            "Читатель с таким именем уже был зарегистрирован");
    }
    m_MemberDb.add(member);
}

void LibService::removeMember(const Member &member) {
    const auto &bookings = m_BookingDb.getAll();

    const auto it = std::find_if(bookings.cbegin(), bookings.cend(),
                                 [&member](const auto &booking) {
                                     return booking.memberId == member.id;
                                 });

    if (it != bookings.cend()) {
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

std::vector<Book> LibService::getMemberBooks(const Member &member) {
    const auto &bookings = m_BookingDb.getAll();

    std::vector<Booking> memberBookings;
    std::copy_if(bookings.cbegin(), bookings.cend(),
                 std::back_inserter(memberBookings),
                 [&member](const auto &booking) {
                     return booking.memberId == member.id;
                 });

    const auto &books = getBooks();

    std::vector<Book> memberBooks;
    for (const auto &booking : memberBookings) {
        const auto bookIt = std::find_if(
            books.cbegin(), books.cend(),
            [&booking](const auto &book) { return booking.bookId == book.id; });

        memberBooks.push_back(*bookIt);
    }

    return memberBooks;
}

void LibService::takeBook(const Member &member, const Book &book) {
    Booking booking;
    booking.memberId = member.id;
    booking.bookId = book.id;

    m_BookingDb.add(std::move(booking));
}

void LibService::returnBook(const Member &member, const Book &book) {
    const auto &bookings = m_BookingDb.getAll();

    const auto bookingIt = std::find_if(
        bookings.cbegin(), bookings.cend(),
        [&member, &book](const auto &booking) {
            return booking.memberId == member.id && booking.bookId == book.id;
        });

    if (bookingIt == bookings.cend()) {
        throw std::invalid_argument("Бронирование не найдено");
    }

    m_BookingDb.remove(*bookingIt);
}