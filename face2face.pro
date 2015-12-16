#-------------------------------------------------
#
# Project created by QtCreator 2015-11-10T16:22:22
#
#-------------------------------------------------

QT       += core network opengl widgets gui multimedia
CONFIG += debug console
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = face2face
TEMPLATE = app
INCLUDEPATH += ./IL \
    ./sdl \
    ./TUIO \
    ./oscpack \
    ./GeneratedFiles \
    . \
    ./GeneratedFiles/Debug \
    ./libs \
    .C:\opencv3-mingw\install\include


INCLUDEPATH += C:/opencv3-mingw/install/x86/mingw \
            C:/opencv3-mingw/install/include \
            C:\Users\Paul\Documents\Bachelor\QT\face2face\x264
DEPENDPATH += C:/opencv3-mingw/install/x86/mingw \
            C:/opencv3-mingw/install/include

LIBS +=-L./libs \
    -L./dlls \
    -lopengl32 \
    -lDevIL \
    -lILU \
    -lILUT \
    -lglu32 \
    -lassimp \
    -lws2_32 \
    -lwinmm \
    -lx264
#    -lBasicUsageEnvironment \
#    -lgroupsock \
#    -lliveMedia \
#    -lUsageEnvironment
LIBS +=-LC:\opencv3-mingw\install\x86\mingw\lib \
       -LC:\opencv3-mingw\install\x86\mingw\bin \
    -lopencv_core300 \
    -lopencv_highgui300 \
    -lopencv_videoio300
#    -lopencv_objdetect2411 \
#    -lopencv_nonfree2411 \
#    -lopencv_imgproc2411 \
 #   -lopencv_features2d2411 \
 #   -lopencv_contrib2411 \
  #  -lopencv_legacy2411 \
 #   -lopencv_ml2411 \
  # -lopencv_calib3d2411


SOURCES += main.cpp\
        mainwindow.cpp \
    AABB.cpp \
    BVH.cpp \
    Camera.cpp \
    Connection.cpp \
    DevILImage.cpp \
    EscapiThread.cpp \
    HitRec.cpp \
    Material.cpp \
    Model.cpp \
    ModelController.cpp \
    ModellMessage.cpp \
    ModelManager.cpp \
    ModelViewer5.cpp \
    Node.cpp \
    OpenCvThread.cpp \
    qtmodelviewer5.cpp \
    Ray.cpp \
    TraversalStack.cpp \
    Triangle.cpp \
    TuioDump.cpp \
    tuiothread.cpp \
    assimp/color4.inl \
    assimp/material.inl \
    assimp/matrix3x3.inl \
    assimp/matrix4x4.inl \
    assimp/quaternion.inl \
    assimp/vector2.inl \
    assimp/vector3.inl \
    oscpack/osc/OscOutboundPacketStream.cpp \
    oscpack/osc/OscPrintReceivedElements.cpp \
    oscpack/osc/OscReceivedElements.cpp \
    oscpack/osc/OscTypes.cpp \
    oscpack/ip/IpEndpointName.cpp \
    oscpack/ip/win32/NetworkingUtils.cpp \
    oscpack/ip/win32/UdpSocket.cpp \
    TUIO/TuioClient.cpp \
    TUIO/TuioServer.cpp \
    TUIO/TuioTime.cpp \
    escapi/escapi.cpp \
    x264thread.cpp \


HEADERS  += mainwindow.h \
    AABB.h \
    BVH.h \
    Camera.h \
    Connection.h \
    DevILImage.h \
    EscapiThread.h \
    HitRec.h \
    Material.h \
    Model.h \
    ModelController.h \
    ModelData.h \
    ModellMessage.h \
    ModelManager.h \
    ModelViewer5.h \
    Node.h \
    OpenCvThread.h \
    qtmodelviewer5.h \
    Ray.h \
    resource.h \
    TraversalStack.h \
    Triangle.h \
    TuioDump.h \
    TuioThread.h \
    assimp/ai_assert.h \
    assimp/anim.h \
    assimp/camera.h \
    assimp/Compiler/poppack1.h \
    assimp/Compiler/pushpack1.h \
