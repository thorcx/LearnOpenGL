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
	//眼睛世界位置，计算specLight用
	void SetEyeWorldPos(const Vector3f& EyeWorldPos);
	void SetMatSpecularIntensity(float Intensity);
	void SetMatSpecularPower(float Power);
private:
	GLuint	m_WVPLocation;
	GLuint  m_WorldMatrixLocation;
	GLuint	m_SamplerLocation;

	GLuint m_eyeWorldPosLocation;
	GLuint m_matSpecularIntensityLocation;
	GLuint m_matSpecularPowerLocation;

	struct {
		GLuint Color;
		GLuint AmbientIntensity;
		GLuint Direction;
		GLuint DiffuseIntensity;
	}m_DirLightLocation;
};
