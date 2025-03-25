#pragma once
#include <string>
#include <nlohmann/json.hpp>

class QueryHistoryPositionRequest {
public:
    class Builder {
    public:
        Builder& sym(const std::string& value) {
            sym_ = value;
            return *this;
        }
        
        Builder& exchange(const std::string& value) {
            exchange_ = value;
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
        
        QueryHistoryPositionRequest build() {
            return QueryHistoryPositionRequest(*this);
        }
        
    private:
        friend class QueryHistoryPositionRequest;
        std::string sym_;
        std::string exchange_;
        std::string begin_;
        std::string end_;
        std::string page_;
        std::string pageSize_;
    };
    
    static Builder builder() { return Builder(); }
    
    std::string toJsonString() const {
        nlohmann::json j;
        if (!sym.empty()) j["sym"] = sym;
        if (!exchange.empty()) j["exchange"] = exchange;
        if (!begin.empty()) j["begin"] = begin;
        if (!end.empty()) j["end"] = end;
        if (!page.empty()) j["page"] = page;
        if (!pageSize.empty()) j["pageSize"] = pageSize;
        return j.empty() ? "{}" : j.dump();
    }
    
private:
    QueryHistoryPositionRequest(const Builder& builder) :
        sym(builder.sym_),
        exchange(builder.exchange_),
        begin(builder.begin_),
        end(builder.end_),
        page(builder.page_),
        pageSize(builder.pageSize_) {}
        
    std::string sym;
    std::string exchange;
    std::string begin;
    std::string end;
    std::string page;
    std::string pageSize;
}; 