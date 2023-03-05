#ifndef M64P_ENCODER_FFM_ENCODER_HPP
#define M64P_ENCODER_FFM_ENCODER_HPP


#include <exception>
extern "C" {
    #include "api/m64p_types.h"
    #include <libavcodec/avcodec.h>
    #include <libavformat/avformat.h>
    #include <libavutil/avutil.h>
    #include <libavutil/audio_fifo.h>
    #include <libswscale/swscale.h>
    #include <libswresample/swresample.h>
}

namespace m64p {
    class unsupported_error : std::exception {
    public:
        using std::exception::exception;
    };
    
    class ffm_encoder {
    public:
        ffm_encoder(const char* path, m64p_encoder_format fmt);
        
        ~ffm_encoder();
        
        void push_video();
        
        void set_sample_rate(unsigned int rate);
        
        void push_audio(void* samples, size_t len);
        
        void finish(bool discard);
    private:
        AVFormatContext* m_fmt_ctx;
        
        AVStream* m_vstream;
        int64_t m_vpts;
        AVCodecContext* m_vcodec_ctx;
        const AVCodec* m_vcodec;
        AVPacket* m_vpacket;
        AVFrame* m_vframe1;
        AVFrame* m_vframe2;
        SwsContext* m_sws;
        
        AVStream* m_astream;
        int64_t m_apts;
        AVCodecContext* m_acodec_ctx;
        const AVCodec* m_acodec;
        AVPacket* m_apacket;
        AVFrame* m_aframe1;
        AVFrame* m_aframe2;
        SwrContext* m_swr;
        int m_aframe_size;
        
        void video_init();
        void audio_init();
    };
}

extern "C" struct encoder_backend_interface g_iffmpeg_encoder_backend;

#endif