
#include "plugin.h"
#include "MorphProcedural.h"
#include "morph.h"
#include "actors.h"

namespace RBS2020 {
    SInt32 femalesFound = 0;
	SInt32 malesFound = 0;

	bool RegisterFuncs(VMClassRegistry* registry) {
		registry->RegisterFunction(new NativeFunction0 <StaticFunctionTag, bool>("IsPrefiltered", "RBS2020PluginScript", RBS2020::IsPrefiltered, registry));
		registry->RegisterFunction(new NativeFunction0 <StaticFunctionTag, void>("PreFilterActors", "RBS2020PluginScript", RBS2020::PreFilterActors, registry));
		registry->RegisterFunction(new NativeFunction0 <StaticFunctionTag, void>("MorphMale", "RBS2020PluginScript", RBS2020::MorphMale, registry));
		registry->RegisterFunction(new NativeFunction0 <StaticFunctionTag, void>("MorphFEmale", "RBS2020PluginScript", RBS2020::MorphFemale, registry));
		registry->RegisterFunction(new NativeFunction1 <StaticFunctionTag, void, BSFixedString>("SetSeedOffset", "RBS2020PluginScript", RBS2020::SetSeedOffset, registry));
		registry->RegisterFunction(new NativeFunction0 <StaticFunctionTag, BSFixedString>("GetSeedOffset", "RBS2020PluginScript", RBS2020::GetSeedOffset, registry));
		registry->RegisterFunction(new NativeFunction0 <StaticFunctionTag, float>("GetMorphfactorFemale", "RBS2020PluginScript", RBS2020::GetMorphfactorFemale, registry));
		registry->RegisterFunction(new NativeFunction0 <StaticFunctionTag, float>("GetMorphfactorMale", "RBS2020PluginScript", RBS2020::GetMorphfactorMale, registry));
		registry->RegisterFunction(new NativeFunction1 <StaticFunctionTag, void, float>("SetMorphfactorFemale", "RBS2020PluginScript", RBS2020::SetMorphfactorFemale, registry));
		registry->RegisterFunction(new NativeFunction1 <StaticFunctionTag, void, float>("SetMorphfactorMale", "RBS2020PluginScript", RBS2020::SetMorphfactorMale, registry));
		registry->RegisterFunction(new NativeFunction0 <StaticFunctionTag, float>("GetMorphfactorBreasts", "RBS2020PluginScript", RBS2020::GetMorphfactorBreasts, registry));
		registry->RegisterFunction(new NativeFunction1 <StaticFunctionTag, void, float>("SetMorphfactorBreasts", "RBS2020PluginScript", RBS2020::SetMorphfactorBreasts, registry));
		registry->RegisterFunction(new NativeFunction0 <StaticFunctionTag, SInt32>("GetFemalesFound", "RBS2020PluginScript", RBS2020::GetFemalesFound, registry));
		registry->RegisterFunction(new NativeFunction0 <StaticFunctionTag, SInt32>("GetMalesFound", "RBS2020PluginScript", RBS2020::GetMalesFound, registry));
		registry->RegisterFunction(new NativeFunction0 <StaticFunctionTag, void>("DeleteMorphs", "RBS2020PluginScript", RBS2020::DeleteMorphs, registry));
		registry->RegisterFunction(new NativeFunction1 <StaticFunctionTag, void, bool>("SetSkipEssential", "RBS2020PluginScript", RBS2020::SetSkipEssential, registry));
		registry->RegisterFunction(new NativeFunction0 <StaticFunctionTag, bool>("GetSkipEssential", "RBS2020PluginScript", RBS2020::GetSkipEssential, registry));
		registry->RegisterFunction(new NativeFunction1 <StaticFunctionTag, void, bool>("SetSkipUnique", "RBS2020PluginScript", RBS2020::SetSkipUnique, registry));
		registry->RegisterFunction(new NativeFunction0 <StaticFunctionTag, bool>("GetSkipUnique", "RBS2020PluginScript", RBS2020::GetSkipUnique, registry));
		registry->RegisterFunction(new NativeFunction0 <StaticFunctionTag, bool>("TriFemaleExists", "RBS2020PluginScript", RBS2020::TriFemaleExists, registry));
		registry->RegisterFunction(new NativeFunction0 <StaticFunctionTag, bool>("TriMaleExists", "RBS2020PluginScript", RBS2020::TriMaleExists, registry));
		return true;
	}

	void PreFilterActors(StaticFunctionTag* base) {
		Actors::PrefilterActors();
	}
	bool IsPrefiltered(StaticFunctionTag* base) {
		return Actors::IsPrefiltered();
	}

	void SetSkipEssential(StaticFunctionTag* base, bool mySkipEssential) {
		Morph::SetSkipEssential(mySkipEssential);
	}
	bool GetSkipEssential(StaticFunctionTag* base) {
		return Morph::GetSkipEssential();
	}

	void SetSkipUnique(StaticFunctionTag* base, bool mySkipUnique) {
		Morph::SetSkipUnique(mySkipUnique);
	}

	bool GetSkipUnique(StaticFunctionTag* base) {
		return Morph::GetSkipUnique();
	}
	
	void SetSeedOffset(StaticFunctionTag* base, BSFixedString s_seedOffset) {
		SInt32 seedOffset = std::strtol(s_seedOffset.c_str(), nullptr, 10);
		MorphProcedural::SetSeedOffset(seedOffset);
	}

	BSFixedString GetSeedOffset(StaticFunctionTag* base) {
		std::string s = std::to_string(MorphProcedural::GetSeedOffset());

		return s.c_str();
	}

	SInt32 GetFemalesFound(StaticFunctionTag* base) {
		return femalesFound;
	}

	SInt32 GetMalesFound(StaticFunctionTag* base) {
		return malesFound;
	}

	bool TriFemaleExists(StaticFunctionTag* base) {
		return Morph::TriFemaleExists();
	}

	bool TriMaleExists(StaticFunctionTag* base) {
		return Morph::TriMaleExists();
	}

	void MorphMale(StaticFunctionTag* base) {
		malesFound = Morph::MorphMale();
	}

	void MorphFemale(StaticFunctionTag* base) {
		femalesFound = Morph::MorphFemale();
	}

	void DeleteMorphs(StaticFunctionTag* base) {
		Morph::DeleteMorphs();
	}

	void SetMorphfactorFemale(StaticFunctionTag* base, float morphfactorFemale) {
		MorphProcedural::SetMorphfactorFemale(morphfactorFemale);
	}

	void SetMorphfactorMale(StaticFunctionTag* base, float morphfactorMale) {
		MorphProcedural::SetMorphfactorMale(morphfactorMale);
	}

	float GetMorphfactorMale(StaticFunctionTag* base) {
		return MorphProcedural::GetMorphfactorMale();
	}

	float GetMorphfactorFemale(StaticFunctionTag* base) {
		return MorphProcedural::GetMorphfactorFemale();
	}

	void SetMorphfactorBreasts(StaticFunctionTag* base, float morphfactorBreasts) {
		MorphProcedural::SetMorphfactorBreasts(morphfactorBreasts);
	}

	float GetMorphfactorBreasts(StaticFunctionTag* base) {
		return MorphProcedural::GetMorphfactorBreasts();
	}
};