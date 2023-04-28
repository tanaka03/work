//============================
//
// �A�C�e���ݒ�
// Author:hamada ryuuga
//
//============================

#include <stdio.h>
#include "item.h"
#include "camera.h"
#include "shadow.h"
#include "file.h"
#include "line.h"
#include "comn.h"
#include "score.h"
#include "fade.h"
#include "mesh.h"
#include "floor.h"
#include "end.h"
#include "title.h"
#include "suzu.h"
#include "Tmesh.h"
#include "player.h"
#include "ui.h"
#include "gameover.h"
#include "sound.h"
#include "paticle.h"

//�}�N��
#define Attenuation	(0.5f)		//�����W��
//#define Speed	(1.0f)			//�X�s�[�h
#define WIDTH (10.0f)			//���f���̔��a
#define Vtx (4)		//���_��
//------------------------------------
// static�ϐ�
//------------------------------------
static bool s_bIsLanding;
static ITEM s_Item[MAX_ITEM];	// �|���S���̍\����
static int s_nSet, s_nTimer2,s_nTimer, s_nSuzu,MaxSuzu; //�ő吔,�^�C�}�[,��̐�,��̍ő吔
D3DXVECTOR3 posDist[MAX_ITEM];//�A�C�e���ƃv���C���[�̋���
//=========================================
// ����������
//=========================================
void InitItem(void)
{
	//�J�����̃f�[�^�擾
	CAMERA *pCamera;
	pCamera = GetCamera();
	// �^�C�}�[
	s_nTimer = 0;
	s_nTimer2 = 0;

	s_nSet = 0;//�ő吔
	s_nSuzu = 0;//��̐�
	MaxSuzu = 0;//��̍ő吔
	for (int i = 0; i < MAX_ITEM; i++)
	{
		// ����������
		s_Item[i].s_pBuffItem = NULL;
		s_Item[i].s_Item = 0;
		s_Item[i].s_pVtxMesh = NULL;			//�c�@�@�@�@�@�@�@�@�@�@//��
		s_Item[i].RotMove = D3DXVECTOR3(D3DX_PI + pCamera->rot.y, D3DX_PI*0.5f + pCamera->rot.y, 0.0f);
		s_Item[i].consumption = 0.0f;
		s_Item[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ���_���W
		s_Item[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ��]���W
		s_Item[i].nLife = 10;
		s_Item[i].bFinish = false;
		s_Item[i].dist = false;
		s_Item[i].bUse = false;
		s_Item[i].SIZ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ��]���W
		s_Item[i].ItemMin = D3DXVECTOR3(FLT_MAX, FLT_MAX, FLT_MAX);
		s_Item[i].ItemMax = D3DXVECTOR3(-FLT_MAX, -FLT_MAX, -FLT_MAX);
		posDist[i] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ��]���W

	}
	
}

//=========================================
// �I������
//=========================================
void UninitItem(void)
{
	StopSound();

	for (int j = 0; j < s_nSet; j++)
	{
		for (int i = 0; i < (int)s_Item[j].s_Item; i++)
		{
			if (s_Item[j].s_pTexture[i] != NULL)
			{// �e�N�X�`���̉��
				s_Item[j].s_pTexture[i]->Release();
				s_Item[j].s_pTexture[i] = NULL;
			}
		}
	}
	for (int i = 0; i < MAX_ITEM; i++)
	{
		// ���_�o�b�t�@�[�̉��
		if (s_Item[i].s_pVtxMesh != NULL)
		{
			s_Item[i].s_pVtxMesh->Release();
			s_Item[i].s_pVtxMesh = NULL;
		}
		if (s_Item[i].s_pBuffItem != NULL)
		{
			s_Item[i].s_pBuffItem->Release();
			s_Item[i].s_pBuffItem = NULL;
		}
	}
}

