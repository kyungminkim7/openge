#include <filesystem>
#include <ios>
#include <system_error>

#include <openge/Asset.hpp>
#include <openge/AssetManager.hpp>

namespace ge {

Asset::Asset(const char *filepath, Mode mode) :
    asset(AAssetManager_open(AssetManager::get(), filepath,
                             static_cast<int>(mode))),
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

std::size_t Asset::getLength() const {
    return AAsset_getLength64(asset);
}

std::size_t Asset::getRemainingLength() const {
    return AAsset_getRemainingLength64(asset);
}

void Asset::read(void *buffer, std::size_t count) {
    auto totalNumBytesRead = 0;

    do {
        const auto numRemainingBytes = count - totalNumBytesRead;
        const auto numBytesRead = AAsset_read(asset, buffer, numRemainingBytes);

        if (numBytesRead < 0) {
            throw std::ios_base::failure("Failed to read " + filepath);
        }

        totalNumBytesRead += numBytesRead;
    } while (totalNumBytesRead < count);
}

std::size_t Asset::seek(std::size_t offset, Seek whence) {
    const auto position = AAsset_seek64(asset, offset,
                                        static_cast<int>(whence));
    if (position < 0) {
        const auto errorCode = std::make_error_code(std::errc::invalid_seek);
        const auto errorMessage = "Failed to seek offset in " + filepath;
        throw std::filesystem::filesystem_error(errorMessage, errorCode);
    }
    return position;
}

}  // namespace ge
