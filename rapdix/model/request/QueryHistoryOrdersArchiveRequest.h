#pragma once
#include <string>
#include <nlohmann/json.hpp>

class QueryHistoryOrdersArchiveRequest {
public:
    class Builder {
    public:
        Builder& sym(const std::string& value) {
            sym_ = value;
            return *this;
        }
        
        Builder& businessType(const std::string& value) {
            businessType_ = value;
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
        
        Builder& filterExecuted(bool value) {
            filterExecuted_ = value;
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
        
        QueryHistoryOrdersArchiveRequest build() {
            return QueryHistoryOrdersArchiveRequest(*this);
        }
        
    private:
        friend class QueryHistoryOrdersArchiveRequest;
        std::string sym_;
        std::string businessType_;
        std::string exchange_;
        std::string begin_;
        std::string end_;
        bool filterExecuted_ = false;
        std::string page_;
        std::string pageSize_;
    };
    
    static Builder builder() { return Builder(); }
    
    std::string toJsonString() const {
        nlohmann::json j = *this;
        // 移除空值
        for (auto it = j.begin(); it != j.end();) {
            if ((it.value().is_string() && it.value().get<std::string>().empty()) ||
                (it.key() == "filterExecuted" && !filterExecuted)) {
                it = j.erase(it);
            } else {
                ++it;
            }
        }
        return j.dump();
    }
    
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(QueryHistoryOrdersArchiveRequest,
        sym,
        businessType,
        exchange,
        begin,
        end,
        filterExecuted,
        page,
        pageSize
    )
    
private:
    QueryHistoryOrdersArchiveRequest(const Builder& builder) :
        sym(builder.sym_),
        businessType(builder.businessType_),
        exchange(builder.exchange_),
        begin(builder.begin_),
        end(builder.end_),
        filterExecuted(builder.filterExecuted_),
        page(builder.page_),
        pageSize(builder.pageSize_) {}
        
    std::string sym;
    std::string businessType;
    std::string exchange;
    std::string begin;
    std::string end;
    bool filterExecuted;
    std::string page;
    std::string pageSize;
}; 