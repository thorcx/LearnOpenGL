#pragma once

#include "../ogl/technique.h"
#include "../ogl/ogldev_math_3d.h"
#include "../ogl/ogldev_lights_common.h"



//基本光照shader组合
class FLightingTechnique :public Technique
{
public:
	FLightingTechnique();

	virtual bool Init();

	void SetWVP(const Matrix4f& WVP);
	void SetWorldMatrix(const Matrix4f& World);
	void SetTextureUnit(unsigned int TextureUnit);
	void SetDirectionalLight(const DirectionalLight& Light);

private:
	GLuint	m_WVPLocation;
	GLuint  m_WorldMatrixLocation;
	GLuint	m_SamplerLocation;

	struct {
		GLuint Color;
		GLuint AmbientIntensity;
		GLuint Direction;
		GLuint DiffuseIntensity;
	}m_DirLightLocation;
};
