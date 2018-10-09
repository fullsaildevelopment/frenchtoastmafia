#pragma once
#include "fbxsdk.h"
#include <vector>
#include "Ben_structs.h"

using namespace std;

FbxManager* create_and_import(const char* fbx_file_path, FbxScene*& lScene)
{
	// Initialize the SDK manager. This object handles all our memory management.
	FbxManager* lSdkManager = FbxManager::Create();
	// Create the IO settings object.
	FbxIOSettings *ios = FbxIOSettings::Create(lSdkManager, IOSROOT);
	lSdkManager->SetIOSettings(ios);
	// Create an importer using the SDK manager.
	FbxImporter* lImporter = FbxImporter::Create(lSdkManager, "");
	// Use the first argument as the filename for the importer.
	if (!lImporter->Initialize(fbx_file_path, -1, lSdkManager->GetIOSettings())) {
		printf("Call to FbxImporter::Initialize() failed.\n");
		printf("Error returned: %s\n\n", lImporter->GetStatus().GetErrorString());
		return nullptr;
	}
	// Create a new scene so that it can be populated by the imported file.
	lScene = FbxScene::Create(lSdkManager, "imported_scene");
	// Import the contents of the file into the scene.
	lImporter->Import(lScene);
	lImporter->Destroy();
	return lSdkManager;
}

int get_scene_poly_count(const char* fbx_file_path)
{
	int result = -1;
	// Scene pointer, set by call to create_and_import
	FbxScene* scene = nullptr;
	// Create the FbxManager and import the scene from file
	FbxManager* sdk_manager = create_and_import(fbx_file_path, scene);
	// Check if manager creation failed
	if (sdk_manager == nullptr)
		return result;
	//If the scene was imported...
	if (scene != nullptr)
	{
		//No errors to report, so start polygon count at 0
		result = 0;
		// Get the count of geometry objects in the scene
		int geo_count = scene->GetGeometryCount();
		for (int i = 0; i < geo_count; ++i)
		{
			//Get geometry number 'i' 
			FbxGeometry* geo = scene->GetGeometry(i);
			// If it's not a mesh, skip it
			// Geometries might be some other type like nurbs
			if (geo->GetAttributeType() != FbxNodeAttribute::eMesh)
				continue;
			// Found a mesh, add its polygon count to the result
			FbxMesh* mesh = (FbxMesh*)geo;
			result += mesh->GetPolygonCount();
		}
	}
	//Destroy the manager
	sdk_manager->Destroy();
	//Return the polygon count for the scene
	return result;
}

