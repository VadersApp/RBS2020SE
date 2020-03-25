#pragma once
#include "skee/IPluginInterface.h"
#include "skse64/PapyrusNativeFunctions.h"
#include "re/skyrim.h"


namespace RBS2020
{
	class Morph {
	private:
		static inline bool skipEssential = false;
		static inline bool skipUnique = false;
		static inline IBodyMorphInterface* bodyMorphInterface;

	public:

		static void PrintMorphs(RE::Actor* myActor);
		static SInt32 MorphFemale();
		static SInt32 MorphMale();
		static SInt32 MorphActors(std::vector<RE::Actor*>, bool female);
		static bool SetMorphInterface(IBodyMorphInterface* mi);

		static void MorphActorCBBE(RE::Actor* myActor);
		static void MorphActorBHUNP(RE::Actor* myActor);
		static void MorphActorSMMB(RE::Actor* myActor);
		static void DeleteMorph(RE::Actor* myActor);
		//static void OutfitTest(RE::Actor* myActor);

		static float CalculateFitness(RE::Actor* myActor);
		static float CalculateMusclepower(RE::Actor* myActor);
		static float GetMorphfactorMale(StaticFunctionTag* base);
		static float GetMorphfactorFemale(StaticFunctionTag* base);

		static void SetMorphfactorMale(StaticFunctionTag* base, float morphfactor);
		static void SetMorphfactorFemale(StaticFunctionTag* base, float morphfactor);

		static float GetMorphfactorBreasts(StaticFunctionTag* base);
		static void SetMorphfactorBreasts(StaticFunctionTag* base, float fmorphfactorBreasts);

		static void DeleteMorphs();

		static bool TriFemaleExists();
		static bool TriMaleExists();

		static void SetSkipEssential(bool myNonEssential);
		static bool GetSkipEssential();
		static void SetSkipUnique(bool mySkipUnique);
		static bool GetSkipUnique();
	};
}