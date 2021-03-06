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

#ifndef __interface4j_h__
#define __interface4j_h__

#include <Ice/ProxyF.h>
#include <Ice/ObjectF.h>
#include <Ice/Exception.h>
#include <Ice/LocalObject.h>
#include <Ice/StreamHelpers.h>
#include <Ice/Proxy.h>
#include <Ice/Object.h>
#include <Ice/Outgoing.h>
#include <Ice/OutgoingAsync.h>
#include <Ice/Incoming.h>
#include <Ice/Direct.h>
#include <IceUtil/ScopedArray.h>
#include <IceUtil/Optional.h>
#include <Ice/StreamF.h>
#include <Ice/UndefSysMacros.h>

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

namespace IceProxy
{

namespace sending
{

namespace server
{

class Api;
void __read(::IceInternal::BasicStream*, ::IceInternal::ProxyHandle< ::IceProxy::sending::server::Api>&);
::IceProxy::Ice::Object* upCast(::IceProxy::sending::server::Api*);

}

}

}

namespace sending
{

namespace server
{

class Api;
bool operator==(const Api&, const Api&);
bool operator<(const Api&, const Api&);
::Ice::Object* upCast(::sending::server::Api*);
typedef ::IceInternal::Handle< ::sending::server::Api> ApiPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::sending::server::Api> ApiPrx;
void __patch(ApiPtr&, const ::Ice::ObjectPtr&);

}

}

namespace sending
{

namespace server
{

struct Command
{
    ::std::string id;
    ::Ice::Int type;

    bool operator==(const Command& __rhs) const
    {
        if(this == &__rhs)
        {
            return true;
        }
        if(id != __rhs.id)
        {
            return false;
        }
        if(type != __rhs.type)
        {
            return false;
        }
        return true;
    }

    bool operator<(const Command& __rhs) const
    {
        if(this == &__rhs)
        {
            return false;
        }
        if(id < __rhs.id)
        {
            return true;
        }
        else if(__rhs.id < id)
        {
            return false;
        }
        if(type < __rhs.type)
        {
            return true;
        }
        else if(__rhs.type < type)
        {
            return false;
        }
        return false;
    }

    bool operator!=(const Command& __rhs) const
    {
        return !operator==(__rhs);
    }
    bool operator<=(const Command& __rhs) const
    {
        return operator<(__rhs) || operator==(__rhs);
    }
    bool operator>(const Command& __rhs) const
    {
        return !operator<(__rhs) && !operator==(__rhs);
    }
    bool operator>=(const Command& __rhs) const
    {
        return !operator<(__rhs);
    }
};

struct Rtn
{
    ::Ice::Int e;
    ::std::string str;

    bool operator==(const Rtn& __rhs) const
    {
        if(this == &__rhs)
        {
            return true;
        }
        if(e != __rhs.e)
        {
            return false;
        }
        if(str != __rhs.str)
        {
            return false;
        }
        return true;
    }

    bool operator<(const Rtn& __rhs) const
    {
        if(this == &__rhs)
        {
            return false;
        }
        if(e < __rhs.e)
        {
            return true;
        }
        else if(__rhs.e < e)
        {
            return false;
        }
        if(str < __rhs.str)
        {
            return true;
        }
        else if(__rhs.str < str)
        {
            return false;
        }
        return false;
    }

    bool operator!=(const Rtn& __rhs) const
    {
        return !operator==(__rhs);
    }
    bool operator<=(const Rtn& __rhs) const
    {
        return operator<(__rhs) || operator==(__rhs);
    }
    bool operator>(const Rtn& __rhs) const
    {
        return !operator<(__rhs) && !operator==(__rhs);
    }
    bool operator>=(const Rtn& __rhs) const
    {
        return !operator<(__rhs);
    }
};

}

}

namespace Ice
{
template<>
struct StreamableTraits< ::sending::server::Command>
{
    static const StreamHelperCategory helper = StreamHelperCategoryStruct;
    static const int minWireSize = 5;
    static const bool fixedLength = false;
};

template<class S>
struct StreamWriter< ::sending::server::Command, S>
{
    static void write(S* __os, const ::sending::server::Command& v)
    {
        __os->write(v.id);
        __os->write(v.type);
    }
};

template<class S>
struct StreamReader< ::sending::server::Command, S>
{
    static void read(S* __is, ::sending::server::Command& v)
    {
        __is->read(v.id);
        __is->read(v.type);
    }
};

template<>
struct StreamableTraits< ::sending::server::Rtn>
{
    static const StreamHelperCategory helper = StreamHelperCategoryStruct;
    static const int minWireSize = 5;
    static const bool fixedLength = false;
};

template<class S>
struct StreamWriter< ::sending::server::Rtn, S>
{
    static void write(S* __os, const ::sending::server::Rtn& v)
    {
        __os->write(v.e);
        __os->write(v.str);
    }
};

template<class S>
struct StreamReader< ::sending::server::Rtn, S>
{
    static void read(S* __is, ::sending::server::Rtn& v)
    {
        __is->read(v.e);
        __is->read(v.str);
    }
};

}

