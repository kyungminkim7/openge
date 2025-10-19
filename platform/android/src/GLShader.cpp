#include <openge/Asset.hpp>
#include <openge/GLShader.hpp>
#include <spdlog/spdlog.h>

namespace ge {

void GLShader::compileSourceFile(const char *filepath) {
    spdlog::info("Compiling shader: {}", filepath);
    const auto source = ge::Asset::read(filepath);
    compileSourceCode(source.c_str());
}

}  // namespace ge
