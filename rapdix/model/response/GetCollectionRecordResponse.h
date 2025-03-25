#pragma once
#include <string>
#include <vector>
#include <ostream>
#include <nlohmann/json.hpp>

class GetCollectionRecordResponse {
public:
    struct RecordData {
        std::string userId;
        std::string portfolioId;
        std::string subPortfolioId;
        std::string exchangeType;
        std::string businessType;
        std::string transactionId;
        std::string coin;
        std::string amount;
        std::string status;
        std::string createAt;
        
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(RecordData,
            userId, portfolioId, subPortfolioId, exchangeType, businessType,
            transactionId, coin, amount, status, createAt)
    };

    GetCollectionRecordResponse() : code(0) {}
    
    // Getters
    int getCode() const { return code; }
    const std::string& getMessage() const { return message; }
    const std::vector<RecordData>& getData() const { return data; }
    
    // 输出运算符重载
    friend std::ostream& operator<<(std::ostream& os, const GetCollectionRecordResponse& response) {
        os << "GetCollectionRecordResponse{code=" << response.code 
           << ", message='" << response.message << "'";
        if (!response.data.empty()) {
            os << ", records=[";
            for (const auto& record : response.data) {
                os << "\n  {userId='" << record.userId
                   << "', portfolioId='" << record.portfolioId
                   << "', subPortfolioId='" << record.subPortfolioId
                   << "', exchangeType='" << record.exchangeType
                   << "', businessType='" << record.businessType
                   << "', transactionId='" << record.transactionId
                   << "', coin='" << record.coin
                   << "', amount='" << record.amount
                   << "', status='" << record.status
                   << "', createAt='" << record.createAt
                   << "'}";
            }
            os << "\n]";
        }
        os << "}";
        return os;
    }
    
    // 自定义 JSON 序列化
    friend void from_json(const nlohmann::json& j, GetCollectionRecordResponse& response) {
        j.at("code").get_to(response.code);
        j.at("message").get_to(response.message);
        
        if (j.contains("data") && !j.at("data").is_null()) {
            const auto& dataArray = j.at("data");
            if (dataArray.is_array()) {
                response.data = dataArray.get<std::vector<RecordData>>();
            }
        }
    }
    
    friend void to_json(nlohmann::json& j, const GetCollectionRecordResponse& response) {
        j = {
            {"code", response.code},
            {"message", response.message},
            {"data", response.data}
        };
    }
    
private:
    int code;
    std::string message;
    std::vector<RecordData> data;
}; 