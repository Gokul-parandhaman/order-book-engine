#pragma once

#include <cstdint>
#include <chrono>

namespace obe {

enum class Side { BUY, SELL };
enum class OrderType { LIMIT, MARKET };
enum class OrderStatus { NEW, PARTIALLY_FILLED, FILLED, CANCELLED };

using OrderId = uint64_t;
using Price   = double;
using Qty     = uint64_t;
using Timestamp = std::chrono::steady_clock::time_point;

struct Order {
    OrderId     id;
    Side        side;
    OrderType   type;
    Price       price;
    Qty         quantity;
    Qty         filled_quantity = 0;
    OrderStatus status = OrderStatus::NEW;
    Timestamp   timestamp;

    Qty remaining() const { return quantity - filled_quantity; }
};

struct Trade {
    OrderId     resting_order_id;
    OrderId     incoming_order_id;
    Price       price;
    Qty         quantity;
    Timestamp   timestamp;
};

} 
