// MmsMuxer.h

#ifndef _JUST_MUX_MMS_MMS_MUXER_H_
#define _JUST_MUX_MMS_MMS_MUXER_H_

#include <just/mux/asf/AsfMuxer.h>

namespace just
{
    namespace mmspd
    {

        class MmsTransfer;

        class MmsMuxer
            : public just::mux::AsfMuxer
        {
        public:
            MmsMuxer(
                boost::asio::io_service & io_svc);

            ~MmsMuxer();

        public:
            virtual void media_info(
                just::mux::MediaInfo & info) const;

        private:
            virtual void add_stream(
                just::mux::StreamInfo & info, 
                just::mux::FilterPipe & pipe);

            virtual void file_header(
                just::mux::Sample & sample);

        private:
            MmsTransfer * mms_transfer_;
        };

        JUST_REGISTER_MUXER("mms", MmsMuxer);

    } // namespace mmspd
} // namespace just

#endif // _JUST_MUX_MMS_MMS_MUXER_H_
