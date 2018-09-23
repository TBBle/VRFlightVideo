#include <android_native_app_glue.h>

#include <android/looper.h>

/**
 * Entry point for the application thread
 */
void android_main(struct android_app *pApp) {
    // Absolute bare-minimum application loop for native_app_glue
    // Assumes any non-callback-based events added to the Looper will use a
    // struct android_poll_source* as their data pointer.
    while (1) {
        struct android_poll_source *pSource = nullptr;
        if (ALooper_pollAll(-1, nullptr, nullptr, reinterpret_cast<void **>(&pSource)) > 0) {
            pSource->process(pSource->app, pSource);
        }

        if (pApp->destroyRequested) {
            break;
        }
    }
}