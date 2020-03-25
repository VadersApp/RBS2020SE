
#include "morph.h"
#include "MorphProcedural.h"
#include <filesystem>
#include "actors.h"
namespace RBS2020
{
	MorphProcedural morphProcedural;
	bool Morph::SetMorphInterface(IBodyMorphInterface* mi) {
		if (mi->GetVersion()) {
			bodyMorphInterface = mi;
		}
		else return false;
		return true;
	}

	void Morph::SetSkipEssential(bool mySkipEssential) {
		skipEssential = mySkipEssential;
	}
	bool Morph::GetSkipEssential() {
		return skipEssential;
	}
	void Morph::SetSkipUnique(bool mySkipUnique) {
		skipUnique = mySkipUnique;
	}
	bool Morph::GetSkipUnique() {
		return skipUnique;
	}

	float Morph::CalculateMusclepower(RE::Actor* myActor) {
		float oneHanded = myActor->GetActorValue(RE::ActorValue::kOneHanded);
		if (oneHanded < 15) { oneHanded = 15; }
		if (oneHanded > 30) { oneHanded = 30; }
		float smithing = myActor->GetActorValue(RE::ActorValue::kSmithing);
		if (smithing < 15) { smithing = 15; }
		if (smithing > 30) { smithing = 30; }
		float block = myActor->GetActorValue(RE::ActorValue::kBlock);
		if (block < 15) { block = 15; }
		if (block > 30) { block = 30; }
		float unarmedDamage = myActor->GetActorValue(RE::ActorValue::kUnarmedDamage);
		if (unarmedDamage < 15) { unarmedDamage = 15; }
		if (unarmedDamage > 30) { unarmedDamage = 30; }
		return (((oneHanded + smithing + block + unarmedDamage) - 60) / (120.0 - 60.0) * 1.8);
	}

	float Morph::CalculateFitness(RE::Actor* myActor) {
		float sneak = myActor->GetActorValue(RE::ActorValue::kSneak);
		if (sneak < 15) { sneak = 15; }
		if (sneak > 30) { sneak = 30; }
		float pickpocket = myActor->GetActorValue(RE::ActorValue::kPickpocket);
		if (pickpocket < 15) { pickpocket = 15; }
		if (pickpocket > 30) { pickpocket = 30; }
		float lockpicking = myActor->GetActorValue(RE::ActorValue::kLockpicking);
		if (lockpicking < 15) { lockpicking = 15; }
		if (lockpicking > 30) { lockpicking = 30; }
		float lightArmor = myActor->GetActorValue(RE::ActorValue::kLightArmor);
		if (lightArmor < 15) { lightArmor = 15; }
		if (lightArmor > 30) { lightArmor = 30; }
		return ((sneak + pickpocket + lockpicking + lightArmor) - 60) / (120.0 - 60.0);
	}

	bool  Morph::TriFemaleExists() {
		bool isTri = std::filesystem::exists(std::filesystem::current_path() / std::filesystem::path("Data\\meshes\\actors\\character\\character assets\\femalebody.tri").string().c_str());
		if (isTri) _MESSAGE("femalebody.tri found");
		else { _MESSAGE("femalebody.tri NOT found"); }
		return isTri;
	}

	bool  Morph::TriMaleExists() {
		bool isTri = std::filesystem::exists(std::filesystem::current_path() / std::filesystem::path("Data\\meshes\\actors\\character\\character assets\\malebody.tri").string().c_str());
		if (isTri) _MESSAGE("Malebody.tri found");
		else {
			_MESSAGE("Malebody.tri NOT found");
		}
		return isTri;
	}

	SInt32 Morph::MorphMale() {
		return (Morph::MorphActors(Actors::GetMales(), false));

	}

	SInt32 Morph::MorphFemale() {
		return (Morph::MorphActors(Actors::GetFemales(), true));
	}

	SInt32 Morph::MorphActors(std::vector<RE::Actor*> Actors, bool female) {
		SInt32 actorsFound = 0;
		for (auto myActor : Actors) {
			_MESSAGE("");
			if (myActor->GetName()) {
				//_MESSAGENNL("Name : %s race Formid %i", myActor->GetName(), myActor->GetRace()->GetFormID());
			}
			if (!myActor->IsPlayer()) {
				//_MESSAGENNL("Begin Morphing ");
				if (female) {
					MorphActorCBBE(myActor);
					actorsFound++;
				}
				else {
					MorphActorSMMB(myActor);
					actorsFound++;
				}
				//_MESSAGENNL("End Morphing ");

			}
		}
		return actorsFound;
	}

	void Morph::DeleteMorphs() {
		auto lookup = RE::GlobalLookupInfo::GetSingleton();
		RE::BSReadLockGuard locker(lookup->allFormsMapLock);
		if (!lookup->allForms) {

		}
		auto& formIDs = *lookup->allForms;
		_MESSAGE("Delete Morphs called");
		UInt32 TotalActors = formIDs.size();
		_MESSAGE("Total Actors %i", TotalActors);
		for (auto elem : formIDs) {
			auto myActor = RE::TESForm::LookupByID<RE::Actor>(elem.first);
			if (myActor) {
				if (!myActor->IsChild()) {
					DeleteMorph(myActor);
				}
			}
		}
	}

