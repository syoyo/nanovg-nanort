//
// Copyright (c) 2013 Mikko Mononen memon@inside.org
//
// This software is provided 'as-is', without any express or implied
// warranty.  In no event will the authors be held liable for any damages
// arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.
//

#include <stdio.h>
#include "nanovg.h"
#define NANOVG_RT_IMPLEMENTATION
#define NANORT_IMPLEMENTATION
#include "nanovg_rt.h"
#include "demo.h"

#ifdef __cplusplus
extern "C" {
#endif

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#ifdef __cplusplus
}
#endif


int main()
{
	NVGcontext* vg = NULL;
	DemoData data;

  int winWidth = 1024;
  int winHeight = 1024;

	vg = nvgCreateRT(NVG_STENCIL_STROKES | NVG_DEBUG, winWidth, winHeight);
	if (vg == NULL) {
		printf("Could not init nanovg.\n");
		return -1;
	}

	if (loadDemoData(vg, &data) == -1)
		return -1;

  float pxRatio = 1.0f;

  nvgBeginFrame(vg, winWidth, winHeight, pxRatio);

	renderDemo(vg, 0,0, winWidth,winHeight, 15.0f, 0, &data);

  nvgEndFrame(vg);

	freeDemoData(vg, &data);

	unsigned char* rgba = nvgReadPixelsRT(vg);
  stbi_write_png("render.png",  winWidth, winHeight, 4, rgba, winWidth * 4);

	nvgDeleteRT(vg);

	return 0;
}
