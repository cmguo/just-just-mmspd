// MmspdModule.h

#ifndef _JUST_MMSPD_MMSPD_MODULE_H_
#define _JUST_MMSPD_MMSPD_MODULE_H_

#include <framework/network/ServerManager.h>
#include <framework/string/Url.h>

namespace just
{
    namespace dispatch
    {
        class DispatchModule;
    }

    namespace mmspd
    {

        class MmspSession;
        class MmspDispatcher;

        class MmspdModule 
            : public just::common::CommonModuleBase<MmspdModule>
            , public framework::network::ServerManager<MmspSession, MmspdModule>
        {
        public:
            MmspdModule(
                util::daemon::Daemon & daemon);

            virtual ~MmspdModule();

        public:
            virtual bool startup(
                boost::system::error_code & ec);

            virtual bool shutdown(
                boost::system::error_code & ec);

        public:
            using just::common::CommonModuleBase<MmspdModule>::io_svc;

            MmspDispatcher * alloc_dispatcher(
                framework::string::Url & url, 
                boost::system::error_code & ec);

            void free_dispatcher(
                MmspDispatcher * dispatcher);

        private:
            framework::network::NetName addr_;
            just::dispatch::DispatchModule & dispatch_module_;
        };

    } // namespace mmspd
} // namespace just

#endif // _JUST_MMSPD_MMSPD_MODULE_H_
