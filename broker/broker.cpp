// broker.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "zhelpers.h"


int _tmain(int argc, _TCHAR* argv[])
{

	//first create the context
	void* context = zmq_ctx_new();

	//then create the router and dealer
	void* router = zmq_socket(context, ZMQ_ROUTER);
	void* dealer = zmq_socket(context, ZMQ_DEALER);

	char server_router[] = "tcp://127.0.0.1:5050";
	char server_dealer[] = "tcp://127.0.0.1:5060";

	zmq_bind(router, server_router);
	zmq_bind(dealer, server_dealer);



	return 0;
}

