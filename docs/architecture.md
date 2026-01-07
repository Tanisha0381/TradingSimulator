# Architecture Overview

## Introduction
This trading simulator models the core behavior of a simplified electronic exchange.
The implementation focuses on clarity and correctness rather than performance or scale,
making it suitable for understanding fundamental trading system concepts.

The architecture intentionally avoids unnecessary abstraction so that system behavior
can be traced directly through the code.

---

## Overall Design
The simulator is implemented as a single-process, single-threaded C++ application.
All logic resides in a single translation unit (`simulator.cpp`) to keep control flow
explicit and easy to reason about.

---

## Core Components

### Exchange
The `Exchange` class is responsible for:
- running the command-line interaction loop,
- parsing user commands,
- creating orders,
- assigning unique order identifiers,
- and routing orders to the order book.

---

### OrderBook
The `OrderBook` class maintains the internal market state and is responsible for:
- storing buy and sell orders using price-ordered containers,
- applying matching logic between incoming and resting orders,
- recording executed trades,
- handling order cancellation.

Buy orders are stored in descending price order, while sell orders are stored in
ascending price order to support efficient best-price matching.

---

### Order and Trade Models
Orders encapsulate:
- order ID
- symbol
- side (BUY / SELL)
- order type (LIMIT / MARKET)
- quantity
- price (for limit orders)

Trades record:
- buy order ID
- sell order ID
- execution price
- executed quantity

---

## Execution Flow
1. User enters a command via standard input
2. The command is parsed by the exchange
3. An order object is created
4. The order is passed to the order book
5. Matching logic is applied sequentially
6. Trades are generated if matches occur
7. Order book and trade history are updated

---

## Design Decisions
- Single-threaded execution ensures deterministic behavior
- Sequential processing simplifies correctness and debugging
- Minimal abstraction keeps the system easy to understand

---

## Extensibility
The current design can be extended to support:
- per-symbol order books,
- modular matching engines,
- strategy simulation layers,
- risk checks,
- automated testing.

---

## Known Limitations
- No persistence layer
- No real-time market data
- No concurrency
- No automated test suite (planned)
