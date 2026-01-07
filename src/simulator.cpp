#include <iostream>
#include <string>
#include "exchange/exchange.h"

using namespace std;

int main()
{
    Exchange exchange;

    cout << "Interactive Trading Simulator\n";
    exchange.printHelp();

    string line;
    while (getline(cin, line))
    {
        if (line == "EXIT")
            break;

        exchange.processCommand(line);
    }

    return 0;
}
