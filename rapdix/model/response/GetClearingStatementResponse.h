#pragma once
#include <string>
#include <vector>
#include <ostream>
#include <nlohmann/json.hpp>

class GetClearingStatementResponse {
public:
    struct StatementData {
        std::string id;
        std::string userId;
        std::string portfolioId;
        std::string exchangeType;
        std::string businessType;
        std::string transactionId;
        std::string statementFlowType;
        std::string coin;
        std::string amount;
        std::string createAt;
        std::string updateAt;
        
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(StatementData,
            id, userId, portfolioId, exchangeType, businessType, transactionId,
            statementFlowType, coin, amount, createAt, updateAt)
    };

    GetClearingStatementResponse() : code(0) {}
    
    // Getters
    int getCode() const { return code; }
    const std::string& getMessage() const { return message; }
    const std::vector<StatementData>& getData() const { return data; }
    
    // 输出运算符重载
    friend std::ostream& operator<<(std::ostream& os, const GetClearingStatementResponse& response) {
        os << "GetClearingStatementResponse{code=" << response.code 
           << ", message='" << response.message << "'";
        if (!response.data.empty()) {
            os << ", statements=[";
            for (const auto& statement : response.data) {
                os << "\n  {id='" << statement.id
                   << "', userId='" << statement.userId
                   << "', portfolioId='" << statement.portfolioId
                   << "', exchangeType='" << statement.exchangeType
                   << "', businessType='" << statement.businessType
                   << "', transactionId='" << statement.transactionId
                   << "', statementFlowType='" << statement.statementFlowType
                   << "', coin='" << statement.coin
                   << "', amount='" << statement.amount
                   << "', createAt='" << statement.createAt
                   << "', updateAt='" << statement.updateAt
                   << "'}";
            }
            os << "\n]";
        }
        os << "}";
        return os;
    }
    
    // 自定义 JSON 序列化
    friend void from_json(const nlohmann::json& j, GetClearingStatementResponse& response) {
        j.at("code").get_to(response.code);
        j.at("message").get_to(response.message);
        
        if (j.contains("data") && !j.at("data").is_null()) {
            const auto& dataArray = j.at("data");
            if (dataArray.is_array()) {
                response.data = dataArray.get<std::vector<StatementData>>();
            }
        }
    }
    
    friend void to_json(nlohmann::json& j, const GetClearingStatementResponse& response) {
        j = {
            {"code", response.code},
            {"message", response.message},
            {"data", response.data}
        };
    }
    
private:
    int code;
    std::string message;
    std::vector<StatementData> data;
}; 