// broker.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "zhelpers.h"
#include "../configsetting.h"



void forwardmsg(void* socket, char* msg)
{
	s_send(socket, msg);
}

int _tmain(int argc, _TCHAR* argv[])
{

	//first create the context
	void* context = zmq_ctx_new();

	//then create the router and dealer
	void* router = zmq_socket(context, ZMQ_ROUTER);
	void* dealer = zmq_socket(context, ZMQ_DEALER);

	

	zmq_bind(router, server_router);
	zmq_bind(dealer, server_dealer);

	//then setup the poll items
	zmq_pollitem_t poll[] = {
		{ router, 0, ZMQ_POLLIN, 0},
		{ dealer, 0, ZMQ_POLLIN, 0 },
	};

	//char buff[256];

	while (1)
	{
		int nRet = zmq_poll(poll, 2, -1);
		int64_t nMore = 0;

		if (poll[0].events & ZMQ_POLLIN)
		{
			//2017/8/25 glen here should support multi-part message
			//for ROUTER-DEALER mode, see details in ZGuide http://zguide.zeromq.org/page:all#advanced-request-reply
			/*memset(buff, 256, 0);
			int nLen = zmq_recv(router, buff, 256, 0);

			if (nLen > 0)
			{
				printf("recv from client:%s\n", buff);
				zmq_send(dealer, buff, nLen, 0);
			}*/
			while (1)
			{
				zmq_msg_t msg_recv;
				zmq_msg_init(&msg_recv);
				zmq_msg_recv(&msg_recv, router, 0);

				size_t nSizeMore = sizeof(nMore);
				zmq_getsockopt(router, ZMQ_RCVMORE, &nMore, &nSizeMore);
				zmq_msg_send(&msg_recv, dealer, nMore ? ZMQ_SNDMORE : 0);
				zmq_msg_close(&msg_recv);

				if (!nMore)
					break;


			}
		}

		if (poll[1].events & ZMQ_POLLIN)
		{
			//2017/8/25 glen here must support multi-part message
			//for ROUTER-DEALER mode, see details in ZGuide http://zguide.zeromq.org/page:all#advanced-request-reply
			/*memset(buff, 256, 0);
			int nLen = zmq_recv(dealer, buff, 256, 0);
			if (nLen > 0)
			{
				printf("recv from server:%s\n", buff);
				zmq_send(router, buff, nLen, 0);
			}*/

			while (1)
			{
				zmq_msg_t msg_recv;
				zmq_msg_init(&msg_recv);
				zmq_msg_recv(&msg_recv, dealer, 0);

				size_t nSizeMore = sizeof(nMore);
				zmq_getsockopt(dealer, ZMQ_RCVMORE, &nMore, &nSizeMore);
				zmq_msg_send(&msg_recv, router, nMore ? ZMQ_SNDMORE : 0);
				zmq_msg_close(&msg_recv);
				if (!nMore)
					break;


			}
		}

	}

	zmq_close(router);
	zmq_close(dealer);

	zmq_ctx_term(context);

	return 0;
}

