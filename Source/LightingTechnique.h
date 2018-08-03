#pragma once

#include "ogl/technique.h"
#include "ogl/ogldev_math_3d.h"
#include "ogl/ogldev_lights_common.h"


class FLightingTechnique :public Technique
{
public:
	FLightingTechnique();

	virtual bool Init();

	void SetWVP(const Matrix4f& WVP);
	void SetTextureUnit(unsigned int TextureUnit);
	void SetDirectionalLight(const DirectionalLight& Light);

private:
	GLuint	m_WVPLocation;
	GLuint	m_SamplerLocation;
	GLuint	m_DirLightColorLocation;
	GLuint	m_DirLightAmbientIntensityLocation;
};
