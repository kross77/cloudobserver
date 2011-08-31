#ifndef TEST_DATA_STRUCTURE_H
#define TEST_DATA_STRUCTURE_H

template <class map_t_1, class map_t_2>
class test_data_structure 
{
public:

	virtual bool containsKey(map_t_1 key)=0;
	virtual map_t_2 get(map_t_1 key)=0;
	virtual map_t_1 put(map_t_1 key, map_t_2 value)=0;
	virtual int remove(map_t_1 key)=0;

	virtual int size()=0;
	virtual const char* name()=0;
	virtual void print()=0;
	virtual void shutdown()=0;
};

#endif // TEST_DATA_STRUCTURE_H