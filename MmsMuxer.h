// MmsMuxer.h

#ifndef _PPBOX_MUX_MMS_MMS_MUXER_H_
#define _PPBOX_MUX_MMS_MMS_MUXER_H_

#include <ppbox/mux/asf/AsfMuxer.h>

namespace ppbox
{
    namespace mmspd
    {

        class MmsTransfer;

        class MmsMuxer
            : public ppbox::mux::AsfMuxer
        {
        public:
            MmsMuxer(
                boost::asio::io_service & io_svc);

            ~MmsMuxer();

        public:
            virtual void media_info(
                ppbox::mux::MediaInfo & info) const;

        private:
            virtual void add_stream(
                ppbox::mux::StreamInfo & info, 
                ppbox::mux::FilterPipe & pipe);

            virtual void file_header(
                ppbox::mux::Sample & sample);

        private:
            MmsTransfer * mms_transfer_;
        };

        PPBOX_REGISTER_MUXER("mms", MmsMuxer);

    } // namespace mmspd
} // namespace ppbox

#endif // _PPBOX_MUX_MMS_MMS_MUXER_H_
