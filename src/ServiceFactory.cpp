////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) The Ultraschall Project (http://ultraschall.fm)
//
// The MIT License (MIT)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
////////////////////////////////////////////////////////////////////////////////

#include "ServiceFactory.h"

namespace Ultraschall { namespace Core {

ServiceFactory::~ServiceFactory()
{
    std::lock_guard<std::recursive_mutex> lock(functionsLock_);

    functions_.clear();
}

ServiceStatus ServiceFactory::RegisterService(const String& serviceId, CREATE_SERVICE_FUNCTION factoryFunction)
{
    PRECONDITION_RETURN(serviceId.empty() == false, SERVICE_INVALID_PARAMETER);
    PRECONDITION_RETURN(factoryFunction != 0, SERVICE_INVALID_PARAMETER);

    std::lock_guard<std::recursive_mutex> lock(functionsLock_);

    ServiceStatus status = SERVICE_FAILURE;

    const FunctionDictionary::const_iterator functionIterator = functions_.find(serviceId);
    if(functionIterator == functions_.end())
    {
        status
            = ((functions_.insert(std::pair<String, CREATE_SERVICE_FUNCTION>(serviceId, factoryFunction)).second
                == true) ?
                   SERVICE_SUCCESS :
                   SERVICE_FAILURE);
    }
    else
    {
        status = SERVICE_ALREADY_REGISTERED;
    }

    return status;
}

void ServiceFactory::UnregisterService(const String& serviceId)
{
    PRECONDITION(serviceId.empty() == false);

    std::lock_guard<std::recursive_mutex> lock(functionsLock_);

    const FunctionDictionary::const_iterator functionIterator = functions_.find(serviceId);
    if(functionIterator == functions_.end())
    {
        functions_.erase(functionIterator);
    }
}

ServiceStatus ServiceFactory::CreateService(
    const String& serviceId, IServiceCallback* serviceCallback, IService*& service) const
{
    PRECONDITION_RETURN(serviceId.empty() == false, SERVICE_INVALID_PARAMETER);
    PRECONDITION_RETURN(serviceCallback != 0, SERVICE_INVALID_PARAMETER);
    PRECONDITION_RETURN(service == 0, SERVICE_INVALID_PARAMETER);

    std::lock_guard<std::recursive_mutex> lock(functionsLock_);

    ServiceStatus status = SERVICE_FAILURE;

    service                                                   = 0;
    const FunctionDictionary::const_iterator functionIterator = functions_.find(serviceId);
    if(functionIterator != functions_.end())
    {
        status = (functionIterator->second)(serviceCallback, service);
        if((SERVICE_SUCCEEDED(status)) && (service != 0))
        {
            status = SERVICE_SUCCESS;
        }
    }

    return status;
}
}} // namespace Ultraschall::Core
