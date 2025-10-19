#pragma once

#include <android/asset_manager.h>

#include <cstddef>
#include <string>

namespace ge {

/**
 * Provides access to a read-only Android asset.
 */
class Asset {
 public:
    /**
     * Access modes for opening assets.
     */
    enum class Mode {
        Buffer = AASSET_MODE_BUFFER,
        Random = AASSET_MODE_RANDOM,
        Streaming = AASSET_MODE_STREAMING,
        Unknown = AASSET_MODE_UNKNOWN
    };

    /**
     * Seek mode.
     */
    enum class Seek {
        Set = SEEK_SET,
        Current = SEEK_CUR,
        End = SEEK_END
    };

    /**
     * Reads the entire asset data as a string.
     *
     * @return Asset data as a string.
     */
    static std::string read(const char *filepath);

    /**
     * Check whether a file exists.
     *
     * @param filepath Path of file to check.
     * @return true if file exists, otherwise false.
     */
    static bool exists(const char *filepath);

    /**
     * Opens an asset.
     *
     * @param filepath Asset filepath.
     * @param mode Access mode.
     */
    explicit Asset(const char *filepath, Mode mode);

    /**
     * Closes the asset.
     */
    ~Asset();

    /**
     * Returns a pointer to the managed asset.
     *
     * @return Managed asset.
     */
    AAsset * get();

    /**
     * Gets the total size of the asset.
     *
     * @return Asset size.
     */
    std::size_t getLength() const;

    /**
     * Gets the total amount of asset data that can
     * be read from the current position.
     *
     * @return Remaining amount of asset data.
     */
    std::size_t getRemainingLength() const;

    /**
     * Reads bytes of data from the current offset.
     *
     * @param buffer Buffer to output data to.
     * @param count Number of bytes to read.
     * @return number of bytes read, zero on EOF, or <0 on error.
     */
    std::size_t read(void *buffer, std::size_t count);

    /**
     * Seeks to the specified offset within the asset data.
     *
     * @param offset Data offset to seek to.
     * @param whence Where to specify the offset from.
     * @return New position on success, otherwise -1 on error.
     */
    std::size_t seek(std::size_t offset, Seek whence);

 private:
    AAsset *asset;
    std::string filepath;
};

}  // namespace ge
