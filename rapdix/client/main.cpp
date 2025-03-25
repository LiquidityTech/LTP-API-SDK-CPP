#include "../service/order/OrderService.h"
#include <iostream>

int main() {
    try {
        auto request = PlaceOrderRequest::builder()
            .sym("BINANCE_PERP_BTC_USDT")
            .side("BUY")
            .orderType("LIMIT")
            .orderQty("0.001")
            .limitPrice("40000")
            .timeInForce("GTC")
            .clientOrderId("test_" + std::to_string(std::time(nullptr)))
            .build();
        
        PlaceOrderResponse response = OrderService::placeOrder(request);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
} 