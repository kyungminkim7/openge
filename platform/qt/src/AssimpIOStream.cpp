#include <string>
#include <system_error>

#include <openge/AssimpIOStream.hpp>

namespace ge {

AssimpIOStream::AssimpIOStream(const std::filesystem::path &filepath,
                               IODevice::OpenMode mode) :
    file(filepath) {
    if (!file.open(mode)) {
        const auto errorCode = std::make_error_code(std::errc::io_error);

        throw std::system_error(errorCode,
                                "Failed to open " + std::string(filepath));
    }
}

size_t AssimpIOStream::FileSize() const {
    return file.size();
}

void AssimpIOStream::Flush() {
    file.flush();
}

size_t AssimpIOStream::Read(void *buffer, size_t size, size_t count) {
    const auto bytesRead = file.read(reinterpret_cast<char *>(buffer),
                                     size * count);

    return bytesRead > 0 ?
        bytesRead / size :
        bytesRead;
}

aiReturn AssimpIOStream::Seek(size_t offset, aiOrigin origin) {
    auto position = 0;

    switch (origin) {
        case aiOrigin_SET:
            position = offset;
            break;

        case aiOrigin_CUR:
            position = file.pos() + offset;
            break;

        case aiOrigin_END:
            position = file.size() + offset;
            break;

        default:
            return aiReturn_FAILURE;
    }

    return file.seek(position) ?
        aiReturn_SUCCESS :
        aiReturn_FAILURE;
}

size_t AssimpIOStream::Tell() const {
    return file.pos();
}

size_t AssimpIOStream::Write(const void *buffer, size_t size, size_t count) {
    const auto bytesWritten = file.write(reinterpret_cast<const char *>(buffer),
                                         size * count);

    return bytesWritten > 0 ?
        bytesWritten / size :
        bytesWritten;
}

}  // namespace ge
