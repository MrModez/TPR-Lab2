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

void KRCritSys::ChangeCoeff(int Index, int Value) {
	Crits[Index].Coeff = Value;
};

int KRCritSys::GetSize() {
	return Crits.size();
};

int KRCritSys::GetValue(int Index) {
	return Crits[Index].Value;
}

int KRCritSys::GetCoeff(int Index) {
	return Crits[Index].Coeff;
}

KRCrit KRCritSys::GetByIndex(int Index) {
	return Crits[Index];
};

void KRCritSys::SetPrority(std::vector<int>Pr) {
	Priority = Pr;
};

KRCrit KRCritSys::GetByPriority(int Index) {
	return Crits[Priority[Index]];
};

int KRCritSys::GetPriority(int Index) {
	return Priority[Index];
};
