#include "KRProfile.h"

KRProfile::KRProfile() {
};

KRProfile::KRProfile(String N, KRCritSys Cs) {
	Name = N;
	CritsSys = Cs;
}

void KRProfile::ChangeCrit(int Index, int Value) {
	CritsSys.ChangeCrit(Index, Value);
	// this->Crits
	// Crits[Index] = Value;;
}

void KRProfile::SetCrits(int* Cts) {
	for (int i = 0; i < CritsSys.GetSize(); i++) {
		ChangeCrit(i, Cts[i]);
	}
};

int KRProfile::GetValue(int Index) {
	return CritsSys.GetValue(Index);
};
