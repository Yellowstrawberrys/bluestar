//
// Created by 정은수 on 2024. 6. 13..
//

#pragma once
#include <raylib.h>
#include "map.h"

#include <assert.h>
#include <raylib-tmx.h>
#include <stdio.h>
#include <stdlib.h>

#include "bsutils.h"
#include "tmx.h"


Texture2D *LoadMapTexture(const char *fileName);
void UnloadMapTexture(Texture2D *tex);
void DrawTmxLayer(tmx_map *map, tmx_layer *layer);
void RenderTmxMapToFramebuf(const char *mapFileName, RenderTexture2D *buf);
