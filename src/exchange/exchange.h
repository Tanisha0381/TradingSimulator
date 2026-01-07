#pragma once
#include <string>
#include "../orderbook/orderbook.h"

class Exchange
{
public:
    Exchange();
    void processCommand(const std::string &line);
    void printHelp() const;

private:
    OrderBook orderBook;
    int nextOrderId;

    void handleOrder(const std::string &side,
                     const std::string &type,
                     const std::string &symbol,
                     double price,
                     int qty);
};
