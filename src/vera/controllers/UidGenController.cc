#include "UidGenController.h"
#include "snowflake.h"

void UidGenController::asyncHandleHttpRequest(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback)
{

    Json::Value ret;
    ret["result"] = "ok";
    ret["id"] = uuid.GetNextId();

    auto resp = HttpResponse::newHttpJsonResponse(ret); 
    //resp->setStatusCode(k200OK);
    //resp->setContentTypeCode(CT_TEXT_HTML);
    //resp->setBody("Hello World uid");
    callback(resp);
}
