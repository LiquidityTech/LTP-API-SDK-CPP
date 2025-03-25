#include "SignatureUtil.h"
#include <chrono>
#include <iomanip>
#include <sstream>
#include <openssl/hmac.h>
#include <nlohmann/json.hpp>
#include <algorithm>
#include <iostream>

std::string SignatureUtil::gmtNow() {
    auto now = std::chrono::system_clock::now();
    auto now_sec = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch());
    return std::to_string(now_sec.count());
}

std::string SignatureUtil::hmacSHA256(const std::string& data, const std::string& key) {
    unsigned char* digest = HMAC(EVP_sha256(), 
                                key.c_str(), key.length(),
                                (unsigned char*)data.c_str(), data.length(),
                                NULL, NULL);
    
    std::stringstream ss;
    for(int i = 0; i < 32; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)digest[i];
    }
    return ss.str();
}

std::string SignatureUtil::getPayloadForSign(const std::string& jsonRequest) {
    if (jsonRequest.empty() || jsonRequest == "{}") {
        return "";
    }

    try {
        nlohmann::json j = nlohmann::json::parse(jsonRequest);
        
        std::vector<std::string> keys;
        for (auto& item : j.items()) {
            keys.push_back(item.key());
        }
        std::sort(keys.begin(), keys.end());

        std::string queryString;
        for (const auto& key : keys) {
            if (!queryString.empty()) {
                queryString += "&";
            }
            auto value = j[key];
            if (value.is_array()) {
                queryString += key + "=";
                bool first = true;
                for (const auto& item : value) {
                    if (!first) {
                        queryString += ",";
                    }
                    queryString += item.dump();
                    first = false;
                }
            } else if (value.is_number() || value.is_number_float()) {
                queryString += key + "=" + value.dump();
            } else {
                std::string valueStr = value.dump();
                if (value.is_string()) {
                    valueStr = valueStr.substr(1, valueStr.length() - 2);
                }
                queryString += key + "=" + valueStr;
            }
        }
        return queryString;
    } catch (const std::exception& e) {
        throw std::runtime_error("Error generating payload for sign: " + std::string(e.what()));
    }
} 
