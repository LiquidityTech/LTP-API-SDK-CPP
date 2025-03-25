#pragma once
#include "rapdix/model/request/QueryTransactionsRequest.h"
#include "rapdix/model/response/QueryTransactionsResponse.h"
#include "rapdix/model/request/QueryTransactionsPageableRequest.h"
#include "rapdix/model/response/QueryTransactionsPageableResponse.h"
#include "rapdix/model/request/QueryArchivedTransactionsRequest.h"
#include "rapdix/model/response/QueryArchivedTransactionsResponse.h"

class TransactionService {
public:
    static QueryTransactionsResponse queryTransactions(const QueryTransactionsRequest& request);
    static QueryTransactionsPageableResponse queryTransactionsPageable(const QueryTransactionsPageableRequest& request);
    static QueryArchivedTransactionsResponse queryArchivedTransactions(const QueryArchivedTransactionsRequest& request);
}; 