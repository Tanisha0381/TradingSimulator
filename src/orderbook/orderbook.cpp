#include "orderbook.h"

using namespace std;

void OrderBook::addOrder(Order order)
{
    if (order.side == BUY)
    {
        matchBuy(order);
    }
    else
    {
        matchSell(order);
    }
}

// Remove an order id from both sides (if present).
void OrderBook::cancelOrder(int id)
{
    removeFromBook(buyBook, id);
    removeFromBook(sellBook, id);
}

void OrderBook::printBook()
{
    cout << "\n--- ORDER BOOK ---\n";
    cout << "ASKS:\n";
    printSide(sellBook);
    cout << "BIDS:\n";
    printSide(buyBook);
}

void OrderBook::printTrades()
{
    cout << "\n--- TRADES ---\n";
    for (auto &t : trades)
    {
        cout << "BUY#" << t.buyId
             << " SELL#" << t.sellId
             << " @ " << t.price
             << " Qty " << t.qty << "\n";
    }
}

void OrderBook::matchBuy(Order &order)
{
    while (order.qty > 0 && !sellBook.empty())
    {
        auto it = sellBook.begin(); // best (lowest) ask

        if (order.type == LIMIT && order.price < it->first)
        {
            break; // best ask is above buy limit
        }

        executeTrade(order, it->second.front(), it->first);

        if (it->second.front().qty == 0)
            it->second.pop_front();
        if (it->second.empty())
            sellBook.erase(it);
    }

    if (order.qty > 0 && order.type == LIMIT)
        buyBook[order.price].push_back(order);
}

void OrderBook::matchSell(Order &order)
{
    while (order.qty > 0 && !buyBook.empty())
    {
        auto it = buyBook.begin(); // best (highest) bid

        if (order.type == LIMIT && order.price > it->first)
        {
            break; // best bid is below sell limit
        }

        executeTrade(it->second.front(), order, it->first);

        if (it->second.front().qty == 0)
            it->second.pop_front();
        if (it->second.empty())
            buyBook.erase(it);
    }

    if (order.qty > 0 && order.type == LIMIT)
        sellBook[order.price].push_back(order);
}

void OrderBook::executeTrade(Order &buy, Order &sell, double price)
{
    int tradeQty = min(buy.qty, sell.qty);
    buy.qty -= tradeQty;
    sell.qty -= tradeQty;

    trades.push_back({buy.id, sell.id, tradeQty, price});

    // friendly single-line notification (keeps output easy to read)
    std::cout << "Executed trade: BUY#" << buy.id
              << " SELL#" << sell.id
              << " Qty " << tradeQty
              << " @ " << price << "\n";
}

// Remove an order with matching id from a book.
template<typename Book>
void OrderBook::removeFromBook(Book &book, int id)
{
    for (auto it = book.begin(); it != book.end(); ++it)
    {
        auto &q = it->second;
        q.erase(remove_if(q.begin(), q.end(),
                          [&](Order &o) { return o.id == id; }),
                q.end());
        if (q.empty())
        {
            book.erase(it);
            return;
        }
    }
}

template<typename Book>
void OrderBook::printSide(Book &book)
{
    for (const auto &p : book)
    {
        int total = 0;
        for (const auto &o : p.second)
            total += o.qty;
        cout << p.first << " -> " << total << "\n";
    }
}
