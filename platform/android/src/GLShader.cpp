#include <spdlog/spdlog.h>

#include <openge/Asset.hpp>
#include <openge/GLShader.hpp>

namespace ge {

void GLShader::compileSourceFile(const char* filepath) {
  spdlog::info("Compiling shader: {}", filepath);
  const auto source = ge::Asset::read(filepath);
  compileSourceCode(source.c_str());
}

}  // namespace ge
