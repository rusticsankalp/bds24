#pragma once

#include <drogon/HttpSimpleController.h>

using namespace drogon;

class UidGenController : public drogon::HttpSimpleController<UidGenController>
{
  public:
    void asyncHandleHttpRequest(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback) override;
    PATH_LIST_BEGIN
    // list path definitions here;
    // PATH_ADD("/path", "filter1", "filter2", HttpMethod1, HttpMethod2...);
    PATH_ADD("/",Get,Post);
    PATH_ADD("/uid",Get);
    PATH_LIST_END
};