	void  Morph::DeleteMorph(RE::Actor* myActor) {
		TESObjectREFR* myREFR = (TESObjectREFR*)myActor;
		bodyMorphInterface->ClearBodyMorphKeys(myREFR, "RBS2020");
		bodyMorphInterface->ApplyBodyMorphs(myREFR, false);
		bodyMorphInterface->UpdateModelWeight(myREFR, true);
	}

	void Morph::SetMorphfactorFemale(StaticFunctionTag* base, float morphfactorFemale) {
		morphProcedural.SetMorphfactorFemale(morphfactorFemale);
	}

	void Morph::SetMorphfactorMale(StaticFunctionTag* base, float morphfactorMale) {
		morphProcedural.SetMorphfactorMale(morphfactorMale);
	}

	float Morph::GetMorphfactorMale(StaticFunctionTag* base) {
		return morphProcedural.GetMorphfactorMale();
	}

	float Morph::GetMorphfactorFemale(StaticFunctionTag* base) {
		return morphProcedural.GetMorphfactorFemale();
	}

	void  Morph::SetMorphfactorBreasts(StaticFunctionTag* base, float morphfactorBreasts) {
		morphProcedural.SetMorphfactorBreasts(morphfactorBreasts);
	}

	float  Morph::GetMorphfactorBreasts(StaticFunctionTag* base) {
		return morphProcedural.GetMorphfactorBreasts();
	}
	void  Morph::PrintMorphs(RE::Actor* myActor) {
		TESObjectREFR* myREFR = (TESObjectREFR*)myActor;
		float ForearmSize = bodyMorphInterface->GetBodyMorphs(myREFR, "ForearmSize");
		float ChubbyArms = bodyMorphInterface->GetBodyMorphs(myREFR, "ChubbyArms");
		float ShoulderWidth = bodyMorphInterface->GetBodyMorphs(myREFR, "ShoulderWidth");
		float Arms = bodyMorphInterface->GetBodyMorphs(myREFR, "Arms");
		float ShoulderSmooth = bodyMorphInterface->GetBodyMorphs(myREFR, "ShoulderSmooth");
		float ShoulderTweak = bodyMorphInterface->GetBodyMorphs(myREFR, "ShoulderTweak");

		float Belly = bodyMorphInterface->GetBodyMorphs(myREFR, "Belly");
		float TummyTuck = bodyMorphInterface->GetBodyMorphs(myREFR, "TummyTuck");
		float BigBelly = bodyMorphInterface->GetBodyMorphs(myREFR, "BigBelly");

		float HipBone = bodyMorphInterface->GetBodyMorphs(myREFR, "HipBone");
		float Hips = bodyMorphInterface->GetBodyMorphs(myREFR, "Hips");
		float HipForward = bodyMorphInterface->GetBodyMorphs(myREFR, "HipForward");
		float HipUpperWidth = bodyMorphInterface->GetBodyMorphs(myREFR, "HipUpperWidth");

		float NippleLength = bodyMorphInterface->GetBodyMorphs(myREFR, "NippleLength");
		float NipplePerkiness = bodyMorphInterface->GetBodyMorphs(myREFR, "NipplePerkiness");
		float NipplePerkManga = bodyMorphInterface->GetBodyMorphs(myREFR, "NipplePerkManga");
		float NippleTipManga = bodyMorphInterface->GetBodyMorphs(myREFR, "NippleTipManga");
		float NippleDistance = bodyMorphInterface->GetBodyMorphs(myREFR, "NippleDistance");
		float NippleSize = bodyMorphInterface->GetBodyMorphs(myREFR, "NippleSize");
		float AreolaSize = bodyMorphInterface->GetBodyMorphs(myREFR, "AreolaSize");
		float NippleDown = bodyMorphInterface->GetBodyMorphs(myREFR, "NippleDown");

		float MuscleAbs = bodyMorphInterface->GetBodyMorphs(myREFR, "MuscleAbs");
		float MuscleArms = bodyMorphInterface->GetBodyMorphs(myREFR, "MuscleArms");
		float MuscleButt = bodyMorphInterface->GetBodyMorphs(myREFR, "MuscleButt");
		float MuscleLegs = bodyMorphInterface->GetBodyMorphs(myREFR, "MuscleLegs");
		float MusclePecs = bodyMorphInterface->GetBodyMorphs(myREFR, "MusclePecs");

		float BigButt = bodyMorphInterface->GetBodyMorphs(myREFR, "BigButt");
		float ChubbyButt = bodyMorphInterface->GetBodyMorphs(myREFR, "ChubbyButt");
		float Butt = bodyMorphInterface->GetBodyMorphs(myREFR, "Butt");

		float ButtClassic = bodyMorphInterface->GetBodyMorphs(myREFR, "ButtClassic");
		float ButtShape2 = bodyMorphInterface->GetBodyMorphs(myREFR, "ButtShape2");
		float ButtCrack = bodyMorphInterface->GetBodyMorphs(myREFR, "ButtCrack");
		float AppleCheeks = bodyMorphInterface->GetBodyMorphs(myREFR, "AppleCheeks");
		float RoundAss = bodyMorphInterface->GetBodyMorphs(myREFR, "RoundAss");
		float CrotchBack = bodyMorphInterface->GetBodyMorphs(myREFR, "CrotchBack");
		float Groin = bodyMorphInterface->GetBodyMorphs(myREFR, "Groin");

		float ChubbyLegs = bodyMorphInterface->GetBodyMorphs(myREFR, "ChubbyLegs");
		float Legs = bodyMorphInterface->GetBodyMorphs(myREFR, "Legs");
		float Thighs = bodyMorphInterface->GetBodyMorphs(myREFR, "Thighs");

		float KneeShape = bodyMorphInterface->GetBodyMorphs(myREFR, "KneeShape");
		float KneeHeight = bodyMorphInterface->GetBodyMorphs(myREFR, "KneeHeight");
		float CalfSize = bodyMorphInterface->GetBodyMorphs(myREFR, "CalfSize");
		float CalfSmooth = bodyMorphInterface->GetBodyMorphs(myREFR, "CalfSmooth");
		float LegShapeClassic = bodyMorphInterface->GetBodyMorphs(myREFR, "LegShapeClassic");

		float BigTorso = bodyMorphInterface->GetBodyMorphs(myREFR, "BigTorso");
		float ChestDepth = bodyMorphInterface->GetBodyMorphs(myREFR, "ChestDepth");
		float ChestWidth = bodyMorphInterface->GetBodyMorphs(myREFR, "ChestWidth");
		float ChubbyWaist = bodyMorphInterface->GetBodyMorphs(myREFR, "ChubbyWaist");
		float Waist = bodyMorphInterface->GetBodyMorphs(myREFR, "Waist");
		float SternumDepth = bodyMorphInterface->GetBodyMorphs(myREFR, "SternumDepth");
		float SternumHeight = bodyMorphInterface->GetBodyMorphs(myREFR, "SternumHeight");
		float WaistHeight = bodyMorphInterface->GetBodyMorphs(myREFR, "WaistHeight");
		float WaistLine = bodyMorphInterface->GetBodyMorphs(myREFR, "WaistLine");

		float Breasts = bodyMorphInterface->GetBodyMorphs(myREFR, "Breasts");
		float BreastsNewSH = bodyMorphInterface->GetBodyMorphs(myREFR, "BreastsNewSH");
		float BreastCleavage = bodyMorphInterface->GetBodyMorphs(myREFR, "BreastCleavage");
		float BreastsFantasy = bodyMorphInterface->GetBodyMorphs(myREFR, "BreastsFantasy");
		float BreastCenter = bodyMorphInterface->GetBodyMorphs(myREFR, "BreastCenter");
		float BreastCenterBig = bodyMorphInterface->GetBodyMorphs(myREFR, "BreastCenterBig");
		float BreastFlatness2 = bodyMorphInterface->GetBodyMorphs(myREFR, "BreastFlatness2");
		float BreastFlatness = bodyMorphInterface->GetBodyMorphs(myREFR, "BreastFlatness");
		float BreastGravity2 = bodyMorphInterface->GetBodyMorphs(myREFR, "BreastGravity2");
		float BreastHeight = bodyMorphInterface->GetBodyMorphs(myREFR, "BreastHeight");
		float BreastsTogether = bodyMorphInterface->GetBodyMorphs(myREFR, "BreastsTogether");
		float BreastTopSlope = bodyMorphInterface->GetBodyMorphs(myREFR, "BreastTopSlope");
		// float PushUp", "",  MorphProcedural::GetMorphValuePushUp");

		float BreastPerkiness = bodyMorphInterface->GetBodyMorphs(myREFR, "BreastPerkiness");
		float BreastWidth = bodyMorphInterface->GetBodyMorphs(myREFR, "BreastWidth");
		//_MESSAGE("Name: %i %s Musclepower:%f Samson:%f Fitness:%f Weight: %f", myActor->GetFormType(), myActor->GetName(), MorphProcedural::GetMusclepower(), MorphProcedural::GetMorphValueSamSamson(), MorphProcedural::GetFitness(), MorphProcedural::GetWeight());
	}

