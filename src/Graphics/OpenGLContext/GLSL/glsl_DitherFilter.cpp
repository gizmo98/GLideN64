#include "glsl_DitherFilter.h"

using namespace glsl;

DitherFilterVertexShader::DitherFilterVertexShader(const opengl::GLInfo & _glinfo)
{
	m_part =
		"precision mediump float;                                 \n"
		"                                                         \n"
		"//texcoords computed in vertex step                      \n"
		"//to avoid dependent texture reads                       \n"
		"OUT vec2 v_11;                                           \n"
		"OUT vec2 v_12;                                           \n"
		"OUT vec2 v_21;                                           \n"
		"OUT vec2 v_22;                                           \n"
		"                                                         \n"
		"uniform vec2 uTextureSize;                               \n"
		"IN highp vec4 aRectPosition;                             \n"
		"                                                         \n"
		"void main(void) {                                        \n"
		"  gl_Position = aRectPosition;                           \n"
		"                                                         \n"
		"  //compute the texture coords and send them to varyings \n"
		"  vec2 vUv = (aRectPosition.xy + 1.0) * 0.5;             \n"
		"  vec2 fragCoord = floor(vUv * uTextureSize - 0.5);      \n"
		"  vec2 inverseVP = vec2(1.0) / uTextureSize;             \n"
		"  v_1 = (fragCoord + vec2(0.5, -1.5)) * inverseVP;       \n"
		"  v_2 = (fragCoord + vec2(0.5, -0.5)) * inverseVP;       \n"
		"  v_3 = (fragCoord + vec2(0.5,  0.5)) * inverseVP;       \n"
		"  v_4 = (fragCoord + vec2(0.5,  1.5)) * inverseVP;       \n"
		"}                                                        \n"
		;
}

DitherFilterFragmentShader::DitherFilterFragmentShader(const opengl::GLInfo & _glinfo)
{
	m_part =
		"                                                                               \n"
		"precision mediump float;                                                       \n"
		"IN vec2 v_1;                                                                   \n"
		"IN vec2 v_2;                                                                   \n"
		"IN vec2 v_3;                                                                   \n"
		"IN vec2 v_4;                                                                   \n"
		"                                                                               \n"
		"uniform vec2 uTextureSize;                                                     \n"
		"uniform sampler2D uTex0;                                                       \n"
		"                                                                               \n"
		"OUT lowp vec4 fragColor;                                                       \n"
		"                                                                               \n"
		"void main() {                                                                  \n"
		"    lowp vec4 a = texture( uTex0, v_1 ) * 0.5;									\n"
		"    lowp vec4 b = texture( uTex0, v_2 ) * 1.5;									\n"
		"    lowp vec4 c = texture( uTex0, v_3 ) * 1.5;									\n"
		"    lowp vec4 d = texture( uTex0, v_4 ) * 0.5;									\n"
		"																				\n"
		"    fragColor = (a + b + c + d) / 4.0;											\n"
		;
}
