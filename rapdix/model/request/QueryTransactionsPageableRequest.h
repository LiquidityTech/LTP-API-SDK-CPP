#pragma once
#include <string>
#include <nlohmann/json.hpp>

class QueryTransactionsPageableRequest {
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
        
        Builder& page(const std::string& value) {
            page_ = value;
            return *this;
        }
        
        Builder& pageSize(const std::string& value) {
            pageSize_ = value;
            return *this;
        }
        
        QueryTransactionsPageableRequest build() {
            return QueryTransactionsPageableRequest(*this);
        }
        
    private:
        friend class QueryTransactionsPageableRequest;
        std::string orderId_;
        std::string sym_;
        std::string begin_;
        std::string end_;
        std::string page_;
        std::string pageSize_;
    };
    
    static Builder builder() { return Builder(); }
    
    std::string toJsonString() const {
        nlohmann::json j;
        if (!orderId.empty()) j["orderId"] = orderId;
        if (!sym.empty()) j["sym"] = sym;
        if (!begin.empty()) j["begin"] = begin;
        if (!end.empty()) j["end"] = end;
        if (!page.empty()) j["page"] = page;
        if (!pageSize.empty()) j["pageSize"] = pageSize;
        return j.empty() ? "{}" : j.dump();
    }
    
private:
    QueryTransactionsPageableRequest(const Builder& builder) :
        orderId(builder.orderId_),
        sym(builder.sym_),
        begin(builder.begin_),
        end(builder.end_),
        page(builder.page_),
        pageSize(builder.pageSize_) {}
        
    std::string orderId;
    std::string sym;
    std::string begin;
    std::string end;
    std::string page;
    std::string pageSize;
}; 