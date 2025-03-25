#pragma once
#include <string>
#include <vector>
#include <ostream>
#include <nlohmann/json.hpp>

class QueryOpenOrdersResponse {
public:
    QueryOpenOrdersResponse() = default;
    
    // Getters
    int getCode() const { return code; }
    const std::string& getMessage() const { return message; }
    
    // 输出运算符重载
    friend std::ostream& operator<<(std::ostream& os, const QueryOpenOrdersResponse& response) {
        os << "QueryOpenOrdersResponse{code=" << response.code 
           << ", message='" << response.message << "'";
        if (response.data.list.empty()) {
            os << ", page=" << response.data.page
               << ", pageSize=" << response.data.pageSize
               << ", totalSize=" << response.data.totalSize
               << ", orders=[]}";
        } else {
            os << ", page=" << response.data.page
               << ", pageSize=" << response.data.pageSize
               << ", totalSize=" << response.data.totalSize
               << ", orders=[";
            for (const auto& order : response.data.list) {
                os << "\n  {orderId='" << order.orderId 
                   << "', sym='" << order.sym
                   << "', side='" << order.side
                   << "', orderType='" << order.orderType
                   << "', limitPrice='" << order.limitPrice
                   << "', orderQty='" << order.orderQty
                   << "', executedQty='" << order.executedQty
                   << "', orderState='" << order.orderState
                   << "', reduceOnly=" << (order.reduceOnly ? "true" : "false") << "}";
            }
            os << "\n]}";
        }
        return os;
    }
    
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(QueryOpenOrdersResponse, code, message, data)
    
private:
    int code;
    std::string message;
    struct OrderData {
        std::string portfolioId;
        std::string portfolioName;
        std::string orderId;
        std::string clientOrderId;
        std::string orderState;
        std::string sym;
        std::string side;
        std::string exchangeOrderType;
        std::string orderType;
        std::string exchangeType;
        std::string businessType;
        std::string orderQty;
        std::string quoteOrderQty;
        std::string limitPrice;
        std::string timeInForce;
        std::string reason;
        std::string executedQty;
        std::string executedAvgPrice;
        std::string executedAmount;
        bool reduceOnly;
        std::string lastExecutedQty;
        std::string lastExecutedPrice;
        std::string lastExecutedAmount;
        std::string fee;
        std::string feeCoin;
        std::string rebate;
        std::string rebateCoin;
        int leverage;
        std::string borrowAmount;
        std::string borrowAsset;
        std::string positionSide;
        std::string tpTriggerPrice;
        std::string tpTriggerType;
        std::string tpPrice;
        std::string slTriggerPrice;
        std::string slTriggerType;
        std::string slPrice;
        std::string createAt;
        std::string updateAt;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(OrderData, 
            portfolioId, portfolioName, orderId, clientOrderId, orderState, sym, side,
            exchangeOrderType, orderType, exchangeType, businessType,
            orderQty, quoteOrderQty, limitPrice, timeInForce, reason,
            executedQty, executedAvgPrice, executedAmount, reduceOnly,
            lastExecutedQty, lastExecutedPrice, lastExecutedAmount,
            fee, feeCoin, rebate, rebateCoin, leverage, borrowAmount, borrowAsset,
            positionSide, tpTriggerPrice, tpTriggerType, tpPrice,
            slTriggerPrice, slTriggerType, slPrice, createAt, updateAt)
    };

    struct PageData {
        int page;
        int pageSize;
        int pageNum;
        int totalSize;
        std::vector<OrderData> list;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(PageData, 
            page, pageSize, pageNum, totalSize, list)
    } data;
}; 