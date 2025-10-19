#pragma once

#include <assimp/IOSystem.hpp>

namespace ge {

/**
 * IOSystem implementation for reading 3D models.
 */
class AssimpIOSystem : public Assimp::IOSystem {
 public:
    /**
     * Creates a new AssimpIOSystem instance.
     *
     * @return New AssimpIOSystem instance.
     */
    static AssimpIOSystem * create();

    /**
     * Tests for the existence of a file at the given path.
     *
     * @param filepath Path to the file.
     * @return true if there is a file with this path, else false.
     */
    bool Exists(const char *filepath) const override;

    /**
     * Open a new file with a given path.
     *
     * @param filepath Path to the file.
     * @param mode Desired file I/O mode (rb, r, rt)
     *
     * @return New IOStream interface allowing the lib to access
     *         the underlying file.
     */
    Assimp::IOStream * Open(const char *filepath, const char *mode) override;

    /**
     * Closes the given file and releases all resources associated with it.
     *
     * @param stream The file instance previously created by Open().
     */
    void Close(Assimp::IOStream *stream) override;

    /**
     * Returns the system specific directory separator.
     *
     * @return System specific directory separator.
     */
    char getOsSeparator() const override;

 private:
    AssimpIOSystem() = default;
};

}  // namespace ge
