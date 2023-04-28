//============================
//
// �A�C�e���ݒ�w�b�^�[
// Author:hamada ryuuga
//
//============================
#ifndef _ITEM_H_
#define _ITEM_H_

#include "main.h"

#define MAX_ITEM (128)			//�ő吔
#define ITEMPS "Data/system/item.txt"
#define ITEMPSHD "Data/system/itemHd.txt"
#define ITEMPSEZ "Data/system/itemEz.txt"

#define KI "kagi.x"
#define SUZU "suzu.x"

#define MAX_ITEMWAID (50.0f)	//�}�b�v�̃T�C�Y/�������ŏo���}�b�v�T�C�Y�v�Z��MIN-�P�T�O�OMAX+�P�T�O�O�͂Ȃ�R�O�O�O�ɂȂ�
#define MINX (-1500.0f)			
#define MINY (-1500.0f)
#define MAXX (1500.0f)
#define MAXY (1500.0f)
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 posOld;	//�ߋ����W
	D3DXVECTOR3 rot;	//��]
	D3DXVECTOR3 RotMove;//��]���[�u
	D3DXVECTOR3 ItemMin;
	D3DXVECTOR3 ItemMax;
	D3DXVECTOR3 SIZ;
	D3DXMATRIX MtxWorld; //�}�g���b�N�X//�|���S���̈ʒu���]�s�񂷂ׂĂ��߂Ă�i�j�J
	int nType;			//�^�C�v
	int nLife;			//���C�t
	int Numbers;			//�����������̔ԍ�
	bool dist;
	bool bFinish;			//������O�̉��o
	bool bUse;			//�g���Ă邩�g���ĂȂ���
	LPD3DXMESH s_pVtxMesh;	// ���b�V���̃|�C���^
	LPD3DXBUFFER s_pBuffItem; //�o�b�t�@�̃|�C���^
	LPDIRECT3DTEXTURE9	s_pTexture[MAX_ITEM];		// �e�N�X�`���ւ̃|�C���^
	DWORD s_Item;		//�}�e���A�����
	float consumption;
}ITEM;

//�v���g�^�C�v�錾
void InitItem(void);//������
void UninitItem(void);//�j��
void UpdateItem(void);//�X�V
void DrawItem(void);//�`��
void SetItem(D3DXVECTOR3 pos, char *Filename, int nType);//�Z�b�g�������W�Ɠǂݍ��ރt�@�C����
ITEM *GetItem(void);//�A�C�e���̍\���̂��Q�b�g���܂�
int *GetItemMax(void);//�A�C�e���̍ő吔���Q�b�g���܂�
bool  CollisionItem(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 Siz);
void InitItem(char *Filename);
void OutputMap(char *Filename);
#endif