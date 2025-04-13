#pragma once
#ifndef XDRAWLINE_H
#define XDRAWLINE_H

#include "Transform.h"

class Shader;


class XDrawLine
{
private:
    Shader          *pShader_;
    unsigned int VAO_, VBO_;
    float vertices[6];

public:
    XDrawLine();
    ~XDrawLine();
    void draw(const Vector2& begin, const Vector2& end);

};


#endif // !
