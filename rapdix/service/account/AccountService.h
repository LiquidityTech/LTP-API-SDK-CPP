#pragma once
#include "rapdix/model/request/ChangePositionModeRequest.h"
#include "rapdix/model/response/ChangePositionModeResponse.h"
#include "rapdix/model/response/QueryAccountResponse.h"

class AccountService {
public:
    static ChangePositionModeResponse changePositionMode(const ChangePositionModeRequest& request);
    static QueryAccountResponse queryAccount();
}; 