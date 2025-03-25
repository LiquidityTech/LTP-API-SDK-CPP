#pragma once
#include <string>
#include <vector>
#include <ostream>
#include <nlohmann/json.hpp>

class ClosePositionsResponse {
public:
    struct CloseResult {
        std::string sym;
        std::string orderId;
        std::string positionSide;
        std::string success;
        std::string errorMsg;
        
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(CloseResult,
            sym, orderId, positionSide, success, errorMsg)
    };

    ClosePositionsResponse() : code(0) {}
    
    // Getters
    int getCode() const { return code; }
    const std::string& getMessage() const { return message; }
    const std::vector<CloseResult>& getData() const { return data; }
    
    // 输出运算符重载
    friend std::ostream& operator<<(std::ostream& os, const ClosePositionsResponse& response) {
        os << "ClosePositionsResponse{code=" << response.code 
           << ", message='" << response.message << "'";
        if (!response.data.empty()) {
            os << ", results=[";
            for (const auto& result : response.data) {
                os << "\n  {sym='" << result.sym
                   << "', orderId='" << result.orderId
                   << "', positionSide='" << result.positionSide
                   << "', success='" << result.success
                   << "', errorMsg='" << result.errorMsg
                   << "'}";
            }
            os << "\n]";
        }
        os << "}";
        return os;
    }
    
    // JSON 序列化
    friend void from_json(const nlohmann::json& j, ClosePositionsResponse& response) {
        j.at("code").get_to(response.code);
        j.at("message").get_to(response.message);
        if (j.contains("data") && !j.at("data").is_null()) {
            j.at("data").get_to(response.data);
        }
    }
    
    friend void to_json(nlohmann::json& j, const ClosePositionsResponse& response) {
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
    std::vector<CloseResult> data;
}; 