#pragma once

#include <QFile>
#include <filesystem>

#include <assimp/IOStream.hpp>
#include <openge/IODevice.hpp>

namespace ge {

/**
 * IOStream implementation for reading 3D models through the Qt resource system.
 */
class AssimpIOStream : public Assimp::IOStream {
 public:
    /**
     * Opens an IOStream for a file.
     *
     * @param filepath File to open.
     * @param mode Mode to open file in.
     */
    explicit AssimpIOStream(const std::filesystem::path &filepath,
                            IODevice::OpenMode mode);

    /**
     * Returns the file size.
     *
     * @return File size.
     */
    size_t FileSize() const override;

    /**
     * Flush the content of the file buffer.
     */
    void Flush() override;

    /**
     * Read binary data.
     *
     * @param buffer Buffer to read binary data into.
     * @param size Size of each item to read in bytes.
     * @param count Number of items to read.
     * @return Number of items read.
     */
    size_t Read(void *buffer, size_t size, size_t count) override;

    /**
     * Set the file position indicator for the stream.
     *
     * @param offset Number of bytes to offset from origin position.
     * @param origin Origin from which to specify the position offset from.
     * @return aiReturn_SUCCESS upon success, otherwise aiReturn_FAILURE.
     */
    aiReturn Seek(size_t offset, aiOrigin origin) override;

    /**
     * Obtains the current value of the file position indicator.
     *
     * @return Current file position.
     */
    size_t Tell() const override;

    /**
     * Write binary data.
     *
     * @param buffer Buffer containing binary data to write.
     * @param size Size of each item to write in bytes.
     * @param count Number of items to write.
     * @return Number of items written.
     */
    size_t Write(const void *buffer, size_t size, size_t count) override;

 private:
    QFile file;
};

}  // namespace ge
