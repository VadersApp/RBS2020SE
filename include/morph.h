#pragma once
#include "re/skyrim.h"
#include "skee/IPluginInterface.h"
#include "skse64/PapyrusNativeFunctions.h"

namespace RBS2020
{
	class Morph
	{
	public:
		static Morph* GetSingleton();

		void PrintMorphs(RE::Actor* myActor);
		SInt32 MorphFemale();
		SInt32 MorphMale();
		SInt32 MorphActors(std::vector<RE::Actor*>, bool female);
		bool SetMorphInterface(IBodyMorphInterface* mi);

		void MorphActorCBBE(RE::Actor* myActor);
		void MorphActorBHUNP(RE::Actor* myActor);
		void MorphActorSMMB(RE::Actor* myActor);
		void DeleteMorph(RE::Actor* myActor);
		// static void OutfitTest(RE::Actor* myActor);

		float CalculateFitness(RE::Actor* myActor);
		float CalculateMusclepower(RE::Actor* myActor);
		float GetMorphfactorMale(StaticFunctionTag* base);
		float GetMorphfactorFemale(StaticFunctionTag* base);

		void SetMorphfactorMale(StaticFunctionTag* base, float morphfactor);
		void SetMorphfactorFemale(StaticFunctionTag* base, float morphfactor);

		float GetMorphfactorBreasts(StaticFunctionTag* base);
		void SetMorphfactorBreasts(StaticFunctionTag* base, float fmorphfactorBreasts);
		void DeleteMorphs();

		bool TriFemaleExists();
		bool TriMaleExists();

		void SetSkipEssential(bool myNonEssential);
		bool GetSkipEssential();
		void SetSkipUnique(bool mySkipUnique);
		bool GetSkipUnique();

	private:
		Morph() {}
		Morph(const Morph&);
		~Morph() {}
		static Morph* _instance;
		bool skipEssential = false;
		bool skipUnique = false;
		IBodyMorphInterface* bodyMorphInterface;
	};
}  // namespace RBS2020
