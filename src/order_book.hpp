#pragma once

#include <map>
#include <deque>
#include <unordered_map>
#include <vector>
#include "order.hpp"

namespace obe {


class OrderBook {
public:
    OrderBook() = default;

    std::vector<Trade> add_limit_order(Order order);

    std::vector<Trade> add_market_order(Order order);

    bool cancel_order(OrderId id);

    bool best_bid(Price& out_price, Qty& out_qty) const;
    bool best_ask(Price& out_price, Qty& out_qty) const;

    size_t bid_levels() const { return bids_.size(); }
    size_t ask_levels() const { return asks_.size(); }

private:

    std::map<Price, std::deque<Order>, std::greater<Price>> bids_;
    std::map<Price, std::deque<Order>, std::less<Price>>    asks_;


    std::unordered_map<OrderId, std::pair<Side, Price>> order_index_;

    std::vector<Trade> match(Order& incoming);
};

}
