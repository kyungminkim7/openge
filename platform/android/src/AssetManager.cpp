#include <android/asset_manager_jni.h>

#include <openge/AssetManager.hpp>

namespace {

AAssetManager* assetManager = nullptr;

}  // namespace

namespace ge {
namespace AssetManager {

void create(JNIEnv* env, jobject jAssetManager) {
  assetManager = AAssetManager_fromJava(env, jAssetManager);
}

void destroy() { assetManager = nullptr; }

AAssetManager* get() { return assetManager; }

}  // namespace AssetManager
}  // namespace ge
