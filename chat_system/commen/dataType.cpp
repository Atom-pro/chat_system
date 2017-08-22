#include "dataType.h"


int dataType::stringToValue(string &inString)
{
    Json::Value v;
    jsonApi::deSerialize(inString, v);
    name = v["name"].asString();
    school = v["school"].asString();
    msg = v["msg"].asString();
    cmd = v["cmd"].asString();
    return 0;
}


int dataType::valueToString(string &outString)
{
    Json::Value v;
    v["name"] = name;
    v["school"] = school;
    v["msg"] = msg;
    v["cmd"] = cmd;
    return jsonApi::serialize(v, outString);
}
