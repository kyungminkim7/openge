#include "openge/ImageDecoder.hpp"

namespace ge {

using namespace std::string_literals;

ImageDecoderError::ImageDecoderError(int error, const std::string &whatArg) :
    Error(whatArg + " - " + AImageDecoder_resultToString(error)) {}

ImageDecoder::ImageDecoder(const char *filepath) :
    filepath(filepath), asset(filepath, Asset::Mode::Streaming) {
    auto status = AImageDecoder_createFromAAsset(asset.get(), &decoder);
    if (status != ANDROID_IMAGE_DECODER_SUCCESS) {
        throw ImageDecoderError(status,
            "Failed to create image decoder for "s + filepath);
    }
}

ImageDecoder::~ImageDecoder() {
    AImageDecoder_delete(decoder);
}

void ImageDecoder::setAndroidBitmapFormat(std::int32_t format) {
    const auto status = AImageDecoder_setAndroidBitmapFormat(decoder,
                                                             format);
    if (status != ANDROID_IMAGE_DECODER_SUCCESS) {
        throw ImageDecoderError(status,
            "Failed to request output format for "s + filepath);
    }
}

void ImageDecoder::setUnpremultipliedRequired(bool required) {
    const auto status = AImageDecoder_setUnpremultipliedRequired(decoder,
                                                                    required);
    if (status != ANDROID_IMAGE_DECODER_SUCCESS) {
        throw ImageDecoderError(status,
            "Failed to set unpre-multiply alpha for "s + filepath);
    }
}

ADataSpace ImageDecoder::getDataSpace() const {
    return static_cast<ADataSpace>(
        AImageDecoderHeaderInfo_getDataSpace(getHeaderInfo()));
}

void ImageDecoder::setDataSpace(std::int32_t dataSpace) {
    const auto status = AImageDecoder_setDataSpace(decoder, dataSpace);
    if (status != ANDROID_IMAGE_DECODER_SUCCESS) {
        throw ImageDecoderError(status,
            "Failed to set SRGB color space for "s + filepath);
    }
}

std::int32_t ImageDecoder::getWidth() const {
    return AImageDecoderHeaderInfo_getWidth(getHeaderInfo());
}

std::int32_t ImageDecoder::getHeight() const {
    return AImageDecoderHeaderInfo_getHeight(getHeaderInfo());
}

std::size_t ImageDecoder::getMinimumStride() {
    return AImageDecoder_getMinimumStride(decoder);
}

std::vector<std::uint8_t> ImageDecoder::decodeImage(std::size_t stride,
                                                    std::size_t size) {
    std::vector<std::uint8_t> pixels(size);

    const auto status = AImageDecoder_decodeImage(decoder, pixels.data(),
                                                  stride, size);
    if (status != ANDROID_IMAGE_DECODER_SUCCESS) {
        throw ImageDecoderError(status,
            "Failed to decode image "s + filepath);
    }

    return pixels;
}

const AImageDecoderHeaderInfo * ImageDecoder::getHeaderInfo() const {
    return AImageDecoder_getHeaderInfo(decoder);
}

}  // namespace ge
