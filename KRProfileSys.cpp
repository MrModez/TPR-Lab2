#include "KRProfileSys.h"

KRProfileSys::KRProfileSys() {
}

KRProfileSys::KRProfileSys(KRCritSys Crt) {
	Crits = Crt;
}

KRProfileSys::KRProfileSys(std::vector<KRProfile>P) {
	Profiles = P;
}

void KRProfileSys::AddProfile(KRProfile Profile) {
	Profiles.push_back(Profile);
}

void KRProfileSys::AddBest(KRProfile Profile) {
	Best = Profile;
}

void KRProfileSys::AddWorst(KRProfile Profile) {
	Worst = Profile;
}

void KRProfileSys::ChangeProfile(int Index1, int Index2, int Value) {
	Profiles[Index1].ChangeCrit(Index2, Value);
}

void KRProfileSys::ChangeBest(int Index, int Value) {
	Best.ChangeCrit(Index, Value);
}

void KRProfileSys::ChangeWorst(int Index, int Value) {
	Worst.ChangeCrit(Index, Value);
}

int KRProfileSys::GetSize() {
	return Profiles.size();
};

KRProfile KRProfileSys::GetByIndex(int Index) {
	return Profiles[Index];
};

KRProfile KRProfileSys::GetBest() {
	return Best;
};

KRProfile KRProfileSys::GetWorst() {
	return Worst;
};
