#include <filesystem>
#include <sstream>
#include <stdexcept>

#include <openge/AssimpIOStream.hpp>
#include <openge/AssimpIOSystem.hpp>
#include <openge/File.hpp>

namespace ge {

bool AssimpIOSystem::Exists(const char *filepath) const {
    return File::exists(filepath);
}

Assimp::IOStream * AssimpIOSystem::Open(const char *filepath,
                                        const char *mode) {
    if (mode[0] != 'r') {
        std::stringstream errorMessage;
        errorMessage << "Invalid file mode specified for " << filepath
                        << ": " << mode;

        throw std::invalid_argument(errorMessage.str());
    }

    return new AssimpIOStream(filepath);
}

void AssimpIOSystem::Close(Assimp::IOStream *stream) {
    delete stream;
}

char AssimpIOSystem::getOsSeparator() const {
    return std::filesystem::path::preferred_separator;
}

}  // namespace ge
