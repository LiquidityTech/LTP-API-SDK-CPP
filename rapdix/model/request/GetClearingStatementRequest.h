#pragma once
#include <string>
#include <nlohmann/json.hpp>

class GetClearingStatementRequest {
public:
    class Builder {
    public:
        Builder& exchange(const std::string& value) {
            exchange_ = value;
            return *this;
        }
        
        Builder& instType(const std::string& value) {
            instType_ = value;
            return *this;
        }
        
        Builder& coin(const std::string& value) {
            coin_ = value;
            return *this;
        }
        
        Builder& begin(const std::string& value) {
            begin_ = value;
            return *this;
        }
        
        Builder& end(const std::string& value) {
            end_ = value;
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
        
        GetClearingStatementRequest build() {
            return GetClearingStatementRequest(*this);
        }
        
    private:
        friend class GetClearingStatementRequest;
        std::string exchange_;
        std::string instType_;
        std::string coin_;
        std::string begin_;
        std::string end_;
        std::string pageNum_;
        std::string pageSize_;
    };
    
    static Builder builder() { return Builder(); }
    
    std::string toJsonString() const {
        nlohmann::json j;
        if (!exchange.empty()) j["exchange"] = exchange;
        if (!instType.empty()) j["instType"] = instType;
        if (!coin.empty()) j["coin"] = coin;
        if (!begin.empty()) j["begin"] = begin;
        if (!end.empty()) j["end"] = end;
        if (!pageNum.empty()) j["pageNum"] = pageNum;
        if (!pageSize.empty()) j["pageSize"] = pageSize;
        return j.empty() ? "{}" : j.dump();
    }
    
private:
    GetClearingStatementRequest(const Builder& builder) :
        exchange(builder.exchange_),
        instType(builder.instType_),
        coin(builder.coin_),
        begin(builder.begin_),
        end(builder.end_),
        pageNum(builder.pageNum_),
        pageSize(builder.pageSize_) {}
        
    std::string exchange;
    std::string instType;
    std::string coin;
    std::string begin;
    std::string end;
    std::string pageNum;
    std::string pageSize;
}; 