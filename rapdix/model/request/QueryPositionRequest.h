#pragma once
#include <string>
#include <nlohmann/json.hpp>

class QueryPositionRequest {
public:
    class Builder {
    public:
        Builder& sym(const std::string& value) {
            sym_ = value;
            return *this;
        }
        
        QueryPositionRequest build() {
            return QueryPositionRequest(*this);
        }
        
    private:
        friend class QueryPositionRequest;
        std::string sym_;
    };
    
    static Builder builder() { return Builder(); }
    
    std::string toJsonString() const {
        nlohmann::json j;
        if (!sym.empty()) j["sym"] = sym;
        return j.empty() ? "{}" : j.dump();
    }
    
private:
    QueryPositionRequest(const Builder& builder) :
        sym(builder.sym_) {}
        
    std::string sym;
}; 