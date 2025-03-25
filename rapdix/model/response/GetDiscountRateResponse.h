#pragma once
#include <string>
#include <vector>
#include <ostream>
#include <nlohmann/json.hpp>

class GetDiscountRateResponse {
public:
    struct DiscountData {
        std::string coin;
        std::string discount;
        
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(DiscountData,
            coin, discount)
    };

    GetDiscountRateResponse() : code(0) {}
    
    // Getters
    int getCode() const { return code; }
    const std::string& getMessage() const { return message; }
    const std::vector<DiscountData>& getData() const { return data; }
    
    // 输出运算符重载
    friend std::ostream& operator<<(std::ostream& os, const GetDiscountRateResponse& response) {
        os << "GetDiscountRateResponse{code=" << response.code 
           << ", message='" << response.message << "'";
        if (!response.data.empty()) {
            os << ", discounts=[";
            for (const auto& discount : response.data) {
                os << "\n  {coin='" << discount.coin
                   << "', discount='" << discount.discount
                   << "'}";
            }
            os << "\n]";
        }
        os << "}";
        return os;
    }
    
    // 自定义 JSON 序列化
    friend void from_json(const nlohmann::json& j, GetDiscountRateResponse& response) {
        j.at("code").get_to(response.code);
        j.at("message").get_to(response.message);
        if (j.contains("data") && !j.at("data").is_null()) {
            const auto& data = j.at("data");
            if (data.is_array()) {
                response.data = data.get<std::vector<DiscountData>>();
            }
            // 如果是空对象 {}，就保持 data 为空数组
        }
    }
    
    friend void to_json(nlohmann::json& j, const GetDiscountRateResponse& response) {
        j = {
            {"code", response.code},
            {"message", response.message},
            {"data", response.data}
        };
    }
    
private:
    int code;
    std::string message;
    std::vector<DiscountData> data;
}; 