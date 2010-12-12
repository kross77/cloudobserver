#pragma once

class SourceStream
{
public:
	SourceStream(int id);
	~SourceStream(void);
	
	static void doThread(void* param) {
		static_cast<SourceStream*>(param)->run();
    }
	void run();
	static void stopAll();
private:
	int m_id;
};
