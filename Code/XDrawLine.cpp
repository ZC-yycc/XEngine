#include "XDrawLine.h"
#include "CameraManager.h"
#include "XCameraComponent.h"
#include "Shader.h"
#include "ThirdPartyLib/GL/glew.h"
#include "BufferManager.h"



XDrawLine::XDrawLine()
{
    glGenVertexArrays(1, &VAO_);
    glGenBuffers(1, &VBO_);


    // 创建着色器程序
    pShader_ = new Shader("Resource/LineVShader.vsr", "Resource/LineFShader.fsr");
}

XDrawLine::~XDrawLine()
{
    glDeleteVertexArrays(1, &VAO_);
    glDeleteBuffers(1, &VBO_);
    delete pShader_;
    pShader_ = nullptr;
}

void XDrawLine::draw(const Vector2& begin, const Vector2& end)
{
    vertices[0] = begin.x_;
    vertices[1] = begin.y_;
    vertices[2] = 0.0f;
    vertices[3] = end.x_;
    vertices[4] = end.y_;
    vertices[5] = 0.0f;

    // 绑定VAO/VBO
    glBindVertexArray(VAO_);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 配置顶点属性
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

	glm::mat4 mvo_mat4_ = CameraManager::getMainCamera()->getOrthomMat() * CameraManager::getMainCamera()->getViewMat()/* * model_mat4_*/;
    // 使用着色器程序
    pShader_->enableShader(true);
    pShader_->setUniformMat4f("mvo_mat4", mvo_mat4_);
    pShader_->setUniform3f("lineColor", 1.0f, 0.0f, 0.0f);

    glDrawArrays(GL_LINES, 0, 2); // 绘制两条线段
}
