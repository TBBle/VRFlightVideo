# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

cmake_minimum_required(VERSION 3.6.0)

# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

# log - Android logging shared library from the NDK
add_library(log SHARED IMPORTED)
find_library(LOG_LIB_PATH log)
set_target_properties(log PROPERTIES IMPORTED_LOCATION ${LOG_LIB_PATH})

# native_app_glue - sourceful static library from the NDK
set(NATIVE_APP_GLUE_PATH "${ANDROID_NDK}/sources/android/native_app_glue/")
add_library(native_app_glue STATIC
    ${NATIVE_APP_GLUE_PATH}/android_native_app_glue.c
)

target_include_directories(native_app_glue INTERFACE ${NATIVE_APP_GLUE_PATH})
target_link_libraries(native_app_glue PRIVATE android)
target_link_libraries(native_app_glue PRIVATE log)
# Ensure that ANativeActivity_onCreate is referenced, or the linker will not
# pull any symbols from the library. See https://github.com/android-ndk/ndk/issues/381#issuecomment-309662037
target_link_libraries(native_app_glue INTERFACE "-Wl,-u,ANativeActivity_onCreate")

# native_activity - our main library
add_library(native_activity SHARED
    src/main/cpp/main.cpp
)
target_link_libraries(native_activity PRIVATE native_app_glue)