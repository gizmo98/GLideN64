#pragma once
#include "glsl_ShaderPart.h"
#include <Graphics/OpenGLContext/opengl_GLInfo.h>

namespace glsl {

	class DitherFilterVertexShader : public ShaderPart
	{
	public:
		DitherFilterVertexShader(const opengl::GLInfo & _glinfo);
	};

	class DitherFilterFragmentShader : public ShaderPart
	{
	public:
		DitherFilterFragmentShader(const opengl::GLInfo & _glinfo);
	};
}