#pragma once
#include <string>
#include <nlohmann/json.hpp>

class QueryPortfolioAssetsRequest {
public:
    class Builder {
    public:
        Builder& exchangeType(const std::string& value) {
            exchangeType_ = value;
            return *this;
        }
        
        Builder& pageNum(const std::string& value) {
            pageNum_ = value;
            return *this;
        }
        
        Builder& pageSize(const std::string& value) {
            pageSize_ = value;
            return *this;
        }
        
        QueryPortfolioAssetsRequest build() {
            return QueryPortfolioAssetsRequest(*this);
        }
        
    private:
        friend class QueryPortfolioAssetsRequest;
        std::string exchangeType_;
        std::string pageNum_;
        std::string pageSize_;
    };
    
    static Builder builder() { return Builder(); }
    
    std::string toJsonString() const {
        nlohmann::json j;
        if (!exchangeType.empty()) j["exchangeType"] = exchangeType;
        if (!pageNum.empty()) j["pageNum"] = pageNum;
        if (!pageSize.empty()) j["pageSize"] = pageSize;
        return j.empty() ? "{}" : j.dump();
    }
    
private:
    QueryPortfolioAssetsRequest(const Builder& builder) :
        exchangeType(builder.exchangeType_),
        pageNum(builder.pageNum_),
        pageSize(builder.pageSize_) {}
        
    std::string exchangeType;
    std::string pageNum;
    std::string pageSize;
}; 