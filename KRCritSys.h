#ifndef KR_KRCRITSYS_H_
#define KR_KRCRITSYS_H_

#include "KRShared.h"
#include "KRCrit.h"

class KRCritSys {
public:
	KRCritSys();
	KRCritSys(std::vector<KRCrit>C);
	void AddCrit(KRCrit Crit);
	void ChangeCrit(int Index, int Value);
	void ChangeCoeff(float Value);
	void ChangeCoeff(int Index, float Value);
	int GetSize();
	int GetValue(int Index);
	KRCrit GetByIndex(int Index);
	void SetPrority(std::vector<int>Pr);
	KRCrit GetByPriority(int Index);
	int GetPriority(int Index);
	float GetCoeff(int Index);
	void SetLambdas(std::vector<float>L);
	float GetLambda(int Index);

protected:
	std::vector<KRCrit>Crits;
	std::vector<int>Priority;
	std::vector<float>Lambdas;

};

#endif //KR_KRCRITSYS_H_
