#include "order_book.hpp"

namespace obe {

bool OrderBook::best_bid(Price& out_price, Qty& out_qty) const {
    if (bids_.empty()) return false;
    const auto& [price, queue] = *bids_.begin();
    out_price = price;
    out_qty = 0;
    for (const auto& o : queue) out_qty += o.remaining();
    return true;
}

bool OrderBook::best_ask(Price& out_price, Qty& out_qty) const {
    if (asks_.empty()) return false;
    const auto& [price, queue] = *asks_.begin();
    out_price = price;
    out_qty = 0;
    for (const auto& o : queue) out_qty += o.remaining();
    return true;
}

bool OrderBook::cancel_order(OrderId id) {
    auto it = order_index_.find(id);
    if (it == order_index_.end()) return false;

    auto [side, price] = it->second;
    if (side == Side::BUY) {
        auto level_it = bids_.find(price);
        if (level_it == bids_.end()) return false;
        auto& dq = level_it->second;
        for (auto oit = dq.begin(); oit != dq.end(); ++oit) {
            if (oit->id == id) {
                dq.erase(oit);
                if (dq.empty()) bids_.erase(level_it);
                order_index_.erase(it);
                return true;
            }
        }
    } else {
        auto level_it = asks_.find(price);
        if (level_it == asks_.end()) return false;
        auto& dq = level_it->second;
        for (auto oit = dq.begin(); oit != dq.end(); ++oit) {
            if (oit->id == id) {
                dq.erase(oit);
                if (dq.empty()) asks_.erase(level_it);
                order_index_.erase(it);
                return true;
            }
        }
    }
    return false;
}


std::vector<Trade> OrderBook::match(Order& /*incoming*/) {
    // TODO: walk the opposite side book while price crosses, generate
    // Trade records, decrement remaining quantity on both sides, remove
    // fully-filled resting orders, stop when incoming is filled or book
    // is exhausted / price no longer crosses.
    return {};
}

std::vector<Trade> OrderBook::add_limit_order(Order order) {
    // Currently just rests the order without attempting to match.
    // TODO: call match() first, then rest any remaining quantity.
    if (order.side == Side::BUY) {
        bids_[order.price].push_back(order);
    } else {
        asks_[order.price].push_back(order);
    }
    order_index_[order.id] = {order.side, order.price};
    return {};
}

std::vector<Trade> OrderBook::add_market_order(Order /*order*/) {
    // TODO: implement — should never rest, only match against best
    // available liquidity until filled or book exhausted.
    return {};
}

}
