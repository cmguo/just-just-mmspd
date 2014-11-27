// MmsTransfer.h

#ifndef _JUST_MUX_MMS_MMS_TRANSFER_H_
#define _JUST_MUX_MMS_MMS_TRANSFER_H_

#include <just/mux/Transfer.h>

#include <util/protocol/mmsp/MmspData.h>

namespace just
{
    namespace mmspd
    {

        class MmsTransfer
            : public just::mux::Transfer
        {
        public:
            MmsTransfer();

            ~MmsTransfer();

        public:
            virtual void transfer(
                just::mux::Sample & sample);

        public:
            void file_header(
                just::mux::Sample & sample);

        private:
            std::vector<boost::uint8_t> header_buffer_;
            util::protocol::MmspDataHeader header_;
        };

    } // namespace mmspd
} // namespace just

#endif // _JUST_MUX_MMS_MMS_TRANSFER_H_
