// MmsMuxer.cpp

#include "just/mmspd/Common.h"
#include "just/mmspd/MmsMuxer.h"
#include "just/mmspd/MmsTransfer.h"

#include <just/mux/filter/MergeFilter.h>
using namespace just::mux;

#include <util/buffers/BuffersCopy.h>

namespace just
{
    namespace mmspd
    {

        MmsMuxer::MmsMuxer(
            boost::asio::io_service & io_svc)
            : AsfMuxer(io_svc)
            , mms_transfer_(NULL)
        {
            format("asf");
        }

        MmsMuxer::~MmsMuxer()
        {
        }

        void MmsMuxer::add_stream(
            StreamInfo & info, 
            FilterPipe & pipe)
        {
            AsfMuxer::add_stream(info, pipe);
            if (mms_transfer_ == NULL) {
                mms_transfer_ = new MmsTransfer;
            }
            pipe.insert(new MergeFilter(mms_transfer_));
        }

        void MmsMuxer::file_header(
            Sample & sample)
        {
        }

        void MmsMuxer::media_info(
            MediaInfo & info) const
        {
            Muxer::media_info(info);
            Sample tag;
            const_cast<MmsMuxer *>(this)->AsfMuxer::file_header(tag);
            mms_transfer_->file_header(tag);
            info.format_data.resize(tag.size);
            util::buffers::buffers_copy(
                boost::asio::buffer(&info.format_data.at(0), info.format_data.size()), 
                tag.data);
        }

    } // namespace mmspd
} // namespace just
