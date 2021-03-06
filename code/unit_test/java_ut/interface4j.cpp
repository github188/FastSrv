// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************
//
// Ice version 3.5.0
//
// <auto-generated>
//
// Generated from file `interface4j.ice'
//
// Warning: do not edit this file.
//
// </auto-generated>
//

#include <interface4j.h>
#include <Ice/LocalException.h>
#include <Ice/ObjectFactory.h>
#include <Ice/BasicStream.h>
#include <Ice/Object.h>
#include <IceUtil/Iterator.h>

#ifndef ICE_IGNORE_VERSION
#   if ICE_INT_VERSION / 100 != 305
#       error Ice version mismatch!
#   endif
#   if ICE_INT_VERSION % 100 > 50
#       error Beta header file detected
#   endif
#   if ICE_INT_VERSION % 100 < 0
#       error Ice patch level mismatch!
#   endif
#endif

namespace
{

namespace
{

const ::std::string __sending__server__Api__push_name = "push";

}

}

namespace Ice
{
}
::IceProxy::Ice::Object* ::IceProxy::sending::server::upCast(::IceProxy::sending::server::Api* p) { return p; }

void
::IceProxy::sending::server::__read(::IceInternal::BasicStream* __is, ::IceInternal::ProxyHandle< ::IceProxy::sending::server::Api>& v)
{
    ::Ice::ObjectPrx proxy;
    __is->read(proxy);
    if(!proxy)
    {
        v = 0;
    }
    else
    {
        v = new ::IceProxy::sending::server::Api;
        v->__copyFrom(proxy);
    }
}

::sending::server::Rtn
IceProxy::sending::server::Api::push(const ::sending::server::Command& m, const ::Ice::Context* __ctx)
{
    ::IceInternal::InvocationObserver __observer(this, __sending__server__Api__push_name, __ctx);
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase;
        try
        {
            __checkTwowayOnly(__sending__server__Api__push_name);
            __delBase = __getDelegate(false);
            ::IceDelegate::sending::server::Api* __del = dynamic_cast< ::IceDelegate::sending::server::Api*>(__delBase.get());
            return __del->push(m, __ctx, __observer);
        }
        catch(const ::IceInternal::LocalExceptionWrapper& __ex)
        {
            __handleExceptionWrapper(__delBase, __ex, __observer);
        }
        catch(const ::Ice::LocalException& __ex)
        {
            __handleException(__delBase, __ex, true, __cnt, __observer);
        }
    }
}

::Ice::AsyncResultPtr
IceProxy::sending::server::Api::begin_push(const ::sending::server::Command& m, const ::Ice::Context* __ctx, const ::IceInternal::CallbackBasePtr& __del, const ::Ice::LocalObjectPtr& __cookie)
{
    __checkAsyncTwowayOnly(__sending__server__Api__push_name);
    ::IceInternal::OutgoingAsyncPtr __result = new ::IceInternal::OutgoingAsync(this, __sending__server__Api__push_name, __del, __cookie);
    try
    {
        __result->__prepare(__sending__server__Api__push_name, ::Ice::Normal, __ctx);
        ::IceInternal::BasicStream* __os = __result->__startWriteParams(::Ice::DefaultFormat);
        __os->write(m);
        __result->__endWriteParams();
        __result->__send(true);
    }
    catch(const ::Ice::LocalException& __ex)
    {
        __result->__exceptionAsync(__ex);
    }
    return __result;
}

::sending::server::Rtn
IceProxy::sending::server::Api::end_push(const ::Ice::AsyncResultPtr& __result)
{
    ::Ice::AsyncResult::__check(__result, this, __sending__server__Api__push_name);
    ::sending::server::Rtn __ret;
    bool __ok = __result->__wait();
    try
    {
        if(!__ok)
        {
            try
            {
                __result->__throwUserException();
            }
            catch(const ::Ice::UserException& __ex)
            {
                throw ::Ice::UnknownUserException(__FILE__, __LINE__, __ex.ice_name());
            }
        }
        ::IceInternal::BasicStream* __is = __result->__startReadParams();
        __is->read(__ret);
        __result->__endReadParams();
        return __ret;
    }
    catch(const ::Ice::LocalException& ex)
    {
        __result->__getObserver().failed(ex.ice_name());
        throw;
    }
}

const ::std::string&
IceProxy::sending::server::Api::ice_staticId()
{
    return ::sending::server::Api::ice_staticId();
}

::IceInternal::Handle< ::IceDelegateM::Ice::Object>
IceProxy::sending::server::Api::__createDelegateM()
{
    return ::IceInternal::Handle< ::IceDelegateM::Ice::Object>(new ::IceDelegateM::sending::server::Api);
}

::IceInternal::Handle< ::IceDelegateD::Ice::Object>
IceProxy::sending::server::Api::__createDelegateD()
{
    return ::IceInternal::Handle< ::IceDelegateD::Ice::Object>(new ::IceDelegateD::sending::server::Api);
}

::IceProxy::Ice::Object*
IceProxy::sending::server::Api::__newInstance() const
{
    return new Api;
}

::sending::server::Rtn
IceDelegateM::sending::server::Api::push(const ::sending::server::Command& m, const ::Ice::Context* __context, ::IceInternal::InvocationObserver& __observer)
{
    ::IceInternal::Outgoing __og(__handler.get(), __sending__server__Api__push_name, ::Ice::Normal, __context, __observer);
    try
    {
        ::IceInternal::BasicStream* __os = __og.startWriteParams(::Ice::DefaultFormat);
        __os->write(m);
        __og.endWriteParams();
    }
    catch(const ::Ice::LocalException& __ex)
    {
        __og.abort(__ex);
    }
    bool __ok = __og.invoke();
    ::sending::server::Rtn __ret;
    try
    {
        if(!__ok)
        {
            try
            {
                __og.throwUserException();
            }
            catch(const ::Ice::UserException& __ex)
            {
                ::Ice::UnknownUserException __uue(__FILE__, __LINE__, __ex.ice_name());
                throw __uue;
            }
        }
        ::IceInternal::BasicStream* __is = __og.startReadParams();
        __is->read(__ret);
        __og.endReadParams();
        return __ret;
    }
    catch(const ::Ice::LocalException& __ex)
    {
        throw ::IceInternal::LocalExceptionWrapper(__ex, false);
    }
}

