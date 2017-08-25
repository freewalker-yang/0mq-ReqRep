// server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "zmq.h"
#include "zhelpers.h"

char szServer[] = "tcp://127.0.0.1:5050";

int _tmain(int argc, _TCHAR* argv[])
{

	void* context = zmq_ctx_new();

	void* responder = zmq_socket(context, ZMQ_REP);

	int nRet = zmq_bind(responder, szServer);
	if (nRet != 0)
	{
		nRet = zmq_errno();
		const char* szError = zmq_strerror(nRet);

		printf("failed to connect %s:%d\n", szServer, szError);
	}

	int nCnt = 0;

	for (;;)
	{
		/*zmq_msg_t msg_recv;
		zmq_msg_init(&msg_recv);
		zmq_msg_recv(&msg_recv, responder, 0);*/
		char* buff = s_recv(responder);

		printf("#%d recv:%s\n", ++nCnt, buff);
		free(buff);

		Sleep(10);

		/*zmq_msg_t msg_send;
		zmq_msg_init(&msg_send);
		zmq_msg_init_size(&msg_send, 6);
		memcpy(zmq_msg_data(&msg_send), "World!", 6);
		zmq_msg_send(&msg_send, responder, 0);*/
		s_send(responder, "World!");
	}

	zmq_close(responder);
	zmq_ctx_destroy(context);

	return 0;
}

