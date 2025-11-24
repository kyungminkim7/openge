#include <openge/AssimpIOStream.hpp>
#include <string>
#include <system_error>

namespace ge {

AssimpIOStream::AssimpIOStream(const std::filesystem::path& filepath)
    : asset(filepath.string().c_str(), Asset::Mode::Random) {}

size_t AssimpIOStream::FileSize() const { return asset.getLength(); }

void AssimpIOStream::Flush() {
  const auto errorCode =
      std::make_error_code(std::errc::operation_not_supported);

  throw std::system_error(errorCode,
                          "Writing to files with Assimp is not supported");
}

size_t AssimpIOStream::Read(void* buffer, size_t size, size_t count) {
  const auto bytesRead = asset.read(buffer, size * count);

  return bytesRead > 0 ? bytesRead / size : bytesRead;
}

aiReturn AssimpIOStream::Seek(size_t offset, aiOrigin origin) {
  Asset::Seek whence;

  switch (origin) {
    case aiOrigin_SET:
      whence = Asset::Seek::Set;
      break;

    case aiOrigin_CUR:
      whence = Asset::Seek::Current;
      break;

    case aiOrigin_END:
      whence = Asset::Seek::End;
      break;

    default:
      return aiReturn_FAILURE;
  }

  return asset.seek(offset, whence) == -1 ? aiReturn_FAILURE : aiReturn_SUCCESS;
}

size_t AssimpIOStream::Tell() const {
  return asset.seek(0, Asset::Seek::Current);
}

size_t AssimpIOStream::Write(const void*, size_t, size_t) {
  const auto errorCode =
      std::make_error_code(std::errc::operation_not_supported);

  throw std::system_error(errorCode,
                          "Writing to files with Assimp is not supported");
}

}  // namespace ge