//=========================================
// �X�V����
//=========================================
void UpdateItem(void)
{
	s_nTimer2++;
	s_nTimer++;
	s_nTimer %= 60;

	for (int nCnt = 0; nCnt < s_nSet; nCnt++)
	{
		if (s_Item[nCnt].bUse)
		{
			s_Item[nCnt].posOld = s_Item[nCnt].pos;
			if (s_Item[nCnt].bFinish)
			{
				PLAYER *pPlayer = GetPlayer();

				D3DXVECTOR3 vecPlayerDist = pPlayer->pos - s_Item[nCnt].pos;
				float distPlayer = D3DXVec3Length(&vecPlayerDist);
				if (!s_Item[nCnt].dist)
				{
					s_Item[nCnt].pos += vecPlayerDist / distPlayer * 5.0f;
				}
				if (distPlayer <= 5.0f)
				{
					s_Item[nCnt].dist = true;		
					//s_Item[nCnt].bUse = false;
				}
				if (s_Item[nCnt].dist)
				{	
					posDist[s_Item[nCnt].Numbers] = s_Item[nCnt].pos;
					
					if (s_Item[nCnt].Numbers - 1 == 0)
					{//��ԍŏ��̂����v���C���[�̑̂ɖ��ߍ���
						s_Item[nCnt].pos.x = pPlayer->pos.x - pPlayer->move.x*s_Item[nCnt].Numbers+ s_Item[s_nSet].SIZ.x;
						s_Item[nCnt].pos.z = pPlayer->pos.z - pPlayer->move.z*s_Item[nCnt].Numbers+ s_Item[s_nSet].SIZ.z;
						s_Item[nCnt].pos.y = pPlayer->pos.y;
					}
					else
					{//��O�̂ɂ��Ă��鏈��
						s_Item[nCnt].pos.x = posDist[s_Item[nCnt].Numbers - 1].x;//pPlayer->pos.x - pPlayer->move.x*s_Item[nCnt].Numbers+ s_Item[s_nSet].SIZ.x;
						s_Item[nCnt].pos.z = posDist[s_Item[nCnt].Numbers - 1].z;//pPlayer->pos.z - pPlayer->move.z*s_Item[nCnt].Numbers+ s_Item[s_nSet].SIZ.z;
						s_Item[nCnt].pos.y = posDist[s_Item[nCnt].Numbers - 1].y;//pPlayer->pos.y;
					}
					s_Item[nCnt].rot.y += 0.01f;
				}
			}
			else
			{
				if (s_Item[nCnt].nType == 0)
				{//��
					if (s_nTimer <= 30)
					{
						s_Item[nCnt].pos.y += 0.1f;
					}
					if (s_nTimer >= 30)
					{
						s_Item[nCnt].pos.y -= 0.1f;
					}
					s_Item[nCnt].rot.y += 0.01f;
				}
				else
				{
					if (s_nTimer <= 30)
					{
						s_Item[nCnt].pos.y += 0.2f;
					}
					if (s_nTimer >= 30)
					{
						s_Item[nCnt].pos.y -= 0.2f;
					}
					s_Item[nCnt].rot.y -= 0.01f;
					if (s_nTimer2 >= MaxSuzu)
					{
						s_nTimer2 = 0;
						SetParticle(s_Item[nCnt].pos, s_Item[nCnt].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 20.0f, 20.0f, PARTICLETYPE_STAR, 20);
					}
				}	
			}
			//���K��
			if (s_Item[nCnt].rot.y > D3DX_PI * 2)
			{
				s_Item[nCnt].rot.y += -D3DX_PI * 2;
			}
			if (s_Item[nCnt].rot.y < -D3DX_PI * 2)
			{
				s_Item[nCnt].rot.y += D3DX_PI * 2;
			}
		}
	}

}

