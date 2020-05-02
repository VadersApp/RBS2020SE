#pragma once
#include "skse64/PapyrusNativeFunctions.h"

namespace RBS2020 {

	
	bool RegisterFuncs(VMClassRegistry* registry);
	void MorphFemale(StaticFunctionTag* base);
	void MorphMale(StaticFunctionTag* base);

	void SetSeedOffset(StaticFunctionTag* base, BSFixedString seedOffset);
	BSFixedString GetSeedOffset(StaticFunctionTag* base);

	float GetMorphfactorMale(StaticFunctionTag* base);
	float GetMorphfactorFemale(StaticFunctionTag* base);

	void SetMorphfactorMale(StaticFunctionTag* base, float morphfactor);
	void SetMorphfactorFemale(StaticFunctionTag* base, float morphfactor);

	float GetMorphfactorBreasts(StaticFunctionTag* base);
	void SetMorphfactorBreasts(StaticFunctionTag* base, float fmorphfactorBreasts);
	SInt32 GetFemalesFound(StaticFunctionTag* base);
	SInt32 GetMalesFound(StaticFunctionTag* base);
	void DeleteMorphs(StaticFunctionTag* base);
	void SetSkipEssential(StaticFunctionTag* base, bool myNonEssential);
	bool GetSkipEssential(StaticFunctionTag* base);
	void SetSkipUnique(StaticFunctionTag* base, bool mySkipUnique);
	bool GetSkipUnique(StaticFunctionTag* base);

	bool TriFemaleExists(StaticFunctionTag* base);
	bool TriMaleExists(StaticFunctionTag* base);
	SInt32 PreFilterActors(StaticFunctionTag* base);
	bool IsPrefiltered(StaticFunctionTag* base);
	void ChangeHair(StaticFunctionTag* base);;
	RE::FormID GetRandomFemaleFormID(StaticFunctionTag* base);

} // namespace RBS2020
