#include "KRCritSys.h"

KRCritSys::KRCritSys() {
};

KRCritSys::KRCritSys(std::vector<KRCrit>C) {
	Crits = C;
}

void KRCritSys::AddCrit(KRCrit Crit) {
	Crits.push_back(Crit);
}

void KRCritSys::ChangeCrit(int Index, int Value) {
	Crits[Index].Value = Value;
};

int KRCritSys::GetSize() {
	return Crits.size();
};

int KRCritSys::GetValue(int Index) {
	return Crits[Index].Value;
}

KRCrit KRCritSys::GetByIndex(int Index) {
	return Crits[Index];
};
