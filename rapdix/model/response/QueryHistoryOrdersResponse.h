#pragma once
#include <string>
#include <vector>
#include <ostream>
#include <optional>
#include <nlohmann/json.hpp>

// 为 std::optional 添加 JSON 序列化支持
namespace nlohmann {
    template<typename T>
    struct adl_serializer<std::optional<T>> {
        static void to_json(json& j, const std::optional<T>& opt) {
            if (opt.has_value()) {
                j = opt.value();
            } else {
                j = nullptr;
            }
        }

        static void from_json(const json& j, std::optional<T>& opt) {
            if (j.is_null()) {
                opt = std::nullopt;
            } else {
                opt = j.get<T>();
            }
        }
    };
}

class QueryHistoryOrdersResponse {
public:
    QueryHistoryOrdersResponse() = default;
    
    // Getters
    int getCode() const { return code; }
    const std::string& getMessage() const { return message; }
    
    // 输出运算符重载
    friend std::ostream& operator<<(std::ostream& os, const QueryHistoryOrdersResponse& response) {
        os << "QueryHistoryOrdersResponse{code=" << response.code 
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
                   << "', limitPrice='" << (order.limitPrice ? *order.limitPrice : "null")
                   << "', orderQty='" << order.orderQty
                   << "', executedQty='" << order.executedQty
                   << "', orderState='" << order.orderState
                   << "', reduceOnly=" << (order.reduceOnly ? "true" : "false") << "}";
            }
            os << "\n]}";
        }
        return os;
    }
    
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(QueryHistoryOrdersResponse, code, message, data)
    
private:
    int code;
    std::string message;
    struct OrderData {
        std::string portfolioId;
        std::optional<std::string> portfolioName;  // 可能为 null
        std::string orderId;
        std::optional<std::string> clientOrderId;  // 可能为 null
        std::string orderState;
        std::string sym;
        std::string side;
        std::string exchangeOrderType;
        std::string orderType;
        std::string exchangeType;
        std::string businessType;
        std::string orderQty;
        std::optional<std::string> quoteOrderQty;  // 可能为 null
        std::optional<std::string> limitPrice;     // 可能为 null
        std::optional<std::string> timeInForce;    // 可能为 null
        std::optional<std::string> reason;         // 可能为 null
        std::string executedQty;
        std::optional<std::string> executedAvgPrice;  // 可能为 null
        std::string executedAmount;
        bool reduceOnly;
        std::optional<std::string> lastExecutedQty;    // 可能为 null
        std::optional<std::string> lastExecutedPrice;  // 可能为 null
        std::optional<std::string> lastExecutedAmount; // 可能为 null
        std::optional<std::string> fee;      // 可能为 null
        std::optional<std::string> feeCoin;  // 可能为 null
        std::optional<std::string> rebate;   // 可能为 null
        std::optional<std::string> rebateCoin; // 可能为 null
        std::optional<int> leverage;         // 可能为 null
        std::optional<std::string> borrowAmount; // 可能为 null
        std::optional<std::string> borrowAsset; // 可能为 null
        std::string positionSide;
        std::optional<std::string> tpTriggerPrice; // 可能为 null
        std::optional<std::string> tpTriggerType;  // 可能为 null
        std::optional<std::string> tpPrice;        // 可能为 null
        std::optional<std::string> slTriggerPrice; // 可能为 null
        std::optional<std::string> slTriggerType;  // 可能为 null
        std::optional<std::string> slPrice;        // 可能为 null
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