namespace sending
{

namespace server
{

class Callback_Api_push_Base : virtual public ::IceInternal::CallbackBase { };
typedef ::IceUtil::Handle< Callback_Api_push_Base> Callback_Api_pushPtr;

}

}

namespace IceProxy
{

namespace sending
{

namespace server
{

class Api : virtual public ::IceProxy::Ice::Object
{
public:

    ::sending::server::Rtn push(const ::sending::server::Command& m)
    {
        return push(m, 0);
    }
    ::sending::server::Rtn push(const ::sending::server::Command& m, const ::Ice::Context& __ctx)
    {
        return push(m, &__ctx);
    }
#ifdef ICE_CPP11
    ::Ice::AsyncResultPtr
    begin_push(const ::sending::server::Command& m, const ::IceInternal::Function<void (const ::sending::server::Rtn&)>& response, const ::IceInternal::Function<void (const ::Ice::Exception&)>& exception = ::IceInternal::Function<void (const ::Ice::Exception&)>(), const ::IceInternal::Function<void (bool)>& sent = ::IceInternal::Function<void (bool)>())
    {
        return __begin_push(m, 0, response, exception, sent);
    }
    ::Ice::AsyncResultPtr
    begin_push(const ::sending::server::Command& m, const ::IceInternal::Function<void (const ::Ice::AsyncResultPtr&)>& completed, const ::IceInternal::Function<void (const ::Ice::AsyncResultPtr&)>& sent = ::IceInternal::Function<void (const ::Ice::AsyncResultPtr&)>())
    {
        return begin_push(m, 0, ::Ice::newCallback(completed, sent), 0);
    }
    ::Ice::AsyncResultPtr
    begin_push(const ::sending::server::Command& m, const ::Ice::Context& ctx, const ::IceInternal::Function<void (const ::sending::server::Rtn&)>& response, const ::IceInternal::Function<void (const ::Ice::Exception&)>& exception = ::IceInternal::Function<void (const ::Ice::Exception&)>(), const ::IceInternal::Function<void (bool)>& sent = ::IceInternal::Function<void (bool)>())
    {
        return __begin_push(m, &ctx, response, exception, sent);
    }
    ::Ice::AsyncResultPtr
    begin_push(const ::sending::server::Command& m, const ::Ice::Context& ctx, const ::IceInternal::Function<void (const ::Ice::AsyncResultPtr&)>& completed, const ::IceInternal::Function<void (const ::Ice::AsyncResultPtr&)>& sent = ::IceInternal::Function<void (const ::Ice::AsyncResultPtr&)>())
    {
        return begin_push(m, &ctx, ::Ice::newCallback(completed, sent));
    }
    
private:

    ::Ice::AsyncResultPtr __begin_push(const ::sending::server::Command& m, const ::Ice::Context* ctx, const ::IceInternal::Function<void (const ::sending::server::Rtn&)>& response, const ::IceInternal::Function<void (const ::Ice::Exception&)>& exception, const ::IceInternal::Function<void (bool)>& sent)
    {
        class Cpp11CB : public ::IceInternal::Cpp11FnCallbackNC
        {
        public:

            Cpp11CB(const ::std::function<void (const ::sending::server::Rtn&)>& responseFunc, const ::std::function<void (const ::Ice::Exception&)>& exceptionFunc, const ::std::function<void (bool)>& sentFunc) :
                ::IceInternal::Cpp11FnCallbackNC(exceptionFunc, sentFunc),
                _response(responseFunc)
            {
                CallbackBase::checkCallback(true, responseFunc || exceptionFunc != nullptr);
            }

            virtual void __completed(const ::Ice::AsyncResultPtr& __result) const
            {
                ::sending::server::ApiPrx __proxy = ::sending::server::ApiPrx::uncheckedCast(__result->getProxy());
                ::sending::server::Rtn __ret;
                try
                {
                    __ret = __proxy->end_push(__result);
                }
                catch(::Ice::Exception& ex)
                {
                    Cpp11FnCallbackNC::__exception(__result, ex);
                    return;
                }
                if(_response != nullptr)
                {
                    _response(__ret);
                }
            }
        
        private:
            
            ::std::function<void (const ::sending::server::Rtn&)> _response;
        };
        return begin_push(m, ctx, new Cpp11CB(response, exception, sent));
    }
    
public:
#endif

