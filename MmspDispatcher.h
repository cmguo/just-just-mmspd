// RtpDispatcher.h

#ifndef _JUST_MMSPD_MMSP_DISPATCHER_H_
#define _JUST_MMSPD_MMSP_DISPATCHER_H_

#include <just/dispatch/CustomDispatcher.h>

#include <boost/asio/ip/tcp.hpp>

#include <boost/asio/streambuf.hpp>

namespace util
{
    namespace protocol
    {
        struct MmspDataStartPlaying;
        struct MmspDataReportOpenFile;
    }
}

namespace just
{
    namespace mmspd
    {  

        class MmspDispatcher 
            : public just::dispatch::CustomDispatcher
        {
        public:

            MmspDispatcher(
                just::dispatch::DispatcherBase & dispatcher);

            ~MmspDispatcher();

        public:
            void async_open(
                framework::string::Url & url, 
                util::protocol::MmspDataReportOpenFile & rsp, 
                just::dispatch::response_t  const & resp);

            bool setup(
                boost::asio::ip::tcp::socket & mmsp_sock, 
                std::string const & transport, 
                boost::system::error_code & ec);

            bool write_header(
                boost::asio::ip::tcp::socket & mmsp_sock, 
                boost::system::error_code & ec);

            void async_play(
                util::protocol::MmspDataStartPlaying & req, 
                just::dispatch::response_t const & seek_resp, 
                just::dispatch::response_t const & resp);

            bool teardown(
                boost::system::error_code & ec);

        private:
            void handle_open(
                util::protocol::MmspDataReportOpenFile & rsp, 
                just::dispatch::response_t  const & resp, 
                boost::system::error_code ec);

            void handle_seek(
                std::string & rtp_info, 
                just::dispatch::SeekRange & range, 
                just::dispatch::response_t const & resp, 
                boost::system::error_code ec);

        private:
            just::avbase::MediaInfo media_info_;
            util::stream::Sink * sink_;
        };

    } // namespace mmspd
} // namespace just

#endif // _JUST_MMSPD_RTP_DISPATCHER_H_
