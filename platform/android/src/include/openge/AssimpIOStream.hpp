#pragma once

#include <assimp/IOStream.hpp>
#include <filesystem>
#include <openge/Asset.hpp>

namespace ge {

/**
 * IOStream implementation for reading 3D models.
 */
class AssimpIOStream : public Assimp::IOStream {
 public:
  /**
   * Opens an IOStream for a file.
   *
   * @param filepath File to open.
   */
  explicit AssimpIOStream(const std::filesystem::path& filepath);

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
  size_t Read(void* buffer, size_t size, size_t count) override;

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
   * Operation not supported and will throw an exception if invoked.
   */
  size_t Write(const void*, size_t, size_t) override;

 private:
  mutable Asset asset;
};

}  // namespace ge
