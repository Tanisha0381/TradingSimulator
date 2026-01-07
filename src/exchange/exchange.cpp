#include "exchange.h"
#include <iostream>
#include <sstream>

using namespace std;

Exchange::Exchange() : nextOrderId(1) {}

void Exchange::printHelp() const
{
    std::cout << "\n=== Trading Simulator — Supported Commands ===\n";
    std::cout << "BUY LIMIT <SYMBOL> <PRICE> <QTY>     place a buy limit order\n";
    std::cout << "SELL LIMIT <SYMBOL> <PRICE> <QTY>    place a sell limit order\n";
    std::cout << "BUY MARKET <SYMBOL> <QTY>            place a buy market order\n";
    std::cout << "SELL MARKET <SYMBOL> <QTY>           place a sell market order\n";
    std::cout << "BOOK                                 show current order book\n";
    std::cout << "TRADES                               show executed trades\n";
    std::cout << "HELP                                 show this help text\n";
    std::cout << "EXIT                                 quit the simulator\n";
    std::cout << "===============================================\n\n";
}

void Exchange::processCommand(const string &line)
{
    if (line == "HELP")
    {
        printHelp();
        return;
    }

    if (line == "BOOK")
    {
        orderBook.printBook();
        return;
    }

    if (line == "TRADES")
    {
        orderBook.printTrades();
        return;
    }

    istringstream iss(line);
    string sideStr, typeStr, symbol;
    iss >> sideStr >> typeStr >> symbol;

    Order order;
    order.id = nextOrderId++;
    order.symbol = symbol;

    order.side = (sideStr == "BUY") ? BUY : SELL;
    order.type = (typeStr == "LIMIT") ? LIMIT : MARKET;

    if (order.type == LIMIT)
        iss >> order.price >> order.qty;
    else
        iss >> order.qty;

    orderBook.addOrder(order);

    cout << "Order placed. ID=" << order.id << "\n";
}
