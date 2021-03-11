#pragma once

#include <memory>
#include <utility>

static int counter = 0;

template <typename T> class Stack {
  private:
    struct StackItem {
        T data;
        std::shared_ptr<StackItem> next;

        StackItem() { counter++; }

        ~StackItem() { counter--; }
    };

    std::shared_ptr<StackItem> m_Top;

  public:
    Stack() : m_Top(nullptr) {}

    Stack(const Stack &other) : m_Top(nullptr) { *this = other; };

    Stack(Stack &&other) : m_Top(other.m_Top) { other.m_Top = nullptr; }

    ~Stack() { clear(); }

    T pop() {
        if (empty()) {
            throw "stack is empty";
        }

        T data = std::move(m_Top->data);

        auto item = m_Top;
        m_Top = m_Top->next;

        return data;
    }

    template <typename... Args> void emplace_back(Args &&...args) {
        auto item = std::make_shared<StackItem>();
        item->data = T(std::forward<Args>(args)...);
        item->next = m_Top;
        m_Top = item;
    }

    void push(T data) {
        auto item = std::make_shared<StackItem>();
        item->data = std::move(data);
        item->next = m_Top;
        m_Top = item;
    }

    bool empty() const { return m_Top == nullptr; }

    void clear() {
        while (!empty()) {
            pop();
        }
    }

    Stack &operator=(const Stack &other) {
        if (this == &other) {
            return *this;
        }

        clear();
        Stack tmp;
        auto current = other.m_Top;
        while (current != nullptr) {
            T data = current->data;
            tmp.push(data);
            current = current->next;
        }

        while (!tmp.empty()) {
            push(tmp.pop());
        }

        return *this;
    }

    Stack &operator=(Stack &&other) {
        if (this == &other) {
            return *this;
        }

        clear();
        m_Top = other.m_Top;
        other.m_Top = nullptr;

        return *this;
    }
};