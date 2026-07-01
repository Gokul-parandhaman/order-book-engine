
#include <cassert>
#include <iostream>
#include "../src/order_book.hpp"

using namespace obe;

static Order make_order(OrderId id, Side s, Price p, Qty q) {
    return Order{id, s, OrderType::LIMIT, p, q, 0, OrderStatus::NEW,
                 std::chrono::steady_clock::now()};
}

void test_resting_and_best_bid_ask() {
    OrderBook book;
    book.add_limit_order(make_order(1, Side::BUY, 100.0, 10));
    book.add_limit_order(make_order(2, Side::BUY, 101.0, 5));
    book.add_limit_order(make_order(3, Side::SELL, 102.0, 8));

    Price p; Qty q;
    assert(book.best_bid(p, q) && p == 101.0 && q == 5);
    assert(book.best_ask(p, q) && p == 102.0 && q == 8);
    std::cout << "test_resting_and_best_bid_ask passed\n";
}

void test_cancel() {
    OrderBook book;
    book.add_limit_order(make_order(1, Side::BUY, 100.0, 10));
    assert(book.cancel_order(1) == true);
    assert(book.cancel_order(1) == false);
    std::cout << "test_cancel passed\n";
}

int main() {
    test_resting_and_best_bid_ask();
    test_cancel();
    std::cout << "All tests passed.\n";
    return 0;
}
