#include "OrderService.h"
#include "rapdix/util/HttpClient.h"
#include "rapdix/constants/RapidxAPIConstants.h"
#include <iostream>

PlaceOrderResponse OrderService::placeOrder(const PlaceOrderRequest& request) {
    try {
        std::cout << "Sending request: " << request.toJsonString() << std::endl;
        return HttpClient::getInstance().doPost<PlaceOrderResponse>(
            RapidxAPIConstants::ORDER,
            request.toJsonString()
        );
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        throw; 
    }
}

ReplaceOrderResponse OrderService::replaceOrder(const ReplaceOrderRequest& request) {
        return HttpClient::getInstance().doPut<ReplaceOrderResponse>(
            RapidxAPIConstants::ORDER,
            request.toJsonString()
        );
}

CancelOrderResponse OrderService::cancelOrder(const CancelOrderRequest& request) {
    return HttpClient::getInstance().doDelete<CancelOrderResponse>(
        RapidxAPIConstants::ORDER,
        request.toJsonString()
    );
}

QueryOrderResponse OrderService::queryOrder(const QueryOrderRequest& request) {
    return HttpClient::getInstance().doGet<QueryOrderResponse>(
        RapidxAPIConstants::ORDER,
        request.toJsonString()
    );
}

QueryOpenOrdersResponse OrderService::queryOpenOrders(const QueryOpenOrdersRequest& request) {
    return HttpClient::getInstance().doGet<QueryOpenOrdersResponse>(
        RapidxAPIConstants::ORDERS,
        request.toJsonString()
    );
}

QueryHistoryOrdersResponse OrderService::queryHistoryOrders(const QueryHistoryOrdersRequest& request) {
    return HttpClient::getInstance().doGet<QueryHistoryOrdersResponse>(
        RapidxAPIConstants::ORDER_HISTORY,
        request.toJsonString()
    );
}

QueryHistoryOrdersResponse OrderService::queryHistoryOrdersArchive(const QueryHistoryOrdersArchiveRequest& request) {
    return HttpClient::getInstance().doGet<QueryHistoryOrdersResponse>(
        RapidxAPIConstants::ORDER_HISTORY_ARCHIVE,
        request.toJsonString()
    );
}

CancelAllOrdersResponse OrderService::cancelAllOrders(const CancelAllOrdersRequest& request) {
    return HttpClient::getInstance().doDelete<CancelAllOrdersResponse>(
        RapidxAPIConstants::ORDER_CANCEL_ALL,
        request.toJsonString()
    );
}