//=========================================
// �`�揈��
//=========================================
void DrawItem(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScale, mtxTrans, mtxRot;	// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9 marDef;
	D3DXMATERIAL *pMat;
	//MESH *pMesh = GetMesh();
	for (int j = 0; j < s_nSet; j++)//�o�Ă郂�f���̐�������
	{
		if (s_Item[j].bUse)//�g���Ă��o��
		{
			// ���[���h�}�g���b�N�X�̏�����
			// �s�񏉊����֐�(��1�����̍s���P�ʍs��ɏ�����)
			D3DXMatrixIdentity(&s_Item[j].MtxWorld);

			D3DXMatrixScaling(&mtxScale, 1.0f, 1.0f, 1.0f);

			// �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)
			D3DXMatrixMultiply(&s_Item[j].MtxWorld, &s_Item[j].MtxWorld, &mtxScale);

			// �����𔽉f
			// �s���]�֐�(��1�����Ƀ��[(y)�s�b�`(x)���[��(z)�����̉�]�s����쐬)
			D3DXMatrixRotationYawPitchRoll(&mtxRot, s_Item[j].rot.y, s_Item[j].rot.x, s_Item[j].rot.z);
			// �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)
			D3DXMatrixMultiply(&s_Item[j].MtxWorld, &s_Item[j].MtxWorld, &mtxRot);

			// �ʒu�𔽉f
			// �s��ړ��֐�(��P������X,Y,Z�����̈ړ��s����쐬)
			D3DXMatrixTranslation(&mtxTrans, s_Item[j].pos.x, s_Item[j].pos.y, s_Item[j].pos.z);
			// �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)
			D3DXMatrixMultiply(&s_Item[j].MtxWorld, &s_Item[j].MtxWorld, &mtxTrans);

			// ���[���h���W�s��̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &s_Item[j].MtxWorld);

			//���݂̃}�e���A����ێ�
			pDevice->GetMaterial(&marDef);

			//�}�e���A���f�[�^�̃|�C���^���擾
			pMat = (D3DXMATERIAL*)s_Item[j].s_pBuffItem->GetBufferPointer();

			for (int i = 0; i < (int)s_Item[j].s_Item; i++)
			{
				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, NULL);
				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[i].MatD3D);
				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, s_Item[j].s_pTexture[i]);
				//���f���p�[�c�̕`��
				s_Item[j].s_pVtxMesh->DrawSubset(i);
			}
			//���݂̃}�e���A����ێ�
			pDevice->SetMaterial(&marDef);
		}
	}
	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);
}
void SetItem(D3DXVECTOR3 pos, char *Filename ,int nType)
{
	//�J�����̃f�[�^�擾
	CAMERA *pCamera;
	pCamera = GetCamera();

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	char aFile[128] = FILE_3D_MODEL;

	strcat(aFile, &Filename[0]);//�����@aFile��-�����ɓ����

	D3DXLoadMeshFromX(&aFile[0],
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&s_Item[s_nSet].s_pBuffItem,
		NULL,
		&s_Item[s_nSet].s_Item,
		&s_Item[s_nSet].s_pVtxMesh
	);
	//��������X�t�@�C����ǂݍ��񂾌�

	//���ׂĂ̒��_����ۑ�����֐������
	int NumVpx;	//���_��
				//��̒��_�̃T�C�Y������֐�
	DWORD sizeFVF;
	//�o�C�g�����̃|�C���^�[char
	BYTE *pVtxBuff;

	//�����Œ��_�����Q��
	NumVpx = s_Item[s_nSet].s_pVtxMesh->GetNumVertices();

	//�����ŃT�C�Y������
	sizeFVF = D3DXGetFVFVertexSize(s_Item[s_nSet].s_pVtxMesh->GetFVF());

	//	���_�o�b�t�@�̃��b�N���܂��傤
	s_Item[s_nSet].s_pVtxMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	// �o�b�t�@�̐擪�|�C���^��D3DXMATERIAL�ɃL���X�g���Ď擾
	D3DXMATERIAL *pMat = (D3DXMATERIAL*)s_Item[s_nSet].s_pBuffItem->GetBufferPointer();

	// �e���b�V���̃}�e���A�������擾����
	for (int i = 0; i < (int)s_Item[s_nSet].s_Item; i++)
	{
		s_Item[s_nSet].s_pTexture[i] = NULL;

		if (pMat[i].pTextureFilename != NULL)
		{// �}�e���A���Őݒ肳��Ă���e�N�X�`���ǂݍ���
			D3DXCreateTextureFromFileA(pDevice,
				pMat[i].pTextureFilename,
				&s_Item[s_nSet].s_pTexture[i]);
		}
		else
		{
			s_Item[s_nSet].s_pTexture[i] = NULL;
		}
	}

	for (int i = 0; i < NumVpx; i++)
	{
		D3DXVECTOR3 pVtx = *(D3DXVECTOR3*)pVtxBuff;
		//������g���ă��f���̍ő�l�ƍŏ��l���g���ċ��߂�
		//XYZ�S�����߂�
		if (pVtx.x <= s_Item[s_nSet].ItemMin.x)
		{
			s_Item[s_nSet].ItemMin.x = pVtx.x;
		}
		if (pVtx.x >= s_Item[s_nSet].ItemMax.x)
		{
			s_Item[s_nSet].ItemMax.x = pVtx.x;
		}
		if (pVtx.y <= s_Item[s_nSet].ItemMin.y)
		{
			s_Item[s_nSet].ItemMin.y = pVtx.y;
		}
		if (pVtx.y >= s_Item[s_nSet].ItemMax.y)
		{
			s_Item[s_nSet].ItemMax.y = pVtx.y;
		}
		if (pVtx.z <= s_Item[s_nSet].ItemMin.z)
		{
			s_Item[s_nSet].ItemMin.z = pVtx.z;
		}
		if (pVtx.z >= s_Item[s_nSet].ItemMax.z)
		{
			s_Item[s_nSet].ItemMax.z = pVtx.z;
		}

		//������߂��玟�ɐ��������̂�
		pVtxBuff += sizeFVF;
		//��������΍ő�ŏ������߂���

	}

	s_Item[s_nSet].SIZ = (s_Item[s_nSet].ItemMax - s_Item[s_nSet].ItemMin);

	//�T�C�Y��傫�����ē����蔻���傫�����܂�
	s_Item[s_nSet].ItemMax *= 10;
	s_Item[s_nSet].ItemMin *= 10;
	//	���_�o�b�t�@�̃��b�N���܂��傤
	s_Item[s_nSet].s_pVtxMesh->UnlockVertexBuffer();

	// ����������
	s_Item[s_nSet].nType = nType;
	s_Item[s_nSet].pos = pos;	// ���_���W
	s_Item[s_nSet].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ��]���W
	s_Item[s_nSet].bUse = true;
	s_Item[s_nSet].RotMove = D3DXVECTOR3(D3DX_PI + pCamera->rot.y, D3DX_PI*0.5f + pCamera->rot.y, 0.0f);
	
	//�������b�V���ɖ��܂��Ă��疄�܂��ĂȂ��Ƃ��܂ŉ����グ�鏈��
	CollisionMesh(&s_Item[s_nSet].pos);
	
	if (s_Item[s_nSet].nType == 0)
	{
		s_nSuzu++;//��̍ő吔��
		MaxSuzu = s_nSuzu;//���݂̍ő吔�ɉ��Z����
	}
	s_nSet++;
}

