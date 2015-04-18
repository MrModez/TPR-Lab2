#ifndef KR_KRPROFILE_H_
#define KR_KRPROFILE_H_

#include "KRShared.h"
#include "KRCritSys.h"

class KRProfile {
public:
	KRProfile();
	KRProfile(String N, KRCritSys Crits);
	void ChangeCrit(int Index, int Value);
	void SetCrits(int* Crits);
	void ChangeCoeff(int Index, int Value);
	int GetValue(int Index);
	int GetCoeff(int Index);

	String Name;

protected:
	KRCritSys CritsSys;
};

#endif //KR_KRPROFILE_H_
