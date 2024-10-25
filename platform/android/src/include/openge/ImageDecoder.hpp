#pragma once

#include <android/data_space.h>
#include <android/imagedecoder.h>

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

#include <openge/Asset.hpp>
#include <openge/Exception.hpp>

namespace ge {

/**
 * Represents errors from decoding images into RGBA pixels.
 */
class ImageDecoderError : public Error {
 public:
    /**
     * Constructs an ImageDecoderError with the given message.
     *
     * @param error Error code.
     * @param whatArg Explanatory error message.
     */
    explicit ImageDecoderError(int error, const std::string &whatArg);
};

/**
 * Wrapper class for decoding images directly.
 */
class ImageDecoder {
 public:
    /**
     * Creates a new ImageDecoder.
     */
    explicit ImageDecoder(const char *filepath);

    ~ImageDecoder();

    /**
     * Choose the desired output format.
     *
     * @param format Output format.
     */
    void setAndroidBitmapFormat(std::int32_t format);

    /**
     * Specifly whether output's pixels shoult be unpremultiplied.
     *
     * @param required Specified whether to leave pixels unpremultiplied.
     */
    void setUnpremultipliedRequired(bool required);

    /**
     * Report the dataspace to decode to by default.
     *
     * @return Default dataspace.
     */
    ADataSpace getDataSpace() const;

    /**
     * Choose the dataspace for the output.
     *
     * @param dataSpace Dataspace to set.
     */
    void setDataSpace(std::int32_t dataSpace);

    /**
     * Gets image width.
     *
     * @return Image width.
     */
    std::int32_t getWidth() const;

    /**
     * Gets image height.
     *
     * @return Image height.
     */
    std::int32_t getHeight() const;

    /**
     * Gets image minimum stride.
     *
     * @return Image minimum stride.
     */
    std::size_t getMinimumStride();

    /**
     * Decodes the image into pixels.
     *
     * @param stride Width of a single row in bytes.
     * @param size Size of the pixel buffer in bytes.
     */ 
    std::vector<std::uint8_t> decodeImage(std::size_t stride,
                                          std::size_t size);

 private:
    const AImageDecoderHeaderInfo * getHeaderInfo() const;

    std::string filepath;
    Asset asset;
    AImageDecoder *decoder;
};

}  // namespace ge
