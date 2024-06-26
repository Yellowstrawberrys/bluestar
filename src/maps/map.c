//
// Created by 정은수 on 2024. 6. 13..
//

#include <raylib.h>
#include "map.h"

#include <assert.h>
#include <raylib-tmx.h>
#include <stdio.h>
#include <stdlib.h>

#include "utils/bsutils.h"
#include "tmx.h"

Texture2D *LoadMapTexture(const char *fileName)
{
    Texture2D *tex = (Texture2D *)malloc(sizeof(Texture2D));
    if (tex != NULL)
    {
        *tex = LoadTexture(fileName);
        TraceLog(LOG_INFO, "TMX texture loaded from %s", fileName);
        return tex;
    }
    return NULL;
}

void UnloadMapTexture(Texture2D *tex)
{
    if (tex != NULL)
    {
        UnloadTexture(*tex);
        free(tex);
    }
}

void DrawTmxLayer(tmx_map *map, tmx_layer *layer)
{
    unsigned long row, col;
    unsigned int gid;
    unsigned int flip;
    tmx_tile *tile;
    unsigned int tile_width;
    unsigned int tile_height;
    Rectangle sourceRect;
    Rectangle destRect;
    Texture2D *tsTexture;
    float rotation = 0.0;
    Vector2 origin = {0.0, 0.0};

    for (row = 0; row < map->height; row++)
    {
        for (col = 0; col < map->width; col++)
        {
            gid = layer->content.gids[(row * map->width) + col];
            flip = gid & ~TMX_FLIP_BITS_REMOVAL;
            gid = gid & TMX_FLIP_BITS_REMOVAL;
            tile = map->tiles[gid];
            if (tile != NULL)
            {
                // Get tile's texture out of the tileset texture
                if (tile->image != NULL)
                {
                    tsTexture = (Texture2D *)tile->image->resource_image;
                    tile_width = tile->image->width;
                    tile_height = tile->image->height;
                }
                else
                {
                    tsTexture = (Texture2D *)tile->tileset->image->resource_image;
                    tile_width = tile->tileset->tile_width;
                    tile_height = tile->tileset->tile_height;
                }

                sourceRect.x = tile->ul_x;
                sourceRect.y = tile->ul_y;
                sourceRect.width = destRect.width = tile_width;
                sourceRect.height = destRect.height = tile_height;
                destRect.x = col * tile_width;
                destRect.y = row * tile_height;

                origin.x = 0.0;
                origin.y = 0.0;
                rotation = 0.0;
                switch(flip)
                {
                    case TMX_FLIPPED_DIAGONALLY:
                    {
                        sourceRect.height = -1 * sourceRect.height;
                        rotation = 90.0;
                    } break;
                    case TMX_FLIPPED_VERTICALLY:
                    {
                        sourceRect.height = -1 * sourceRect.height;
                    } break;
                    case TMX_FLIPPED_DIAGONALLY + TMX_FLIPPED_VERTICALLY:
                    {
                        rotation = -90.0;
                    } break;
                    case TMX_FLIPPED_HORIZONTALLY:
                    {
                        sourceRect.width = -1 * sourceRect.width;
                    } break;
                    case  TMX_FLIPPED_DIAGONALLY + TMX_FLIPPED_HORIZONTALLY:
                    {
                        rotation = 90.0;
                    } break;
                    case TMX_FLIPPED_HORIZONTALLY + TMX_FLIPPED_VERTICALLY:
                    {
                        rotation = 180.0;
                    } break;
                    case TMX_FLIPPED_DIAGONALLY + TMX_FLIPPED_HORIZONTALLY + TMX_FLIPPED_VERTICALLY:
                    {
                        sourceRect.width = -1 * sourceRect.width;
                        rotation = 90.0;
                    } break;
                    default:
                    {
                        origin.x = 0.0;
                        origin.y = 0.0;
                        rotation = 0.0;
                    } break;
                }

                if (rotation != 0.0)
                {
                    origin.x = tile_width / 2;
                    origin.y = tile_height / 2;
                    destRect.x += tile_width / 2;
                    destRect.y += tile_height / 2;
                }

                DrawTexturePro(*tsTexture, sourceRect, destRect, origin, rotation, WHITE);
            }
        }
    }
}

void RenderTmxMapToFramebuf(const char *mapFileName, RenderTexture2D *buf)
{
    tmx_layer *layer = NULL;

    tmx_img_load_func = (void *(*)(const char *))LoadMapTexture;
    tmx_img_free_func = (void (*)(void *))UnloadMapTexture;
    tmx_map *mapTmx = tmx_load(mapFileName);
    if (mapTmx == NULL) {
        tmx_perror("tmx_load");
        return;
    }

    *buf = LoadRenderTexture(mapTmx->width * mapTmx->tile_width, mapTmx->height * mapTmx->tile_height);

    BeginTextureMode(*buf);
        ClearBackground(SKYBLUE);
        layer = mapTmx->ly_head;
        while(layer)
        {
            if (layer->visible)
            {
                switch(layer->type)
                {
                    case L_LAYER:
                    {
                        TraceLog(LOG_INFO, "Render TMX layer \"%s\"", layer->name);
                        DrawTmxLayer(mapTmx, layer);
                    } break;

                    case L_GROUP:
                    case L_OBJGR:
                    case L_IMAGE:
                    case L_NONE:
                    default:
                        break;
                }
            }
            layer = layer->next;
        }
    EndTextureMode();

    tmx_map_free(mapTmx);
}
