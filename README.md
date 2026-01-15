# Trading Simulator (C++)

An interactive command-line trading simulator written in C++ that demonstrates
the core mechanics of a simplified electronic exchange.

The project focuses on clarity, correctness, and deterministic behavior rather
than production-scale performance.

---

## Features

- Place BUY and SELL orders
- Support for LIMIT and MARKET orders
- Price-time priority order matching
- Maintain an in-memory order book
- Cancel open orders
- View current order book state
- View executed trades


---

## Architecture Overview

The simulator is implemented as a single-process, single-threaded application.

Key components:
- **Exchange**: handles command parsing, order creation, and routing
- **OrderBook**: maintains buy/sell books, performs order matching, and records trades

Matching is deterministic and sequential, making system behavior easy to reason about.

For detailed design decisions and execution flow, see:
➡️ [`docs/architecture.md`](docs/architecture.md)

---

## Supported Commands

BUY LIMIT <SYMBOL> <PRICE> <QTY>
SELL LIMIT <SYMBOL> <PRICE> <QTY>
BUY MARKET <SYMBOL> <QTY>
SELL MARKET <SYMBOL> <QTY>
CANCEL <ORDER_ID>
BOOK
TRADES
HELP
EXIT


---

## Example Session

BUY LIMIT RELIANCE 1560 5
SELL LIMIT RELIANCE 1560 2
BOOK
TRADES


---

## Build & Run

### Compile
```bash
g++ src/simulator.cpp -o simulator

./simulator

### Run with Docker

```bash
docker build -t trading-simulator .
docker run -it trading-simulator

> Docker support is provided for reproducible builds. Local execution depends on Docker Desktop availability.

