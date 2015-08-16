// MmspdModule.cpp

#include "just/mmspd/Common.h"
#include "just/mmspd/MmspdModule.h"
#include "just/mmspd/MmspDispatcher.h"
#include "just/mmspd/MmspSession.h"
#include "just/mmspd/ClassRegister.h"

#include <just/dispatch/DispatchModule.h>

#include <framework/network/TcpSocket.hpp>

namespace just
{
    namespace mmspd
    {

        MmspdModule::MmspdModule(
            util::daemon::Daemon & daemon)
            : just::common::CommonModuleBase<MmspdModule>(daemon, "MmspdModule")
            , framework::network::ServerManager<MmspSession, MmspdModule>(daemon.io_svc())
            , addr_("0.0.0.0:1755+")
            , dispatch_module_(util::daemon::use_module<just::dispatch::DispatchModule>(get_daemon()))
        {
            daemon.config().register_module("MmspdModule")
                << CONFIG_PARAM_NAME_RDWR("addr",addr_ );
        }

        MmspdModule::~MmspdModule()
        {
        }

        bool MmspdModule::startup(
            boost::system::error_code & ec)
        {
            start(addr_,ec);
            return !ec;
        }

        bool MmspdModule::shutdown(
            boost::system::error_code & ec)
        {
            stop(ec);
            return !ec;
        }

        MmspDispatcher * MmspdModule::alloc_dispatcher(
            framework::string::Url & url, 
            boost::system::error_code & ec)
        {
            dispatch_module_.normalize_url(url, ec);
            return new MmspDispatcher(*dispatch_module_.alloc_dispatcher(true));
        }

        void MmspdModule::free_dispatcher(
            MmspDispatcher * dispatcher)
        {
            dispatch_module_.free_dispatcher(dispatcher->detach());
            delete dispatcher;
        }

    } // namespace mmspd
} // namespace just
