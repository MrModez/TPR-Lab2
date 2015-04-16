#ifndef KR_KRPROFILESYS_H_
#define KR_KRPROFILESYS_H_

#include "KRShared.h"
#include "KRProfile.h"
#include "KRCritSys.h"

class KRProfileSys {
public:
	KRProfileSys();
	KRProfileSys(KRCritSys Crt);
	KRProfileSys(std::vector<KRProfile>P);
	void AddProfile(KRProfile Profile);
	void AddBest(KRProfile Profile);
	void AddWorst(KRProfile Profile);
	void ChangeProfile(int Index1, int Index2, int Value);
	void ChangeBest(int Index, int Value);
	void ChangeWorst(int Index, int Value);
	KRProfile GetByIndex(int Index);
	KRProfile GetBest();
	KRProfile GetWorst();
	int GetSize();

	KRCritSys Crits;

private:

	std::vector<KRProfile>Profiles;
	KRProfile Best;
	KRProfile Worst;
};

#endif //KR_KRPROFILESYS_H_
