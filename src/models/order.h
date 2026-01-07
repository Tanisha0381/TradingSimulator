#pragma once
#include <string>

enum Side 
{
     BUY, SELL 
};
enum OrderType 
{ 
    LIMIT, MARKET 
};

struct Order
{
    int id;
    int qty;
    double price;
    std::string symbol;
    Side side;
    OrderType type;
};
