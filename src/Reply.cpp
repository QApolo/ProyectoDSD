#include "Reply.h"
#include <string.h>

Reply::Reply(int iport){
	localSocket = new DatagramSocket(iport);
}

Message* Reply::getRequest() {
	Message *msg = new Message();
	DatagramPacket pq((char*)msg, sizeof(Message));
	localSocket->receive(pq);

	address = pq.getAddress();
	port = pq.getPort();
	operation = msg->operationId;
	requestId = msg->requestId;

	return msg;
}

void Reply::sendReply(const char *arguments, size_t len) {
	Message *msg = new Message();
	msg->messageType = Message::kindMessages::reply;
	msg->operationId = operation;
	msg->requestId = requestId;
	memcpy(msg->arguments, arguments, len);
	msg->length = len;

	DatagramPacket paquete((char*)msg, sizeof(Message), address, port);
	localSocket->send(paquete);
}