    ::Ice::AsyncResultPtr begin_push(const ::sending::server::Command& m)
    {
        return begin_push(m, 0, ::IceInternal::__dummyCallback, 0);
    }

    ::Ice::AsyncResultPtr begin_push(const ::sending::server::Command& m, const ::Ice::Context& __ctx)
    {
        return begin_push(m, &__ctx, ::IceInternal::__dummyCallback, 0);
    }

    ::Ice::AsyncResultPtr begin_push(const ::sending::server::Command& m, const ::Ice::CallbackPtr& __del, const ::Ice::LocalObjectPtr& __cookie = 0)
    {
        return begin_push(m, 0, __del, __cookie);
    }

    ::Ice::AsyncResultPtr begin_push(const ::sending::server::Command& m, const ::Ice::Context& __ctx, const ::Ice::CallbackPtr& __del, const ::Ice::LocalObjectPtr& __cookie = 0)
    {
        return begin_push(m, &__ctx, __del, __cookie);
    }

    ::Ice::AsyncResultPtr begin_push(const ::sending::server::Command& m, const ::sending::server::Callback_Api_pushPtr& __del, const ::Ice::LocalObjectPtr& __cookie = 0)
    {
        return begin_push(m, 0, __del, __cookie);
    }

    ::Ice::AsyncResultPtr begin_push(const ::sending::server::Command& m, const ::Ice::Context& __ctx, const ::sending::server::Callback_Api_pushPtr& __del, const ::Ice::LocalObjectPtr& __cookie = 0)
    {
        return begin_push(m, &__ctx, __del, __cookie);
    }

    ::sending::server::Rtn end_push(const ::Ice::AsyncResultPtr&);
    
private:

    ::sending::server::Rtn push(const ::sending::server::Command&, const ::Ice::Context*);
    ::Ice::AsyncResultPtr begin_push(const ::sending::server::Command&, const ::Ice::Context*, const ::IceInternal::CallbackBasePtr&, const ::Ice::LocalObjectPtr& __cookie = 0);
    
public:
    
    ::IceInternal::ProxyHandle<Api> ice_context(const ::Ice::Context& __context) const
    {
        return dynamic_cast<Api*>(::IceProxy::Ice::Object::ice_context(__context).get());
    }
    
    ::IceInternal::ProxyHandle<Api> ice_adapterId(const ::std::string& __id) const
    {
        return dynamic_cast<Api*>(::IceProxy::Ice::Object::ice_adapterId(__id).get());
    }
    
    ::IceInternal::ProxyHandle<Api> ice_endpoints(const ::Ice::EndpointSeq& __endpoints) const
    {
        return dynamic_cast<Api*>(::IceProxy::Ice::Object::ice_endpoints(__endpoints).get());
    }
    
    ::IceInternal::ProxyHandle<Api> ice_locatorCacheTimeout(int __timeout) const
    {
        return dynamic_cast<Api*>(::IceProxy::Ice::Object::ice_locatorCacheTimeout(__timeout).get());
    }
    
    ::IceInternal::ProxyHandle<Api> ice_connectionCached(bool __cached) const
    {
        return dynamic_cast<Api*>(::IceProxy::Ice::Object::ice_connectionCached(__cached).get());
    }
    
    ::IceInternal::ProxyHandle<Api> ice_endpointSelection(::Ice::EndpointSelectionType __est) const
    {
        return dynamic_cast<Api*>(::IceProxy::Ice::Object::ice_endpointSelection(__est).get());
    }
    
    ::IceInternal::ProxyHandle<Api> ice_secure(bool __secure) const
    {
        return dynamic_cast<Api*>(::IceProxy::Ice::Object::ice_secure(__secure).get());
    }
    
    ::IceInternal::ProxyHandle<Api> ice_preferSecure(bool __preferSecure) const
    {
        return dynamic_cast<Api*>(::IceProxy::Ice::Object::ice_preferSecure(__preferSecure).get());
    }
    
