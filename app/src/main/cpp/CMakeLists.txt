# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

set (MY_LIB C:/source/lib)
set( FREETYPE_SRC_PATH ${MY_LIB}/freetype )
set( lib_src_DIR ${MY_LIB}/libpng )
set( lib_ndk_helper_DIR ${ANDROID_NDK}/sources/android/ndk_helper )

include_directories(
        ${lib_src_DIR}/jni
        ${ANDROID_NDK}/sources/android/native_app_glue
        ${ANDROID_NDK}/sources/android/ndk_helper
        ${FREETYPE_SRC_PATH}/include
)

add_definitions(-DFT2_BUILD_LIBRARY)


add_library(
        native_app_glue
        STATIC
        ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c

)



add_library(
        ndk_helper
        STATIC
        ${lib_ndk_helper_DIR}/JNIHelper.cpp
        ${lib_ndk_helper_DIR}/interpolator.cpp
        ${lib_ndk_helper_DIR}/tapCamera.cpp
        ${lib_ndk_helper_DIR}/gestureDetector.cpp
        ${lib_ndk_helper_DIR}/perfMonitor.cpp
        ${lib_ndk_helper_DIR}/vecmath.cpp
        ${lib_ndk_helper_DIR}/GLContext.cpp
        ${lib_ndk_helper_DIR}/shader.cpp
        ${lib_ndk_helper_DIR}/gl3stub.c
)

add_library(
        freetype
        STATIC
        # base components (required)

        ${FREETYPE_SRC_PATH}/src/base/ftsystem.c
        ${FREETYPE_SRC_PATH}/src/base/ftinit.c
        ${FREETYPE_SRC_PATH}/src/base/ftdebug.c

        ${FREETYPE_SRC_PATH}/src/base/ftbase.c

        ${FREETYPE_SRC_PATH}/src/base/ftbbox.c       # recommended, see <ftbbox.h>
        ${FREETYPE_SRC_PATH}/src/base/ftglyph.c      # recommended, see <ftglyph.h>

        ${FREETYPE_SRC_PATH}/src/base/ftbdf.c        # optional, see <ftbdf.h>
        ${FREETYPE_SRC_PATH}/src/base/ftbitmap.c     # optional, see <ftbitmap.h>
        ${FREETYPE_SRC_PATH}/src/base/ftcid.c        # optional, see <ftcid.h>
        ${FREETYPE_SRC_PATH}/src/base/ftfntfmt.c     # optional, see <ftfntfmt.h>
        ${FREETYPE_SRC_PATH}/src/base/ftfstype.c     # optional
        ${FREETYPE_SRC_PATH}/src/base/ftgasp.c       # optional, see <ftgasp.h>
        ${FREETYPE_SRC_PATH}/src/base/ftgxval.c      # optional, see <ftgxval.h>
        ${FREETYPE_SRC_PATH}/src/base/ftlcdfil.c     # optional, see <ftlcdfil.h>
        ${FREETYPE_SRC_PATH}/src/base/ftmm.c         # optional, see <ftmm.h>
        ${FREETYPE_SRC_PATH}/src/base/ftotval.c      # optional, see <ftotval.h>
        ${FREETYPE_SRC_PATH}/src/base/ftpatent.c     # optional
        ${FREETYPE_SRC_PATH}/src/base/ftpfr.c        # optional, see <ftpfr.h>
        ${FREETYPE_SRC_PATH}/src/base/ftstroke.c     # optional, see <ftstroke.h>
        ${FREETYPE_SRC_PATH}/src/base/ftsynth.c      # optional, see <ftsynth.h>
        ${FREETYPE_SRC_PATH}/src/base/fttype1.c      # optional, see <t1tables.h>
        ${FREETYPE_SRC_PATH}/src/base/ftwinfnt.c     # optional, see <ftwinfnt.h>

        ${FREETYPE_SRC_PATH}/src/base/ftmac.c        # only on the Macintosh

        # font drivers (optional; at least one is needed)

        ${FREETYPE_SRC_PATH}/src/bdf/bdf.c           # BDF font driver
        ${FREETYPE_SRC_PATH}/src/cff/cff.c           # CFF/OpenType font driver
        ${FREETYPE_SRC_PATH}/src/cid/type1cid.c      # Type 1 CID-keyed font driver
        ${FREETYPE_SRC_PATH}/src/pcf/pcf.c           # PCF font driver
        ${FREETYPE_SRC_PATH}/src/pfr/pfr.c           # PFR/TrueDoc font driver
        ${FREETYPE_SRC_PATH}/src/sfnt/sfnt.c         # SFNT files support (TrueType & OpenType)
        ${FREETYPE_SRC_PATH}/src/truetype/truetype.c # TrueType font driver
        ${FREETYPE_SRC_PATH}/src/type1/type1.c       # Type 1 font driver
        ${FREETYPE_SRC_PATH}/src/type42/type42.c     # Type 42 font driver
        ${FREETYPE_SRC_PATH}/src/winfonts/winfnt.c   # Windows FONT / FNT font driver

        # rasterizers (optional; at least one is needed for vector         formats)

        ${FREETYPE_SRC_PATH}/src/raster/raster.c     # monochrome rasterizer
        ${FREETYPE_SRC_PATH}/src/smooth/smooth.c     # anti-aliasing rasterizer

        # auxiliary modules (optional)

        ${FREETYPE_SRC_PATH}/src/autofit/autofit.c   # auto hinting module
        ${FREETYPE_SRC_PATH}/src/cache/ftcache.c     # cache sub-system (in beta)
        ${FREETYPE_SRC_PATH}/src/gzip/ftgzip.c       # support for compressed fonts (.gz)
        ${FREETYPE_SRC_PATH}/src/lzw/ftlzw.c         # support for compressed fonts (.Z)
        ${FREETYPE_SRC_PATH}/src/bzip2/ftbzip2.c     # support for compressed fonts (.bz2)
        ${FREETYPE_SRC_PATH}/src/gxvalid/gxvalid.c   # TrueTypeGX/AAT table validation
        ${FREETYPE_SRC_PATH}/src/otvalid/otvalid.c   # OpenType table validation
        ${FREETYPE_SRC_PATH}/src/psaux/psaux.c       # PostScript Type 1 parsing
        ${FREETYPE_SRC_PATH}/src/pshinter/pshinter.c # PS hinting module
        ${FREETYPE_SRC_PATH}/src/psnames/psnames.c   # PostScript glyph names support
)


