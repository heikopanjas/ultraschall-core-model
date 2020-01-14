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

#include "ServiceRegistry.h"
#include "ServiceFactory.h"

namespace Ultraschall { namespace Core {

ServiceRegistry::ServiceRegistry(ServiceFactory& serviceFactory) : serviceFactory_(serviceFactory) {}

ServiceRegistry::~ServiceRegistry()
{
    std::lock_guard<std::recursive_mutex> lock(servicesLock_);
}

ServiceStatus ServiceRegistry::AcquireService(
    const String& serviceId, IServiceCallback* serviceCallback, IService*& service)
{
    PRECONDITION_RETURN(serviceId.empty() == false, SERVICE_INVALID_PARAMETER);

    std::lock_guard<std::recursive_mutex> lock(servicesLock_);
    ServiceStatus                         status = SERVICE_FAILURE;
    service                                      = 0;

    const ServiceDictionary::iterator serviceIterator = services_.find(serviceId);
    if(serviceIterator == services_.end())
    {
        status = serviceFactory_.CreateService(serviceId, serviceCallback, service);
        if(SERVICE_SUCCEEDED(status))
        {
            status
                = ((services_.insert(std::pair<String, IService*>(serviceId, service)).second == true) ?
                       SERVICE_SUCCESS :
                       SERVICE_FAILURE);
        }
    }
    else
    {
        service = serviceIterator->second;
        if(service != 0)
        {
            service->AddRef();
            status = SERVICE_SUCCESS;
        }
    }

    return status;
}

ServiceStatus ServiceRegistry::ReleaseService(const String& serviceId)
{
    PRECONDITION_RETURN(serviceId.empty() == false, SERVICE_INVALID_PARAMETER);

    std::lock_guard<std::recursive_mutex> lock(servicesLock_);
    ServiceStatus                         status = SERVICE_NOT_FOUND;

    const ServiceDictionary::iterator serviceIterator = services_.find(serviceId);
    if(serviceIterator != services_.end())
    {
        IService* pService = serviceIterator->second;
        if(pService != 0)
        {
            if(pService->Release() == 0)
            {
                services_.erase(serviceIterator);
            }
            status = SERVICE_SUCCESS;
        }
        else
        {
            status = SERVICE_FAILURE;
            // FIXME: raise fatal error
        }
    }

    return status;
}
}} // namespace Ultraschall::Core