    ::IceInternal::ProxyHandle<Api> ice_router(const ::Ice::RouterPrx& __router) const
    {
        return dynamic_cast<Api*>(::IceProxy::Ice::Object::ice_router(__router).get());
    }
    
    ::IceInternal::ProxyHandle<Api> ice_locator(const ::Ice::LocatorPrx& __locator) const
    {
        return dynamic_cast<Api*>(::IceProxy::Ice::Object::ice_locator(__locator).get());
    }
    
    ::IceInternal::ProxyHandle<Api> ice_collocationOptimized(bool __co) const
    {
        return dynamic_cast<Api*>(::IceProxy::Ice::Object::ice_collocationOptimized(__co).get());
    }
    
    ::IceInternal::ProxyHandle<Api> ice_twoway() const
    {
        return dynamic_cast<Api*>(::IceProxy::Ice::Object::ice_twoway().get());
    }
    
    ::IceInternal::ProxyHandle<Api> ice_oneway() const
    {
        return dynamic_cast<Api*>(::IceProxy::Ice::Object::ice_oneway().get());
    }
    
    ::IceInternal::ProxyHandle<Api> ice_batchOneway() const
    {
        return dynamic_cast<Api*>(::IceProxy::Ice::Object::ice_batchOneway().get());
    }
    
    ::IceInternal::ProxyHandle<Api> ice_datagram() const
    {
        return dynamic_cast<Api*>(::IceProxy::Ice::Object::ice_datagram().get());
    }
    
    ::IceInternal::ProxyHandle<Api> ice_batchDatagram() const
    {
        return dynamic_cast<Api*>(::IceProxy::Ice::Object::ice_batchDatagram().get());
    }
    
    ::IceInternal::ProxyHandle<Api> ice_compress(bool __compress) const
    {
        return dynamic_cast<Api*>(::IceProxy::Ice::Object::ice_compress(__compress).get());
    }
    
    ::IceInternal::ProxyHandle<Api> ice_timeout(int __timeout) const
    {
        return dynamic_cast<Api*>(::IceProxy::Ice::Object::ice_timeout(__timeout).get());
    }
    
    ::IceInternal::ProxyHandle<Api> ice_connectionId(const ::std::string& __id) const
    {
        return dynamic_cast<Api*>(::IceProxy::Ice::Object::ice_connectionId(__id).get());
    }
    
    ::IceInternal::ProxyHandle<Api> ice_encodingVersion(const ::Ice::EncodingVersion& __v) const
    {
        return dynamic_cast<Api*>(::IceProxy::Ice::Object::ice_encodingVersion(__v).get());
    }
    
    static const ::std::string& ice_staticId();

private: 

    virtual ::IceInternal::Handle< ::IceDelegateM::Ice::Object> __createDelegateM();
    virtual ::IceInternal::Handle< ::IceDelegateD::Ice::Object> __createDelegateD();
    virtual ::IceProxy::Ice::Object* __newInstance() const;
};

}

}

}

namespace IceDelegate
{

namespace sending
{

namespace server
{

class Api : virtual public ::IceDelegate::Ice::Object
{
public:

    virtual ::sending::server::Rtn push(const ::sending::server::Command&, const ::Ice::Context*, ::IceInternal::InvocationObserver&) = 0;
};

}

}

}

namespace IceDelegateM
{

namespace sending
{

namespace server
{

class Api : virtual public ::IceDelegate::sending::server::Api,
            virtual public ::IceDelegateM::Ice::Object
{
public:

    virtual ::sending::server::Rtn push(const ::sending::server::Command&, const ::Ice::Context*, ::IceInternal::InvocationObserver&);
};

}

}

}

namespace IceDelegateD
{

namespace sending
{

namespace server
{

class Api : virtual public ::IceDelegate::sending::server::Api,
            virtual public ::IceDelegateD::Ice::Object
{
public:

    virtual ::sending::server::Rtn push(const ::sending::server::Command&, const ::Ice::Context*, ::IceInternal::InvocationObserver&);
};

}

}

}

namespace sending
{

namespace server
{

class Api : virtual public ::Ice::Object
{
public:

