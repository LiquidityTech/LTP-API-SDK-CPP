#pragma once
#include <string>
#include <nlohmann/json.hpp>

class QueryTransactionsRequest {
public:
    class Builder {
    public:
        Builder& orderId(const std::string& value) {
            orderId_ = value;
            return *this;
        }
        
        Builder& sym(const std::string& value) {
            sym_ = value;
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
        
        Builder& limit(const std::string& value) {
            limit_ = value;
            return *this;
        }
        
        QueryTransactionsRequest build() {
            return QueryTransactionsRequest(*this);
        }
        
    private:
        friend class QueryTransactionsRequest;
        std::string orderId_;
        std::string sym_;
        std::string begin_;
        std::string end_;
        std::string limit_;
    };
    
    static Builder builder() { return Builder(); }
    
    std::string toJsonString() const {
        nlohmann::json j;
        if (!orderId.empty()) j["orderId"] = orderId;
        if (!sym.empty()) j["sym"] = sym;
        if (!begin.empty()) j["begin"] = begin;
        if (!end.empty()) j["end"] = end;
        if (!limit.empty()) j["limit"] = limit;
        return j.empty() ? "{}" : j.dump();
    }
    
private:
    QueryTransactionsRequest(const Builder& builder) :
        orderId(builder.orderId_),
        sym(builder.sym_),
        begin(builder.begin_),
        end(builder.end_),
        limit(builder.limit_) {}
        
    std::string orderId;
    std::string sym;
    std::string begin;
    std::string end;
    std::string limit;
}; 