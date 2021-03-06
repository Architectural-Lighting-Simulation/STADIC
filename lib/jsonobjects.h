/******************************************************************************
 * Copyright (c) 2014-2015, The Pennsylvania State University
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission of the
 *    respective copyright holder or contributor.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE,
 * AND NONINFRINGEMENT OF INTELLECTUAL PROPERTY ARE EXPRESSLY DISCLAIMED. IN
 * NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *****************************************************************************/

#ifndef JSONOBJECTS_H
#define JSONOBJECTS_H

#include "stadicapi.h"
#include "logging.h"

#include <json/json.h>
#include <boost/optional.hpp>

namespace stadic {

typedef Json::Value JsonObject;

boost::optional<JsonObject> readJsonDocument(const std::string &filename);

boost::optional<double> STADIC_API getDouble(const JsonObject &json, const std::string &key);
boost::optional<double> STADIC_API getDouble(const JsonObject &json, const std::string &key,
    const std::string &errorMissing, const std::string &errorBad, Severity severity);

boost::optional<int> STADIC_API getInt(const JsonObject &json, const std::string &key);
boost::optional<int> STADIC_API getInt(const JsonObject &json, const std::string &key, const std::string &errorMissing,
    const std::string &errorBad, Severity severity);

boost::optional<std::string> STADIC_API getString(const JsonObject &json, const std::string &key);
boost::optional<std::string> STADIC_API getString(const JsonObject &json, const std::string &key,
    const std::string &errorMissing, const std::string &errorBad, Severity severity);

boost::optional<bool> STADIC_API getBool(const JsonObject &json, const std::string &key);
boost::optional<bool> STADIC_API getBool(const JsonObject &json, const std::string &key, const std::string &errorMissing,
    const std::string &errorBad, Severity severity);
boost::optional<bool> STADIC_API getBool(const JsonObject &json, const std::string &key, bool defaultValue, 
    const std::string &errorBad, Severity severity);

boost::optional<JsonObject> STADIC_API getObject(const JsonObject &json, const std::string &key);
boost::optional<JsonObject> STADIC_API getObject(const JsonObject &json, const std::string &key,
    const std::string &errorMissing, Severity severity);

boost::optional<JsonObject> STADIC_API getArray(const JsonObject &json, const std::string &key);
boost::optional<JsonObject> STADIC_API getArray(const JsonObject &json, const std::string &key,
    const std::string &errorMissing, Severity severity);

boost::optional<double> STADIC_API asDouble(const JsonObject &json, const std::string &errorBad, Severity severity);
boost::optional<int> STADIC_API asInt(const JsonObject &json, const std::string &errorBad, Severity severity);
boost::optional<std::string> STADIC_API asString(const JsonObject &json, const std::string &errorBad, Severity severity);
boost::optional<bool> STADIC_API asBool(const JsonObject &json, const std::string &errorBad, Severity severity);
}

#endif