# Sets lib_src_DIR to the path of the target CMake project.

target_include_directories(
        native_app_glue
        PUBLIC
        ${ANDROID_NDK}/sources/android/native_app_glue
        ${MY_LIB}/glm
        # ${lib_src_DIR}/jni

)
target_include_directories(
        ndk_helper
        PUBLIC
        #${ANDROID_NDK}/sources/android/native_app_glue
        ${ANDROID_NDK}/sources/android/ndk_helper
        # ${lib_src_DIR}/jni

)

target_include_directories(
        freetype
        PUBLIC
        #${ANDROID_NDK}/sources/android/native_app_glue
        ${FREETYPE_SRC_PATH}/include
        ${FREETYPE_SRC_PATH}/src
        # ${lib_src_DIR}/jni

)






set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -u ANativeActivity_onCreate")



# library and names it lib_gmath.
add_library( libpng STATIC IMPORTED )
set_target_properties( # Specifies the target library.
        libpng

        # Specifies the parameter you want to define.
        PROPERTIES IMPORTED_LOCATION

        # Provides the path to the library you want to import.
        ${lib_src_DIR}/obj/local/${ANDROID_ABI}/libpng.a
)


# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.


add_library( # Sets the name of the library.
        horse-engine

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        main.cpp
        Application.cpp
        Asset.cpp
        ShadersManager.cpp
        cc.cpp
        Texture2D.cpp
        Sprite.cpp
        SpriteText.cpp
        Rectangle.cpp
        EventEngine.cpp
        GameEngine.cpp
        World.cpp
        iObject.cpp
        iWorld.cpp
        iEvent.cpp
        iButton.cpp
        Cube.cpp
        Race.cpp
        Horse.cpp
        Rinconada.cpp
        Scene.cpp
        Actor.cpp
        Object3D.cpp
        Rectangle2D.cpp
        Button2D.cpp
        Sprite2D.cpp
        Text2D.cpp
        SoundSystem.cpp
        QueueSound.cpp
        Cube3D.cpp
        )





# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.


target_link_libraries( # Specifies the target library.
        horse-engine
        android
        native_app_glue
        ndk_helper
        freetype
        EGL
        GLESv2
        OpenSLES
        libpng

        z

        # Links the target library to the log library
        # included in the NDK.
        ${log-lib})
