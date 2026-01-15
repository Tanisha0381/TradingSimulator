cmake_minimum_required(VERSION 3.10)

project(TradingSimulator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(src)

# Source files
set(SRC_FILES
    src/orderbook/orderbook.cpp
    src/exchange/exchange.cpp
    src/simulator/simulator.cpp
)

# Main executable
add_executable(trading_simulator ${SRC_FILES})

# Test executable
add_executable(orderbook_tests
    tests/test_orderbook.cpp
    src/orderbook/orderbook.cpp
)

# Enable testing
enable_testing()

add_test(NAME OrderBookTests COMMAND orderbook_tests)
