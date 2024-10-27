#include <utility>

#include <openge/ColorConstants.hpp>
#include <openge/Material.hpp>
#include <openge/RenderPipeline.hpp>

namespace ge {

Material::Material(std::shared_ptr<GLShaderProgram> shaderProgram) :
    shaderProgram(std::move(shaderProgram)),
    color(ColorConstants::WHITE) { }

void Material::addTexture(TexturePtr texture) {
    const int textureUnit = textures.size();

    textures.push_back(std::move(texture));

    shaderProgram->bind();

    shaderProgram->setUniformValue(
        ge::RenderPipeline::Uniform::Material::TEXTURES[textureUnit],
        textureUnit);
}

std::shared_ptr<GLShaderProgram> Material::getShaderProgram() {
    return shaderProgram;
}

void Material::bind() {
    shaderProgram->setUniformValue(ge::RenderPipeline::Uniform::Material::COLOR,
                                   color.redF(), color.greenF(), color.blueF(),
                                   color.alphaF());

    for (std::size_t i = 0; i < textures.size(); ++i) {
        textures[i]->bind(i);
    }
}

void Material::setColor(const Color &color) {
    this->color = color;
}

void Material::setTexture(TexturePtr texture, std::size_t index) {
    textures[index] = std::move(texture);
}

}  // namespace ge
