#pragma once

#include <android/asset_manager.h>
#include <jni.h>

#include <string>

namespace ge {
namespace AssetManager {

void create(JNIEnv *env, jobject jAssetManager);
void destroy();
AAssetManager *get();

}  // namespace AssetManager
}  // namespace ge
