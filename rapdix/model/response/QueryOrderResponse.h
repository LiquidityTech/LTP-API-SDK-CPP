#pragma once
#include <string>
#include <ostream>
#include <nlohmann/json.hpp>

class QueryOrderResponse {
public:
    QueryOrderResponse() = default;
    
    // Getters
    int getCode() const { return code; }
    const std::string& getMessage() const { return message; }
    
    // 输出运算符重载
    friend std::ostream& operator<<(std::ostream& os, const QueryOrderResponse& response) {
        os << "QueryOrderResponse{code=" << response.code 
           << ", message='" << response.message << "'";
        if (response.data.orderId.empty()) {
            os << "}";
        } else {
            os << ", orderId='" << response.data.orderId 
               << "', clientOrderId='" << response.data.clientOrderId
               << "', orderState='" << response.data.orderState
               << "', sym='" << response.data.sym
               << "', side='" << response.data.side
               << "', orderType='" << response.data.orderType
               << "', limitPrice='" << response.data.limitPrice
               << "', orderQty='" << response.data.orderQty
               << "', executedQty='" << response.data.executedQty
               << "', executedAvgPrice='" << response.data.executedAvgPrice 
               << "', reduceOnly=" << (response.data.reduceOnly ? "true" : "false") << "'}";
        }
        return os;
    }
    
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(QueryOrderResponse, code, message, data)
    
private:
    int code;
    std::string message;
    struct Data {
        std::string portfolioId;
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

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(Data, 
            portfolioId, orderId, clientOrderId, orderState, sym, side,
            exchangeOrderType, orderType, exchangeType, businessType,
            orderQty, quoteOrderQty, limitPrice, timeInForce, reason,
            executedQty, executedAvgPrice, executedAmount, reduceOnly,
            lastExecutedQty, lastExecutedPrice, lastExecutedAmount,
            fee, feeCoin, rebate, rebateCoin, borrowAmount, borrowAsset,
            positionSide, tpTriggerPrice, tpTriggerType, tpPrice,
            slTriggerPrice, slTriggerType, slPrice, createAt, updateAt)
    } data;
}; 