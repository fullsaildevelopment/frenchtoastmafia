/************************************************************************
* Filename:  		Graphic_Setup.cpp
* Date:      		26/10/2018
* Mod. Date: 		08/11/2018
* Mod. Initials:	WM
* Author:    		Wichet Manawanitjarern
* Purpose:   		Combine Initialization of Render system and VR system to remove circular requirment.
					(Concept idea suggested by Lari Norri)
*************************************************************************/
#include "Graphic_Setup.h"


cGraphics_Setup::cGraphics_Setup(HWND _hwnd)
{
	hWnd = _hwnd;
}

cGraphics_Setup::~cGraphics_Setup()
{
}

void cGraphics_Setup::Initialize()
{
	UINT createDeviceFlags = 0;

	vr::EVRInitError eError = vr::VRInitError_None;

	m_pHMD = vr::VR_Init(&eError, vr::VRApplication_Scene);

	m_pRenderModels = (vr::IVRRenderModels *)vr::VR_GetGenericInterface(vr::IVRRenderModels_Version, &eError);

	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE, // the first thing to try, if failed, go to the next
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE
	};
	UINT numDriverTypes = ARRAYSIZE(driverTypes);

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0, // texture size and others..
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

	// Get Current Window Size
	RECT current_window_size;
	GetClientRect(hWnd, &current_window_size);
	m_nRenderHeight = (float)current_window_size.bottom - (float)current_window_size.top;
	m_nRenderWidth = (float)current_window_size.right - (float)current_window_size.left;



	ZeroMemory(&d3d_Swap_Chain_Desc, sizeof(DXGI_SWAP_CHAIN_DESC));
	d3d_Swap_Chain_Desc.BufferCount = 1;
	d3d_Swap_Chain_Desc.BufferDesc.Width = m_nRenderWidth;
	d3d_Swap_Chain_Desc.BufferDesc.Height = m_nRenderHeight;
	d3d_Swap_Chain_Desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // unsigned normal
	d3d_Swap_Chain_Desc.BufferDesc.RefreshRate.Numerator = 60;
	d3d_Swap_Chain_Desc.BufferDesc.RefreshRate.Denominator = 1;
	d3d_Swap_Chain_Desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	d3d_Swap_Chain_Desc.OutputWindow = hWnd;
	d3d_Swap_Chain_Desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	d3d_Swap_Chain_Desc.Windowed = true;
	d3d_Swap_Chain_Desc.SampleDesc.Count = 1; // multisampling, which antialiasing for geometry. Turn it off
	d3d_Swap_Chain_Desc.SampleDesc.Quality = 0;
	d3d_Swap_Chain_Desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH; // alt-enter fullscreen

	d3d_Swap_Chain_Desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	d3d_Swap_Chain_Desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	D3D_FEATURE_LEVEL d3d_Feature_Level = D3D_FEATURE_LEVEL_10_0;
	D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, D3D11_CREATE_DEVICE_DEBUG, nullptr, 0, D3D11_SDK_VERSION, &d3d_Swap_Chain_Desc, d3d_Swap_Chain.GetAddressOf(), d3d_Device.GetAddressOf(), &d3d_Feature_Level, d3d_Context.GetAddressOf());

	// SWAPPING BACK BUFFER
	ID3D11Texture2D *back_buffer;
	d3d_Swap_Chain.Get()->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&back_buffer);

	ZeroMemory(&d3d_Z_Buffer_Desc, sizeof(D3D11_TEXTURE2D_DESC));
	back_buffer->GetDesc(&d3d_Z_Buffer_Desc);

	ZeroMemory(&d3d_RTV_Desc, sizeof(D3D11_RENDER_TARGET_VIEW_DESC));
	d3d_RTV_Desc.Format = d3d_Z_Buffer_Desc.Format;
	d3d_RTV_Desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	d3d_RTV_Desc.Texture2D.MipSlice = 0;

	d3d_Device.Get()->CreateRenderTargetView(back_buffer, &d3d_RTV_Desc, d3d_RTV.GetAddressOf());

	d3d_Swap_Chain.Get()->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&d3d_Render_Left_Eye);
	d3d_Device.Get()->CreateRenderTargetView(d3d_Render_Left_Eye.Get(), &d3d_RTV_Desc, d3d_RTV_Left_Eye.GetAddressOf());

	d3d_Swap_Chain.Get()->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&d3d_Render_Right_Eye);
	d3d_Device.Get()->CreateRenderTargetView(d3d_Render_Right_Eye.Get(), &d3d_RTV_Desc, d3d_RTV_Right_Eye.GetAddressOf());
	back_buffer->Release();

	// Z BUFFER / DEPTH STENCIL
	ZeroMemory(&d3d_Z_Buffer_Desc, sizeof(D3D11_TEXTURE2D_DESC));
	d3d_Z_Buffer_Desc.Width = m_nRenderWidth;
	d3d_Z_Buffer_Desc.Height = m_nRenderHeight;
	d3d_Z_Buffer_Desc.MipLevels = 1;
	d3d_Z_Buffer_Desc.ArraySize = 1;
	d3d_Z_Buffer_Desc.Format = DXGI_FORMAT_D32_FLOAT_S8X24_UINT; //DXGI_FORMAT_D32_FLOAT
	d3d_Z_Buffer_Desc.SampleDesc.Count = 1;
	d3d_Z_Buffer_Desc.SampleDesc.Quality = 0;
	d3d_Z_Buffer_Desc.Usage = D3D11_USAGE_DEFAULT;
	d3d_Z_Buffer_Desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	d3d_Z_Buffer_Desc.CPUAccessFlags = 0;
	d3d_Z_Buffer_Desc.MiscFlags = 0;

	d3d_Device.Get()->CreateTexture2D(&d3d_Z_Buffer_Desc, nullptr, d3d_Z_Buffer.GetAddressOf());

	ZeroMemory(&d3d_DSS_Desc, sizeof(D3D11_DEPTH_STENCIL_DESC));
	// Depth test parameters
	d3d_DSS_Desc.DepthEnable = true;
	d3d_DSS_Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	d3d_DSS_Desc.DepthFunc = D3D11_COMPARISON_LESS;

	// Stencil test parameters
	d3d_DSS_Desc.StencilEnable = true;
	d3d_DSS_Desc.StencilReadMask = 0xFF;
	d3d_DSS_Desc.StencilWriteMask = 0xFF;

	// Stencil operations if pixel is front-facing
	d3d_DSS_Desc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	d3d_DSS_Desc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	d3d_DSS_Desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	d3d_DSS_Desc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Stencil operations if pixel is back-facing
	d3d_DSS_Desc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	d3d_DSS_Desc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	d3d_DSS_Desc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	d3d_DSS_Desc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Create depth stencil state
	d3d_Device.Get()->CreateDepthStencilState(&d3d_DSS_Desc, &d3d_DSS);

	// Bind depth stencil state
	d3d_Context.Get()->OMSetDepthStencilState(d3d_DSS.Get(), 1);

	ZeroMemory(&d3d_DSV_Desc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
	d3d_DSV_Desc.Format = d3d_Z_Buffer_Desc.Format;// DXGI_FORMAT_D32_FLOAT_S8X24_UINT;
	d3d_DSV_Desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	//descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
	d3d_DSV_Desc.Texture2D.MipSlice = 0;

	// Create the depth stencil view
	d3d_Device.Get()->CreateDepthStencilView(d3d_Z_Buffer.Get(), // Depth stencil texture
		&d3d_DSV_Desc, // Depth stencil desc
		d3d_DSV.GetAddressOf());  // [out] Depth stencil view


	//BIND RENDER TARGET VIEW
	//d3d_Context.Get()->OMSetRenderTargets(1, &d3d_RTV, d3d_DSV); // depth stencil view is for shadow map

	d3d_Context.Get()->OMSetDepthStencilState(d3d_DSS.Get(), 1);
	ID3D11RenderTargetView *tmp_rtv[] = { d3d_RTV.Get() };
	d3d_Context.Get()->OMSetRenderTargets(1, tmp_rtv, d3d_DSV.Get());
	// Clear the second depth stencil state before setting the parameters.
	//ZeroMemory(&d3d_2D_DS_Desc, sizeof(D3D11_DEPTH_STENCIL_DESC));

	// Now create a second depth stencil state which turns off the Z buffer for 2D rendering.  The only difference is
	// that DepthEnable is set to false, all other parameters are the same as the other depth stencil state.
	//d3d_2D_DS_Desc.DepthEnable = false;
	//d3d_2D_DS_Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	//d3d_2D_DS_Desc.DepthFunc = D3D11_COMPARISON_LESS;
	//d3d_2D_DS_Desc.StencilEnable = true;
	//d3d_2D_DS_Desc.StencilReadMask = 0xFF;
	//d3d_2D_DS_Desc.StencilWriteMask = 0xFF;
	//d3d_2D_DS_Desc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	//d3d_2D_DS_Desc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	//d3d_2D_DS_Desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	//d3d_2D_DS_Desc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	//d3d_2D_DS_Desc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	//d3d_2D_DS_Desc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	//d3d_2D_DS_Desc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	//d3d_2D_DS_Desc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Create the state using the device.
	//d3d_Device.Get()->CreateDepthStencilState(&d3d_2D_DS_Desc, &d3d_2D_DSS);

	//d3d_View_Port CREATION
	d3d_View_Port.Width = m_nRenderWidth;
	d3d_View_Port.Height = m_nRenderHeight;
	d3d_View_Port.TopLeftX = 0;
	d3d_View_Port.TopLeftY = 0;
	d3d_View_Port.MinDepth = 0.0f;
	d3d_View_Port.MaxDepth = 1.0f;

	// RASTERIZER STATE
	ZeroMemory(&d3d_Rasterizer_Desc, sizeof(D3D11_RASTERIZER_DESC));
	d3d_Rasterizer_Desc.FillMode = D3D11_FILL_SOLID;
	d3d_Rasterizer_Desc.CullMode = D3D11_CULL_NONE;
	d3d_Rasterizer_Desc.DepthBias = 0;
	d3d_Rasterizer_Desc.SlopeScaledDepthBias = 0.0f;
	d3d_Rasterizer_Desc.DepthBiasClamp = 0.0f;
	d3d_Rasterizer_Desc.DepthClipEnable = TRUE;
	d3d_Rasterizer_Desc.ScissorEnable = FALSE;
	d3d_Rasterizer_Desc.MultisampleEnable = FALSE;
	d3d_Rasterizer_Desc.AntialiasedLineEnable = FALSE;

	d3d_Device.Get()->CreateRasterizerState(&d3d_Rasterizer_Desc, &d3d_Rasterizer_State);

	// SAMPLER STATE
	ZeroMemory(&d3d_Sampler_State_Desc, sizeof(D3D11_SAMPLER_DESC));
	d3d_Sampler_State_Desc.Filter = D3D11_FILTER_ANISOTROPIC;
	d3d_Sampler_State_Desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	d3d_Sampler_State_Desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	d3d_Sampler_State_Desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	d3d_Sampler_State_Desc.MipLODBias = 0.0;
	d3d_Sampler_State_Desc.MaxAnisotropy = 16;
	d3d_Sampler_State_Desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	d3d_Sampler_State_Desc.MinLOD = 0;
	d3d_Sampler_State_Desc.MaxLOD = 0;

	d3d_Device.Get()->CreateSamplerState(&d3d_Sampler_State_Desc, d3d_Sampler_State.GetAddressOf());

	// SHADERS
	d3d_Device.Get()->CreateVertexShader(VertexShader, sizeof(VertexShader), NULL, d3d_Vertex_Shader.GetAddressOf());
	d3d_Device.Get()->CreatePixelShader(PixelShader, sizeof(PixelShader), NULL, d3d_Pixel_Shader.GetAddressOf());

	// INPUT ELEMENT
	D3D11_INPUT_ELEMENT_DESC d3d_Input_Element[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXTURE", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "JOINTS", 0, DXGI_FORMAT_R32G32B32A32_UINT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "WEIGHTS", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	d3d_Device.Get()->CreateInputLayout(d3d_Input_Element, ARRAYSIZE(d3d_Input_Element), VertexShader, sizeof(VertexShader), d3d_Input_Layout.GetAddressOf());


	// BIND d3d_View_Port
	d3d_Context.Get()->RSSetViewports(1, &d3d_View_Port);

	m_cCameraLeft = new cCamera;

	// Set the initial position of the camera.
	m_cCameraLeft->SetPosition(tFloat4x4{
											1.0f, 0.0f, 0.0f, 0.0f,
											0.0f, 1.0f, 0.0f, 0.0f,
											0.0f, 0.0f, 1.0f, 0.0f,
											0.0f, 0.0f, 0.0f, 1.0f
		});

	// Create the camera object.
	m_cCameraRight = new cCamera;

	// Set the initial position of the camera.
	m_cCameraRight->SetPosition(tFloat4x4{
											1.0f, 0.0f, 0.0f, 0.0f,
											0.0f, 1.0f, 0.0f, 0.0f,
											0.0f, 0.0f, 1.0f, 0.0f,
											1.0f, 0.0f, 0.0f, 1.0f
		});

	//Removed model and shader class declaration

	//Removed texture class declaration

	//Removed debug window stuff


	// Create an orthographic projection matrix for 2D rendering.
	//D3DXMatrixOrthoLH(&m_orthoMatrix, (float)screenWidth, (float)screenHeight, screenNear, screenDepth);
	//DirectX::XMMATRIX mo = DirectX::XMMatrixOrthographicLH((float)fWindow_Width, (float)fWindow_Height, 0, 10);
	//m_orthoMatrix.set((const float*)&mo.r);

	m_fScale = 0.3f;
	m_fScaleSpacing = 4.0f;

	m_fNearClip = fNearClip;
	m_fFarClip = fFarClip; // 30-125 dont use fFarClip (1000)

	//SetupCameras();

	if (!vr::VRCompositor())
	{
		printf("Compositor initialization failed. See log file for details\n");
		//		return false;
	}

	//	return true;

	//UpdateHMDMatrixPose();
}

void cGraphics_Setup::Clean_Up()
{
}

vr::IVRSystem* cGraphics_Setup::Get_HMD()
{
	return m_pHMD;
}

ComPtr<ID3D11Device> cGraphics_Setup::Get_Device()
{
	return d3d_Device;
}

ComPtr<ID3D11DeviceContext> cGraphics_Setup::Get_Context()
{
	return d3d_Context;
}

ComPtr<ID3D11RenderTargetView> cGraphics_Setup::Get_RTV()
{
	return d3d_RTV;
}

ComPtr<ID3D11RenderTargetView> cGraphics_Setup::Get_RTV_Left()
{
	return d3d_RTV_Left_Eye;
}

ComPtr<ID3D11RenderTargetView> cGraphics_Setup::Get_RTV_Right()
{
	return d3d_RTV_Right_Eye;
}

ComPtr<ID3D11DepthStencilView> cGraphics_Setup::Get_DSV()
{
	return d3d_DSV;
}

ComPtr<ID3D11InputLayout> cGraphics_Setup::Get_Input_Layout()
{
	return d3d_Input_Layout;
}

ComPtr<ID3D11VertexShader> cGraphics_Setup::Get_Vertex_Shader()
{
	return d3d_Vertex_Shader;
}

ComPtr<ID3D11PixelShader> cGraphics_Setup::Get_Pixel_Shader()
{
	return d3d_Pixel_Shader;
}

ComPtr<IDXGISwapChain> cGraphics_Setup::Get_Swap_Chain()
{
	return d3d_Swap_Chain;
}

D3D11_VIEWPORT cGraphics_Setup::Get_View_Port()
{
	return d3d_View_Port;
}

ComPtr<ID3D11DepthStencilState> cGraphics_Setup::Get_Depth_Stencil_State()
{
	return d3d_DSS;
}

ComPtr<ID3D11Texture2D> cGraphics_Setup::Get_Texture_Left_Eye()
{
	return d3d_Render_Left_Eye;
}

ComPtr<ID3D11Texture2D> cGraphics_Setup::Get_Texture_Right_Eye()
{
	return d3d_Render_Right_Eye;
}

cCamera cGraphics_Setup::get_Camera_Left()
{
	return *m_cCameraLeft;
}

cCamera cGraphics_Setup::get_Camera_Right()
{
	return *m_cCameraRight;
}