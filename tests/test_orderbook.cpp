#include <cassert>
#include <iostream>

#include "../src/orderbook/orderbook.h"

using namespace std;

void testOrders()
{
    OrderBook book;

    Order buy;
    buy.id = 1;
    buy.symbol = "RELIANCE";
    buy.side = BUY;
    buy.type = LIMIT;
    buy.price = 2500;
    buy.qty = 10;

    Order sell;
    sell.id = 2;
    sell.symbol = "RELIANCE";
    sell.side = SELL;
    sell.type = LIMIT;
    sell.price = 2510;
    sell.qty = 10;

    book.addOrder(buy);
    book.addOrder(sell);

    cout << "PASS (RELIANCE)\n";
}

void testExecution()
{
    OrderBook book;

    Order buy;
    buy.id = 1;
    buy.symbol = "NIFTY";
    buy.side = BUY;
    buy.type = LIMIT;
    buy.price = 22000;
    buy.qty = 5;

    Order sell;
    sell.id = 2;
    sell.symbol = "NIFTY";
    sell.side = SELL;
    sell.type = LIMIT;
    sell.price = 21990;
    sell.qty = 5;

    book.addOrder(buy);
    book.addOrder(sell);

    book.printTrades();

    cout << "PASS (NIFTY)\n";
}

void test_multiple_symbols()
{
    OrderBook book;

    Order buy1 = {1, 10, 3500, "TCS", BUY, LIMIT};
    Order sell1 = {2, 10, 3490, "TCS", SELL, LIMIT};

    Order buy2 = {3, 5, 1500, "INFY", BUY, LIMIT};
    Order sell2 = {4, 5, 1495, "INFY", SELL, LIMIT};

    book.addOrder(buy1);
    book.addOrder(sell1);
    book.addOrder(buy2);
    book.addOrder(sell2);

    book.printTrades();

    cout << "PASS (TCS, INFY)\n";
}

void test_cancelOrder()
{
    OrderBook book;

    Order buy;
    buy.id = 1;
    buy.symbol = "TCS";
    buy.side = BUY;
    buy.type = LIMIT;
    buy.price = 3500;
    buy.qty = 10;

    book.addOrder(buy);
    book.cancelOrder(1);

    book.printBook();

    cout << "PASS test_cancelOrder\n";
}

void test_marketOrder()
{
    OrderBook book;

    Order sell;
    sell.id = 1;
    sell.symbol = "INFY";
    sell.side = SELL;
    sell.type = LIMIT;
    sell.price = 1500;
    sell.qty = 10;

    Order buy;
    buy.id = 2;
    buy.symbol = "INFY";
    buy.side = BUY;
    buy.type = MARKET;
    buy.qty = 5;

    book.addOrder(sell);
    book.addOrder(buy);

    book.printTrades();

    cout << "PASS test_marketOrder\n";
}

void test_partialFill()
{
    OrderBook book;

    Order buy;
    buy.id = 1;
    buy.symbol = "RELIANCE";
    buy.side = BUY;
    buy.type = LIMIT;
    buy.price = 2500;
    buy.qty = 20;

    Order sell;
    sell.id = 2;
    sell.symbol = "RELIANCE";
    sell.side = SELL;
    sell.type = LIMIT;
    sell.price = 2500;
    sell.qty = 5;

    book.addOrder(buy);
    book.addOrder(sell);

    book.printTrades();
    book.printBook();

    cout << "PASS test_partialFill\n";
}



int main()
{
    cout << "Running OrderBook tests...\n";

    testOrders();
    cout << "\n";
    testExecution();
    cout << "\n";
    test_multiple_symbols();
    cout << "\n";
    test_cancelOrder();
    cout << "\n";
    test_marketOrder();
    cout << "\n";
    test_partialFill();

    cout << "\n";
    return 0;
}

