#pragma once
#include <string>
#include <nlohmann/json.hpp>

class ClosePositionsRequest {
public:
    class Builder {
    public:
        Builder& symList(const std::string& value) {
            symList_ = value;
            return *this;
        }
        
        Builder& positionSide(const std::string& value) {
            positionSide_ = value;
            return *this;
        }
        
        Builder& closeAllPos(const std::string& value) {
            closeAllPos_ = value;
            return *this;
        }
        
        Builder& exchangeType(const std::string& value) {
            exchangeType_ = value;
            return *this;
        }
        
        ClosePositionsRequest build() {
            return ClosePositionsRequest(*this);
        }
        
    private:
        friend class ClosePositionsRequest;
        std::string symList_;
        std::string positionSide_;
        std::string closeAllPos_;
        std::string exchangeType_;
    };
    
    static Builder builder() { return Builder(); }
    
    std::string toJsonString() const {
        nlohmann::json j;
        if (!symList.empty()) j["symList"] = symList;
        if (!positionSide.empty()) j["positionSide"] = positionSide;
        if (!closeAllPos.empty()) j["closeAllPos"] = closeAllPos;
        if (!exchangeType.empty()) j["exchangeType"] = exchangeType;
        return j.dump();
    }
    
private:
    ClosePositionsRequest(const Builder& builder) :
        symList(builder.symList_),
        positionSide(builder.positionSide_),
        closeAllPos(builder.closeAllPos_),
        exchangeType(builder.exchangeType_) {}
        
    std::string symList;
    std::string positionSide;
    std::string closeAllPos;
    std::string exchangeType;
}; 