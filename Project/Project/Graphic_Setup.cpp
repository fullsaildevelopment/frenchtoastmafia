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
	d3d_Swap_Chain_Desc.BufferDesc.Width = m_nRenderHeight;
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
	D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, D3D11_CREATE_DEVICE_DEBUG, nullptr, 0, D3D11_SDK_VERSION, &d3d_Swap_Chain_Desc, &d3d_Swap_Chain, &d3d_Device, &d3d_Feature_Level, &d3d_Context);

	// SWAPPING BACK BUFFER
	ID3D11Texture2D *back_buffer;
	d3d_Swap_Chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&back_buffer);

	ZeroMemory(&d3d_Z_Buffer_Desc, sizeof(D3D11_TEXTURE2D_DESC));
	back_buffer->GetDesc(&d3d_Z_Buffer_Desc);

	ZeroMemory(&d3d_RTV_Desc, sizeof(D3D11_RENDER_TARGET_VIEW_DESC));
	d3d_RTV_Desc.Format = d3d_Z_Buffer_Desc.Format;
	d3d_RTV_Desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	d3d_RTV_Desc.Texture2D.MipSlice = 0;

	d3d_Device->CreateRenderTargetView(back_buffer, NULL, &d3d_RTV.p);
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

	d3d_Device->CreateTexture2D(&d3d_Z_Buffer_Desc, nullptr, &d3d_Z_Buffer.p);

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
	d3d_Device->CreateDepthStencilState(&d3d_DSS_Desc, &d3d_DSS);

	// Bind depth stencil state
	d3d_Context->OMSetDepthStencilState(d3d_DSS, 1);

	ZeroMemory(&d3d_DSV_Desc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
	d3d_DSV_Desc.Format = d3d_Z_Buffer_Desc.Format;// DXGI_FORMAT_D32_FLOAT_S8X24_UINT;
	d3d_DSV_Desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	//descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
	d3d_DSV_Desc.Texture2D.MipSlice = 0;

	// Create the depth stencil view
	d3d_Device->CreateDepthStencilView(d3d_Z_Buffer, // Depth stencil texture
		&d3d_DSV_Desc, // Depth stencil desc
		&d3d_DSV.p);  // [out] Depth stencil view


	//BIND RENDER TARGET VIEW
	//d3d_Context->OMSetRenderTargets(1, &d3d_RTV, d3d_DSV); // depth stencil view is for shadow map

	ID3D11RenderTargetView *tmp_rtv[] = { d3d_RTV };
	d3d_Context->OMSetDepthStencilState(d3d_DSS, 1);
	d3d_Context->OMSetRenderTargets(1, tmp_rtv, d3d_DSV);
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
	//d3d_Device->CreateDepthStencilState(&d3d_2D_DS_Desc, &d3d_2D_DSS);

	//d3d_View_Port CREATION
	d3d_View_Port.Width = static_cast<float>(m_nRenderWidth);
	d3d_View_Port.Height = static_cast<float>(m_nRenderHeight);
	d3d_View_Port.TopLeftX = 0;
	d3d_View_Port.TopLeftY = 0;
	d3d_View_Port.MinDepth = 0.0f;
	d3d_View_Port.MaxDepth = 1.0f;

	// RASTERIZER STATE
	ZeroMemory(& d3d_Rasterizer_Desc, sizeof(D3D11_RASTERIZER_DESC));
	 d3d_Rasterizer_Desc.FillMode = D3D11_FILL_SOLID;
	 d3d_Rasterizer_Desc.CullMode = D3D11_CULL_BACK;
	 d3d_Rasterizer_Desc.DepthBias = 0;
	 d3d_Rasterizer_Desc.SlopeScaledDepthBias = 0.0f;
	 d3d_Rasterizer_Desc.DepthBiasClamp = 0.0f;
	 d3d_Rasterizer_Desc.DepthClipEnable = TRUE;
	 d3d_Rasterizer_Desc.ScissorEnable = FALSE;
	 d3d_Rasterizer_Desc.MultisampleEnable = FALSE;
	 d3d_Rasterizer_Desc.AntialiasedLineEnable = FALSE;

	d3d_Device->CreateRasterizerState(& d3d_Rasterizer_Desc, &d3d_Rasterizer_State);

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

	d3d_Device->CreateSamplerState(&d3d_Sampler_State_Desc, &d3d_Sampler_State.p);

	// SHADERS
	d3d_Device->CreateVertexShader(VertexShader, sizeof(VertexShader), NULL, &d3d_Vertex_Shader.p);
	d3d_Device->CreatePixelShader(PixelShader, sizeof(PixelShader), NULL, &d3d_Pixel_Shader.p);

	// INPUT ELEMENT
	D3D11_INPUT_ELEMENT_DESC d3d_Input_Element[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXTURE", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	d3d_Device->CreateInputLayout(d3d_Input_Element, ARRAYSIZE(d3d_Input_Element), VertexShader, sizeof(VertexShader), &d3d_Input_Layout.p);


	// BIND d3d_View_Port
	d3d_Context->RSSetViewports(1, &d3d_View_Port);

	m_cCameraLeft = new cCamera;
	
	// Set the initial position of the camera.
	m_cCameraLeft->SetPosition(tFloat4{ 0.0f, 0.0f, -10.0f, 1.0f });

	// Create the camera object.
	m_cCameraRight = new cCamera;

	// Set the initial position of the camera.
	m_cCameraRight->SetPosition(tFloat4{ 0.0f, 0.0f, -10.0f, 1.0f });

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
	m_fFarClip = fFarClip;

	SetupCameras();

	if (!vr::VRCompositor())
	{
		printf("Compositor initialization failed. See log file for details\n");
//		return false;
	}

//	return true;


}

void cGraphics_Setup::Clean_Up()
{
}


tFloat4x4 cGraphics_Setup::GetHMDMatrixPoseEye(vr::Hmd_Eye nEye)
{
	if (!m_pHMD)
	{
		return tFloat4x4();
	}

	vr::HmdMatrix34_t matEyeRight = m_pHMD->GetEyeToHeadTransform(nEye);
	tFloat4x4 in_mat, out_mat;

	in_mat.tX.fX = matEyeRight.m[0][0];
	in_mat.tX.fY = matEyeRight.m[1][0];
	in_mat.tX.fZ = matEyeRight.m[2][0];
	in_mat.tX.fW = 0.0f;

	in_mat.tY.fX = matEyeRight.m[0][1];
	in_mat.tY.fY = matEyeRight.m[1][1];
	in_mat.tY.fZ = matEyeRight.m[2][1];
	in_mat.tY.fW = 0.0f;

	in_mat.tZ.fX = matEyeRight.m[0][2];
	in_mat.tZ.fY = matEyeRight.m[1][2];
	in_mat.tZ.fZ = matEyeRight.m[2][2];
	in_mat.tZ.fW = 0.0f;

	in_mat.tW.fX = matEyeRight.m[0][3];
	in_mat.tW.fY = matEyeRight.m[1][3];
	in_mat.tW.fZ = matEyeRight.m[2][3];
	in_mat.tW.fW = 1.0f;

	out_mat = TMATRIX_To_tFloat4x4(Matrix_Inverse(tFloat4x4_To_TMATRIX(in_mat)));

	return out_mat;
}


tFloat4x4 cGraphics_Setup::GetHMDMatrixProjectionEye(vr::Hmd_Eye nEye)
{
	if (!m_pHMD)
		return tFloat4x4();
	// TODO check here
	vr::HmdMatrix44_t mat = m_pHMD->GetProjectionMatrix(nEye, m_fNearClip, m_fFarClip);

	tFloat4x4 out_mat;

	out_mat.tX.fX = mat.m[0][0];
	out_mat.tX.fY = mat.m[1][0];
	out_mat.tX.fZ = mat.m[2][0];
	out_mat.tX.fW = mat.m[3][0];

	out_mat.tY.fX = mat.m[0][1];
	out_mat.tY.fY = mat.m[1][1];
	out_mat.tY.fZ = mat.m[2][1];
	out_mat.tY.fW = mat.m[3][1];

	out_mat.tZ.fX = mat.m[0][2];
	out_mat.tZ.fY = mat.m[1][2];
	out_mat.tZ.fZ = mat.m[2][2];
	out_mat.tZ.fW = mat.m[3][2];

	out_mat.tW.fX = mat.m[0][3];
	out_mat.tW.fY = mat.m[1][3];
	out_mat.tW.fZ = mat.m[2][3];
	out_mat.tW.fW = mat.m[3][3];

	return out_mat;
}

void cGraphics_Setup::SetupCameras()
{
	m_mat4ProjectionLeft = GetHMDMatrixProjectionEye(vr::Eye_Left);
	m_mat4ProjectionRight = GetHMDMatrixProjectionEye(vr::Eye_Right);
	m_mat4eyePosLeft = GetHMDMatrixPoseEye(vr::Eye_Left);
	m_mat4eyePosRight = GetHMDMatrixPoseEye(vr::Eye_Right);
}

tFloat4x4 cGraphics_Setup::GetCurrentViewProjectionMatrix(vr::Hmd_Eye nEye)
{
	tFloat4x4 out_mat;
	if (nEye == vr::Eye_Left)
	{
		out_mat = TMATRIX_To_tFloat4x4(Matrix_Matrix_Multiply(Matrix_Matrix_Multiply(tFloat4x4_To_TMATRIX(m_mat4ProjectionLeft), tFloat4x4_To_TMATRIX(m_mat4eyePosLeft)), tFloat4x4_To_TMATRIX(m_mat4HMDPose)));
	}
	else if (nEye == vr::Eye_Right)
	{
		out_mat = TMATRIX_To_tFloat4x4(Matrix_Matrix_Multiply(Matrix_Matrix_Multiply(tFloat4x4_To_TMATRIX(m_mat4ProjectionRight), tFloat4x4_To_TMATRIX(m_mat4eyePosRight)), tFloat4x4_To_TMATRIX(m_mat4HMDPose)));
	}

	return out_mat;
}

tFloat4x4 cGraphics_Setup::ConvertSteamVRMatrixToMatrix4(const vr::HmdMatrix34_t &matPose)
{
	tFloat4x4 out_mat;

	out_mat.tX.fX = matPose.m[0][0];
	out_mat.tX.fY = matPose.m[1][0];
	out_mat.tX.fZ = matPose.m[2][0];
	out_mat.tX.fW = 0.0f;

	out_mat.tY.fX = matPose.m[0][1];
	out_mat.tY.fY = matPose.m[1][1];
	out_mat.tY.fZ = matPose.m[2][1];
	out_mat.tY.fW = 0.0f;

	out_mat.tZ.fX = matPose.m[0][2];
	out_mat.tZ.fY = matPose.m[1][2];
	out_mat.tZ.fZ = matPose.m[2][2];
	out_mat.tZ.fW = 0.0f;

	out_mat.tW.fX = matPose.m[0][3];
	out_mat.tW.fY = matPose.m[1][3];
	out_mat.tW.fZ = matPose.m[2][3];
	out_mat.tW.fW = 1.0f;

	return out_mat;
}

void cGraphics_Setup::UpdateHMDMatrixPose()
{
	if (!m_pHMD)
		return;

	vr::VRCompositor()->WaitGetPoses(m_rTrackedDevicePose, vr::k_unMaxTrackedDeviceCount, NULL, 0);

	m_iValidPoseCount = 0;
	m_strPoseClasses = "";
	for (int nDevice = 0; nDevice < vr::k_unMaxTrackedDeviceCount; ++nDevice)
	{
		if (m_rTrackedDevicePose[nDevice].bPoseIsValid)
		{
			m_iValidPoseCount++;

			m_mat4HMDPose.tX.fX = ConvertSteamVRMatrixToMatrix4(m_rTrackedDevicePose[nDevice].mDeviceToAbsoluteTracking).tX.fX;
			m_mat4HMDPose.tX.fY = ConvertSteamVRMatrixToMatrix4(m_rTrackedDevicePose[nDevice].mDeviceToAbsoluteTracking).tX.fY;
			m_mat4HMDPose.tX.fZ = ConvertSteamVRMatrixToMatrix4(m_rTrackedDevicePose[nDevice].mDeviceToAbsoluteTracking).tX.fZ;
			m_mat4HMDPose.tX.fW = ConvertSteamVRMatrixToMatrix4(m_rTrackedDevicePose[nDevice].mDeviceToAbsoluteTracking).tX.fW;

			m_mat4HMDPose.tY.fX = ConvertSteamVRMatrixToMatrix4(m_rTrackedDevicePose[nDevice].mDeviceToAbsoluteTracking).tY.fX;
			m_mat4HMDPose.tY.fY = ConvertSteamVRMatrixToMatrix4(m_rTrackedDevicePose[nDevice].mDeviceToAbsoluteTracking).tY.fY;
			m_mat4HMDPose.tY.fZ = ConvertSteamVRMatrixToMatrix4(m_rTrackedDevicePose[nDevice].mDeviceToAbsoluteTracking).tY.fZ;
			m_mat4HMDPose.tY.fW = ConvertSteamVRMatrixToMatrix4(m_rTrackedDevicePose[nDevice].mDeviceToAbsoluteTracking).tY.fW;

			m_mat4HMDPose.tZ.fX = ConvertSteamVRMatrixToMatrix4(m_rTrackedDevicePose[nDevice].mDeviceToAbsoluteTracking).tZ.fX;
			m_mat4HMDPose.tZ.fY = ConvertSteamVRMatrixToMatrix4(m_rTrackedDevicePose[nDevice].mDeviceToAbsoluteTracking).tZ.fY;
			m_mat4HMDPose.tZ.fZ = ConvertSteamVRMatrixToMatrix4(m_rTrackedDevicePose[nDevice].mDeviceToAbsoluteTracking).tZ.fZ;
			m_mat4HMDPose.tZ.fW = ConvertSteamVRMatrixToMatrix4(m_rTrackedDevicePose[nDevice].mDeviceToAbsoluteTracking).tZ.fW;

			m_mat4HMDPose.tW.fX = ConvertSteamVRMatrixToMatrix4(m_rTrackedDevicePose[nDevice].mDeviceToAbsoluteTracking).tW.fX;
			m_mat4HMDPose.tW.fY = ConvertSteamVRMatrixToMatrix4(m_rTrackedDevicePose[nDevice].mDeviceToAbsoluteTracking).tW.fY;
			m_mat4HMDPose.tW.fZ = ConvertSteamVRMatrixToMatrix4(m_rTrackedDevicePose[nDevice].mDeviceToAbsoluteTracking).tW.fZ;
			m_mat4HMDPose.tW.fW = ConvertSteamVRMatrixToMatrix4(m_rTrackedDevicePose[nDevice].mDeviceToAbsoluteTracking).tW.fW;

			if (m_rDevClassChar[nDevice] == 0)
			{
				switch (m_pHMD->GetTrackedDeviceClass(nDevice))
				{
				case vr::TrackedDeviceClass_Controller:        m_rDevClassChar[nDevice] = 'C'; break;
				case vr::TrackedDeviceClass_HMD:               m_rDevClassChar[nDevice] = 'H'; break;
				case vr::TrackedDeviceClass_Invalid:           m_rDevClassChar[nDevice] = 'I'; break;
				case vr::TrackedDeviceClass_GenericTracker:    m_rDevClassChar[nDevice] = 'O'; break;
				case vr::TrackedDeviceClass_TrackingReference: m_rDevClassChar[nDevice] = 'T'; break;
				default:                                       m_rDevClassChar[nDevice] = '?'; break;
				}
			}
			m_strPoseClasses += m_rDevClassChar[nDevice];
		}
	}

	if (m_rTrackedDevicePose[vr::k_unTrackedDeviceIndex_Hmd].bPoseIsValid)
	{
		m_mat4HMDPose = TMATRIX_To_tFloat4x4(Matrix_Inverse(tFloat4x4_To_TMATRIX(m_rmat4DevicePose[vr::k_unTrackedDeviceIndex_Hmd])));
	}
	else
	{
		//dprintf("pose not valid");
	}
}

CComPtr<ID3D11Device> cGraphics_Setup::GetDevice()
{
	return d3d_Device;
}
