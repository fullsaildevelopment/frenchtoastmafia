/************************************************************************
* Filename:  		Animation_Manager.cpp
* Date:      		05/11/2018
* Mod. Date: 		08/11/2018
* Mod. Initials:	WM
* Author:    		Wichet Manawanitjarern
* Purpose:   		Managing system to handle all animation related task.
*************************************************************************/

#include "Animation_Manager.h"

cAnimation_Manager::cAnimation_Manager()
{
	m_fCurrent_Time = 0.0f;
}

cAnimation_Manager::~cAnimation_Manager()
{
}

void cAnimation_Manager::Animate(double dDelta, double dTotal, tScene_Objects* tObject_List)
{
	for (int i = 0; i < tObject_List->nObject_Count; i++)
	{
		//turn off mage
		if (i == 0)
		{
			continue;
		}
		if (tObject_List->bIs_Animated[i])
		{
			if (i == 2)
			{
				if (tObject_List->currAnim[i] != currentAnim)
				{
					currentAnim = tObject_List->currAnim[i];

					m_fCurrent_Time = 0.0f;
				}
			}
			m_fCurrent_Time += (float)dDelta * 0.5;

			int nFrame_Size = tObject_List->tAnim_Clip[i][currentAnim].tKeyFrames.size();

			int nNext_Frame, nPrevious_Frame;
			float fNext_Time, fPrevious_Time, fRatio, fTotal_Time;
			std::vector<tJoint> tLerped_Joints;
			std::vector<XMMATRIX> tTweened_Joints;

			while (m_fCurrent_Time < (float)tObject_List->tAnim_Clip[i][currentAnim].tKeyFrames[0].dTime)
				m_fCurrent_Time += (float)tObject_List->tAnim_Clip[i][currentAnim].dDuration;

			while (m_fCurrent_Time > (float)tObject_List->tAnim_Clip[i][currentAnim].dDuration)
				m_fCurrent_Time -= (float)tObject_List->tAnim_Clip[i][currentAnim].dDuration;

			for (int j = 1; j < nFrame_Size; j++)
			{
				nNext_Frame = j;
				fNext_Time = (float)tObject_List->tAnim_Clip[i][currentAnim].tKeyFrames[nNext_Frame].dTime;

				if (j == 1)
				{
					nPrevious_Frame = (int)tObject_List->tAnim_Clip[i][currentAnim].tKeyFrames.size() - 1;
					fPrevious_Time = 0.0f;
				}
				else
				{
					nPrevious_Frame = j - 1;
					fPrevious_Time = (float)tObject_List->tAnim_Clip[i][currentAnim].tKeyFrames[nPrevious_Frame].dTime;
				}

				if (m_fCurrent_Time < fNext_Time)
					break;
			}

			//printf("dDelta = %d\n", dDelta);
			//printf("Next Frame = %d\n", nNext_Frame);

			fTotal_Time = fNext_Time - fPrevious_Time;
			fRatio = (m_fCurrent_Time - fPrevious_Time) / fTotal_Time;

			if (currentAnim == 1 && fRatio > 1)
			{
				tObject_List->currAnim[i] = 0;
			}

			int nJoint_Size = (int)tObject_List->tAnim_Clip[i][currentAnim].tKeyFrames[nNext_Frame].tJoints.size();

			for (int j = 0; j < nJoint_Size; j++)
			{
				tJoint tNext_Joint = tObject_List->tAnim_Clip[i][currentAnim].tKeyFrames[nNext_Frame].tJoints[j];
				tJoint tPrevious_Joint = tObject_List->tAnim_Clip[i][currentAnim].tKeyFrames[nPrevious_Frame].tJoints[j];

				tFloat3 tNext_Position, tPrevious_Position;

				tNext_Position.fX = tNext_Joint.tData.tW.fX;
				tNext_Position.fY = tNext_Joint.tData.tW.fY;
				tNext_Position.fZ = tNext_Joint.tData.tW.fZ;

				tPrevious_Position.fX = tPrevious_Joint.tData.tW.fX;
				tPrevious_Position.fY = tPrevious_Joint.tData.tW.fY;
				tPrevious_Position.fZ = tPrevious_Joint.tData.tW.fZ;

				tFloat4 tLerped_Position = Joint_Position_Lerp(tPrevious_Position, tNext_Position, fRatio);

				XMFLOAT4X4 fPrevious_Joint = tFloat4x4_to_XMFLOAT4x4(tPrevious_Joint.tData);
				XMMATRIX mPrevious_Joint = XMLoadFloat4x4(&fPrevious_Joint);
				XMVECTOR vPrevious_Joint = XMQuaternionRotationMatrix(mPrevious_Joint);

				XMFLOAT4X4 fNext_Joint = tFloat4x4_to_XMFLOAT4x4(tNext_Joint.tData);
				XMMATRIX mNext_Joint = XMLoadFloat4x4(&fNext_Joint);
				XMVECTOR vNext_Joint = XMQuaternionRotationMatrix(mNext_Joint);

				XMVECTOR vSlerped = XMQuaternionSlerp(vPrevious_Joint, vNext_Joint, fRatio);
				XMMATRIX mQuarted = XMMatrixRotationQuaternion(vSlerped);

				mQuarted.r[3].m128_f32[0] = tLerped_Position.fX;
				mQuarted.r[3].m128_f32[1] = tLerped_Position.fY;
				mQuarted.r[3].m128_f32[2] = tLerped_Position.fZ;
				mQuarted.r[3].m128_f32[3] = tLerped_Position.fW;

				tTweened_Joints.push_back(mQuarted);
				XMFLOAT4X4 fQuarted;
				XMStoreFloat4x4(&fQuarted, mQuarted);
				tJoint tQuarted;
				tQuarted.tData = XMFLOAT4x4_to_tFloat4x4(fQuarted);
				tLerped_Joints.push_back(tQuarted);
			}

			for (int j = 0; j < nJoint_Size; j++)
			{
				//	tObject_List->tAnim_Data[i].tTweened.clear();
				tFloat4x4 tInverse = tObject_List->tAnim_Data[i].tInverse[j];
				XMFLOAT4X4 xmf_Inverse = tFloat4x4_to_XMFLOAT4x4(tInverse);
				XMMATRIX xmm_Inverse = XMLoadFloat4x4(&xmf_Inverse);
				XMMATRIX xmm_Out = XMMatrixMultiply(xmm_Inverse, tTweened_Joints[j]);
				XMFLOAT4X4 xmf_Out;
				XMStoreFloat4x4(&xmf_Out, xmm_Out);
				tFloat4x4 tOut = XMFLOAT4x4_to_tFloat4x4(xmf_Out);

				tObject_List->tAnim_Data[i].tTweened[j] = tOut;
			}
		}
	}
}
