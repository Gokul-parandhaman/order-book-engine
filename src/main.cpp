#include <iostream>
#include "order_book.hpp"

using namespace obe;

int main() {
    OrderBook book;

    Order o1{1, Side::BUY, OrderType::LIMIT, 100.5, 10, 0, OrderStatus::NEW,
             std::chrono::steady_clock::now()};
    Order o2{2, Side::SELL, OrderType::LIMIT, 101.0, 5, 0, OrderStatus::NEW,
             std::chrono::steady_clock::now()};

    book.add_limit_order(o1);
    book.add_limit_order(o2);

    Price bid_p, ask_p;
    Qty bid_q, ask_q;
    if (book.best_bid(bid_p, bid_q))
        std::cout << "Best bid: " << bid_p << " x " << bid_q << "\n";
    if (book.best_ask(ask_p, ask_q))
        std::cout << "Best ask: " << ask_p << " x " << ask_q << "\n";

    std::cout << "(Matching engine not yet implemented — orders just rest for now.)\n";
    return 0;
}
