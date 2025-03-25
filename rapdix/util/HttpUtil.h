#pragma once
#include <string>
#include <map>
#include <curl/curl.h>

class HttpUtil {
public:
    static std::string httpRequest(const std::string& url, 
                                 const std::string& method, 
                                 const std::string& payload, 
                                 const std::map<std::string, std::string>& headers);
}; 