#    opencv2/opencv.hpp \
#    opencv2/opencv_modules.hpp \
#    opencv2/core/core.hpp \
#    opencv2/core/core_c.h \
#    opencv2/core/cuda_devptrs.hpp \
#    opencv2/core/devmem2d.hpp \
#    opencv2/core/eigen.hpp \
#    opencv2/core/gpumat.hpp \
#    opencv2/core/internal.hpp \
#    opencv2/core/mat.hpp \
#    opencv2/core/opengl_interop.hpp \
#    opencv2/core/opengl_interop_deprecated.hpp \
#    opencv2/core/operations.hpp \
#    opencv2/core/types_c.h \
#    opencv2/core/version.hpp \
#    opencv2/core/wimage.hpp \
#    opencv2/features2d/features2d.hpp \
#    opencv2/flann/all_indices.h \
#    opencv2/flann/allocator.h \
#    opencv2/flann/any.h \
#    opencv2/flann/autotuned_index.h \
#    opencv2/flann/composite_index.h \
#    opencv2/flann/config.h \
#    opencv2/flann/defines.h \
#    opencv2/flann/dist.h \
#    opencv2/flann/dummy.h \
#    opencv2/flann/dynamic_bitset.h \
#    opencv2/flann/flann.hpp \
#    opencv2/flann/flann_base.hpp \
#    opencv2/flann/general.h \
#    opencv2/flann/ground_truth.h \
#    opencv2/flann/hdf5.h \
#    opencv2/flann/heap.h \
#    opencv2/flann/hierarchical_clustering_index.h \
#    opencv2/flann/index_testing.h \
#    opencv2/flann/kdtree_index.h \
#    opencv2/flann/kdtree_single_index.h \
#    opencv2/flann/kmeans_index.h \
#    opencv2/flann/linear_index.h \
#    opencv2/flann/logger.h \
#    opencv2/flann/lsh_index.h \
#    opencv2/flann/lsh_table.h \
#    opencv2/flann/matrix.h \
#    opencv2/flann/miniflann.hpp \
#    opencv2/flann/nn_index.h \
#    opencv2/flann/object_factory.h \
#    opencv2/flann/params.h \
#    opencv2/flann/random.h \
#    opencv2/flann/result_set.h \
#    opencv2/flann/sampling.h \
#    opencv2/flann/saving.h \
#    opencv2/flann/simplex_downhill.h \
#    opencv2/flann/timer.h \
#    opencv2/gpu/devmem2d.hpp \
#    opencv2/gpu/gpu.hpp \
#    opencv2/gpu/gpumat.hpp \
#    opencv2/gpu/stream_accessor.hpp \
#    opencv2/gpu/device/block.hpp \
#    opencv2/gpu/device/border_interpolate.hpp \
#    opencv2/gpu/device/color.hpp \
#    opencv2/gpu/device/common.hpp \
#    opencv2/gpu/device/datamov_utils.hpp \
#    opencv2/gpu/device/dynamic_smem.hpp \
#    opencv2/gpu/device/emulation.hpp \
#    opencv2/gpu/device/filters.hpp \
#    opencv2/gpu/device/funcattrib.hpp \
#    opencv2/gpu/device/functional.hpp \
#    opencv2/gpu/device/limits.hpp \
#    opencv2/gpu/device/reduce.hpp \
#    opencv2/gpu/device/saturate_cast.hpp \
#    opencv2/gpu/device/scan.hpp \
#    opencv2/gpu/device/simd_functions.hpp \
#    opencv2/gpu/device/static_check.hpp \
#    opencv2/gpu/device/transform.hpp \
#    opencv2/gpu/device/type_traits.hpp \
#    opencv2/gpu/device/utility.hpp \
#    opencv2/gpu/device/vec_distance.hpp \
#    opencv2/gpu/device/vec_math.hpp \
#    opencv2/gpu/device/vec_traits.hpp \
#    opencv2/gpu/device/warp.hpp \
#    opencv2/gpu/device/warp_reduce.hpp \
#    opencv2/gpu/device/warp_shuffle.hpp \
#    opencv2/gpu/device/detail/color_detail.hpp \
#    opencv2/gpu/device/detail/reduce.hpp \
#    opencv2/gpu/device/detail/reduce_key_val.hpp \
#    opencv2/gpu/device/detail/transform_detail.hpp \
#    opencv2/gpu/device/detail/type_traits_detail.hpp \
#    opencv2/gpu/device/detail/vec_distance_detail.hpp \
#    opencv2/highgui/cap_ios.h \
#    opencv2/highgui/highgui.hpp \
#    opencv2/highgui/highgui_c.h \
#    opencv2/highgui/ios.h \
#    opencv2/imgproc/imgproc.hpp \
#    opencv2/imgproc/imgproc_c.h \
#    opencv2/imgproc/types_c.h \
#    opencv2/legacy/blobtrack.hpp \
#    opencv2/legacy/compat.hpp \
#    opencv2/legacy/legacy.hpp \
#    opencv2/legacy/streams.hpp \
#    opencv2/ml/ml.hpp \
#    opencv2/nonfree/features2d.hpp \
#    opencv2/nonfree/gpu.hpp \
#    opencv2/nonfree/nonfree.hpp \
#    opencv2/nonfree/ocl.hpp \
#    opencv2/objdetect/objdetect.hpp \
#    opencv2/ocl/matrix_operations.hpp \
#    opencv2/ocl/ocl.hpp \
#    opencv2/photo/photo.hpp \
#    opencv2/photo/photo_c.h \
#    opencv2/stitching/stitcher.hpp \
#    opencv2/stitching/warpers.hpp \
#    opencv2/stitching/detail/autocalib.hpp \
#    opencv2/stitching/detail/blenders.hpp \
#    opencv2/stitching/detail/camera.hpp \
#    opencv2/stitching/detail/exposure_compensate.hpp \
#    opencv2/stitching/detail/matchers.hpp \
#    opencv2/stitching/detail/motion_estimators.hpp \
#    opencv2/stitching/detail/seam_finders.hpp \
#    opencv2/stitching/detail/util.hpp \
#    opencv2/stitching/detail/util_inl.hpp \
#    opencv2/stitching/detail/warpers.hpp \
#    opencv2/stitching/detail/warpers_inl.hpp \
#    opencv2/superres/optical_flow.hpp \
#    opencv2/superres/superres.hpp \
#    opencv2/ts/gpu_perf.hpp \
#    opencv2/ts/gpu_test.hpp \
#    opencv2/ts/ts.hpp \
#    opencv2/ts/ts_gtest.h \
#    opencv2/ts/ts_perf.hpp \
#    opencv2/video/background_segm.hpp \
#    opencv2/video/tracking.hpp \
#    opencv2/video/video.hpp \
#    opencv2/videostab/deblurring.hpp \
#    opencv2/videostab/fast_marching.hpp \
#    opencv2/videostab/fast_marching_inl.hpp \
#    opencv2/videostab/frame_source.hpp \
#    opencv2/videostab/global_motion.hpp \
#    opencv2/videostab/inpainting.hpp \
#    opencv2/videostab/log.hpp \
#    opencv2/videostab/motion_stabilizing.hpp \
#    opencv2/videostab/optical_flow.hpp \
#    opencv2/videostab/stabilizer.hpp \
#    opencv2/videostab/videostab.hpp \
    oscpack/ip/IpEndpointName.h \
    oscpack/ip/NetworkingUtils.h \
    oscpack/ip/PacketListener.h \
    oscpack/ip/TimerListener.h \
    oscpack/ip/UdpSocket.h \
    oscpack/osc/MessageMappingOscPacketListener.h \
    oscpack/osc/OscException.h \
    oscpack/osc/OscHostEndianness.h \
    oscpack/osc/OscOutboundPacketStream.h \
    oscpack/osc/OscPacketListener.h \
    oscpack/osc/OscPrintReceivedElements.h \
    oscpack/osc/OscReceivedElements.h \
    oscpack/osc/OscTypes.h \
    sdl/include/begin_code.h \
    sdl/include/close_code.h \
    sdl/include/SDL.h \
    sdl/include/SDL_active.h \
    sdl/include/SDL_audio.h \
    sdl/include/SDL_byteorder.h \
    sdl/include/SDL_cdrom.h \
    sdl/include/SDL_config.h \
    sdl/include/SDL_config_minimal.h \
    sdl/include/SDL_config_win32.h \
    sdl/include/SDL_copying.h \
    sdl/include/SDL_cpuinfo.h \
    sdl/include/SDL_endian.h \
    sdl/include/SDL_error.h \
    sdl/include/SDL_events.h \
    sdl/include/SDL_getenv.h \
    sdl/include/SDL_joystick.h \
    sdl/include/SDL_keyboard.h \
    sdl/include/SDL_keysym.h \
    sdl/include/SDL_loadso.h \
    sdl/include/SDL_main.h \
    sdl/include/SDL_mouse.h \
    sdl/include/SDL_mutex.h \
    sdl/include/SDL_name.h \
    sdl/include/SDL_opengl.h \
    sdl/include/SDL_platform.h \
    sdl/include/SDL_quit.h \
    sdl/include/SDL_rwops.h \
    sdl/include/SDL_stdinc.h \
    sdl/include/SDL_syswm.h \
    sdl/include/SDL_thread.h \
    sdl/include/SDL_timer.h \
    sdl/include/SDL_types.h \
    sdl/include/SDL_version.h \
    sdl/include/SDL_video.h \
    sdl/include/GL/glut.h \
    TUIO/TuioClient.h \
    TUIO/TuioContainer.h \
    TUIO/TuioCursor.h \
    TUIO/TuioListener.h \
    TUIO/TuioObject.h \
    TUIO/TuioPoint.h \
    TUIO/TuioServer.h \
    TUIO/TuioTime.h \
    IL/config.h \
    IL/config.h.win \
    IL/devil_internal_exports.h \
    IL/il.h \
    IL/il_wrap.h \
    IL/ilu.h \
    IL/ilu_region.h \
    IL/ilut.h \
    IL/ilut_config.h \
    escapi/escapi.h \
    ui_qtmodelviewer5.h \
    assimp/cexport.h \
    assimp/cfileio.h \
    assimp/cimport.h \
    assimp/color4.h \
    assimp/config.h \
    assimp/DefaultLogger.hpp \
    assimp/defs.h \
    assimp/Exporter.hpp \
    assimp/Importer.hpp \
    assimp/importerdesc.h \
    assimp/IOStream.hpp \
    assimp/IOSystem.hpp \
    assimp/light.h \
    assimp/Logger.hpp \
    assimp/LogStream.hpp \
    assimp/material.h \
    assimp/matrix3x3.h \
    assimp/matrix4x4.h \
    assimp/mesh.h \
    assimp/NullLogger.hpp \
    assimp/postprocess.h \
    assimp/ProgressHandler.hpp \
    assimp/quaternion.h \
    assimp/scene.h \
    assimp/texture.h \
    assimp/types.h \
    assimp/vector2.h \
    assimp/vector3.h \
    assimp/version.h \
    x264thread.h \


FORMS    += mainwindow.ui

DISTFILES += \
    TUIO/Doxyfile \
    escapi/escapi.dll

