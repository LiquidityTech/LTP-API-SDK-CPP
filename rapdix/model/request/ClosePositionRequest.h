#pragma once
#include <string>
#include <nlohmann/json.hpp>

class ClosePositionRequest {
public:
    class Builder {
    public:
        Builder& sym(const std::string& value) {
            sym_ = value;
            return *this;
        }
        
        Builder& positionSide(const std::string& value) {
            positionSide_ = value;
            return *this;
        }
        
        ClosePositionRequest build() {
            return ClosePositionRequest(*this);
        }
        
    private:
        friend class ClosePositionRequest;
        std::string sym_;
        std::string positionSide_;
    };
    
    static Builder builder() { return Builder(); }
    
    std::string toJsonString() const {
        nlohmann::json j;
        j["sym"] = sym;  // sym 是必需的
        if (!positionSide.empty()) j["positionSide"] = positionSide;
        return j.dump();
    }
    
private:
    ClosePositionRequest(const Builder& builder) :
        sym(builder.sym_),
        positionSide(builder.positionSide_) {}
        
    std::string sym;
    std::string positionSide;
}; 