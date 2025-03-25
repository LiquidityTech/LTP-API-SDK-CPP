#pragma once
#include <string>
#include <nlohmann/json.hpp>

class GetMarginLeverageRequest {
public:
    class Builder {
    public:
        Builder& exchangeType(const std::string& value) {
            exchangeType_ = value;
            return *this;
        }
        
        Builder& coin(const std::string& value) {
            coin_ = value;
            return *this;
        }
        
        Builder& page(const std::string& value) {
            page_ = value;
            return *this;
        }
        
        Builder& pageSize(const std::string& value) {
            pageSize_ = value;
            return *this;
        }
        
        GetMarginLeverageRequest build() {
            return GetMarginLeverageRequest(*this);
        }
        
    private:
        friend class GetMarginLeverageRequest;
        std::string exchangeType_;
        std::string coin_;
        std::string page_;
        std::string pageSize_;
    };
    
    static Builder builder() { return Builder(); }
    
    std::string toJsonString() const {
        nlohmann::json j;
        if (!exchangeType.empty()) j["exchangeType"] = exchangeType;
        if (!coin.empty()) j["coin"] = coin;
        if (!page.empty()) j["page"] = page;
        if (!pageSize.empty()) j["pageSize"] = pageSize;
        return j.empty() ? "{}" : j.dump();
    }
    
private:
    GetMarginLeverageRequest(const Builder& builder) :
        exchangeType(builder.exchangeType_),
        coin(builder.coin_),
        page(builder.page_),
        pageSize(builder.pageSize_) {}
        
    std::string exchangeType;
    std::string coin;
    std::string page;
    std::string pageSize;
}; 