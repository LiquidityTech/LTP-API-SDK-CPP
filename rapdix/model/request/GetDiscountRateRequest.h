#pragma once
#include <string>
#include <nlohmann/json.hpp>

class GetDiscountRateRequest {
public:
    class Builder {
    public:
        Builder& coin(const std::string& value) {
            coin_ = value;
            return *this;
        }
        
        GetDiscountRateRequest build() {
            return GetDiscountRateRequest(*this);
        }
        
    private:
        friend class GetDiscountRateRequest;
        std::string coin_;
    };
    
    static Builder builder() { return Builder(); }
    
    std::string toJsonString() const {
        nlohmann::json j;
        if (!coin.empty()) j["coin"] = coin;
        return j.empty() ? "{}" : j.dump();
    }
    
private:
    GetDiscountRateRequest(const Builder& builder) :
        coin(builder.coin_) {}
        
    std::string coin;
}; 