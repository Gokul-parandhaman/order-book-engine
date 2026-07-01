# Order Book Matching Engine + Backtester (C++)

**Status: In Progress**

A limit order book matching engine implementing price-time priority, built
to explore low-latency systems design in the context of exchange
infrastructure. A backtesting layer on top will let simple trading
strategies run against historical/synthetic market data.

## Why this project

Exchanges match buy/sell orders using data structures and algorithms that
have to be both *correct* (no lost or double-filled orders) and *fast*
(microsecond-scale latency at scale). This project is my attempt to build
one from scratch and understand those tradeoffs directly, rather than just
reading about them.

## Current state

- [x] Core `Order` / `Trade` types
- [x] Order book skeleton with price-sorted bid/ask levels (`std::map`)
- [x] Resting orders + cancel by order id
- [x] Best bid / best ask queries
- [ ] **Matching engine core (in progress)** — crossing logic, partial
      fills, trade generation
- [ ] Market order sweep logic
- [ ] Performance benchmarks (throughput / latency)
- [ ] Backtester harness + simple strategy (market making / mean reversion)
- [ ] Historical data ingestion
- [ ] PnL / Sharpe / drawdown reporting

## Design notes (so far)

- Bids and asks are stored in separate `std::map<Price, deque<Order>>`,
  giving O(log n) access to price levels and O(1) FIFO time-priority within
  a level.
- An `unordered_map<OrderId, ...>` index supports fast cancellation.
- `Price` is currently a `double` — planned to move to a fixed-point/tick
  based integer representation to avoid floating point comparison issues,
  which matter a lot once matching logic is doing price crossing checks.

## Build

```bash
mkdir build && cd build
cmake ..
make
./obe_main
./obe_tests
```

## Roadmap

1. Implement `OrderBook::match()` — the actual crossing logic
2. Wire matching into `add_limit_order` / `add_market_order`
3. Expand test suite around partial fills, price-time priority, edge cases
4. Add benchmarking harness, report orders/sec and per-order latency
5. Build backtester on top, add a first strategy
6. Pull in historical exchange data for realistic backtests
