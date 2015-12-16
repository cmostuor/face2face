#include "x264thread.h"
#include <QVideoFrame>
#define RGB2Y(R, G, B) CLIP(( (  66 * (R) + 129 * (G) +  25 * (B) + 128) >> 8) +  16)
#define RGB2U(R, G, B) CLIP(( ( -38 * (R) -  74 * (G) + 112 * (B) + 128) >> 8) + 128)
#define RGB2V(R, G, B) CLIP(( ( 112 * (R) -  94 * (G) -  18 * (B) + 128) >> 8) + 128)
#include <stdint.h>
#include <stdio.h>
#include <x264.h>
#include <iostream>

x264Thread::x264Thread(QGLWidget* window)
{
    this->window=window;







    //    scheduler = BasicTaskScheduler::createNew();
    //    env = BasicUsageEnvironment::createNew(*scheduler);

    //    authDB = NULL;
    //    RTSPServer* rtspServer;
    //    portNumBits rtspServerPortNum = 554;
    //    rtspServer = DynamicRTSPServer::createNew(*env, rtspServerPortNum, authDB);
    //    if (rtspServer == NULL) {
    //        rtspServerPortNum = 8554;
    //        rtspServer = DynamicRTSPServer::createNew(*env, rtspServerPortNum, authDB);
    //    }
    //    if (rtspServer == NULL) {
    //        *env << "Failed to create RTSP server: " << env->getResultMsg() << "\n";
    //        exit(1);
    //    }

    //    *env << "LIVE555 Media Server\n";
    //    *env << "\tversion " << MEDIA_SERVER_VERSION_STRING
    //         << " (LIVE555 Streaming Media library version "
    //         << LIVEMEDIA_LIBRARY_VERSION_STRING << ").\n";
    //    if (rtspServer->setUpTunnelingOverHTTP(80) || rtspServer->setUpTunnelingOverHTTP(8000) || rtspServer->setUpTunnelingOverHTTP(8080)) {
    //        *env << "(We use port " << rtspServer->httpServerPortNum() << " for optional RTSP-over-HTTP tunneling, or for HTTP live streaming (for indexed Transport Stream files only).)\n";
    //    } else {
    //        *env << "(RTSP-over-HTTP tunneling is not available.)\n";
    //    }

    //    env->taskScheduler().doEventLoop(); // does not return

    //    //    cameraTimer = new QTimer();
    //    //    cameraTimer ->setInterval(64);
    //    //    QObject::connect(cameraTimer, SIGNAL(timeout()), this, SLOT(captureImage()));
    //    //    //start capturing
    //    //    cameraTimer -> start();
}

void x264Thread::streamImage(){
    QImage frameBuffer=window->grabFrameBuffer();
    QVideoFrame image=QVideoFrame(frameBuffer);
    int width=frameBuffer.width();
    int height=frameBuffer.height();
    x264_param_t param;
    x264_picture_t pic;
    x264_picture_t pic_out;
    x264_t *h;
    int i_frame = 0;
    int i_frame_size;
    x264_nal_t *nal;
    int i_nal;

    if( x264_param_default_preset( &param, "medium", NULL ) < 0 ){
        std::cout<<"x264: failed setting up derfault params"<<std::endl;
        return;
    }
    param.i_csp = X264_CSP_I420;
    param.i_width  = width;
    param.i_height = height;
    param.b_vfr_input = 0;
    param.b_repeat_headers = 1;
    param.b_annexb = 1;

    if( x264_param_apply_profile( &param, "high" ) < 0 ){
        std::cout<<"x264: failed changing params to high"<<std::endl;
        return;
    }
    if( x264_picture_alloc( &pic, param.i_csp, param.i_width, param.i_height ) < 0 ){
        std::cout<<"x264: failed picture alloc"<<std::endl;
        return;
    }
    h = x264_encoder_open( &param );
    if( !h ){
        std::cout<<"x264: failed opening encoder"<<std::endl;
        return;
    }
    int luma_size = width * height;
    int chroma_size = luma_size / 4;

    for( ;; i_frame++ )
    {
        /* Read input frame */
        if( fread( pic.img.plane[0], 1, luma_size, stdin ) != luma_size )
            break;
        if( fread( pic.img.plane[1], 1, chroma_size, stdin ) != chroma_size )
            break;
        if( fread( pic.img.plane[2], 1, chroma_size, stdin ) != chroma_size )
            break;

        pic.i_pts = i_frame;
        i_frame_size = x264_encoder_encode( h, &nal, &i_nal, &pic, &pic_out );
        if( i_frame_size < 0 ){
            x264_encoder_close( h );
            x264_picture_clean( &pic );
            return;
        }

        else if( i_frame_size )
        {
            if( !fwrite( nal->p_payload, i_frame_size, 1, stdout ) ){
                x264_encoder_close( h );
                x264_picture_clean( &pic );
                return;
            }
        }
    }

    x264_encoder_close( h );
    x264_picture_clean( &pic );
}
