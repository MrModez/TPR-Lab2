#include "KRProfileSys.h"

KRProfileSys::KRProfileSys() {
}

KRProfileSys::KRProfileSys(KRProfile *W, KRProfile *B, KRCritSys Crt) {
	Crits = Crt;

	Worst = W;
	Best = B;

	AddSpecial(A_25, new KRProfile("A25", Crits));
	AddSpecial(A_50, new KRProfile("A50", Crits));
	AddSpecial(A_75, new KRProfile("A75", Crits));
	AddSpecial(A_EQ, new KRProfile("AEQ", Crits));
	GetSpecial(A_WORST)->ChangeCoeff(0.0);
	GetSpecial(A_25)->ChangeCoeff(0.25);
	GetSpecial(A_50)->ChangeCoeff(0.50);
	GetSpecial(A_75)->ChangeCoeff(0.75);
	GetSpecial(A_BEST)->ChangeCoeff(1.0);
	GetSpecial(A_EQ)->ChangeCoeff(0);

	for (int i = 0; i < Crits.GetSize(); i++) {
		int Worst = 0, Best = 0;
		if (!Crits.GetByIndex(i).dec) {
			Worst = GetWorst()->GetValue(i);
			Best = GetBest()->GetValue(i);
		}
		else {
			Worst = GetWorst()->GetValue(i);
			Best = GetBest()->GetValue(i);
		}
		ChangeSpecial(A_25, i, (Worst + (Worst + Best) / 2.0) / 2.0);
		ChangeSpecial(A_50, i, (Worst + Best) / 2.0);
		ChangeSpecial(A_75, i, (Best + (Worst + Best) / 2.0) / 2.0);
		ChangeSpecial(A_EQ, i, (Worst + Best) / 2.0);
	}
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
	return NULL;
};

float KRProfileSys::GraphValue(int Index, int Value) {
	// int Value = GetSpecial(A_EQ)->GetValue(iEQ);
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

float KRProfileSys::ResultValue(int Index) {
	float result = 0.0;

	for (int i = 0; i < Crits.GetSize(); i++) {
		result += Crits.GetLambda(i) * GraphValue(i, Profiles[Index]->GetValue(i));
	}

	return result;
}

void KRProfileSys::SetLambdas() {
	std::vector<float>X;
	float sum = 1;
	for (unsigned int i = 1; i < Crits.GetSize(); i++) {
		int index = Crits.GetPriority(i);
		sum += GetSpecial(A_EQ)->GetCoeff(index);
	}

	X.push_back(1 / sum);
	for (int i = 1; i < Crits.GetSize(); i++) {
		int index = Crits.GetPriority(i);
		float a = GetSpecial(A_EQ)->GetCoeff(index);
		X.push_back(a * X[0]);
	}

	std::vector<float>L;
	for (int i = 0; i < Crits.GetSize(); i++) {
		int index = Crits.GetPriority(i);
		L.push_back(X[index]);
	}
	Crits.SetLambdas(L);
}

void KRProfileSys::SetEQCoeffs() {
	for (int i = 0; i < Crits.GetSize(); i++) {
		int base = Crits.GetPriority(0);
		int index = Crits.GetPriority(i);
		int value = GetSpecial(A_EQ)->GetValue(index);
		float res = GraphValue(base, value);
		GetSpecial(A_EQ)->ChangeCoeff(index, res);
	}
}