::sending::server::Rtn
IceDelegateD::sending::server::Api::push(const ::sending::server::Command& m, const ::Ice::Context* __context, ::IceInternal::InvocationObserver&)
{
    class _DirectI : public ::IceInternal::Direct
    {
    public:

        _DirectI(::sending::server::Rtn& __result, const ::sending::server::Command& __p_m, const ::Ice::Current& __current) : 
            ::IceInternal::Direct(__current),
            _result(__result),
            _m_m(__p_m)
        {
        }
        
        virtual ::Ice::DispatchStatus
        run(::Ice::Object* object)
        {
            ::sending::server::Api* servant = dynamic_cast< ::sending::server::Api*>(object);
            if(!servant)
            {
                throw ::Ice::OperationNotExistException(__FILE__, __LINE__, _current.id, _current.facet, _current.operation);
            }
            _result = servant->push(_m_m, _current);
            return ::Ice::DispatchOK;
        }
        
    private:
        
        ::sending::server::Rtn& _result;
        const ::sending::server::Command& _m_m;
    };
    
    ::Ice::Current __current;
    __initCurrent(__current, __sending__server__Api__push_name, ::Ice::Normal, __context);
    ::sending::server::Rtn __result;
    try
    {
        _DirectI __direct(__result, m, __current);
        try
        {
            __direct.getServant()->__collocDispatch(__direct);
        }
        catch(...)
        {
            __direct.destroy();
            throw;
        }
        __direct.destroy();
    }
    catch(const ::Ice::SystemException&)
    {
        throw;
    }
    catch(const ::IceInternal::LocalExceptionWrapper&)
    {
        throw;
    }
    catch(const ::std::exception& __ex)
    {
        ::IceInternal::LocalExceptionWrapper::throwWrapper(__ex);
    }
    catch(...)
    {
        throw ::IceInternal::LocalExceptionWrapper(::Ice::UnknownException(__FILE__, __LINE__, "unknown c++ exception"), false);
    }
    return __result;
}

::Ice::Object* sending::server::upCast(::sending::server::Api* p) { return p; }

namespace
{
const ::std::string __sending__server__Api_ids[2] =
{
    "::Ice::Object",
    "::sending::server::Api"
};

}

bool
sending::server::Api::ice_isA(const ::std::string& _s, const ::Ice::Current&) const
{
    return ::std::binary_search(__sending__server__Api_ids, __sending__server__Api_ids + 2, _s);
}

::std::vector< ::std::string>
sending::server::Api::ice_ids(const ::Ice::Current&) const
{
    return ::std::vector< ::std::string>(&__sending__server__Api_ids[0], &__sending__server__Api_ids[2]);
}

const ::std::string&
sending::server::Api::ice_id(const ::Ice::Current&) const
{
    return __sending__server__Api_ids[1];
}

const ::std::string&
sending::server::Api::ice_staticId()
{
    return __sending__server__Api_ids[1];
}

::Ice::DispatchStatus
sending::server::Api::___push(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.startReadParams();
    ::sending::server::Command m;
    __is->read(m);
    __inS.endReadParams();
    ::sending::server::Rtn __ret = push(m, __current);
    ::IceInternal::BasicStream* __os = __inS.__startWriteParams(::Ice::DefaultFormat);
    __os->write(__ret);
    __inS.__endWriteParams(true);
    return ::Ice::DispatchOK;
}

namespace
{
const ::std::string __sending__server__Api_all[] =
{
    "ice_id",
    "ice_ids",
    "ice_isA",
    "ice_ping",
    "push"
};

}

::Ice::DispatchStatus
sending::server::Api::__dispatch(::IceInternal::Incoming& in, const ::Ice::Current& current)
{
    ::std::pair< const ::std::string*, const ::std::string*> r = ::std::equal_range(__sending__server__Api_all, __sending__server__Api_all + 5, current.operation);
    if(r.first == r.second)
    {
        throw ::Ice::OperationNotExistException(__FILE__, __LINE__, current.id, current.facet, current.operation);
    }

    switch(r.first - __sending__server__Api_all)
    {
        case 0:
        {
            return ___ice_id(in, current);
        }
        case 1:
        {
            return ___ice_ids(in, current);
        }
        case 2:
        {
            return ___ice_isA(in, current);
        }
        case 3:
        {
            return ___ice_ping(in, current);
        }
        case 4:
        {
            return ___push(in, current);
        }
    }

    assert(false);
    throw ::Ice::OperationNotExistException(__FILE__, __LINE__, current.id, current.facet, current.operation);
}

void
sending::server::Api::__writeImpl(::IceInternal::BasicStream* __os) const
{
    __os->startWriteSlice(ice_staticId(), -1, true);
    __os->endWriteSlice();
}

void
sending::server::Api::__readImpl(::IceInternal::BasicStream* __is)
{
    __is->startReadSlice();
    __is->endReadSlice();
}

void 
sending::server::__patch(ApiPtr& handle, const ::Ice::ObjectPtr& v)
{
    handle = ::sending::server::ApiPtr::dynamicCast(v);
    if(v && !handle)
    {
        IceInternal::Ex::throwUOE(::sending::server::Api::ice_staticId(), v);
    }
}
