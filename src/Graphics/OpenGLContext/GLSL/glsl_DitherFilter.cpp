#include "glsl_DitherFilter.h"

using namespace glsl;

DitherFilterVertexShader::DitherFilterVertexShader(const opengl::GLInfo & _glinfo)
{
	m_part =
		"precision mediump float;                                 \n"
		"                                                         \n"
		"//texcoords computed in vertex step                      \n"
		"//to avoid dependent texture reads                       \n"
		"OUT vec2 v_rgbL;                                         \n"
		"OUT vec2 v_rgbR;                                         \n"
		"OUT vec2 v_rgbM;                                         \n"
		"                                                         \n"
		"uniform vec2 uTextureSize;                               \n"
		"IN highp vec4 aRectPosition;                             \n"
		"                                                         \n"
		"void main(void) {                                        \n"
		"  gl_Position = aRectPosition;                           \n"
		"                                                         \n"
		"  //compute the texture coords and send them to varyings \n"
		"  vec2 vUv = (aRectPosition.xy + 1.0) * 0.5;             \n"
		"  vec2 fragCoord = vUv * uTextureSize;                   \n"
		"  vec2 inverseVP = vec2(1.0) / uTextureSize;             \n"
		"  v_rgbL = (fragCoord + vec2(-1.0, 0.0)) * inverseVP;    \n"
		"  v_rgbR = (fragCoord + vec2(1.0, 0.0)) * inverseVP;     \n"
		"  v_rgbM = vec2(fragCoord * inverseVP);                  \n"
		"}                                                        \n"
		;
}

DitherFilterFragmentShader::DitherFilterFragmentShader(const opengl::GLInfo & _glinfo)
{
	m_part =
		"                                                                                \n"
		"precision mediump float;                                                        \n"
		"IN vec2 v_rgbL;                                                                 \n"
		"IN vec2 v_rgbR;                                                                 \n"
		"IN vec2 v_rgbM;                                                                 \n"
		"                                                                                \n"
		"uniform vec2 uTextureSize;                                                      \n"
		"uniform sampler2D uTex0;                                                        \n"
		"                                                                                \n"
		"OUT lowp vec4 fragColor;                                                        \n"
		"                                                                                \n"
		"void main() {                                                                   \n"
		"  fragColor = texture2D(uTex0, v_rgbL) * 0.2 + texture2D(uTex0, v_rgbM) * 0.6 + texture2D(uTex0, v_rgbR) * 0.2;\n"
		;
}