	void Morph::MorphActorSMMB(RE::Actor* myActor) {

		TESObjectREFR* myREFR = (TESObjectREFR*)myActor;
		//_MESSAGENNL("Got ObjectRefence,");
		MorphProcedural::SetSeed(myActor->GetFormID());
		//_MESSAGENNL("Seed set,");
		MorphProcedural::SetFitness(CalculateFitness(myActor));
		//_MESSAGENNL("Fitness set,");
		MorphProcedural::SetMusclepower(CalculateMusclepower(myActor));
		//_MESSAGENNL("Musclepower set,");
		MorphProcedural::SetMorphfactor(MorphProcedural::GetMorphfactorMale());
		//_MESSAGENNL("Morphfactor set,");
		MorphProcedural::SetWeight(myActor->GetActorBase()->GetWeight());
		//_MESSAGENNL("Weight set,");
		bodyMorphInterface->SetMorph(myREFR, "SAM Samuel", "RBS2020", MorphProcedural::GetMorphValueSamSamuel());
		//_MESSAGENNL("Morph Samuel,");
		bodyMorphInterface->SetMorph(myREFR, "SAM Samson", "RBS2020", MorphProcedural::GetMorphValueSamSamson());
		//_MESSAGENNL("Morph Samson,");
		bodyMorphInterface->ApplyBodyMorphs((TESObjectREFR*)myREFR, true);
		//_MESSAGENNL("Morphs applied,");
		//bodyMorphInterface->UpdateModelWeight((TESObjectREFR*)myREFR, true);
		//_MESSAGENNL("Modelweight updated,");
	}

