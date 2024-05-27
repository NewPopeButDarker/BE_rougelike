#ifndef SCENE_H
#define SCENE_H

#include "flecs/flecs.h"
#include "cglm/types.h"
#include <windows.h>

typedef struct
{
  const char *type;
  vec2 position;
  float rotation;
} SceneEntity;

typedef struct
{
  ecs_world_t *world;
  BOOL isInitialized;
  long numOfEntitiesToLoad;
  SceneEntity *entitiesToLoad;

} Scene;

Scene CreateScene();
void AddEntityToScene(Scene *scene, SceneEntity entitiy);
void InitScene(Scene *scene);
void DisposeScene(Scene *scene);

#endif
