#include "GETproducer.h"
#include "IGraphElementBase.h"
#include "IPortElement.h"

#ifndef _AGETgenerator_h_
#define _AGETgenerator_h_
//Will use simpleProducerLibAPI to make Graph Element that would have 3 ports with different generated data on them
class  AdvancedGeneratorGraphElement : public IGraphElementBase, public simpleProducerLibAPI
{
public:
	IPortElement<ExtendedCharPtr>* GeneratorLC;
	IPortElement<ExtendedCharPtr>* GeneratorCapitals;
	IPortElement<ExtendedCharPtr>* GeneratorNumbers;
	
	ExtendedCharPtr LCCharPtr;
	ExtendedCharPtr CapitalsCharPtr;
	ExtendedCharPtr NumbersCharPtr;

	void Init(int LCSize, int NumberSize, int CapitalsSize, int sleepTime)
	{
		initSimpleProducerLibAPI(0);

		GeneratorLC = new IPortElement<ExtendedCharPtr>();
		GeneratorCapitals = new IPortElement<ExtendedCharPtr>();
		GeneratorNumbers = new IPortElement<ExtendedCharPtr>();

		LCCharPtr.data = new char[LCSize];
		LCCharPtr.length = LCSize; 

		CapitalsCharPtr.data = new char[CapitalsSize];
		CapitalsCharPtr.length = CapitalsSize; 

		NumbersCharPtr.data = new char[NumberSize];
		NumbersCharPtr.length = NumberSize; 
cout << "1";
		GeneratorLC->Set(&LCCharPtr);
		GeneratorCapitals->Set(&CapitalsCharPtr);
		GeneratorNumbers->Set(&NumbersCharPtr);
cout << "2";		


		SetSleepTime(sleepTime);
	}
	// or we can grab data when we want
	virtual void updateData()
	{

///*
		genCharFilledWithCapitals(CapitalsCharPtr.data, CapitalsCharPtr.length);
		genCharFilledWithLoverCase(LCCharPtr.data, LCCharPtr.length);
		genCharFilledWithNumbers(NumbersCharPtr.data, NumbersCharPtr.length);
//*/
		GeneratorLC->Set(&LCCharPtr);
		GeneratorCapitals->Set(&CapitalsCharPtr);
		GeneratorNumbers->Set(&NumbersCharPtr);
	}

	void CleanAPI()
	{
	}
};
#endif // _AGETgenerator_h_