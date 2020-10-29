#include "glsl_DitherFilter.h"

using namespace glsl;

DitherFilterVertexShader::DitherFilterVertexShader(const opengl::GLInfo & _glinfo)
{
	m_part =
		"precision mediump float;                                 \n"
		"                                                         \n"
		"//texcoords computed in vertex step                      \n"
		"//to avoid dependent texture reads                       \n"
		"OUT vec2 v_rgbT;                                         \n"
		"OUT vec2 v_rgbB;                                         \n"
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
		"  v_rgbT = (fragCoord + vec2(0.0, -1.0)) * inverseVP;    \n"
		"  v_rgbB = (fragCoord + vec2(0.0, 1.0)) * inverseVP;     \n"
		"  v_rgbM = vec2(fragCoord * inverseVP);                  \n"
		"}                                                        \n"
		;
}

DitherFilterFragmentShader::DitherFilterFragmentShader(const opengl::GLInfo & _glinfo)
{
	m_part =
		"                                                                                \n"
		"precision mediump float;                                                        \n"
		"IN vec2 v_rgbT;                                                                 \n"
		"IN vec2 v_rgbB;                                                                 \n"
		"IN vec2 v_rgbM;                                                                 \n"
		"                                                                                \n"
		"uniform vec2 uTextureSize;                                                      \n"
		"uniform sampler2D uTex0;                                                        \n"
		"                                                                                \n"
		"OUT lowp vec4 fragColor;                                                        \n"
		"                                                                                \n"
		"void main() {                                                                   \n"
		"  float limit = 0.2;                                                          \n"
		"  vec3 col = vec3(0.0);                                                         \n"
		"  vec3 colT = texture2D(uTex0, v_rgbT).xyz;                                     \n"
		"  vec3 colM = texture2D(uTex0, v_rgbM).xyz;                                     \n"
		"  vec3 colB = texture2D(uTex0, v_rgbB).xyz;                                     \n"
		"  if(abs(colM.r - colT.r) < limit && abs(colM.g - colT.g) < limit && abs(colM.b - colT.b) < limit)\n"
		"    col += colB * 0.25;                                                         \n"
		"  else                                                                          \n"
		"    col += colM * 0.25;                                                         \n"
		"                                                                                \n"
		"  if(abs(colM.r - colB.r) < limit && abs(colM.g - colB.g) < limit && abs(colM.b - colB.b) < limit)\n"
		"    col += colB * 0.25;                                                         \n"
		"  else                                                                          \n"
		"    col += colM * 0.25;                                                         \n"
		"                                                                                \n"
		"  col += colM * 0.5;                                                            \n"
		"                                                                                \n"
		"  fragColor = vec4(col.r,col.g,col.b,1.0);                                      \n"
		;
}
