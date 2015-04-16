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
	int GetSize();
	int GetValue(int Index);
	KRCrit GetByIndex(int Index);

protected:
	std::vector<KRCrit>Crits;
};

#endif //KR_KRCRITSYS_H_
