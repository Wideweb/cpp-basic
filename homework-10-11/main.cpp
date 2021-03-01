#include "Stack.hpp"
#include <iostream>

// simple template type test
void test1() {
    Stack<int> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);

    assert(stack.empty() == false && "Test 1 failed.");
    assert(stack.pop() == 3 && "Test 1 failed.");
    assert(stack.pop() == 2 && "Test 1 failed.");
    assert(stack.pop() == 1 && "Test 1 failed.");
    assert(stack.empty() == true && "Test 1 failed.");

    std::cout << "Test 1 Passed" << std::endl;
}

// struct template type test
void test2() {
    struct Point {
        float x;
        float y;

        Point() : x(0.0f), y(0.0f) {}
        Point(float x, float y) : x(x), y(y) {}
    };

    Stack<Point> stack;
    stack.emplace_back(1.0f, 2.0f);
    stack.emplace_back(5.0f, 6.0f);

    Point p;

    p = stack.pop();
    assert((p.x == 5.0 && p.y == 6.0) && "Test 1 failed.");

    p = stack.pop();
    assert((p.x == 1.0 && p.y == 2.0) && "Test 2 failed.");

    std::cout << "Test 2 Passed" << std::endl;
}

// pop on empty stack test
void test3() {
    Stack<int> stack;
    stack.push(1);
    stack.pop();

    try {
        stack.pop();
        assert(false && "Test 3 failed.");
    } catch (...) {
        std::cout << "Test 3 Passed" << std::endl;
    }
}

// copy stack test
void test4() {
    Stack<int> stack1;
    stack1.push(1);
    stack1.push(2);
    stack1.push(3);

    Stack<int> stack2;
    stack2.push(4);

    stack2 = stack1;

    assert(stack1.pop() == 3 && "Test 4 failed.");
    assert(stack1.pop() == 2 && "Test 4 failed.");
    assert(stack1.pop() == 1 && "Test 4 failed.");

    assert(stack2.pop() == 3 && "Test 4 failed.");
    assert(stack2.pop() == 2 && "Test 4 failed.");
    assert(stack2.pop() == 1 && "Test 4 failed.");

    std::cout << "Test 4 Passed" << std::endl;
}

// copy constructor stack test
void test5() {
    Stack<int> stack1;
    stack1.push(1);
    stack1.push(2);
    stack1.push(3);

    Stack<int> stack2 = stack1;

    assert(stack1.pop() == 3 && "Test 4 failed.");
    assert(stack1.pop() == 2 && "Test 4 failed.");
    assert(stack1.pop() == 1 && "Test 4 failed.");

    assert(stack2.pop() == 3 && "Test 4 failed.");
    assert(stack2.pop() == 2 && "Test 4 failed.");
    assert(stack2.pop() == 1 && "Test 4 failed.");

    std::cout << "Test 5 Passed" << std::endl;
}

// move stack test
void test6() {
    Stack<int> stack1;
    stack1.push(1);
    stack1.push(2);
    stack1.push(3);

    Stack<int> stack2;
    stack2.push(4);

    stack2 = std::move(stack1);

    assert(stack1.empty() == true && "Test 4 failed.");

    assert(stack2.pop() == 3 && "Test 4 failed.");
    assert(stack2.pop() == 2 && "Test 4 failed.");
    assert(stack2.pop() == 1 && "Test 4 failed.");

    std::cout << "Test 6 Passed" << std::endl;
}

// move constructor stack test
void test7() {
    Stack<int> stack1;
    stack1.push(1);
    stack1.push(2);
    stack1.push(3);

    Stack<int> stack2 = std::move(stack1);

    assert(stack1.empty() == true && "Test 4 failed.");

    assert(stack2.pop() == 3 && "Test 4 failed.");
    assert(stack2.pop() == 2 && "Test 4 failed.");
    assert(stack2.pop() == 1 && "Test 4 failed.");

    std::cout << "Test 7 Passed" << std::endl;
}

int main() {
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();

    std::cout << "All Tests Passed!" << std::endl;
}