    typedef ApiPrx ProxyType;
    typedef ApiPtr PointerType;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual ::sending::server::Rtn push(const ::sending::server::Command&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___push(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);

protected:
    virtual void __writeImpl(::IceInternal::BasicStream*) const;
    virtual void __readImpl(::IceInternal::BasicStream*);
    #ifdef __SUNPRO_CC
    using ::Ice::Object::__writeImpl;
    using ::Ice::Object::__readImpl;
    #endif
};

inline bool operator==(const Api& l, const Api& r)
{
    return static_cast<const ::Ice::Object&>(l) == static_cast<const ::Ice::Object&>(r);
}

inline bool operator<(const Api& l, const Api& r)
{
    return static_cast<const ::Ice::Object&>(l) < static_cast<const ::Ice::Object&>(r);
}

}

}

namespace sending
{

namespace server
{

template<class T>
class CallbackNC_Api_push : public Callback_Api_push_Base, public ::IceInternal::TwowayCallbackNC<T>
{
public:

    typedef IceUtil::Handle<T> TPtr;

    typedef void (T::*Exception)(const ::Ice::Exception&);
    typedef void (T::*Sent)(bool);
    typedef void (T::*Response)(const ::sending::server::Rtn&);

    CallbackNC_Api_push(const TPtr& obj, Response cb, Exception excb, Sent sentcb)
        : ::IceInternal::TwowayCallbackNC<T>(obj, cb != 0, excb, sentcb), response(cb)
    {
    }

    virtual void __completed(const ::Ice::AsyncResultPtr& __result) const
    {
        ::sending::server::ApiPrx __proxy = ::sending::server::ApiPrx::uncheckedCast(__result->getProxy());
        ::sending::server::Rtn __ret;
        try
        {
            __ret = __proxy->end_push(__result);
        }
        catch(::Ice::Exception& ex)
        {
            ::IceInternal::CallbackNC<T>::__exception(__result, ex);
            return;
        }
        if(response)
        {
            (::IceInternal::CallbackNC<T>::callback.get()->*response)(__ret);
        }
    }

    Response response;
};

template<class T> Callback_Api_pushPtr
newCallback_Api_push(const IceUtil::Handle<T>& instance, void (T::*cb)(const ::sending::server::Rtn&), void (T::*excb)(const ::Ice::Exception&), void (T::*sentcb)(bool) = 0)
{
    return new CallbackNC_Api_push<T>(instance, cb, excb, sentcb);
}

template<class T> Callback_Api_pushPtr
newCallback_Api_push(T* instance, void (T::*cb)(const ::sending::server::Rtn&), void (T::*excb)(const ::Ice::Exception&), void (T::*sentcb)(bool) = 0)
{
    return new CallbackNC_Api_push<T>(instance, cb, excb, sentcb);
}

template<class T, typename CT>
class Callback_Api_push : public Callback_Api_push_Base, public ::IceInternal::TwowayCallback<T, CT>
{
public:

    typedef IceUtil::Handle<T> TPtr;

    typedef void (T::*Exception)(const ::Ice::Exception& , const CT&);
    typedef void (T::*Sent)(bool , const CT&);
    typedef void (T::*Response)(const ::sending::server::Rtn&, const CT&);

    Callback_Api_push(const TPtr& obj, Response cb, Exception excb, Sent sentcb)
        : ::IceInternal::TwowayCallback<T, CT>(obj, cb != 0, excb, sentcb), response(cb)
    {
    }

    virtual void __completed(const ::Ice::AsyncResultPtr& __result) const
    {
        ::sending::server::ApiPrx __proxy = ::sending::server::ApiPrx::uncheckedCast(__result->getProxy());
        ::sending::server::Rtn __ret;
        try
        {
            __ret = __proxy->end_push(__result);
        }
        catch(::Ice::Exception& ex)
        {
            ::IceInternal::Callback<T, CT>::__exception(__result, ex);
            return;
        }
        if(response)
        {
            (::IceInternal::Callback<T, CT>::callback.get()->*response)(__ret, CT::dynamicCast(__result->getCookie()));
        }
    }

    Response response;
};

template<class T, typename CT> Callback_Api_pushPtr
newCallback_Api_push(const IceUtil::Handle<T>& instance, void (T::*cb)(const ::sending::server::Rtn&, const CT&), void (T::*excb)(const ::Ice::Exception&, const CT&), void (T::*sentcb)(bool, const CT&) = 0)
{
    return new Callback_Api_push<T, CT>(instance, cb, excb, sentcb);
}

template<class T, typename CT> Callback_Api_pushPtr
newCallback_Api_push(T* instance, void (T::*cb)(const ::sending::server::Rtn&, const CT&), void (T::*excb)(const ::Ice::Exception&, const CT&), void (T::*sentcb)(bool, const CT&) = 0)
{
    return new Callback_Api_push<T, CT>(instance, cb, excb, sentcb);
}

}

}

#endif
