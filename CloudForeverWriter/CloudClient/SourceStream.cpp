#include "StdAfx.h"
#include "SourceStream.h"
#include <boost/thread.hpp>

SourceStream::SourceStream(int id) : m_id(id)
{
}

SourceStream::~SourceStream(void)
{
}

void SourceStream::run() {
	while(true)
	{
		boost::xtime xt;
		boost::xtime_get(&xt, boost::TIME_UTC);
		xt.sec +=1;
		boost::thread::sleep(xt);
	}
}

void SourceStream::stopAll() {
	//interrupt
	//join
}

int SourceStream::stopStream(int id) {
	//interrupt
	//join
	return 0;
}

int SourceStream::pauseStream(int id) {
	return 0;
}

int SourceStream::resumeStream(int id) {
	return 0;
}

int SourceStream::startStream() {
	return 0;
}
