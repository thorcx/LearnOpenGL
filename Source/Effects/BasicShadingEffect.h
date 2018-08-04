#pragma once

#include "../ogl/technique.h"
#include "../ogl/ogldev_math_3d.h"
#include "../ogl/ogldev_lights_common.h"


//基本定点/像素着色器组合效果,用来调试
class FBasicShadingEffect : public Technique
{
public:
	FBasicShadingEffect();

	virtual bool Init();
};


