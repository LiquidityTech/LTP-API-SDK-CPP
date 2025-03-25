#pragma once
#include <string>
#include <vector>
#include <ostream>
#include <nlohmann/json.hpp>

class GetLeverageResponse {
public:
    struct LeverageData {
        std::string sym;
        std::string leverage;
        
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(LeverageData, sym, leverage)
    };

    GetLeverageResponse() : code(0) {}
    
    // Getters
    int getCode() const { return code; }
    const std::string& getMessage() const { return message; }
    const std::vector<LeverageData>& getData() const { return data; }
    
    // 输出运算符重载
    friend std::ostream& operator<<(std::ostream& os, const GetLeverageResponse& response) {
        os << "GetLeverageResponse{code=" << response.code 
           << ", message='" << response.message << "'";
        if (!response.data.empty()) {
            os << ", leverages=[";
            for (const auto& leverage : response.data) {
                os << "\n  {sym='" << leverage.sym
                   << "', leverage='" << leverage.leverage
                   << "'}";
            }
            os << "\n]";
        }
        os << "}";
        return os;
    }
    
    // JSON 序列化
    friend void from_json(const nlohmann::json& j, GetLeverageResponse& response) {
        j.at("code").get_to(response.code);
        j.at("message").get_to(response.message);
        if (j.contains("data")) {
            if (j.at("data").is_object() && j.at("data").empty()) {
                response.data.clear();
            } else {
                j.at("data").get_to(response.data);
            }
        }
    }
    
    friend void to_json(nlohmann::json& j, const GetLeverageResponse& response) {
        j = {
            {"code", response.code},
            {"message", response.message}
        };
        if (!response.data.empty()) {
            j["data"] = response.data;
        }
    }
    
private:
    int code;
    std::string message;
    std::vector<LeverageData> data;
}; 