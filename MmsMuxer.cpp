// MmsMuxer.cpp

#include "ppbox/mmspd/Common.h"
#include "ppbox/mmspd/MmsMuxer.h"
#include "ppbox/mmspd/MmsTransfer.h"

#include <ppbox/mux/filter/MergeFilter.h>
using namespace ppbox::mux;

#include <util/buffers/BuffersCopy.h>

namespace ppbox
{
    namespace mmspd
    {

        MmsMuxer::MmsMuxer()
            : mms_transfer_(NULL)
        {
            format("asf");
        }

        MmsMuxer::~MmsMuxer()
        {
            if (mms_transfer_) {
                delete mms_transfer_;
                mms_transfer_ = NULL;
            }
        }

        void MmsMuxer::add_stream(
            StreamInfo & info, 
            FilterPipe & pipe)
        {
            AsfMuxer::add_stream(info, pipe);
            if (mms_transfer_ == NULL) {
                mms_transfer_ = new MmsTransfer;
            }
            pipe.push_back(new MergeFilter(mms_transfer_));
        }

        void MmsMuxer::file_header(
            Sample & sample)
        {
        }

        void MmsMuxer::media_info(
            MediaInfo & info) const
        {
            MuxerBase::media_info(info);
            Sample tag;
            const_cast<MmsMuxer *>(this)->AsfMuxer::file_header(tag);
            mms_transfer_->file_header(tag);
            info.format_data.resize(tag.size);
            util::buffers::buffers_copy(
                boost::asio::buffer(&info.format_data.at(0), info.format_data.size()), 
                tag.data);
        }

    } // namespace mmspd
} // namespace ppbox
