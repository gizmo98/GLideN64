/**
FXAA implementation for glslify in WebGL, adopted for GLideN64

--

From:
https://github.com/mattdesl/glsl-fxaa
*/
/**
Basic FXAA implementation based on the code on geeks3d.com with the
modification that the texture2DLod stuff was removed since it's
unsupported by WebGL.

--

From:
https://github.com/mitsuhiko/webgl-meincraft

Copyright (c) 2011 by Armin Ronacher.

Some rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are
met:

* Redistributions of source code must retain the above copyright
notice, this list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above
copyright notice, this list of conditions and the following
disclaimer in the documentation and/or other materials provided
with the distribution.

* The names of the contributors may not be used to endorse or
promote products derived from this software without specific
prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "glsl_FXAA.h"

using namespace glsl;

FXAAVertexShader::FXAAVertexShader(const opengl::GLInfo & _glinfo)
{
	m_part =
		"precision mediump float;                                 \n"
		"                                                         \n"
		"//texcoords computed in vertex step                      \n"
		"//to avoid dependent texture reads                       \n"
		"OUT vec2 v_rgbNW;                                        \n"
		"OUT vec2 v_rgbNE;                                        \n"
		"OUT vec2 v_rgbSW;                                        \n"
		"OUT vec2 v_rgbSE;                                        \n"
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
		"  v_rgbL = (fragCoord + vec2(-1.0, 0.0)) * inverseVP;  \n"
		"  v_rgbR = (fragCoord + vec2(1.0, 0.0)) * inverseVP;   \n"
		"  v_rgbM = vec2(fragCoord * inverseVP);                  \n"
		"}                                                        \n"
		;
}

FXAAFragmentShader::FXAAFragmentShader(const opengl::GLInfo & _glinfo)
{
	m_part =
		"                                                                                \n"
		"precision mediump float;                                                        \n"
		"IN vec2 v_rgbL;                                                                \n"
		"IN vec2 v_rgbR;                                                                \n"
		"IN vec2 v_rgbM;                                                                 \n"
		"                                                                                \n"
		"uniform vec2 uTextureSize;                                                      \n"
		"uniform sampler2D uTex0;                                                        \n"
		"                                                                                \n"
		"OUT lowp vec4 fragColor;                                                        \n"
		"                                                                                \n"
		"void main() {                                                                   \n"
		"  fragColor = texture2D(uTex0, v_rgbL).xyz * 0.25 + texture2D(uTex0, v_rgbM).xyz * 0.5 + texture2D(uTex0, v_rgbR).xyz * 0.25;\n"
		;
}