ITEM *GetItem(void)
{
	return &s_Item[0];
}
int *GetItemMax(void)
{
	return &s_nSuzu;
}

//---------------------------------
//�����蔻��
//---------------------------------
bool  CollisionItem(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 Siz)
{

	bool bIsLanding = false;
	{
		for (int nCnt = 0; nCnt < s_nSet; nCnt++)
		{
			if (s_Item[nCnt].bUse)
			{
				D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X
				D3DXMATRIX mtxWorld;

				// ���[���h�}�g���b�N�X�̏�����
				// �s�񏉊����֐�(��1�����̍s���P�ʍs��ɏ�����)
				D3DXMatrixIdentity(&mtxWorld);
				// �����𔽉f
				// �s���]�֐�(��1�����Ƀ��[(y)�s�b�`(x)���[��(z)�����̉�]�s����쐬)
				D3DXMatrixRotationYawPitchRoll(&mtxRot, s_Item[nCnt].rot.y, s_Item[nCnt].rot.x, s_Item[nCnt].rot.z);
				// �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)
				D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

				// �ʒu�𔽉f
				// �s��ړ��֐�(��P������X,Y,Z�����̈ړ��s����쐬)
				D3DXMatrixTranslation(&mtxTrans, s_Item[nCnt].pos.x, s_Item[nCnt].pos.y, s_Item[nCnt].pos.z);
				// �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)
				D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

				D3DXVECTOR3 posCorner[Vtx];

				//���S���璸�_
				posCorner[0] = D3DXVECTOR3(s_Item[nCnt].ItemMin.x, 0.0f, s_Item[nCnt].ItemMax.z);
				posCorner[1] = D3DXVECTOR3(s_Item[nCnt].ItemMax.x, 0.0f, s_Item[nCnt].ItemMax.z);
				posCorner[2] = D3DXVECTOR3(s_Item[nCnt].ItemMax.x, 0.0f, s_Item[nCnt].ItemMin.z);
				posCorner[3] = D3DXVECTOR3(s_Item[nCnt].ItemMin.x, 0.0f, s_Item[nCnt].ItemMin.z);

				for (int i = 0; i < Vtx; i++)
				{
					D3DXVec3TransformCoord(&posCorner[i], &posCorner[i], &mtxWorld);
				}

				int  LineCout = 0;
				for (int i = 0; i < Vtx; i++)
				{
					//V1 move
					D3DXVECTOR3 vecMove = *pPos - *pPosOld;

					D3DXVECTOR3 vecMoveN;

					D3DXVec3Normalize(&vecMoveN, &vecMove);

					//�x�N�g��S2 V2												
					D3DXVECTOR3 vecWall = posCorner[(i + 1) % 4] - posCorner[i] - (vecMoveN*Siz.z);

					//�x�N�g�����݂�POS�Ǝn�_�܂ł̋���
					D3DXVECTOR3 vecPos = *pPos - posCorner[i];

					//�O�όv�Z//�ӂP
					float vecLine = Vec2Cross(&vecPos, &vecWall);

					if (vecLine > 0.0f)
					{
						LineCout++;
					}
				}
				if (LineCout == 4)
				{
					GAMESET *pGame = GetGameMode();//�Q�[�����[�h();//

					LEVEL level = GetLevel();		

					if (s_Item[nCnt].nType == 0)
					{//��
						if (!s_Item[nCnt].bFinish)
						{
							MaxSuzu -= 1;
							PlaySound(SOUND_LABEL_SE_BELL);
							SumSuzu(1);
							AddScore(100 + ((int)level * 100));
							s_Item[nCnt].bFinish = true;
							s_Item[nCnt].Numbers = s_nSuzu - MaxSuzu;
						}
					}
					else
					{//��
						END* pEnd = GetEnd();
						pEnd->Lst = true;
						pEnd->Time = true;
						AddScore(10000 + ((int)level * 2000));
						pGame->NoGame = false;
						pGame->Result = true;
						//�Q�[���I�[�o�[������
						InitGameover();
						bIsLanding = true;
						//SetFade(MODE_RESULT);
						s_Item[nCnt].bUse = false;
					}	
				}
			}
		}
	}
	return bIsLanding;
}

