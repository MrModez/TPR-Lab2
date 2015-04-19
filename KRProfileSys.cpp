#include "KRProfileSys.h"

KRProfileSys::KRProfileSys() {
}

KRProfileSys::KRProfileSys(KRCritSys Crt) {
	Crits = Crt;
}

KRProfileSys::KRProfileSys(std::vector<KRProfile>P) {
	// Profiles = P;
}

void KRProfileSys::AddProfile(KRProfile *Profile) {
	Profiles.push_back(Profile);
}

void KRProfileSys::AddBest(KRProfile *Profile) {
	Best = Profile;
}

void KRProfileSys::AddWorst(KRProfile *Profile) {
	Worst = Profile;
}

void KRProfileSys::AddSpecial(Range A_Range, KRProfile *Profile) {
	switch (A_Range) {
	case A_NONE:
		break;
	case A_WORST:
		Worst = Profile;
		break;
	case A_25:
		A25 = Profile;
		break;
	case A_50:
		A50 = Profile;
		break;
	case A_75:
		A75 = Profile;
		break;
	case A_BEST:
		Best = Profile;
		break;
	case A_EQ:
		AEQ = Profile;
		break;
	default:
		break;
	}
}

void KRProfileSys::ChangeProfile(int Index1, int Index2, int Value) {
	Profiles[Index1]->ChangeCrit(Index2, Value);
}

void KRProfileSys::ChangeBest(int Index, int Value) {
	Best->ChangeCrit(Index, Value);
}

void KRProfileSys::ChangeWorst(int Index, int Value) {
	Worst->ChangeCrit(Index, Value);
}

void KRProfileSys::ChangeSpecial(Range A_Range, int Index, int Value) {
	switch (A_Range) {
	case A_NONE:
		break;
	case A_WORST:
		Worst->ChangeCrit(Index, Value);
		break;
	case A_25:
		A25->ChangeCrit(Index, Value);
		break;
	case A_50:
		A50->ChangeCrit(Index, Value);
		break;
	case A_75:
		A75->ChangeCrit(Index, Value);
		break;
	case A_BEST:
		Best->ChangeCrit(Index, Value);
		break;
	case A_EQ:
		AEQ->ChangeCrit(Index, Value);
		break;
	default:
		break;
	}
}

int KRProfileSys::GetSize() {
	return Profiles.size();
};

KRProfile* KRProfileSys::GetByIndex(int Index) {
	return Profiles[Index];
};

KRProfile* KRProfileSys::GetBest() {
	return Best;
};

KRProfile* KRProfileSys::GetWorst() {
	return Worst;
};

KRProfile* KRProfileSys::GetSpecial(Range A_Range) {
	switch (A_Range) {
	case A_NONE:
		break;
	case A_WORST:
		return Worst;
		break;
	case A_25:
		return A25;
		break;
	case A_50:
		return A50;
		break;
	case A_75:
		return A75;
		break;
	case A_BEST:
		return Best;
		break;
	case A_EQ:
		return AEQ;
		break;
	default:
		break;
	}
};

/*
 float KRProfileSys::GetGraphValue(int Index, int Value) {
 int Val1 = 0, Val2 = 0;
 float Coeff1 = 0, Coeff2 = 0;
 int index = 0;
 if (Value <= GetSpecial(A_WORST)->GetValue(Index))
 return 0.0;
 if (Value >= GetSpecial(A_BEST)->GetValue(Index))
 return 1.0;

 for (int i = A_WORST; i < A_BEST; i++) {
 if (Value > GetSpecial(i)->GetValue(Index) && Value <= GetSpecial(i + 1)->GetValue(Index)) {
 Val1 = GetSpecial(i)->GetValue(Index);
 Val2 = GetSpecial(i + 1)->GetValue(Index);
 Coeff1 = GetSpecial(i)->GetCoeff(Index);
 Coeff2 = GetSpecial(i + 1)->GetCoeff(Index);
 index = i;
 };
 }
 int A1 = Val2 - Val1;
 int A2 = Value - Val1;
 float C2 = Coeff2 - Coeff1;

 float result;
 result = (float)A2 / (float)A1 * (float)C2 + Coeff1;

 return result;
 } */

float KRProfileSys::GraphValue(int Index, int iEQ) {
	int Value = GetSpecial(A_EQ)->GetValue(iEQ);
	int Val1 = 0, Val2 = 0;
	float Coeff1 = 0, Coeff2 = 0;
	int index = 0;
	bool dec = Crits.GetByIndex(Index).dec;

	if (!dec) {
		if (Value <= GetSpecial(A_WORST)->GetValue(Index))
			return 0.0;
		if (Value >= GetSpecial(A_BEST)->GetValue(Index))
			return 1.0;
	}
	else {
		if (Value >= GetSpecial(A_WORST)->GetValue(Index))
			return 0.0;
		if (Value <= GetSpecial(A_BEST)->GetValue(Index))
			return 1.0;
	}

	if (!dec) {
		for (int i = A_WORST; i < A_BEST; i++) {
			if (Value >= GetSpecial(i)->GetValue(Index) && Value <
				GetSpecial(i + 1)->GetValue(Index)) {
				Val1 = GetSpecial(i)->GetValue(Index);
				Val2 = GetSpecial(i + 1)->GetValue(Index);
				Coeff1 = GetSpecial(i)->GetCoeff(Index);
				Coeff2 = GetSpecial(i + 1)->GetCoeff(Index);
				index = i;
			};
		}
	}
	else {
		for (int i = A_BEST; i > A_WORST; i--) {
			index = i;
			if (Value >= GetSpecial(i)->GetValue(Index) && Value <
				GetSpecial(i - 1)->GetValue(Index)) {
				Val2 = GetSpecial(i)->GetValue(Index);
				Val1 = GetSpecial(i - 1)->GetValue(Index);
				Coeff2 = GetSpecial(i)->GetCoeff(Index);
				Coeff1 = GetSpecial(i - 1)->GetCoeff(Index);
			};
		}
	}
	float result;

	int W = GetSpecial(A_WORST)->GetValue(Index);
	int A25 = GetSpecial(A_25)->GetValue(Index);
	int A50 = GetSpecial(A_50)->GetValue(Index);
	int A75 = GetSpecial(A_75)->GetValue(Index);
	int B = GetSpecial(A_BEST)->GetValue(Index);

	if (!dec) {
		int A1 = Val2 - Val1;
		int A2 = Value - Val1;
		float C2 = Coeff2 - Coeff1;

		result = (float)A2 / (float)A1 * (float)C2 + Coeff1;
	}
	else {
		int A1 = Val2 - Val1;
		int A2 = Value - Val1;
		float C2 = Coeff2 - Coeff1;

		result = (float)A2 / (float)A1 * (float)C2 + Coeff1;
	}
	return result;
}
