#pragma once
#include "rapdix/model/request/PlaceOrderRequest.h"
#include "rapdix/model/response/PlaceOrderResponse.h"
#include "rapdix/model/request/ReplaceOrderRequest.h"
#include "rapdix/model/response/ReplaceOrderResponse.h"
#include "rapdix/model/request/CancelOrderRequest.h"
#include "rapdix/model/response/CancelOrderResponse.h"
#include "rapdix/model/request/QueryOrderRequest.h"
#include "rapdix/model/response/QueryOrderResponse.h"
#include "rapdix/model/request/QueryOpenOrdersRequest.h"
#include "rapdix/model/response/QueryOpenOrdersResponse.h"
#include "rapdix/model/request/QueryHistoryOrdersRequest.h"
#include "rapdix/model/response/QueryHistoryOrdersResponse.h"
#include "rapdix/model/request/QueryHistoryOrdersArchiveRequest.h"
#include "rapdix/model/request/CancelAllOrdersRequest.h"
#include "rapdix/model/response/CancelAllOrdersResponse.h"

class OrderService {
public:
    static PlaceOrderResponse placeOrder(const PlaceOrderRequest& request);
    static ReplaceOrderResponse replaceOrder(const ReplaceOrderRequest& request);
    static CancelOrderResponse cancelOrder(const CancelOrderRequest& request);
    static QueryOrderResponse queryOrder(const QueryOrderRequest& request);
    static QueryOpenOrdersResponse queryOpenOrders(const QueryOpenOrdersRequest& request);
    static QueryHistoryOrdersResponse queryHistoryOrders(const QueryHistoryOrdersRequest& request);
    static QueryHistoryOrdersResponse queryHistoryOrdersArchive(const QueryHistoryOrdersArchiveRequest& request);
    static CancelAllOrdersResponse cancelAllOrders(const CancelAllOrdersRequest& request);
    // 其他方法...
}; 