	void Morph::MorphActorCBBE(RE::Actor* myActor) {
		TESObjectREFR* myREFR = (TESObjectREFR*)myActor;
		_MESSAGE("Got ObjectRefence,");
		MorphProcedural::SetSeed(myActor->GetFormID());
		_MESSAGENNL("Seed set,");
		MorphProcedural::SetMusclepower(CalculateMusclepower(myActor));
		_MESSAGENNL("Musclepower set,");;
		MorphProcedural::SetMorphfactor(MorphProcedural::GetMorphfactorFemale());
		_MESSAGENNL("Morphfactor set,");
		if (myActor->GetRace()) {
			_MESSAGENNL("Got Race,");
			if (myActor->GetRace()->GetName()) {
				_MESSAGENNL("Got Racename,");
				std::string raceName = myActor->GetRace()->GetName();
				size_t found = raceName.find("Old");

				if (found != std::string::npos) {
					_MESSAGENNL("Old found,");
					MorphProcedural::SetGravityOffset(MorphProcedural::GetRandomFloat(0.5, 1));
					_MESSAGENNL("Gravity set,");
				}
				else {
					_MESSAGENNL("Old not found,");
					MorphProcedural::SetGravityOffset(0);
					_MESSAGENNL("Gravity set to 0,");
				}
			}
		}

		MorphProcedural::SetWeight(myActor->GetActorBase()->GetWeight());
		//_MESSAGENNL("Got weight,");
		if (myActor->GetActorBase()) {
			//_MESSAGENNL("Got Actorbase,");
			if (myActor->GetActorBase()->GetWeight() == 0) {
				//_MESSAGENNL("Weight was 0,");
				MorphProcedural::SetWeight(MorphProcedural::GetRandomFloat(0, 20));
				//_MESSAGENNL("Changed Weight,");
			}
			else {
				MorphProcedural::SetWeight(myActor->GetActorBase()->GetWeight());
				//_MESSAGENNL("Set Weight,");
			}
		}
		else {
			MorphProcedural::SetWeight(MorphProcedural::GetRandomFloat(0, 100));
			//_MESSAGENNL("Set Weight Random,");
		}
		_MESSAGENNL("Begin Morphing Values,");
		bodyMorphInterface->SetMorph(myREFR, "ForearmSize", "RBS2020", MorphProcedural::GetMorphValueForearmSize());
		bodyMorphInterface->SetMorph(myREFR, "ChubbyArms", "RBS2020", MorphProcedural::GetMorphValueChubbyArms());
		bodyMorphInterface->SetMorph(myREFR, "ShoulderWidth", "RBS2020", MorphProcedural::GetMorphValueShoulderWidth());
		bodyMorphInterface->SetMorph(myREFR, "Arms", "RBS2020", MorphProcedural::GetMorphValueArms());
		bodyMorphInterface->SetMorph(myREFR, "ShoulderSmooth", "RBS2020", MorphProcedural::GetMorphValueShoulderSmooth());
		bodyMorphInterface->SetMorph(myREFR, "ShoulderTweak", "RBS2020", MorphProcedural::GetMorphValueShoulderTweak());

		bodyMorphInterface->SetMorph(myREFR, "Belly", "RBS2020", MorphProcedural::GetMorphValueBelly());
		bodyMorphInterface->SetMorph(myREFR, "TummyTuck", "RBS2020", MorphProcedural::GetMorphValueTummyTuck());
		bodyMorphInterface->SetMorph(myREFR, "BigBelly", "RBS2020", MorphProcedural::GetMorphValueBigBelly());

		bodyMorphInterface->SetMorph(myREFR, "HipBone", "RBS2020", MorphProcedural::GetMorphValueHipBone());
		bodyMorphInterface->SetMorph(myREFR, "Hips", "RBS2020", MorphProcedural::GetMorphValueHips());
		bodyMorphInterface->SetMorph(myREFR, "HipForward", "RBS2020", MorphProcedural::GetMorphValueHipForward());
		bodyMorphInterface->SetMorph(myREFR, "HipUpperWidth", "RBS2020", MorphProcedural::GetMorphValueHipUpperWidth());

		bodyMorphInterface->SetMorph(myREFR, "NippleLength", "RBS2020", MorphProcedural::GetMorphValueNippleLength());
		bodyMorphInterface->SetMorph(myREFR, "NipplePerkiness", "RBS2020", MorphProcedural::GetMorphValueNipplePerkiness());
		bodyMorphInterface->SetMorph(myREFR, "NipplePerkManga", "RBS2020", MorphProcedural::GetMorphValueNipplePerkManga());
		bodyMorphInterface->SetMorph(myREFR, "NippleTipManga", "RBS2020", MorphProcedural::GetMorphValueNippleTipManga());
		bodyMorphInterface->SetMorph(myREFR, "NippleDistance", "RBS2020", MorphProcedural::GetMorphValueNippleDistance());
		bodyMorphInterface->SetMorph(myREFR, "NippleSize", "RBS2020", MorphProcedural::GetMorphValueNippleSize());
		bodyMorphInterface->SetMorph(myREFR, "AreolaSize", "RBS2020", MorphProcedural::GetMorphValueAreolaSize());
		bodyMorphInterface->SetMorph(myREFR, "NippleDown", "RBS2020", MorphProcedural::GetMorphValueNippleDown());

		bodyMorphInterface->SetMorph(myREFR, "MuscleAbs", "RBS2020", MorphProcedural::GetMorphValueMuscleAbs());
		bodyMorphInterface->SetMorph(myREFR, "MuscleArms", "RBS2020", MorphProcedural::GetMorphValueMuscleArms());
		bodyMorphInterface->SetMorph(myREFR, "MuscleButt", "RBS2020", MorphProcedural::GetMorphValueMuscleButt());
		bodyMorphInterface->SetMorph(myREFR, "MuscleLegs", "RBS2020", MorphProcedural::GetMorphValueMuscleLegs());
		bodyMorphInterface->SetMorph(myREFR, "MusclePecs", "RBS2020", MorphProcedural::GetMorphValueMusclePecs());

		bodyMorphInterface->SetMorph(myREFR, "BigButt", "RBS2020", MorphProcedural::GetMorphValueBigButt());
		bodyMorphInterface->SetMorph(myREFR, "ChubbyButt", "RBS2020", MorphProcedural::GetMorphValueChubbyButt());
		bodyMorphInterface->SetMorph(myREFR, "Butt", "RBS2020", MorphProcedural::GetMorphValueButt());

		bodyMorphInterface->SetMorph(myREFR, "ButtClassic", "RBS2020", MorphProcedural::GetMorphValueButtClassic());
		bodyMorphInterface->SetMorph(myREFR, "ButtShape2", "RBS2020", MorphProcedural::GetMorphValueButtShape2());
		bodyMorphInterface->SetMorph(myREFR, "ButtCrack", "RBS2020", MorphProcedural::GetMorphValueButtCrack());
		bodyMorphInterface->SetMorph(myREFR, "AppleCheeks", "RBS2020", MorphProcedural::GetMorphValueAppleCheeks());
		bodyMorphInterface->SetMorph(myREFR, "RoundAss", "RBS2020", MorphProcedural::GetMorphValueRoundAss());
		bodyMorphInterface->SetMorph(myREFR, "CrotchBack", "RBS2020", MorphProcedural::GetMorphValueCrotchBack());
		bodyMorphInterface->SetMorph(myREFR, "Groin", "RBS2020", MorphProcedural::GetMorphValueGroin());

		bodyMorphInterface->SetMorph(myREFR, "ChubbyLegs", "RBS2020", MorphProcedural::GetMorphValueChubbyLegs());
		bodyMorphInterface->SetMorph(myREFR, "Legs", "RBS2020", MorphProcedural::GetMorphValueLegs());
		bodyMorphInterface->SetMorph(myREFR, "Thighs", "RBS2020", MorphProcedural::GetMorphValueThighs());

		bodyMorphInterface->SetMorph(myREFR, "KneeShape", "RBS2020", MorphProcedural::GetMorphValueKneeShape());
		bodyMorphInterface->SetMorph(myREFR, "KneeHeight", "RBS2020", MorphProcedural::GetMorphValueKneeHeight());
		bodyMorphInterface->SetMorph(myREFR, "CalfSize", "RBS2020", MorphProcedural::GetMorphValueCalfSize());
		bodyMorphInterface->SetMorph(myREFR, "CalfSmooth", "RBS2020", MorphProcedural::GetMorphValueCalfSmooth());
		bodyMorphInterface->SetMorph(myREFR, "LegShapeClassic", "RBS2020", MorphProcedural::GetMorphValueLegShapeClassic());

		bodyMorphInterface->SetMorph(myREFR, "BigTorso", "RBS2020", MorphProcedural::GetMorphValueBigTorso());
		bodyMorphInterface->SetMorph(myREFR, "ChestDepth", "RBS2020", MorphProcedural::GetMorphValueChestDepth());
		bodyMorphInterface->SetMorph(myREFR, "ChestWidth", "RBS2020", MorphProcedural::GetMorphValueChestWidth());
		bodyMorphInterface->SetMorph(myREFR, "ChubbyWaist", "RBS2020", MorphProcedural::GetMorphValueChubbyWaist());
		bodyMorphInterface->SetMorph(myREFR, "Waist", "RBS2020", MorphProcedural::GetMorphValueWaist());
		bodyMorphInterface->SetMorph(myREFR, "SternumDepth", "RBS2020", MorphProcedural::GetMorphValueSternumDepth());
		bodyMorphInterface->SetMorph(myREFR, "SternumHeight", "RBS2020", MorphProcedural::GetMorphValueSternumHeight());
		bodyMorphInterface->SetMorph(myREFR, "WaistHeight", "RBS2020", MorphProcedural::GetMorphValueWaistHeight());
		bodyMorphInterface->SetMorph(myREFR, "WaistLine", "RBS2020", MorphProcedural::GetMorphValueWaistLine());

		bodyMorphInterface->SetMorph(myREFR, "Breasts", "RBS2020", MorphProcedural::GetMorphValueBreasts());
		bodyMorphInterface->SetMorph(myREFR, "BreastsNewSH", "RBS2020", MorphProcedural::GetMorphValueBreastsNewSH());
		bodyMorphInterface->SetMorph(myREFR, "BreastCleavage", "RBS2020", MorphProcedural::GetMorphValueBreastCleavage());
		bodyMorphInterface->SetMorph(myREFR, "BreastsFantasy", "RBS2020", MorphProcedural::GetMorphValueBreastsFantasy());
		bodyMorphInterface->SetMorph(myREFR, "BreastCenter", "RBS2020", MorphProcedural::GetMorphValueBreastCenter());
		bodyMorphInterface->SetMorph(myREFR, "BreastCenterBig", "RBS2020", MorphProcedural::GetMorphValueBreastCenterBig());
		bodyMorphInterface->SetMorph(myREFR, "BreastFlatness2", "RBS2020", MorphProcedural::GetMorphValueBreastFlatness2());
		bodyMorphInterface->SetMorph(myREFR, "BreastFlatness", "RBS2020", MorphProcedural::GetMorphValueBreastFlatness());
		bodyMorphInterface->SetMorph(myREFR, "BreastGravity2", "RBS2020", MorphProcedural::GetMorphValueBreastGravity2());
		bodyMorphInterface->SetMorph(myREFR, "BreastHeight", "RBS2020", MorphProcedural::GetMorphValueBreastHeight());
		bodyMorphInterface->SetMorph(myREFR, "BreastsTogether", "RBS2020", MorphProcedural::GetMorphValueBreastsTogether());
		bodyMorphInterface->SetMorph(myREFR, "BreastTopSlope", "RBS2020", MorphProcedural::GetMorphValueBreastTopSlope());
		// bodyMorphInterface->SetMorph(myREFR, "PushUp", "",  MorphProcedural::GetMorphValuePushUp());
		bodyMorphInterface->SetMorph(myREFR, "BreastPerkiness", "RBS2020", MorphProcedural::GetMorphValueBreastPerkiness());
		bodyMorphInterface->SetMorph(myREFR, "BreastWidth", "RBS2020", MorphProcedural::GetMorphValueBreastWidth());
		//_MESSAGENNL("End Morphing Values,");
		bodyMorphInterface->ApplyBodyMorphs((TESObjectREFR*)myREFR, true);
		_MESSAGENNL("Bodymorphs applied,");
		//bodyMorphInterface->UpdateModelWeight((TESObjectREFR*)myREFR, true);
		//_MESSAGENNL("Modelweight updated,");
		//_MESSAGE("Actors %s %f, %f ,%f", myActor->GetName(), MorphProcedural::GetMorphValueBreasts(), MorphProcedural::GetMorphValueBigTorso(), MorphProcedural::GetMorphValueForearmSize());
	}

