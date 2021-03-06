#ifndef KR_KRPROFILESYS_H_
#define KR_KRPROFILESYS_H_

#include "KRShared.h"
#include "KRProfile.h"
#include "KRCritSys.h"
#include <System.Classes.hpp>

enum Range {
	A_NONE, A_WORST, A_25, A_50, A_75, A_BEST, A_EQ
};

class KRProfileSys {
public:
	KRProfileSys();
	KRProfileSys(KRProfile *W, KRProfile *B, KRCritSys Crt);
	KRProfileSys(TStringList* Dat);
	void AddProfile(KRProfile *Profile);
	void AddBest(KRProfile *Profile);
	void AddWorst(KRProfile *Profile);
	void AddSpecial(Range A_Range, KRProfile *Profile);
	void ChangeProfile(int Index1, int Index2, int Value);
	void ChangeBest(int Index, int Value);
	void ChangeWorst(int Index, int Value);
	void ChangeSpecial(Range A_Range, int Index, int Value);
	KRProfile* GetByIndex(int Index);
	KRProfile* GetBest();
	KRProfile* GetWorst();
	KRProfile* GetSpecial(Range A_Range);
	int GetSize();
	float GraphValue(int Index, int Value);
	float ResultValue(int Index);
	void SetLambdas();
	void SetEQCoeffs();

	KRCritSys Crits;

private:

	std::vector<KRProfile*>Profiles;
	KRProfile* Best;
	KRProfile* A75;
	KRProfile* A50;
	KRProfile* A25;
	KRProfile* Worst;
	KRProfile* AEQ;
};

#endif //KR_KRPROFILESYS_H_
