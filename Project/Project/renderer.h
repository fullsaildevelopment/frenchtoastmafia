#pragma once

#include <atlbase.h>
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <DirectXColors.h>
#include <DirectXCollision.h>
using namespace DirectX;
#include <iostream>

#include "basic_structs.h"
#include "binary_reader.h"
#include "collisions.h"
#include "DDSTextureLoader.h"
#include "Render_Manager.h"
#include "renderer_structs.h"
#include "Object System.h"
#include "WICTextureLoader.h"
#include "XTime.h"

#include "VertexShader.csh"
#include "VertexShader_Bullet.csh"
#include "VertexShader_Arena.csh"

#include "PixelShader.csh"
#include "PixelShader_Mage.csh"
#include "PixelShader_Arena.csh"
#include "PixelShader_Priest.csh"

#include "PixelShader_Screen.csh"
#include "dopeSoundSystem.h"