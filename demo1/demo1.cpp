// demo1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "zmq.h"
#include "zhelpers.h"

//this is the client code demostrates how to use the zeromq in request-reply pattern
//

char szServer[] = "tcp://127.0.0.1:5050";

int _tmain(int argc, _TCHAR* argv[])
{
	void* context = zmq_ctx_new();

	void* requester = zmq_socket(context, ZMQ_REQ);
	
	int nRet = zmq_connect(requester, szServer);
	//assert(nRet == 0);
	if (nRet != 0)
	{
		nRet = zmq_errno();
		const char* szError = zmq_strerror(nRet);

		printf("failed to connect %s:%d\n", szServer, szError);
	}

	int request_nbr = 0;
	for (; request_nbr < 10; request_nbr++)
	{
		s_send(requester, "Hello");

	

		char* buff = s_recv(requester);
		printf("#%d received:%s\n", request_nbr + 1, buff);
		free(buff);

	}

	zmq_close(requester);

	zmq_ctx_destroy(context);

	system("pause");
}

