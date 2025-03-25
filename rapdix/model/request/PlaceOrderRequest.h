#pragma once
#include <string>
#include <nlohmann/json.hpp>

class PlaceOrderRequest {
public:
    // Builder 模式
    class Builder {
    public:
        Builder& clientOrderId(const std::string& value) {
            clientOrderId_ = value;
            return *this;
        }
        
        Builder& sym(const std::string& value) {
            sym_ = value;
            return *this;
        }
        
        Builder& side(const std::string& value) {
            side_ = value;
            return *this;
        }
        
        Builder& orderType(const std::string& value) {
            orderType_ = value;
            return *this;
        }
        
        Builder& timeInForce(const std::string& value) {
            timeInForce_ = value;
            return *this;
        }
        
        Builder& orderQty(const std::string& value) {
            orderQty_ = value;
            return *this;
        }
        
        Builder& limitPrice(const std::string& value) {
            limitPrice_ = value;
            return *this;
        }
        
        Builder& quoteOrderQty(const std::string& value) {
            quoteOrderQty_ = value;
            return *this;
        }
        
        Builder& reduceOnly(const std::string& value) {
            reduceOnly_ = value;
            return *this;
        }
        
        Builder& positionSide(const std::string& value) {
            positionSide_ = value;
            return *this;
        }
        
        Builder& tpTriggerPrice(const std::string& value) {
            tpTriggerPrice_ = value;
            return *this;
        }
        
        Builder& tpTriggerType(const std::string& value) {
            tpTriggerType_ = value;
            return *this;
        }
        
        Builder& tpPrice(const std::string& value) {
            tpPrice_ = value;
            return *this;
        }
        
        Builder& slTriggerPrice(const std::string& value) {
            slTriggerPrice_ = value;
            return *this;
        }
        
        Builder& slTriggerType(const std::string& value) {
            slTriggerType_ = value;
            return *this;
        }
        
        Builder& slPrice(const std::string& value) {
            slPrice_ = value;
            return *this;
        }
        
        PlaceOrderRequest build() {
            return PlaceOrderRequest(*this);
        }
        
    private:
        friend class PlaceOrderRequest;
        std::string clientOrderId_;
        std::string sym_;
        std::string side_;
        std::string orderType_;
        std::string timeInForce_;
        std::string orderQty_;
        std::string limitPrice_;
        std::string quoteOrderQty_;
        std::string reduceOnly_;
        std::string positionSide_;
        std::string tpTriggerPrice_;
        std::string tpTriggerType_;
        std::string tpPrice_;
        std::string slTriggerPrice_;
        std::string slTriggerType_;
        std::string slPrice_;
    };
    
    // Getters
    const std::string& getClientOrderId() const { return clientOrderId; }
    const std::string& getSym() const { return sym; }
    const std::string& getSide() const { return side; }
    const std::string& getOrderType() const { return orderType; }
    const std::string& getTimeInForce() const { return timeInForce; }
    const std::string& getOrderQty() const { return orderQty; }
    const std::string& getLimitPrice() const { return limitPrice; }
    const std::string& getQuoteOrderQty() const { return quoteOrderQty; }
    const std::string& getReduceOnly() const { return reduceOnly; }
    const std::string& getPositionSide() const { return positionSide; }
    const std::string& getTpTriggerPrice() const { return tpTriggerPrice; }
    const std::string& getTpTriggerType() const { return tpTriggerType; }
    const std::string& getTpPrice() const { return tpPrice; }
    const std::string& getSlTriggerPrice() const { return slTriggerPrice; }
    const std::string& getSlTriggerType() const { return slTriggerType; }
    const std::string& getSlPrice() const { return slPrice; }
    
    static Builder builder() { return Builder(); }
    
    // 直接转换为JSON字符串
    std::string toJsonString() const {
        nlohmann::json j = *this;
        // 移除空值
        for (auto it = j.begin(); it != j.end();) {
            if (it.value().is_string() && it.value().get<std::string>().empty()) {
                it = j.erase(it);
            } else {
                ++it;
            }
        }
        return j.dump();
    }
    
    // 为 nlohmann/json 添加序列化支持，注意字段名要和 API 文档一致
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(PlaceOrderRequest,
        clientOrderId,
        sym,
        side,
        orderType,
        timeInForce,
        orderQty,
        limitPrice,
        quoteOrderQty,
        reduceOnly,
        positionSide,
        tpTriggerPrice,
        tpTriggerType,
        tpPrice,
        slTriggerPrice,
        slTriggerType,
        slPrice
    )

private:
    PlaceOrderRequest(const Builder& builder) :
        clientOrderId(builder.clientOrderId_),
        sym(builder.sym_),
        side(builder.side_),
        orderType(builder.orderType_),
        timeInForce(builder.timeInForce_),
        orderQty(builder.orderQty_),
        limitPrice(builder.limitPrice_),
        quoteOrderQty(builder.quoteOrderQty_),
        reduceOnly(builder.reduceOnly_),
        positionSide(builder.positionSide_),
        tpTriggerPrice(builder.tpTriggerPrice_),
        tpTriggerType(builder.tpTriggerType_),
        tpPrice(builder.tpPrice_),
        slTriggerPrice(builder.slTriggerPrice_),
        slTriggerType(builder.slTriggerType_),
        slPrice(builder.slPrice_) {}
        
    std::string clientOrderId;
    std::string sym;
    std::string side;
    std::string orderType;
    std::string timeInForce;
    std::string orderQty;
    std::string limitPrice;
    std::string quoteOrderQty;
    std::string reduceOnly;
    std::string positionSide;
    std::string tpTriggerPrice;
    std::string tpTriggerType;
    std::string tpPrice;
    std::string slTriggerPrice;
    std::string slTriggerType;
    std::string slPrice;
}; 