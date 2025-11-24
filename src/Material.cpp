#include <memory>
#include <openge/ColorConstants.hpp>
#include <openge/Material.hpp>
#include <openge/RenderPipeline.hpp>
#include <string>
#include <utility>

namespace ge {

Material::Material(std::shared_ptr<GLShaderProgram> shaderProgram)
    : shaderProgram(std::move(shaderProgram)),
      color(ColorConstants::WHITE),
      shine(32.0f) {}

void Material::addTexture(const std::string& name, int unit,
                          TexturePtr texture) {
  textures[name] = std::make_pair(unit, std::move(texture));

  shaderProgram->bind();
  shaderProgram->setUniformValue(name.c_str(), unit);
}

std::shared_ptr<GLShaderProgram> Material::getShaderProgram() {
  return shaderProgram;
}

void Material::bind() {
  shaderProgram->setUniformValue(ge::RenderPipeline::Uniform::Material::COLOR,
                                 color.redF(), color.greenF(), color.blueF(),
                                 color.alphaF());

  shaderProgram->setUniformValue(ge::RenderPipeline::Uniform::Material::SHINE,
                                 shine);

  for (auto& [name, value] : textures) {
    auto [unit, texture] = value;
    texture->bind(unit);
  }
}

void Material::setColor(const Color& color) { this->color = color; }

void Material::setShine(float shine) { this->shine = shine; }

}  // namespace ge