//==================
//�}�b�v����(�G�N�Z��)���݃V�X�e���ύX��
//autho hamadaryuuga 
//==================
void InitItem(char *Filename)
{
	int s_aMap[MAX_MESH][MAX_MESH];

	FILE *pFile = NULL;	//�t�@�C���|�C���^��錾
	int nCntX, nCntY;

	VERTEX_3D* pVtx = NULL;
	
	//�t�@�C�����J��

	pFile = fopen(&Filename[0], "r");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ
		for (nCntY = 0; nCntY < MAX_MESH; nCntY++)
		{
			for (nCntX = 0; nCntX < MAX_MESH; nCntX++)
			{//Map�̏�������
				fscanf(pFile, "%d", &s_aMap[nCntY][nCntX]);
			}
		}

		//�t�@�C�������
		fclose(pFile);
	}
	else
	{
	}

	float posx = -1500.0f;
	float posz = -1500.0f;
	//�u���b�N�ݒ�
	for (nCntY = 0; nCntY < MAX_MESH; nCntY++, pVtx++)
	{
		for (nCntX = 0; nCntX < MAX_MESH; nCntX++, pVtx++)
		{//Map�̏�������
			posx += MAX_ITEMWAID;

			switch (s_aMap[nCntY][nCntX])
			{
		
			case 1://��
				SetItem(D3DXVECTOR3(posx, 0.1f, posz), SUZU, 0);
				break;
			case 2://��
				SetItem(D3DXVECTOR3(posx, 0.1f, posz), KI, 1);
				break;
			default:
				break;
			}	
		}
		posx = -1500.0f;
		posz += MAX_ITEMWAID;
	}


}
//----------------------------
//�t�@�C���̏o�̓}�b�v������
//----------------------------
void OutputMap(char *Filename)
{

	//�t�@�C���J��
	FILE *pFile = fopen(Filename, "w");
	fprintf(pFile, "SCRIPT\n\n");
	for (int nCnt = 0; nCnt < s_nSet; nCnt++)
	{
		if (s_Item[nCnt].bUse)
		{
			if (s_Item[nCnt].nType == 0)
			{		
				fprintf(pFile, "MODEL_FILENAME " SUZU"\n");
			}

			if (s_Item[nCnt].nType == 1)
			{
				fprintf(pFile, "MODEL_FILENAME " KI"\n");
				
			}
			fprintf(pFile, "MODELSET\n");
			fprintf(pFile, "TYPE = %d\n", s_Item[nCnt].nType);
			fprintf(pFile, "POS = %.4f %.4f %.4f\n", s_Item[nCnt].pos.x,s_Item[nCnt].pos.y, s_Item[nCnt].pos.z);
			fprintf(pFile, "ROT = %.4f %.4f %.4f\n", s_Item[nCnt].rot.x, s_Item[nCnt].rot.y, s_Item[nCnt].rot.z);
			fprintf(pFile, "END_ITEMSET\n");
		}
		fprintf(pFile, "\n");
	}

	fprintf(pFile, "END_SCRIPT");
	fclose(pFile);


}
