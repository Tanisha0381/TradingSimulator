#include <iostream>
#include <map>
#include <deque>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

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
    string symbol;
    Side side;
    OrderType type;
};

struct Trade 
{
    int buyId;
    int sellId;
    int qty;
    double price;
};

void printHelp() 
{
    cout << "\n=== Trading Simulator Commands ===\n";
    cout << "BUY LIMIT <SYMBOL> <PRICE> <QTY>\n";
    cout << "SELL LIMIT <SYMBOL> <PRICE> <QTY>\n";
    cout << "BUY MARKET <SYMBOL> <QTY>\n";
    cout << "SELL MARKET <SYMBOL> <QTY>\n";
    cout << "CANCEL <ORDER_ID>\n";
    cout << "BOOK\n";
    cout << "TRADES\n";
    cout << "HELP\n";
    cout << "EXIT\n";
    cout << "=================================\n\n";
}

class OrderBook 
{
    map<double, deque<Order>, greater<double>> buyBook;
    map<double, deque<Order>> sellBook;
    vector<Trade> tradeInfo;

public:
    
    void addOrder(Order order) 
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

    void cancelOrder(int id) 
    {
        removeFromBook(buyBook, id);
        removeFromBook(sellBook, id);
    }

    void printBook() 
    {
        cout << "\n--- ORDER BOOK ---\n";
        cout << "ASKS:\n";
        printSide(sellBook);

        cout << "BIDS:\n";
        printSide(buyBook);
    }

    void printTrades() 
    {
        cout << "\n--- TRADES ---\n";
        for (auto &trade : tradeInfo) 
        {
            cout << "BUY#" << trade.buyId
                << " SELL#" << trade.sellId
                << " @ " << trade.price
                << " Qty " << trade.qty << "\n";
        }
    }

private:
    
    void matchBuy(Order &order)
    {
        while (order.qty > 0 && !sellBook.empty()) 
        {
            auto it = sellBook.begin();

            if (order.type == LIMIT && order.price < it->first)
                break;

            executeTrade(order, it->second.front(), it->first);
            cleanup(sellBook, it);
        }

        if (order.qty > 0 && order.type == LIMIT) 
        {
            buyBook[order.price].push_back(order);
        }
    }

    void matchSell(Order &order) 
    {
        while (order.qty > 0 && !buyBook.empty()) {
            auto it = buyBook.begin();

            if (order.type == LIMIT && order.price > it->first)
                break;

            executeTrade(it->second.front(), order, it->first);
            cleanup(buyBook, it);
        }

        if (order.qty > 0 && order.type == LIMIT) 
        {
            sellBook[order.price].push_back(order);
        }
    }

    void executeTrade(Order &buy, Order &sell, double price) 
    {
        int tradeQty = min(buy.qty, sell.qty);

        buy.qty -= tradeQty;
        sell.qty -= tradeQty;

        Trade t;

        t.buyId = buy.id;
        t.sellId = sell.id;
        t.price = price;
        t.qty = tradeQty;

        tradeInfo.push_back(t);
    }

    template <typename Book, typename It>
    void cleanup(Book &book, It it) 
    {
        if (it->second.front().qty == 0)
            it->second.pop_front();

        if (it->second.empty())
            book.erase(it);
    }

    template <typename Book>
    void removeFromBook(Book &book, int id) 
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

    template <typename Book>
    void printSide(Book &book) 
    {
        for (auto &p : book) {
            int total = 0;
            for (auto &o : p.second)
                total += o.qty;

            cout << p.first << " -> " << total << "\n";
        }
    }
};

class Exchange 
{
    OrderBook book;
    int nextId = 1;

public:
    void run() 
    {
        cout << "Interactive Trading Simulator\n";
        printHelp();

        string line;
        while (getline(cin, line)) 
        {
            if (line == "EXIT")
                break;

            handleCommand(line);
        }
    }


private:
    
    void handleCommand(string line)
    {
        istringstream iss(line);
        string cmd;
        iss >> cmd;

        if (cmd == "HELP") {
            printHelp();
            return;
        }

        if (cmd == "BOOK") {
            book.printBook();
            return;
        }

        if (cmd == "TRADES") {
            book.printTrades();
            return;
        }

        if (cmd == "CANCEL") {
            int id;
            iss >> id;
            book.cancelOrder(id);
            cout << "Order cancelled\n";
            return;
        }

        createOrder(cmd, iss);
    }

    void createOrder(string sideStr, istringstream &iss) 
    {
        string typeStr, symbol;
        iss >> typeStr >> symbol;

        Order o;
        o.id = nextId++;
        o.symbol = symbol;

        if (sideStr == "BUY")
            o.side = BUY;
        else
            o.side = SELL;

        if (typeStr == "LIMIT")
            o.type = LIMIT;
        else
            o.type = MARKET;

        if (o.type == LIMIT)
            iss >> o.price >> o.qty;
        else
            iss >> o.qty;

        book.addOrder(o);
        cout << "Order placed ID=" << o.id << "\n";
    }
};

int main() 
{
    Exchange ex;
    ex.run();
    return 0;
}
