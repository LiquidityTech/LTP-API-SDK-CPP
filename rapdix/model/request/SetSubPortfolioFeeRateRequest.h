#pragma once
#include <string>
#include <nlohmann/json.hpp>

class SetSubPortfolioFeeRateRequest {
public:
    class Builder {
    public:
        Builder& portfolioId(const std::string& value) {
            portfolioId_ = value;
            return *this;
        }
        
        Builder& exchange(const std::string& value) {
            exchange_ = value;
            return *this;
        }
        
        Builder& instType(const std::string& value) {
            instType_ = value;
            return *this;
        }
        
        Builder& chgType(const std::string& value) {
            chgType_ = value;
            return *this;
        }
        
        Builder& chgTaker(const std::string& value) {
            chgTaker_ = value;
            return *this;
        }
        
        Builder& chgMaker(const std::string& value) {
            chgMaker_ = value;
            return *this;
        }
        
        Builder& effDate(const std::string& value) {
            effDate_ = value;
            return *this;
        }
        
        SetSubPortfolioFeeRateRequest build() {
            if (exchange_.empty()) throw std::runtime_error("exchange is mandatory");
            if (instType_.empty()) throw std::runtime_error("instType is mandatory");
            if (chgType_.empty()) throw std::runtime_error("chgType is mandatory");
            if (chgTaker_.empty() && chgMaker_.empty()) {
                throw std::runtime_error("one of chgTaker and chgMaker must be filled");
            }
            return SetSubPortfolioFeeRateRequest(*this);
        }
        
    private:
        friend class SetSubPortfolioFeeRateRequest;
        std::string portfolioId_;
        std::string exchange_;
        std::string instType_;
        std::string chgType_;
        std::string chgTaker_;
        std::string chgMaker_;
        std::string effDate_;
    };
    
    static Builder builder() { return Builder(); }
    
    std::string toJsonString() const {
        nlohmann::json j;
        if (!portfolioId.empty()) j["portfolioId"] = portfolioId;
        j["exchange"] = exchange;
        j["instType"] = instType;
        j["chgType"] = chgType;
        if (!chgTaker.empty()) j["chgTaker"] = chgTaker;
        if (!chgMaker.empty()) j["chgMaker"] = chgMaker;
        if (!effDate.empty()) j["effDate"] = effDate;
        return j.dump();
    }
    
private:
    SetSubPortfolioFeeRateRequest(const Builder& builder) :
        portfolioId(builder.portfolioId_),
        exchange(builder.exchange_),
        instType(builder.instType_),
        chgType(builder.chgType_),
        chgTaker(builder.chgTaker_),
        chgMaker(builder.chgMaker_),
        effDate(builder.effDate_) {}
        
    std::string portfolioId;
    std::string exchange;
    std::string instType;
    std::string chgType;
    std::string chgTaker;
    std::string chgMaker;
    std::string effDate;
};
 