	void  Morph::MorphActorBHUNP(RE::Actor* myActor) {
		TESObjectREFR* myREFR = (TESObjectREFR*)myActor;
		//_MESSAGENNL("Got ObjectRefence,");
		MorphProcedural::SetSeed(myActor->GetFormID());
		//_MESSAGENNL("Seed set,");
		MorphProcedural::SetMusclepower(CalculateMusclepower(myActor));
		//_MESSAGENNL("Musclepower set,");;
		MorphProcedural::SetMorphfactor(MorphProcedural::GetMorphfactorFemale());
		//_MESSAGENNL("Morphfactor set,");
		if (myActor->GetRace()) {
			//_MESSAGENNL("Got Race,");
			if (myActor->GetRace()->GetName()) {
				//_MESSAGENNL("Got Racename,");
				std::string raceName = myActor->GetRace()->GetName();
				size_t found = raceName.find("Old");

				if (found != std::string::npos) {
					//_MESSAGENNL("Old found,");
					MorphProcedural::SetGravityOffset(MorphProcedural::GetRandomFloat(0.5, 1));
					//_MESSAGENNL("Gravity set,");
				}
				else {
					//_MESSAGENNL("Old not found,");
					MorphProcedural::SetGravityOffset(0);
					//_MESSAGENNL("Gravity set to 0,");
				}
			}
		}

		MorphProcedural::SetWeight(myActor->GetActorBase()->GetWeight());
		//_MESSAGENNL("Got weight,");
		if (myActor->GetActorBase()) {
			//_MESSAGENNL("Got Actorbase,");
			if (myActor->GetActorBase()->GetWeight() == 0) {
				//_MESSAGENNL("Weight was 0,");
				MorphProcedural::SetWeight(MorphProcedural::GetRandomFloat(0, 20));
				//_MESSAGENNL("Changed Weight,");
			}
			else {
				MorphProcedural::SetWeight(myActor->GetActorBase()->GetWeight());
				//_MESSAGENNL("Set Weight,");
			}
		}
		else {
			MorphProcedural::SetWeight(MorphProcedural::GetRandomFloat(0, 100));
			//_MESSAGENNL("Set Weight Random,");
		}
		//_MESSAGENNL("Begin Morphing Values,");
		bodyMorphInterface->SetMorph(myREFR, "ForearmSize", "RBS2020", MorphProcedural::GetMorphValueForearmSize());
		bodyMorphInterface->SetMorph(myREFR, "ChubbyArms", "RBS2020", MorphProcedural::GetMorphValueChubbyArms());
		bodyMorphInterface->SetMorph(myREFR, "ShoulderWidth", "RBS2020", MorphProcedural::GetMorphValueShoulderWidth());
		bodyMorphInterface->SetMorph(myREFR, "Arms", "RBS2020", MorphProcedural::GetMorphValueArms());
		bodyMorphInterface->SetMorph(myREFR, "ShoulderSmooth", "RBS2020", MorphProcedural::GetMorphValueShoulderSmooth());
		bodyMorphInterface->SetMorph(myREFR, "ShoulderTweak", "RBS2020", MorphProcedural::GetMorphValueShoulderTweak());

		bodyMorphInterface->SetMorph(myREFR, "Belly", "RBS2020", MorphProcedural::GetMorphValueBelly());
		bodyMorphInterface->SetMorph(myREFR, "TummyTuck", "RBS2020", MorphProcedural::GetMorphValueTummyTuck());
		bodyMorphInterface->SetMorph(myREFR, "BigBelly", "RBS2020", MorphProcedural::GetMorphValueBigBelly());

		bodyMorphInterface->SetMorph(myREFR, "HipBone", "RBS2020", MorphProcedural::GetMorphValueHipBone());
		bodyMorphInterface->SetMorph(myREFR, "Hips", "RBS2020", MorphProcedural::GetMorphValueHips());
		bodyMorphInterface->SetMorph(myREFR, "HipForward", "RBS2020", MorphProcedural::GetMorphValueHipForward());
		bodyMorphInterface->SetMorph(myREFR, "HipUpperWidth", "RBS2020", MorphProcedural::GetMorphValueHipUpperWidth());

		bodyMorphInterface->SetMorph(myREFR, "NippleLength", "RBS2020", MorphProcedural::GetMorphValueNippleLength());
		bodyMorphInterface->SetMorph(myREFR, "NipplePerkiness", "RBS2020", MorphProcedural::GetMorphValueNipplePerkiness());
		bodyMorphInterface->SetMorph(myREFR, "NipplePerkManga", "RBS2020", MorphProcedural::GetMorphValueNipplePerkManga());
		bodyMorphInterface->SetMorph(myREFR, "NippleTipManga", "RBS2020", MorphProcedural::GetMorphValueNippleTipManga());
		bodyMorphInterface->SetMorph(myREFR, "NippleDistance", "RBS2020", MorphProcedural::GetMorphValueNippleDistance());
		bodyMorphInterface->SetMorph(myREFR, "NippleSize", "RBS2020", MorphProcedural::GetMorphValueNippleSize());
		bodyMorphInterface->SetMorph(myREFR, "AreolaSize", "RBS2020", MorphProcedural::GetMorphValueAreolaSize());
		bodyMorphInterface->SetMorph(myREFR, "NippleDown", "RBS2020", MorphProcedural::GetMorphValueNippleDown());

		bodyMorphInterface->SetMorph(myREFR, "MuscleAbs", "RBS2020", MorphProcedural::GetMorphValueMuscleAbs());
		bodyMorphInterface->SetMorph(myREFR, "MuscleArms", "RBS2020", MorphProcedural::GetMorphValueMuscleArms());
		bodyMorphInterface->SetMorph(myREFR, "MuscleButt", "RBS2020", MorphProcedural::GetMorphValueMuscleButt());
		bodyMorphInterface->SetMorph(myREFR, "MuscleLegs", "RBS2020", MorphProcedural::GetMorphValueMuscleLegs());
		bodyMorphInterface->SetMorph(myREFR, "MusclePecs", "RBS2020", MorphProcedural::GetMorphValueMusclePecs());

		bodyMorphInterface->SetMorph(myREFR, "BigButt", "RBS2020", MorphProcedural::GetMorphValueBigButt());
		bodyMorphInterface->SetMorph(myREFR, "ChubbyButt", "RBS2020", MorphProcedural::GetMorphValueChubbyButt());
		bodyMorphInterface->SetMorph(myREFR, "Butt", "RBS2020", MorphProcedural::GetMorphValueButt());

		bodyMorphInterface->SetMorph(myREFR, "ButtClassic", "RBS2020", MorphProcedural::GetMorphValueButtClassic());
		bodyMorphInterface->SetMorph(myREFR, "ButtShape2", "RBS2020", MorphProcedural::GetMorphValueButtShape2());
		bodyMorphInterface->SetMorph(myREFR, "ButtCrack", "RBS2020", MorphProcedural::GetMorphValueButtCrack());
		bodyMorphInterface->SetMorph(myREFR, "AppleCheeks", "RBS2020", MorphProcedural::GetMorphValueAppleCheeks());
		bodyMorphInterface->SetMorph(myREFR, "RoundAss", "RBS2020", MorphProcedural::GetMorphValueRoundAss());
		bodyMorphInterface->SetMorph(myREFR, "CrotchBack", "RBS2020", MorphProcedural::GetMorphValueCrotchBack());
		bodyMorphInterface->SetMorph(myREFR, "Groin", "RBS2020", MorphProcedural::GetMorphValueGroin());

		bodyMorphInterface->SetMorph(myREFR, "ChubbyLegs", "RBS2020", MorphProcedural::GetMorphValueChubbyLegs());
		bodyMorphInterface->SetMorph(myREFR, "Legs", "RBS2020", MorphProcedural::GetMorphValueLegs());
		bodyMorphInterface->SetMorph(myREFR, "Thighs", "RBS2020", MorphProcedural::GetMorphValueThighs());

		bodyMorphInterface->SetMorph(myREFR, "KneeShape", "RBS2020", MorphProcedural::GetMorphValueKneeShape());
		bodyMorphInterface->SetMorph(myREFR, "KneeHeight", "RBS2020", MorphProcedural::GetMorphValueKneeHeight());
		bodyMorphInterface->SetMorph(myREFR, "CalfSize", "RBS2020", MorphProcedural::GetMorphValueCalfSize());
		bodyMorphInterface->SetMorph(myREFR, "CalfSmooth", "RBS2020", MorphProcedural::GetMorphValueCalfSmooth());
		bodyMorphInterface->SetMorph(myREFR, "LegShapeClassic", "RBS2020", MorphProcedural::GetMorphValueLegShapeClassic());

		bodyMorphInterface->SetMorph(myREFR, "BigTorso", "RBS2020", MorphProcedural::GetMorphValueBigTorso());
		bodyMorphInterface->SetMorph(myREFR, "ChestDepth", "RBS2020", MorphProcedural::GetMorphValueChestDepth());
		bodyMorphInterface->SetMorph(myREFR, "ChestWidth", "RBS2020", MorphProcedural::GetMorphValueChestWidth());
		bodyMorphInterface->SetMorph(myREFR, "ChubbyWaist", "RBS2020", MorphProcedural::GetMorphValueChubbyWaist());
		bodyMorphInterface->SetMorph(myREFR, "Waist", "RBS2020", MorphProcedural::GetMorphValueWaist());
		bodyMorphInterface->SetMorph(myREFR, "SternumDepth", "RBS2020", MorphProcedural::GetMorphValueSternumDepth());
		bodyMorphInterface->SetMorph(myREFR, "SternumHeight", "RBS2020", MorphProcedural::GetMorphValueSternumHeight());
		bodyMorphInterface->SetMorph(myREFR, "WaistHeight", "RBS2020", MorphProcedural::GetMorphValueWaistHeight());
		bodyMorphInterface->SetMorph(myREFR, "WaistLine", "RBS2020", MorphProcedural::GetMorphValueWaistLine());

		bodyMorphInterface->SetMorph(myREFR, "Breasts", "RBS2020", MorphProcedural::GetMorphValueBreasts() * -1);
		bodyMorphInterface->SetMorph(myREFR, "BreastsNewSH", "RBS2020", MorphProcedural::GetMorphValueBreastsNewSH());
		bodyMorphInterface->SetMorph(myREFR, "BreastCleavage", "RBS2020", MorphProcedural::GetMorphValueBreastCleavage());
		bodyMorphInterface->SetMorph(myREFR, "BreastsFantasy", "RBS2020", MorphProcedural::GetMorphValueBreastsFantasy());
		bodyMorphInterface->SetMorph(myREFR, "BreastCenter", "RBS2020", MorphProcedural::GetMorphValueBreastCenter());
		bodyMorphInterface->SetMorph(myREFR, "BreastCenterBig", "RBS2020", MorphProcedural::GetMorphValueBreastCenterBig());
		bodyMorphInterface->SetMorph(myREFR, "BreastFlatness2", "RBS2020", MorphProcedural::GetMorphValueBreastFlatness2());
		bodyMorphInterface->SetMorph(myREFR, "BreastFlatness", "RBS2020", MorphProcedural::GetMorphValueBreastFlatness());
		bodyMorphInterface->SetMorph(myREFR, "BreastGravity2", "RBS2020", MorphProcedural::GetMorphValueBreastGravity2());
		bodyMorphInterface->SetMorph(myREFR, "BreastHeight", "RBS2020", MorphProcedural::GetMorphValueBreastHeight());
		bodyMorphInterface->SetMorph(myREFR, "BreastsTogether", "RBS2020", MorphProcedural::GetMorphValueBreastsTogether());
		bodyMorphInterface->SetMorph(myREFR, "BreastTopSlope", "RBS2020", MorphProcedural::GetMorphValueBreastTopSlope());
		// bodyMorphInterface->SetMorph(myREFR, "PushUp", "",  MorphProcedural::GetMorphValuePushUp());
		bodyMorphInterface->SetMorph(myREFR, "BreastPerkiness", "RBS2020", MorphProcedural::GetMorphValueBreastPerkiness());
		bodyMorphInterface->SetMorph(myREFR, "BreastWidth", "RBS2020", MorphProcedural::GetMorphValueBreastWidth());
		//_MESSAGENNL("End Morphing Values,");
		bodyMorphInterface->ApplyBodyMorphs((TESObjectREFR*)myREFR, true);
		//_MESSAGENNL("Bodymorphs applied,");
		//bodyMorphInterface->UpdateModelWeight((TESObjectREFR*)myREFR, true);
		//_MESSAGENNL("Modelweight updated,");
		//_MESSAGE("Actors %s %f, %f ,%f", myActor->GetName(), MorphProcedural::GetMorphValueBreasts(), MorphProcedural::GetMorphValueBigTorso(), MorphProcedural::GetMorphValueForearmSize());
	}
}