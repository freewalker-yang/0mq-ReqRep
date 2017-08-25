// demo1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "zmq.h"
#include "zhelpers.h"
#include "../configsetting.h"

//this is the client code demostrates how to use the zeromq in request-reply pattern
//client

//char szServer[] = "tcp://127.0.0.1:5050";

int _tmain(int argc, _TCHAR* argv[])
{
	char szServer[64];
	memset(szServer, 0, 64);

	if (argc > 1)
	{
		//use as client id
		sprintf_s(szServer, 64, "Client#%s", argv[1]);
	}
	else
		sprintf_s(szServer, 64, "Client#0");

	

	void* context = zmq_ctx_new();

	void* requester = zmq_socket(context, ZMQ_REQ);
	
	int nRet = zmq_connect(requester, server_router);
	//assert(nRet == 0);
	if (nRet != 0)
	{
		nRet = zmq_errno();
		const char* szError = zmq_strerror(nRet);

		printf("failed to connect %s:%d\n", server_router, szError);
		return 0;
	}

	ULONGLONG dwTick = GetTickCount64();
	printf("%s start\n", szServer);

	int request_nbr = 0;
	char buff[256];

	

	for (; request_nbr < 10; request_nbr++)
	{
		memset(buff, 0, 256);
		sprintf_s(buff, 256, "Hello-%d from %s", request_nbr+1,
			szServer);
		zmq_send(requester, buff, strlen(buff), 0);

		printf("%s:send:%s\n", szServer, buff);

		memset(buff, 0, 256);
		int nRet = zmq_recv(requester, buff, 256, 0);
		printf("%s: received:%s\n", szServer, buff);
	

	}

	zmq_close(requester);
	zmq_ctx_destroy(context);

	ULONGLONG dwTick1 = GetTickCount64();
	printf("%s:task complete[%d]", szServer, dwTick1 - dwTick);

	system("pause");
}

