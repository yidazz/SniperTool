#include "S_ThreadWatchDogWork.h"

/* ʹ��һ���߳���Դ */
extern SThread *TWDThread;

/* ʹ��һ�����Ź�������Դ */
extern SVector *WatchDogVector;

/* ��ʱʹ��һ���洢�����е��̺߳ŵĶ�����Դ */
extern SVector *WorkingThreadNum;

UINT WINAPI TWDWork(void* pParam)
{
	// �߳�ѭ��
	while (!TWDThread->SExit)
	{
		Sleep(100);
		for (uint i = 0;i < WorkingThreadNum->Queue1.size();i++)
		{
			if (TWDThreadNum == WorkingThreadNum->Queue1[i]) { continue; }           //�����߳̿��Ź��߳�
			if (TRUE != WatchDogVector->Queue1[WorkingThreadNum->Queue1[i]])
			{
				qDebug("Thread Error: %d", WorkingThreadNum->Queue1[i]);
			}
			WatchDogVector->Queue1[WorkingThreadNum->Queue1[i]] = FALSE;
		}
	}
	return 0;
}
