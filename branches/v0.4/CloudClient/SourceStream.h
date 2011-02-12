#pragma once

class SourceStream
{
public:
//interface
	static void stopAll();
	static int stopStream(int id);
	static int pauseStream(int id);
	static int resumeStream(int id);
	static int startStream();

public:
	SourceStream(int id);
	~SourceStream(void);
	
	static void doThread(void* param) {
		static_cast<SourceStream*>(param)->run();
    }
	void run();


private:
	int m_id;
	int m_idCounter;
};
