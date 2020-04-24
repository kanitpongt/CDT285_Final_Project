#include "Skybox.hpp"
#include "graphic/camera.h"

namespace EC
{
    void Skybox::Init(std::string vert, std::string frag, std::vector<std::string>& cubemapTexture)
    {
        m_shader = new Graphic::Shader(vert.c_str(), frag.c_str());
        m_shader->setInt("skybox", 0);
        m_cubemap.LoadTexture(cubemapTexture);
    }

    void Skybox::Render(Camera& cam)
    {
        if (!m_shader)
            return;

        // draw skybox as last
        glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
        m_shader->use();
        auto view = glm::mat4(glm::mat3(cam.GetViewMatrix())); // remove translation from the view matrix
        auto projection = cam.GetProjectionMatrix();
        m_shader->setMat4("view", view);
        m_shader->setMat4("projection", projection);
        m_cubemap.Render();
        glDepthFunc(GL_LESS);
        m_shader->unUse();
    }
}

