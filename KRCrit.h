#ifndef KR_KRCRIT_H_
#define KR_KRCRIT_H_

#include "KRShared.h"

class KRCrit {
public:
	KRCrit();
	KRCrit(String N, bool d);

	// protected:
	String Name;
	int Value;
	float Coeff;
	bool dec;
};

#endif //KR_KRCRIT_H_
