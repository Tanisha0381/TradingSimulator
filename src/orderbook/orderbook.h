#pragma once

#include <map>
#include <deque>
#include <vector>
#include <iostream>
#include <algorithm>

#include "../models/order.h"
#include "../models/trade.h"

class OrderBook
{
public:
    void addOrder(Order order);
    void cancelOrder(int id);
    void printBook();
    void printTrades();

private:
    std::map<double, std::deque<Order>, std::greater<double>> buyBook;
    std::map<double, std::deque<Order>> sellBook;
    std::vector<Trade> trades;

    void matchBuy(Order &order);
    void matchSell(Order &order);
    void executeTrade(Order &buy, Order &sell, double price);

    template<typename Book>
    void removeFromBook(Book &book, int id);

    template<typename Book>
    void printSide(Book &book);
};
