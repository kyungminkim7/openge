#include <QFile>
#include <filesystem>
#include <sstream>
#include <stdexcept>

#include <openge/AssimpIOStream.hpp>
#include <openge/AssimpIOSystem.hpp>
#include <openge/IODevice.hpp>

namespace ge {

bool AssimpIOSystem::Exists(const char *filepath) const {
    return QFile::exists(filepath);
}

Assimp::IOStream * AssimpIOSystem::Open(const char *filepath,
                                        const char *mode) {
    IODevice::OpenModeFlag flag;

    switch (mode[0]) {
        case 'r':
            flag = IODevice::OpenModeFlag::ReadOnly;
            break;

        case 'w':
            flag = IODevice::OpenModeFlag::WriteOnly;
            break;

        default:
            std::stringstream errorMessage;
            errorMessage << "Invalid file open mode specified for " << filepath
                         << ": " << mode;

            throw std::invalid_argument(errorMessage.str());
    }

    return new AssimpIOStream(filepath, flag);
}

void AssimpIOSystem::Close(Assimp::IOStream *stream) {
    delete stream;
}

char AssimpIOSystem::getOsSeparator() const {
    return std::filesystem::path::preferred_separator;
}

}  // namespace ge
