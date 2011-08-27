#ifndef TEST_DATA_STRUCTURE_H
#define TEST_DATA_STRUCTURE_H

class test_data_structure 
{
public:

	virtual bool containsKey(int key)=0;
	virtual int get(int key)=0;
	virtual int put(int key, int value)=0;
	virtual int remove(int key)=0;

	virtual int size()=0;
	virtual const char* name()=0;
	virtual void print()=0;
	virtual void shutdown()=0;
};

#endif // TEST_DATA_STRUCTURE_H