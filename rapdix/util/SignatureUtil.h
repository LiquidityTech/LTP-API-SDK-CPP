#pragma once
#include <string>

class SignatureUtil {
public:
    static std::string gmtNow();
    static std::string hmacSHA256(const std::string& data, const std::string& key);
    static std::string getPayloadForSign(const std::string& jsonRequest);
}; 