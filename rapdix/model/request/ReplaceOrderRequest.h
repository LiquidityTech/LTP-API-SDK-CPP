#pragma once
#include <string>
#include <nlohmann/json.hpp>

class ReplaceOrderRequest {
public:
    class Builder {
    public:
        Builder& orderId(const std::string& value) {
            orderId_ = value;
            return *this;
        }
        
        Builder& replaceQty(const std::string& value) {
            replaceQty_ = value;
            return *this;
        }
        
        Builder& replacePrice(const std::string& value) {
            replacePrice_ = value;
            return *this;
        }
        
        ReplaceOrderRequest build() {
            return ReplaceOrderRequest(*this);
        }
        
    private:
        friend class ReplaceOrderRequest;
        std::string orderId_;
        std::string replaceQty_;
        std::string replacePrice_;
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
    
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(ReplaceOrderRequest,
        orderId,
        replaceQty,
        replacePrice
    )
    
private:
    ReplaceOrderRequest(const Builder& builder) :
        orderId(builder.orderId_),
        replaceQty(builder.replaceQty_),
        replacePrice(builder.replacePrice_) {}
        
    std::string orderId;
    std::string replaceQty;
    std::string replacePrice;
}; 