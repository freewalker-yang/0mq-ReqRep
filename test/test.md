## 0mq-request-response pattern test ##
2017/8/25 glen version 0.1

this is tested for request-reply broker pattern
each client do loop :first send hello,  then recv World

### multi-client vs muliti-server ###

the test batch is listed as follows:

		@echo off
		start "" "../Debug/broker.exe"
		start "" "../Debug/client.exe" 1
		start "" "../Debug/client.exe" 2
		start "" "../Debug/client.exe" 3
		start "" "../Debug/client.exe" 4
		start "" "../Debug/client.exe" 5
		start "" "../Debug/client.exe" 6
		start "" "../Debug/client.exe" 7
		start "" "../Debug/client.exe" 8
		start "" "../Debug/client.exe" 9
		start "" "../Debug/client.exe"
		start "" "../Debug/server.exe" 1
		start "" "../Debug/server.exe" 2


the test case listed as follows:

#### 10 clients vs 2 server ####
server connection

+ server1: client 1,3,5,8,9
+ server2: client 2,4,6,7,0

client received content

+ ***#1***-world 1,2,7,12,17,22,27,32,37,42;
+ ***#2***-world 1,6,11,16,21,26,31,36,41,46;
+ ***#3***-world 3,8,13,18,23,28,33,38,43,48;
+ ***#4***-world 2,7,12,17,22,27,32,37,42,47;
+ ***#5***-world 4,9,14,19,24,29,34,39,44,49;
+ ***#6***-world 3,8,13,18,23,28,33,38,43,48;
+ ***#7***-world 4,9,14,19,24,29,34,39,44,49;
+ ***#8***-world 5,10,15,20,25,30,40,45;
+ ***#9***-world 6,11,16,21,26,31,36,41,46;
+ ***#0***-world 5,10,15,20,30,35,40,45,47;

Client task complete time : 1400 - 1800 ms
Server task complete time : 1513 ms

server1 log

<img src="Image/server1_client10.png" width=200 height=300>

server2 log

<img src="Image/server2_client10.png" width=200 height=300>

#### 20 clients vs 2 server ####
server connection

+ server1: client 0,1,3,5,7,9,b,e,f,i,j
+ server2: client 0,2,4,6,8,a,c,d,g,h

client request is not always point to the same server, like client 0

Client task complete time : 3200 - 3800 ms
Server task complete time : 3100 - 3200 ms

#### 20 clients vs 3 server ####
