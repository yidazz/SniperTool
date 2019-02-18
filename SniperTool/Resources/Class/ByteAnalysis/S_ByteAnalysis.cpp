#include "S_ByteAnalysis.h"

/* ʹ��һ���ⲿ�ֽڽ��ն��л�������Դ */
extern SVector *OSCRecByteQueue;
/* ʹ��һ�����ݶ��л�������Դ */
extern SVector *OSCDataBuffQueue;

SFirAnalysis::SFirAnalysis()
{
}

SFirAnalysis::~SFirAnalysis()
{
}

bool SFirAnalysis::FirAnalysis(char &rRecByte)
{
	/** �յ�֡�Ŀ�ͷ */
	if (ProFir_Header == rRecByte)
	{
		/** �жϻ��������Ƿ��в�ȱ���� */
		if (NULL != OSCRecByteQueue->Queue1.size())
		{
			/* �в�ȱ���� �򿽱������������� */
			OSCDataBuffQueue->Queue2.push_back(OSCRecByteQueue->Queue1);
			/* �����ʱ������ */
			OSCRecByteQueue->Queue1.clear();
			/* �������ݴ�����ʱ������ */
			OSCRecByteQueue->Queue1.push_back(rRecByte);
			/* ��ҵ����Ҫ���� */
			return TRUE;
		}
	}

	/** �յ�֡�Ľ�β */
	if (ProFir_End == rRecByte)
	{
		/* �������ݴ�����ʱ������ */
		OSCRecByteQueue->Queue1.push_back(rRecByte);
		/* �ж�֡�Ƿ��������� */
		if(TRUE!= FirConfirm())
		{
		}
		/* ����֡���������������� */
		OSCDataBuffQueue->Queue2.push_back(OSCRecByteQueue->Queue1);
		/* �����ʱ������ */
		OSCRecByteQueue->Queue1.clear();
		/* ��ҵ����Ҫ���� */
		return TRUE;
	}
	/* �������ݴ�����ʱ������ */
	OSCRecByteQueue->Queue1.push_back(rRecByte);
	/* ��ҵ����Ҫ���� */
	return FALSE;
	//OSCSVector->Queue2.erase(OSCSVector->Queue2.begin());
}


bool SFirAnalysis::FirConfirm(void)
{
	/** �Ƿ��д����� */
	BOOL bIsSuccess = TRUE;

	/* �Ƿ���ڵ���4���ֽ�*/
	if (bIsSuccess)
	{
		if (4 > OSCRecByteQueue->Queue1.size()) {
			bIsSuccess = FALSE; }
	}
	/* �Ƿ�Ϊָ��֡ͷ*/
	if (bIsSuccess)
	{
		if (ProFir_Header != OSCRecByteQueue->Queue1[0]) {
			bIsSuccess = FALSE; }
	}
	/* �Ƿ�Ϊָ��֡β*/
	if (bIsSuccess)
	{
		if (ProFir_End != OSCRecByteQueue->Queue1[OSCRecByteQueue->Queue1.size() - 1]) {
			bIsSuccess = FALSE; }
	}
	/* У����Ƿ���ȷ*/
	if (bIsSuccess)
	{
		char CheckBuff = 0;

		for (UINT i = 0; i < OSCRecByteQueue->Queue1.size() - 2; i++)
		{
			CheckBuff += OSCRecByteQueue->Queue1[i];
		}
		if (CheckBuff != OSCRecByteQueue->Queue1[OSCRecByteQueue->Queue1.size() - 2]) {
			bIsSuccess = FALSE; }
	}

	return (TRUE == bIsSuccess);
}