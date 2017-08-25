// server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "zmq.h"
#include "zhelpers.h"
#include "../configsetting.h"

//char szServer[] = "tcp://127.0.0.1:5050";

int _tmain(int argc, _TCHAR* argv[])
{
	char szServer[64];
	memset(szServer, 0, 64);

	if (argc > 1)
	{
		//use as server id
		sprintf_s(szServer, 64, "Server#%s", argv[1]);
	}
	else
		sprintf_s(szServer, 64, "Server#0");

	void* context = zmq_ctx_new();

	void* responder = zmq_socket(context, ZMQ_REP);

	int nRet = zmq_connect(responder, server_dealer);
	if (nRet != 0)
	{
		nRet = zmq_errno();
		const char* szError = zmq_strerror(nRet);

		printf("failed to connect %s:%d\n", server_dealer, szError);
	}

	printf("%s start\n", szServer);

	int nCnt = 1;
	char buff[256];

	ULONGLONG dwTick = GetTickCount64();
	ULONGLONG dwTickCurr = 0 ;

	for (;;)
	{
		/*zmq_msg_t msg_recv;
		zmq_msg_init(&msg_recv);
		zmq_msg_recv(&msg_recv, responder, 0);*/
		//char* buff = s_recv(responder);
		memset(buff, 0, 256);
		int nRet = zmq_recv(responder, buff, 256, 0);

		if (nRet >= 0)
		{
			dwTickCurr = GetTickCount64() - dwTick;
			printf("%s: recv:%s time=%lld\n", szServer, buff, dwTickCurr);
		}
		else
			continue;
		

		Sleep(5);

		memset(buff, 0, 256);
		sprintf_s(buff, 256, "World-%d from %s", nCnt, szServer);
		zmq_send(responder, buff, strlen(buff), 0);

		nCnt++;
	}

	zmq_close(responder);
	zmq_ctx_destroy(context);

	return 0;
}

