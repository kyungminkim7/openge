#include <system_error>

#include <openge/AssimpIOStream.hpp>

namespace ge {

AssimpIOStream::AssimpIOStream(const std::filesystem::path &filepath) :
    file(filepath.string().c_str(), File::Mode::Random) { }

size_t AssimpIOStream::FileSize() const {
    return file.getLength();
}

void AssimpIOStream::Flush() {
    const auto errorCode =
        std::make_error_code(std::errc::operation_not_supported);

    throw std::system_error(errorCode,
                            "Writing to files with Assimp is not supported");
}

size_t AssimpIOStream::Read(void *buffer, size_t size, size_t count) {
    const auto bytesRead = file.read(buffer, size * count);

    return bytesRead > 0 ?
        bytesRead / size :
        bytesRead;
}

aiReturn AssimpIOStream::Seek(size_t offset, aiOrigin origin) {
    File::Seek whence;

    switch (origin) {
        case aiOrigin_SET:
            whence = File::Seek::Set;
            break;

        case aiOrigin_CUR:
            whence = File::Seek::Current;
            break;

        case aiOrigin_END:
            whence = File::Seek::End;
            break;

        default:
            return aiReturn_FAILURE;
    }

    return file.seek(offset, whence) == -1 ?
        aiReturn_FAILURE :
        aiReturn_SUCCESS;
}

size_t AssimpIOStream::Tell() const {
    return file.seek(0, File::Seek::Current);
}

size_t AssimpIOStream::Write(const void *, size_t, size_t) {
    const auto errorCode =
        std::make_error_code(std::errc::operation_not_supported);

    throw std::system_error(errorCode,
                            "Writing to files with Assimp is not supported");
}

}  // namespace ge