void gibVertsPls(const char* fbx_file_path, vector<float> *_floatVec, vector<int> *_indVec, int *_max)
{
	FbxScene* scene = nullptr;

	FbxManager* sdk_manager = create_and_import(fbx_file_path, scene);
	//If the scene was imported...
	if (scene != nullptr)
	{
		// Get the count of geometry objects in the scene
		int geo_count = scene->GetGeometryCount();
		for (int i = 0; i < geo_count; ++i)
		{
			//Get geometry number 'i' 
			FbxGeometry* geo = scene->GetGeometry(i);
			// If it's not a mesh, skip it
			// Geometries might be some other type like nurbs
			if (geo->GetAttributeType() != FbxNodeAttribute::eMesh)
				continue;
			// Found a mesh
			FbxMesh* mesh = (FbxMesh*)geo;

			//POSITIONS

			int poly_count = mesh->GetPolygonCount();

			int* polygon_verts = mesh->GetPolygonVertices();

			const FbxVector4* control_points = mesh->GetControlPoints();
			int cpCount = mesh->GetControlPointsCount();
			int tracker = 0;

			int tempMax = 0;
			for (int i = 0; i < poly_count; i++)
			{
				for (int v = 0; v < 3; v++)
				{
					int vert_ind = i * 3 + v;
					int point_index = polygon_verts[vert_ind];
					FbxVector4 position = control_points[point_index];
					if (point_index > tracker)
					{
						tracker = point_index;
					}
					_floatVec->push_back((float)position.mData[0]);
					_floatVec->push_back((float)position.mData[1]);
					_floatVec->push_back((float)position.mData[2]);

					_indVec->push_back(point_index);

					if (point_index > tempMax)
					{
						tempMax = point_index;
					}
				}

			}

			*_max = tempMax;
			bool tr = true;
			//UVS
			//Code taken from fbx sample

			FbxStringList lUVSetNameList;
			mesh->GetUVSetNames(lUVSetNameList);

			FbxVector2 lUVValue;

			//iterating over all uv sets
			for (int lUVSetIndex = 0; lUVSetIndex < lUVSetNameList.GetCount(); lUVSetIndex++)
			{
				int what = lUVSetNameList.GetCount();
				//get lUVSetIndex-th uv set
				const char* lUVSetName = lUVSetNameList.GetStringAt(lUVSetIndex);
				const FbxGeometryElementUV* lUVElement = mesh->GetElementUV(lUVSetName);

				if (!lUVElement)
					continue;

				// only support mapping mode eByPolygonVertex and eByControlPoint
				if (lUVElement->GetMappingMode() != FbxGeometryElement::eByPolygonVertex &&
					lUVElement->GetMappingMode() != FbxGeometryElement::eByControlPoint)
					return;

				//index array, where holds the index referenced to the uv data
				const bool lUseIndex = lUVElement->GetReferenceMode() != FbxGeometryElement::eDirect;
				const int lIndexCount = (lUseIndex) ? lUVElement->GetIndexArray().GetCount() : 0;

				//iterating through the data by polygon
				const int lPolyCount = mesh->GetPolygonCount();

				if (lUVElement->GetMappingMode() == FbxGeometryElement::eByControlPoint)
				{
					for (int lPolyIndex = 0; lPolyIndex < lPolyCount; ++lPolyIndex)
					{
						// build the max index array that we need to pass into MakePoly
						const int lPolySize = mesh->GetPolygonSize(lPolyIndex);
						for (int lVertIndex = 0; lVertIndex < lPolySize; ++lVertIndex)
						{

							//get the index of the current vertex in control points array
							int lPolyVertIndex = mesh->GetPolygonVertex(lPolyIndex, lVertIndex);

							//the UV index depends on the reference mode
							int lUVIndex = lUseIndex ? lUVElement->GetIndexArray().GetAt(lPolyVertIndex) : lPolyVertIndex;

							lUVValue = lUVElement->GetDirectArray().GetAt(lUVIndex);

							_floatVec->push_back((float)lUVValue.mData[0]);
							_floatVec->push_back((float)lUVValue.mData[1]);
						}
					}
				}
				else if (lUVElement->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
				{
					int lPolyIndexCounter = 0;
					for (int lPolyIndex = 0; lPolyIndex < lPolyCount; ++lPolyIndex)
					{
						// build the max index array that we need to pass into MakePoly
						const int lPolySize = mesh->GetPolygonSize(lPolyIndex);
						for (int lVertIndex = 0; lVertIndex < lPolySize; ++lVertIndex)
						{
							if (lPolyIndexCounter < lIndexCount)
							{

								//the UV index depends on the reference mode
								int lUVIndex = lUseIndex ? lUVElement->GetIndexArray().GetAt(lPolyIndexCounter) : lPolyIndexCounter;

								lUVValue = lUVElement->GetDirectArray().GetAt(lUVIndex);

								_floatVec->push_back((float)lUVValue.mData[0]);
								_floatVec->push_back((float)lUVValue.mData[1]);

								lPolyIndexCounter++;
							}
						}
					}
				}
			}

			//NORMALS
			//Code taken from fbx sample

			FbxGeometryElementNormal* lNormalElement = mesh->GetElementNormal();
			if (lNormalElement)
			{
				//mapping mode is by control points. The mesh should be smooth and soft.
				//we can get normals by retrieving each control point
				if (lNormalElement->GetMappingMode() == FbxGeometryElement::eByControlPoint)
				{

					const int lPolyCount = mesh->GetPolygonCount();
					FbxVector4 lNormal;
					for (int i = 0; i < lPolyCount; i++)
					{
						for (int j = 0; j < 3; j++)
						{
							if (lNormalElement->GetReferenceMode() == FbxGeometryElement::eDirect)
							{
								int vert_ind = i * 3 + j;
								int point_index = polygon_verts[vert_ind];

								lNormal = lNormalElement->GetDirectArray().GetAt(point_index);

								_floatVec->push_back((float)lNormal[0]);
								_floatVec->push_back((float)lNormal[1]);
								_floatVec->push_back((float)lNormal[2]);

								if (i == (lPolyCount - 2))
								{
									bool tr = true;
								}
							}
							else
							{
								//to do
							}
						}
					}
					/*
					//Let's get normals of each vertex, since the mapping mode of normal element is by control point
					for (int lVertexIndex = 0; lVertexIndex < mesh->GetControlPointsCount(); lVertexIndex++)
					{
					int test = mesh->GetControlPointsCount();
					int lNormalIndex = 0;
					//reference mode is direct, the normal index is same as vertex index.
					//get normals by the index of control vertex
					if (lNormalElement->GetReferenceMode() == FbxGeometryElement::eDirect)
					lNormalIndex = lVertexIndex;

					//reference mode is index-to-direct, get normals by the index-to-direct
					if (lNormalElement->GetReferenceMode() == FbxGeometryElement::eIndexToDirect)
					lNormalIndex = lNormalElement->GetIndexArray().GetAt(lVertexIndex);

					//Got normals of each vertex.
					FbxVector4 lNormal = lNormalElement->GetDirectArray().GetAt(lNormalIndex);

					_floatVec->push_back((float)lNormal[0]);
					_floatVec->push_back((float)lNormal[1]);
					_floatVec->push_back((float)lNormal[2]);

					if (lVertexIndex > 1000)
					{
					bool tr = true;
					}
					*/

					//end for lVertexIndex
				}//end eByControlPoint
				 //mapping mode is by polygon-vertex.
				 //we can get normals by retrieving polygon-vertex.
				else if (lNormalElement->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
				{
					int lIndexByPolygonVertex = 0;
					//Let's get normals of each polygon, since the mapping mode of normal element is by polygon-vertex.
					for (int lPolygonIndex = 0; lPolygonIndex < mesh->GetPolygonCount(); lPolygonIndex++)
					{
						//get polygon size, you know how many vertices in current polygon.
						int lPolygonSize = mesh->GetPolygonSize(lPolygonIndex);
						//retrieve each vertex of current polygon.
						for (int i = 0; i < lPolygonSize; i++)
						{
							int lNormalIndex = 0;
							//reference mode is direct, the normal index is same as lIndexByPolygonVertex.
							if (lNormalElement->GetReferenceMode() == FbxGeometryElement::eDirect)
								lNormalIndex = lIndexByPolygonVertex;

							//reference mode is index-to-direct, get normals by the index-to-direct
							if (lNormalElement->GetReferenceMode() == FbxGeometryElement::eIndexToDirect)
								lNormalIndex = lNormalElement->GetIndexArray().GetAt(lIndexByPolygonVertex);

							//Got normals of each polygon-vertex.
							FbxVector4 lNormal = lNormalElement->GetDirectArray().GetAt(lNormalIndex);

							float normX;
							float normY;
							float normZ;

							if (lNormal.mData[0] < 0.000000000001f)
							{
								normX = 0;
							}
							else
							{
								normX = (float)lNormal.mData[0];
							}

							if (lNormal.mData[1] < 0.000000000001f)
							{
								normY = 0;
							}
							else
							{
								normY = (float)lNormal.mData[1];
							}

							if (lNormal.mData[2] < 0.000000000001f)
							{
								normZ = 0;
							}
							else
							{
								normZ = (float)lNormal.mData[2];
							}

							_floatVec->push_back(normX);
							_floatVec->push_back(normY);
							_floatVec->push_back(normZ);

							lIndexByPolygonVertex++;
						}//end for i //lPolygonSize
					}//end for lPolygonIndex //PolygonCount

				}//end eByPolygonVertex
			}//end if lNormalElement

		}
	}

	bool tr = true;
	//Destroy the manager
	sdk_manager->Destroy();
}

int materialStuff(const char* fbx_file_path, vector<myLam>* _lamVec, vector<myPhong>* _phongVec)
{

	//LARGE PORTIONS OF CODE TAKEN FROM FBX EXAMPLE "DISPLAYMATERIAL.CXX"
	FbxScene* scene = nullptr;

	FbxManager* sdk_manager = create_and_import(fbx_file_path, scene);
	//If the scene was imported...
	if (scene != nullptr)
	{
		// Get the count of geometry objects in the scene
		int geo_count = scene->GetGeometryCount();
		for (int i = 0; i < geo_count; ++i)
		{
			//Get geometry number 'i' 
			FbxGeometry* pGeometry = scene->GetGeometry(i);

			int lMaterialCount = 0;
			FbxNode* lNode = NULL;
			if (pGeometry) {
				lNode = pGeometry->GetNode();
				if (lNode)
					lMaterialCount = lNode->GetMaterialCount();
			}

			if (lMaterialCount > 0)
			{
				FbxPropertyT<FbxDouble3> lKFbxDouble3;
				FbxPropertyT<FbxDouble> lKFbxDouble1;

				for (int lCount = 0; lCount < lMaterialCount; lCount++)
				{
					FbxSurfaceMaterial *lMaterial = lNode->GetMaterial(lCount);

					//Get the implementation to see if it's a hardware shader.
					const FbxImplementation* lImplementation = GetImplementation(lMaterial, FBXSDK_IMPLEMENTATION_HLSL);
					FbxString lImplemenationType = "HLSL";
					if (!lImplementation)
					{
						lImplementation = GetImplementation(lMaterial, FBXSDK_IMPLEMENTATION_CGFX);
						lImplemenationType = "CGFX";
					}

					if (lMaterial->GetClassId().Is(FbxSurfacePhong::ClassId))
					{
						myPhong tempPhong;

						//AMBIENT VALUES
						lKFbxDouble3 = ((FbxSurfacePhong *)lMaterial)->Ambient;

						tempPhong.ambient[0] = lKFbxDouble3.Get()[0];
						tempPhong.ambient[1] = lKFbxDouble3.Get()[1];
						tempPhong.ambient[2] = lKFbxDouble3.Get()[2];

						//AMBIENT FILENAME;
						int objCount = ((FbxSurfacePhong*)lMaterial)->Ambient.GetSrcObjectCount<FbxFileTexture>();

						for (int j = 0; j < objCount; ++j)
						{
							FbxFileTexture *lTex = ((FbxSurfacePhong*)lMaterial)->Ambient.GetSrcObject<FbxFileTexture>(j);

							tempPhong.ambientFilePath = lTex->GetRelativeFileName();
						}

						//DIFFUSE VALUES
						lKFbxDouble3 = ((FbxSurfacePhong *)lMaterial)->Diffuse;

						tempPhong.diffuse[0] = lKFbxDouble3.Get()[0];
						tempPhong.diffuse[1] = lKFbxDouble3.Get()[1];
						tempPhong.diffuse[2] = lKFbxDouble3.Get()[2];

						//DIFFUSE FILENAME;
						objCount = ((FbxSurfacePhong*)lMaterial)->Diffuse.GetSrcObjectCount<FbxFileTexture>();

						for (int j = 0; j < objCount; ++j)
						{
							FbxFileTexture *lTex = ((FbxSurfacePhong*)lMaterial)->Diffuse.GetSrcObject<FbxFileTexture>(j);

							tempPhong.diffuseFilePath = lTex->GetRelativeFileName();
						}


						//SPECULAR VALUES
						lKFbxDouble3 = ((FbxSurfacePhong *)lMaterial)->Specular;

						tempPhong.specular[0] = lKFbxDouble3.Get()[0];
						tempPhong.specular[1] = lKFbxDouble3.Get()[1];
						tempPhong.specular[2] = lKFbxDouble3.Get()[2];

						//SPECULAR FILENAME;
						objCount = ((FbxSurfacePhong*)lMaterial)->Specular.GetSrcObjectCount<FbxFileTexture>();

						for (int j = 0; j < objCount; ++j)
						{
							FbxFileTexture *lTex = ((FbxSurfacePhong*)lMaterial)->Specular.GetSrcObject<FbxFileTexture>(j);

							tempPhong.specularFilePath = lTex->GetRelativeFileName();
						}

						//EMISSIVE VALUES
						lKFbxDouble3 = ((FbxSurfacePhong *)lMaterial)->Emissive;

						tempPhong.emissive[0] = lKFbxDouble3.Get()[0];
						tempPhong.emissive[1] = lKFbxDouble3.Get()[1];
						tempPhong.emissive[2] = lKFbxDouble3.Get()[2];

						//EMISSIVE FILENAME
						objCount = ((FbxSurfacePhong*)lMaterial)->Emissive.GetSrcObjectCount<FbxFileTexture>();

						for (int j = 0; j < objCount; ++j)
						{
							FbxFileTexture *lTex = ((FbxSurfacePhong*)lMaterial)->Emissive.GetSrcObject<FbxFileTexture>(j);

							tempPhong.emissiveFilePath = lTex->GetRelativeFileName();
						}

						//TRANSPARENCY
						lKFbxDouble1 = ((FbxSurfacePhong *)lMaterial)->TransparencyFactor;

						tempPhong.transparency = lKFbxDouble1.Get();

						//SHININESS
						lKFbxDouble1 = ((FbxSurfacePhong *)lMaterial)->Shininess;

						tempPhong.shininess = lKFbxDouble1.Get();

						//REFLECTIVIY
						lKFbxDouble1 = ((FbxSurfacePhong *)lMaterial)->ReflectionFactor;

						tempPhong.reflection = lKFbxDouble1.Get();

						//REFLECTIVITY FILENAME
						objCount = ((FbxSurfacePhong*)lMaterial)->Reflection.GetSrcObjectCount<FbxFileTexture>();

						for (int j = 0; j < objCount; ++j)
						{
							FbxFileTexture *lTex = ((FbxSurfacePhong*)lMaterial)->Reflection.GetSrcObject<FbxFileTexture>(j);

							tempPhong.reflectionFilePath = lTex->GetRelativeFileName();
						}

						//RETURN
						_phongVec->push_back(tempPhong);

					}
					else if (lMaterial->GetClassId().Is(FbxSurfaceLambert::ClassId))
					{
						myLam tempLam;
						// We found a Lambert material. Display its properties.


						//AMBIENT VALUES
						lKFbxDouble3 = ((FbxSurfaceLambert *)lMaterial)->Ambient;

						tempLam.ambient[0] = lKFbxDouble3.Get()[0];
						tempLam.ambient[1] = lKFbxDouble3.Get()[1];
						tempLam.ambient[2] = lKFbxDouble3.Get()[2];

						//AMBIENT FILENAME;
						int objCount = ((FbxSurfaceLambert*)lMaterial)->Ambient.GetSrcObjectCount<FbxFileTexture>();

						for (int j = 0; j < objCount; ++j)
						{
							FbxFileTexture *lTex = ((FbxSurfaceLambert*)lMaterial)->Ambient.GetSrcObject<FbxFileTexture>(j);

							tempLam.ambientFilePath = lTex->GetRelativeFileName();
						}

						//DIFFUSE VALUES
						lKFbxDouble3 = ((FbxSurfaceLambert *)lMaterial)->Diffuse;

						tempLam.diffuse[0] = lKFbxDouble3.Get()[0];
						tempLam.diffuse[1] = lKFbxDouble3.Get()[1];
						tempLam.diffuse[2] = lKFbxDouble3.Get()[2];

						//DIFFUSE FILENAME;
						objCount = ((FbxSurfaceLambert*)lMaterial)->Diffuse.GetSrcObjectCount<FbxFileTexture>();

						for (int j = 0; j < objCount; ++j)
						{
							FbxFileTexture *lTex = ((FbxSurfacePhong*)lMaterial)->Diffuse.GetSrcObject<FbxFileTexture>(j);

							tempLam.diffuseFilePath = lTex->GetRelativeFileName();
						}

						//EMISSIVE VALUES
						lKFbxDouble3 = ((FbxSurfaceLambert *)lMaterial)->Emissive;

						tempLam.emissive[0] = lKFbxDouble3.Get()[0];
						tempLam.emissive[1] = lKFbxDouble3.Get()[1];
						tempLam.emissive[2] = lKFbxDouble3.Get()[2];

						//EMISSIVE FILENAME
						objCount = ((FbxSurfaceLambert *)lMaterial)->Emissive.GetSrcObjectCount<FbxFileTexture>();

						for (int j = 0; j < objCount; ++j)
						{
							FbxFileTexture *lTex = ((FbxSurfaceLambert*)lMaterial)->Emissive.GetSrcObject<FbxFileTexture>(j);

							tempLam.emissiveFilePath = lTex->GetRelativeFileName();
						}

						//TRANSPARENCY
						lKFbxDouble1 = ((FbxSurfaceLambert *)lMaterial)->TransparencyFactor;

						tempLam.transparency = lKFbxDouble1.Get();

						//RETURN
						_lamVec->push_back(tempLam);
					}
					//FbxPropertyT<FbxString> lString;
					//lString = lMaterial->ShadingModel;
					//DisplayString("            Shading Model: ", lString.Get().Buffer());
					//DisplayString("");
				}
			}
		}
	}
	return 1;
}

void fillMageMaterial(PhongForShader* _mat, myPhong _phong)
{
	_mat->diffuse.x = _phong.diffuse[0];

	_mat->ambient.x = _phong.ambient[0];
	_mat->ambient.y = _phong.ambient[1];
	_mat->ambient.z = _phong.ambient[2];

	_mat->diffuse.x = _phong.diffuse[0];
	_mat->diffuse.y = _phong.diffuse[1];
	_mat->diffuse.z = _phong.diffuse[2];

	_mat->emissive.x = _phong.emissive[0];
	_mat->emissive.y = _phong.emissive[1];
	_mat->emissive.z = _phong.emissive[2];

	_mat->specular.x = _phong.specular[0];
	_mat->specular.y = _phong.specular[1];
	_mat->specular.z = _phong.specular[2];

	_mat->reflection = _phong.reflection;

	_mat->shininess = _phong.shininess;

	_mat->transparency = _phong.transparency;
}


