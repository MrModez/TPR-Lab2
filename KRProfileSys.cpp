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
	std::vector<int>P;
	P.resize(Crits.GetSize());
	Crits.SetPrority(P);
}

KRProfileSys::KRProfileSys(TStringList* Dat) {
	enum load {
		none, crits, main, profiles, priorities
	};

	load state = none;
	Crits = KRCritSys();
	std::vector<int>P;
	for (int i = 0; i < Dat->Count; i++) {
		if (Dat->Strings[i] == "[Crits]")
			state = crits;
		if (Dat->Strings[i] == "[Main]")
			state = main;
		if (Dat->Strings[i] == "[Profiles]")
			state = profiles;
		if (Dat->Strings[i] == "[Priorities]")
			state = priorities;
		if (Dat->Names[i] == "name") {
			KRProfile *Profile;
			switch (state) {
			case none:
				break;
			case crits:
				Crits.AddCrit(KRCrit(Dat->ValueFromIndex[i], Dat->ValueFromIndex[i + 1].ToInt()));
				break;
			case main:
				Profile = new KRProfile(Dat->ValueFromIndex[i], Crits);
				for (int j = 0; j < Crits.GetSize(); j++)
					Profile->ChangeCrit(j, Dat->ValueFromIndex[i + j + 1].ToInt());
				if (Dat->ValueFromIndex[i] == "Worst") {
					Profile->ChangeCoeff(0.0);
					Worst = Profile;
				}
				if (Dat->ValueFromIndex[i] == "Best") {
					Profile->ChangeCoeff(1.0);
					Best = Profile;
				}
				if (Dat->ValueFromIndex[i] == "A25") {
					Profile->ChangeCoeff(0.25);
					A25 = Profile;
				}
				if (Dat->ValueFromIndex[i] == "A50") {
					Profile->ChangeCoeff(0.50);
					A50 = Profile;
				}
				if (Dat->ValueFromIndex[i] == "A75") {
					Profile->ChangeCoeff(0.75);
					A75 = Profile;
				}
				if (Dat->ValueFromIndex[i] == "AEQ") {
					Profile->ChangeCoeff(0.0);
					AEQ = Profile;
				}
				break;
			case profiles:
				Profile = new KRProfile(Dat->ValueFromIndex[i], Crits);
				for (int j = 0; j < Crits.GetSize(); j++)
					Profile->ChangeCrit(j, Dat->ValueFromIndex[i + j + 1].ToInt());
				AddProfile(Profile);
				break;
			case priorities:
				for (int j = 0; j < Crits.GetSize(); j++)
					P.push_back(Dat->ValueFromIndex[i + j + 1].ToInt());
				Crits.SetPrority(P);
				break;
			default:
				break;
			}
		}
	}

	/*
	 Crits = KRCritSys();
	 Crits.AddCrit(KRCrit("Время решения", 1));
	 Crits.AddCrit(KRCrit("Точность", 0));
	 Crits.AddCrit(KRCrit("Устойчивость", 0));
	 Crits.AddCrit(KRCrit("Память", 1));

	 KRProfile* Worst = new KRProfile("Худ", Crits);
	 int CW[] = {500, 20, 0, 256};
	 Worst->SetCrits(CW);

	 KRProfile* Best = new KRProfile("Луд", Crits);
	 int CB[] = {1, 100, 1, 2};
	 Best->SetCrits(CB);

	 Profiles = KRProfileSys(Worst, Best, Crits);

	 KRProfile* Prof1 = new KRProfile("МВГ", Crits);
	 int C[] = {40, 100, 1, 16};
	 Prof1->SetCrits(C);
	 Profiles.AddProfile(Prof1);

	 KRProfile* Prof2 = new KRProfile("ГА", Crits);
	 int C2[] = {8, 85, 1, 32};
	 Prof2->SetCrits(C2);
	 Profiles.AddProfile(Prof2);

	 KRProfile* Prof3 = new KRProfile("МБС", Crits);
	 int C3[] = {20, 70, 0, 64};
	 Prof3->SetCrits(C3);
	 Profiles.AddProfile(Prof3);

	 KRProfile* Prof4 = new KRProfile("Пере", Crits);
	 int C4[] = {120, 100, 1, 128};
	 Prof4->SetCrits(C4);
	 Profiles.AddProfile(Prof4);
	 */
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
