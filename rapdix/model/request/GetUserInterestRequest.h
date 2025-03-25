#pragma once
#include <string>
#include <nlohmann/json.hpp>

class GetUserInterestRequest {
public:
    class Builder {
    public:
        Builder& exchangeType(const std::string& value) {
            exchangeType_ = value;
            return *this;
        }
        
        GetUserInterestRequest build() {
            return GetUserInterestRequest(*this);
        }
        
    private:
        friend class GetUserInterestRequest;
        std::string exchangeType_;
    };
    
    static Builder builder() { return Builder(); }
    
    std::string toJsonString() const {
        nlohmann::json j;
        j["exchangeType"] = exchangeType;  // 必填
        return j.dump();
    }
    
private:
    GetUserInterestRequest(const Builder& builder) :
        exchangeType(builder.exchangeType_) {}
        
    std::string exchangeType;
}; 