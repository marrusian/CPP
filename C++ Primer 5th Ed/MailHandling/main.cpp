#include "message.h"
#include "folder.h"

#include <iostream>

int main(void)
{
	Message msg1("Message no.1!");
	Message msg2("Message no.2!");
	Folder fld1;

	fld1.save(msg1);
	fld1.save(msg2);

	std::cout << fld1;

	return 0;
}