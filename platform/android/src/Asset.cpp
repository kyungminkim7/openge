#include <filesystem>
#include <ios>
#include <sstream>
#include <system_error>
#include <type_traits>
#include <vector>

#include <openge/Asset.hpp>
#include <openge/AssetManager.hpp>

namespace ge {

bool Asset::exists(const char *filepath) {
    try {
        Asset(filepath, Asset::Mode::Unknown);
    } catch (...) {
        return false;
    }

    return true;
}

Asset::Asset(const char *filepath, Mode mode) :
    asset(AAssetManager_open(AssetManager::get(), filepath,
                             static_cast<std::underlying_type_t<Mode>>(mode))),
    filepath(filepath) {
    if (asset == nullptr) {
        const auto errorCode =
            std::make_error_code(std::errc::no_such_file_or_directory);

        const auto errorMessage = "Failed to open " + this->filepath;

        throw std::filesystem::filesystem_error(errorMessage, errorCode);
    }
}

Asset::~Asset() {
    AAsset_close(asset);
}

AAsset * Asset::get() {
    return asset;
}

std::size_t Asset::getLength() const {
    return AAsset_getLength64(asset);
}

std::size_t Asset::getRemainingLength() const {
    return AAsset_getRemainingLength64(asset);
}

std::string Asset::read(const char *filepath) {
    Asset file(filepath, Asset::Mode::Buffer);
    std::vector<char> data(file.getLength());
    const auto bytesRead = file.read(data.data(), data.size());

    if (bytesRead != data.size()) {
        const auto errorCode = std::make_error_code(std::errc::file_too_large);

        std::ostringstream errorMessage;
        errorMessage << "Failed to read " << filepath;

        throw std::filesystem::filesystem_error(errorMessage.str(), errorCode);
    }

    return {data.cbegin(), data.cend()};
}

std::size_t Asset::read(void *buffer, std::size_t count) {
    return AAsset_read(asset, buffer, count);
}

std::size_t Asset::seek(std::size_t offset, Seek whence) {
    return AAsset_seek64(asset, offset,
                         static_cast<std::underlying_type_t<Seek>>(whence));
}

}  // namespace ge
