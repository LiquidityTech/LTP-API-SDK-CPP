#pragma once
#include <string>
#include <nlohmann/json.hpp>

class CancelOrderRequest {
public:
    class Builder {
    public:
        Builder& orderId(const std::string& value) {
            orderId_ = value;
            return *this;
        }
        
        Builder& clientOrderId(const std::string& value) {
            clientOrderId_ = value;
            return *this;
        }
        
        CancelOrderRequest build() {
            return CancelOrderRequest(*this);
        }
        
    private:
        friend class CancelOrderRequest;
        std::string orderId_;
        std::string clientOrderId_;
    };
    
    static Builder builder() { return Builder(); }
    
    std::string toJsonString() const {
        nlohmann::json j = *this;
        // 移除空值
        for (auto it = j.begin(); it != j.end();) {
            if (it.value().is_string() && it.value().get<std::string>().empty()) {
                it = j.erase(it);
            } else {
                ++it;
            }
        }
        return j.dump();
    }
    
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(CancelOrderRequest,
        orderId,
        clientOrderId
    )
    
private:
    CancelOrderRequest(const Builder& builder) :
        orderId(builder.orderId_),
        clientOrderId(builder.clientOrderId_) {}
        
    std::string orderId;
    std::string clientOrderId;
}; 