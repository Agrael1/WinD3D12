module;
#define VMODULE
#define VEXPORT export
#include <assimp/scene.h>
#include <array>
#include <vector>
#include <span>
#include <cassert>
#include "AlignedAllocator.h"
#include "DawnAdapter.h"
export module Dynamic;
export import DirectXMath;
import Graphics;

#include "DynamicVertex.h"
#include "DynamicVBuffer.h"
#include "DynamicConstant.h"