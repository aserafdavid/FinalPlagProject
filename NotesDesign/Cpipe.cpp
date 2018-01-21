#include "Cpipe.h"
#include <iostream>
#include <thread>

using namespace std;
#define ANSI_COLOR_RED     "\x1b[31m"
void Pipe::Test()
{
	srand(time_t(NULL));


	Pipe p(0);
	bool isConnect = p.connect();

	string ans;
	while (! isConnect)
	{

			printf(ANSI_COLOR_RED "trying connect again..\n" ANSI_COLOR_RED ); /* move to Logger*/
			Sleep(5000);
			isConnect = p.connect();
	}

	char msgToGraphics[1024];
	// msgToGraphics should contain the board string accord the protocol
	// YOUR CODE

	//strcpy_s(msgToGraphics, "tziziz kfizti"); // just example...

	//p.sendMessageToGraphics(msgToGraphics);   // send the board string

											  // get message from graphics
	string msgFromGraphics = p.getMessageFromGraphics();

	while (msgFromGraphics != "quit")
	{
		// should handle the string the sent from graphics
		// according the protocol. Ex: e2e4           (move e2 to e4)

		// YOUR CODE
		strcpy_s(msgToGraphics, "YOUR CODE"); // msgToGraphics should contain the result of the operation
											  // return result to graphics		
		p.sendMessageToGraphics(msgToGraphics);

		// get message from graphics
		msgFromGraphics = p.getMessageFromGraphics();

	}

	p.close();
}