
#include "morph.h"
#include "MorphProcedural.h"
#include "actors.h"
#include <filesystem>
namespace RBS2020
{
	Morph* Morph::_instance = 0;
	Morph* Morph::GetSingleton()
	{
		if (!_instance)
			_instance = new Morph();
		return _instance;
	}

	auto morphProcedural = MorphProcedural::GetSingleton();
	bool Morph::SetMorphInterface(IBodyMorphInterface* mi)
	{
		if (mi->GetVersion()) {
			bodyMorphInterface = mi;
		} else
			return false;
		return true;
	}

	void Morph::SetSkipEssential(bool skipEssential)
	{
		this->skipEssential = skipEssential;
	}
	bool Morph::GetSkipEssential()
	{
		return skipEssential;
	}
	void Morph::SetSkipUnique(bool skipUnique)
	{
		this->skipUnique = skipUnique;
	}
	bool Morph::GetSkipUnique()
	{
		return skipUnique;
	}

	float Morph::CalculateMusclepower(RE::Actor* myActor)
	{
		float oneHanded = myActor->GetActorValue(RE::ActorValue::kOneHanded);
		if (oneHanded < 15) {
			oneHanded = 15;
		}
		if (oneHanded > 30) {
			oneHanded = 30;
		}
		float smithing = myActor->GetActorValue(RE::ActorValue::kSmithing);
		if (smithing < 15) {
			smithing = 15;
		}
		if (smithing > 30) {
			smithing = 30;
		}
		float block = myActor->GetActorValue(RE::ActorValue::kBlock);
		if (block < 15) {
			block = 15;
		}
		if (block > 30) {
			block = 30;
		}
		float unarmedDamage = myActor->GetActorValue(RE::ActorValue::kUnarmedDamage);
		if (unarmedDamage < 15) {
			unarmedDamage = 15;
		}
		if (unarmedDamage > 30) {
			unarmedDamage = 30;
		}
		return (((oneHanded + smithing + block + unarmedDamage) - 60) /
				(120.0 - 60.0) * 1.8);
	}

	float Morph::CalculateFitness(RE::Actor* myActor)
	{
		float sneak = myActor->GetActorValue(RE::ActorValue::kSneak);
		if (sneak < 15) {
			sneak = 15;
		}
		if (sneak > 30) {
			sneak = 30;
		}
		float pickpocket = myActor->GetActorValue(RE::ActorValue::kPickpocket);
		if (pickpocket < 15) {
			pickpocket = 15;
		}
		if (pickpocket > 30) {
			pickpocket = 30;
		}
		float lockpicking = myActor->GetActorValue(RE::ActorValue::kLockpicking);
		if (lockpicking < 15) {
			lockpicking = 15;
		}
		if (lockpicking > 30) {
			lockpicking = 30;
		}
		float lightArmor = myActor->GetActorValue(RE::ActorValue::kLightArmor);
		if (lightArmor < 15) {
			lightArmor = 15;
		}
		if (lightArmor > 30) {
			lightArmor = 30;
		}
		return ((sneak + pickpocket + lockpicking + lightArmor) - 60) /
			   (120.0 - 60.0);
	}

	bool Morph::TriFemaleExists()
	{
		bool isTri = std::filesystem::exists(
			std::filesystem::current_path() /
			std::filesystem::path(
				"Data\\meshes\\actors\\character\\character assets\\femalebody.tri")
				.string()
				.c_str());
		if (isTri)
			_MESSAGE("femalebody.tri found");
		else {
			_MESSAGE("femalebody.tri NOT found");
		}
		return isTri;
	}

	bool Morph::TriMaleExists()
	{
		bool isTri = std::filesystem::exists(
			std::filesystem::current_path() /
			std::filesystem::path("Data\\meshes\\actors\\character\\character assets\\malebody.tri").string().c_str());
		if (isTri)
			_MESSAGE("Malebody.tri found");
		else {
			_MESSAGE("Malebody.tri NOT found");
		}
		return isTri;
	}

	SInt32 Morph::MorphMale()
	{
		return (Morph::MorphActors(Actors::GetSingleton()->GetMales(), false));
	}

	SInt32 Morph::MorphFemale()
	{
		return (Morph::MorphActors(Actors::GetSingleton()->GetFemales(), true));
	}

	SInt32 Morph::MorphActors(std::vector<RE::Actor*> Actors, bool female)
	{
		SInt32 actorsFound = 0;
		for (auto myActor : Actors) {
			//_MESSAGE("");
			//_MESSAGENNL("Begin Morphing ");
			if (this->GetSkipUnique()) {
				if (myActor->GetActorBase()->IsUnique()) {
					continue;
				}
			}
			if (this->GetSkipEssential()) {
				if (myActor->GetActorBase()->IsEssential()) {
					continue;
				}
			}
			if (female) {
				MorphActorCBBE(myActor);
				actorsFound++;
			} else {
				MorphActorSMMB(myActor);
				actorsFound++;
			}
			//_MESSAGENNL("End Morphing ");
		}
		return actorsFound;
	}

	void Morph::DeleteMorphs()
	{
		auto allForms = RE::TESForm::GetAllForms();
		auto& formIDs = *allForms.first;
		_MESSAGE("Delete Morphs called");
		for (auto elem : formIDs) {
			auto myActor = RE::TESForm::LookupByID<RE::Actor>(elem.first);
			if (myActor) {
				if (!myActor->IsChild()) {
					DeleteMorph(myActor);
				}
			}
		}
	}

	void Morph::DeleteMorph(RE::Actor* myActor)
	{
		TESObjectREFR* myREFR = (TESObjectREFR*)myActor;
		bodyMorphInterface->ClearBodyMorphKeys(myREFR, "RBS2020");
		bodyMorphInterface->ApplyBodyMorphs(myREFR, false);
		bodyMorphInterface->UpdateModelWeight(myREFR, true);
	}

	void Morph::SetMorphfactorFemale(StaticFunctionTag* base,
		float morphfactorFemale)
	{
		morphProcedural->SetMorphfactorFemale(morphfactorFemale);
	}

	void Morph::SetMorphfactorMale(StaticFunctionTag* base, float morphfactorMale)
	{
		morphProcedural->SetMorphfactorMale(morphfactorMale);
	}

	float Morph::GetMorphfactorMale(StaticFunctionTag* base)
	{
		return morphProcedural->GetMorphfactorMale();
	}

	float Morph::GetMorphfactorFemale(StaticFunctionTag* base)
	{
		return morphProcedural->GetMorphfactorFemale();
	}

	void Morph::SetMorphfactorBreasts(StaticFunctionTag* base,
		float morphfactorBreasts)
	{
		morphProcedural->SetMorphfactorBreasts(morphfactorBreasts);
	}

	float Morph::GetMorphfactorBreasts(StaticFunctionTag* base)
	{
		return morphProcedural->GetMorphfactorBreasts();
	}
	void Morph::PrintMorphs(RE::Actor* myActor)
	{
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
		// float PushUp", "",  morphProcedural->GetMorphValuePushUp");

		float BreastPerkiness = bodyMorphInterface->GetBodyMorphs(myREFR, "BreastPerkiness");
		float BreastWidth = bodyMorphInterface->GetBodyMorphs(myREFR, "BreastWidth");
		//_MESSAGE("Name: %i %s Musclepower:%f Samson:%f Fitness:%f Weight: %f",
		// myActor->GetFormType(), myActor->GetName(),
		// morphProcedural->GetMusclepower(),
		// morphProcedural->GetMorphValueSamSamson(), morphProcedural->GetFitness(),
		// morphProcedural->GetWeight());
	}

	void Morph::MorphActorSMMB(RE::Actor* myActor)
	{
		TESObjectREFR* myREFR = (TESObjectREFR*)myActor;
		//_MESSAGENNL("Got ObjectRefence,");
		morphProcedural->SetSeed(myActor->GetFormID());
		//_MESSAGENNL("Seed set,");
		morphProcedural->SetFitness(CalculateFitness(myActor));
		//_MESSAGENNL("Fitness set,");
		morphProcedural->SetMusclepower(CalculateMusclepower(myActor));
		//_MESSAGENNL("Musclepower set,");
		morphProcedural->SetMorphfactor(morphProcedural->GetMorphfactorMale());
		//_MESSAGENNL("Morphfactor set,");
		morphProcedural->SetWeight(myActor->GetActorBase()->GetWeight());
		//_MESSAGENNL("Weight set,");
		bodyMorphInterface->SetMorph(myREFR, "SAM Samuel", "RBS2020", morphProcedural->GetMorphValueSamSamuel());
		//_MESSAGENNL("Morph Samuel,");
		bodyMorphInterface->SetMorph(myREFR, "SAM Samson", "RBS2020", morphProcedural->GetMorphValueSamSamson());
		//_MESSAGENNL("Morph Samson,");
		bodyMorphInterface->ApplyBodyMorphs((TESObjectREFR*)myREFR, true);
		//_MESSAGENNL("Morphs applied,");
		// bodyMorphInterface->UpdateModelWeight((TESObjectREFR*)myREFR, true);
		//_MESSAGENNL("Modelweight updated,");
	}

	void Morph::MorphActorCBBE(RE::Actor* myActor)
	{
		TESObjectREFR* myREFR = (TESObjectREFR*)myActor;
		//_MESSAGE("Got ObjectRefence,");
		morphProcedural->SetSeed(myActor->GetFormID());
		//_MESSAGENNL("Seed set,");
		morphProcedural->SetMusclepower(CalculateMusclepower(myActor));
		//_MESSAGENNL("Musclepower set,");
		;
		morphProcedural->SetMorphfactor(morphProcedural->GetMorphfactorFemale());
		//_MESSAGENNL("Morphfactor set,");
		if (myActor->GetRace()) {
			//_MESSAGENNL("Got Race,");
			if (myActor->GetRace()->GetName()) {
				//_MESSAGENNL("Got Racename,");
				std::string raceName = myActor->GetRace()->GetName();
				size_t found = raceName.find("Old");

				if (found != std::string::npos) {
					//_MESSAGENNL("Old found,");
					morphProcedural->SetGravityOffset(
						morphProcedural->GetRandomFloat(0.5, 1));
					//_MESSAGENNL("Gravity set,");
				} else {
					//_MESSAGENNL("Old not found,");
					morphProcedural->SetGravityOffset(0);
					//_MESSAGENNL("Gravity set to 0,");
				}
			}
		}

		morphProcedural->SetWeight(myActor->GetActorBase()->GetWeight());
		//_MESSAGENNL("Got weight,");
		if (myActor->GetActorBase()) {
			//_MESSAGENNL("Got Actorbase,");
			if (myActor->GetActorBase()->GetWeight() == 0) {
				//_MESSAGENNL("Weight was 0,");
				morphProcedural->SetWeight(morphProcedural->GetRandomFloat(0, 20));
				//_MESSAGENNL("Changed Weight,");
			} else {
				morphProcedural->SetWeight(myActor->GetActorBase()->GetWeight());
				//_MESSAGENNL("Set Weight,");
			}
		} else {
			morphProcedural->SetWeight(morphProcedural->GetRandomFloat(0, 100));
			//_MESSAGENNL("Set Weight Random,");
		}
		//_MESSAGENNL("Begin Morphing Values,");
		bodyMorphInterface->SetMorph(myREFR, "ForearmSize", "RBS2020", morphProcedural->GetMorphValueForearmSize());
		bodyMorphInterface->SetMorph(myREFR, "ChubbyArms", "RBS2020", morphProcedural->GetMorphValueChubbyArms());
		bodyMorphInterface->SetMorph(myREFR, "ShoulderWidth", "RBS2020", morphProcedural->GetMorphValueShoulderWidth());
		bodyMorphInterface->SetMorph(myREFR, "Arms", "RBS2020", morphProcedural->GetMorphValueArms());
		bodyMorphInterface->SetMorph(myREFR, "ShoulderSmooth", "RBS2020", morphProcedural->GetMorphValueShoulderSmooth());
		bodyMorphInterface->SetMorph(myREFR, "ShoulderTweak", "RBS2020", morphProcedural->GetMorphValueShoulderTweak());

		bodyMorphInterface->SetMorph(myREFR, "Belly", "RBS2020", morphProcedural->GetMorphValueBelly());
		bodyMorphInterface->SetMorph(myREFR, "TummyTuck", "RBS2020", morphProcedural->GetMorphValueTummyTuck());
		bodyMorphInterface->SetMorph(myREFR, "BigBelly", "RBS2020", morphProcedural->GetMorphValueBigBelly());

		bodyMorphInterface->SetMorph(myREFR, "HipBone", "RBS2020", morphProcedural->GetMorphValueHipBone());
		bodyMorphInterface->SetMorph(myREFR, "Hips", "RBS2020", morphProcedural->GetMorphValueHips());
		bodyMorphInterface->SetMorph(myREFR, "HipForward", "RBS2020", morphProcedural->GetMorphValueHipForward());
		bodyMorphInterface->SetMorph(myREFR, "HipUpperWidth", "RBS2020", morphProcedural->GetMorphValueHipUpperWidth());

		bodyMorphInterface->SetMorph(myREFR, "NippleLength", "RBS2020", morphProcedural->GetMorphValueNippleLength());
		bodyMorphInterface->SetMorph(myREFR, "NipplePerkiness", "RBS2020", morphProcedural->GetMorphValueNipplePerkiness());
		bodyMorphInterface->SetMorph(myREFR, "NipplePerkManga", "RBS2020", morphProcedural->GetMorphValueNipplePerkManga());
		bodyMorphInterface->SetMorph(myREFR, "NippleTipManga", "RBS2020", morphProcedural->GetMorphValueNippleTipManga());
		bodyMorphInterface->SetMorph(myREFR, "NippleDistance", "RBS2020", morphProcedural->GetMorphValueNippleDistance());
		bodyMorphInterface->SetMorph(myREFR, "NippleSize", "RBS2020", morphProcedural->GetMorphValueNippleSize());
		bodyMorphInterface->SetMorph(myREFR, "AreolaSize", "RBS2020", morphProcedural->GetMorphValueAreolaSize());
		bodyMorphInterface->SetMorph(myREFR, "NippleDown", "RBS2020", morphProcedural->GetMorphValueNippleDown());

		bodyMorphInterface->SetMorph(myREFR, "MuscleAbs", "RBS2020", morphProcedural->GetMorphValueMuscleAbs());
		bodyMorphInterface->SetMorph(myREFR, "MuscleArms", "RBS2020", morphProcedural->GetMorphValueMuscleArms());
		bodyMorphInterface->SetMorph(myREFR, "MuscleButt", "RBS2020", morphProcedural->GetMorphValueMuscleButt());
		bodyMorphInterface->SetMorph(myREFR, "MuscleLegs", "RBS2020", morphProcedural->GetMorphValueMuscleLegs());
		bodyMorphInterface->SetMorph(myREFR, "MusclePecs", "RBS2020", morphProcedural->GetMorphValueMusclePecs());

		bodyMorphInterface->SetMorph(myREFR, "BigButt", "RBS2020", morphProcedural->GetMorphValueBigButt());
		bodyMorphInterface->SetMorph(myREFR, "ChubbyButt", "RBS2020", morphProcedural->GetMorphValueChubbyButt());
		bodyMorphInterface->SetMorph(myREFR, "Butt", "RBS2020", morphProcedural->GetMorphValueButt());

		bodyMorphInterface->SetMorph(myREFR, "ButtClassic", "RBS2020", morphProcedural->GetMorphValueButtClassic());
		bodyMorphInterface->SetMorph(myREFR, "ButtShape2", "RBS2020", morphProcedural->GetMorphValueButtShape2());
		bodyMorphInterface->SetMorph(myREFR, "ButtCrack", "RBS2020", morphProcedural->GetMorphValueButtCrack());
		bodyMorphInterface->SetMorph(myREFR, "AppleCheeks", "RBS2020", morphProcedural->GetMorphValueAppleCheeks());
		bodyMorphInterface->SetMorph(myREFR, "RoundAss", "RBS2020", morphProcedural->GetMorphValueRoundAss());
		bodyMorphInterface->SetMorph(myREFR, "CrotchBack", "RBS2020", morphProcedural->GetMorphValueCrotchBack());
		bodyMorphInterface->SetMorph(myREFR, "Groin", "RBS2020", morphProcedural->GetMorphValueGroin());

		bodyMorphInterface->SetMorph(myREFR, "ChubbyLegs", "RBS2020", morphProcedural->GetMorphValueChubbyLegs());
		bodyMorphInterface->SetMorph(myREFR, "Legs", "RBS2020", morphProcedural->GetMorphValueLegs());
		bodyMorphInterface->SetMorph(myREFR, "Thighs", "RBS2020", morphProcedural->GetMorphValueThighs());

		bodyMorphInterface->SetMorph(myREFR, "KneeShape", "RBS2020", morphProcedural->GetMorphValueKneeShape());
		bodyMorphInterface->SetMorph(myREFR, "KneeHeight", "RBS2020", morphProcedural->GetMorphValueKneeHeight());
		bodyMorphInterface->SetMorph(myREFR, "CalfSize", "RBS2020", morphProcedural->GetMorphValueCalfSize());
		bodyMorphInterface->SetMorph(myREFR, "CalfSmooth", "RBS2020", morphProcedural->GetMorphValueCalfSmooth());
		bodyMorphInterface->SetMorph(myREFR, "LegShapeClassic", "RBS2020", morphProcedural->GetMorphValueLegShapeClassic());

		bodyMorphInterface->SetMorph(myREFR, "BigTorso", "RBS2020", morphProcedural->GetMorphValueBigTorso());
		bodyMorphInterface->SetMorph(myREFR, "ChestDepth", "RBS2020", morphProcedural->GetMorphValueChestDepth());
		bodyMorphInterface->SetMorph(myREFR, "ChestWidth", "RBS2020", morphProcedural->GetMorphValueChestWidth());
		bodyMorphInterface->SetMorph(myREFR, "ChubbyWaist", "RBS2020", morphProcedural->GetMorphValueChubbyWaist());
		bodyMorphInterface->SetMorph(myREFR, "Waist", "RBS2020", morphProcedural->GetMorphValueWaist());
		bodyMorphInterface->SetMorph(myREFR, "SternumDepth", "RBS2020", morphProcedural->GetMorphValueSternumDepth());
		bodyMorphInterface->SetMorph(myREFR, "SternumHeight", "RBS2020", morphProcedural->GetMorphValueSternumHeight());
		bodyMorphInterface->SetMorph(myREFR, "WaistHeight", "RBS2020", morphProcedural->GetMorphValueWaistHeight());
		bodyMorphInterface->SetMorph(myREFR, "WaistLine", "RBS2020", morphProcedural->GetMorphValueWaistLine());

		bodyMorphInterface->SetMorph(myREFR, "Breasts", "RBS2020", morphProcedural->GetMorphValueBreasts());
		bodyMorphInterface->SetMorph(myREFR, "BreastsNewSH", "RBS2020", morphProcedural->GetMorphValueBreastsNewSH());
		bodyMorphInterface->SetMorph(myREFR, "BreastCleavage", "RBS2020", morphProcedural->GetMorphValueBreastCleavage());
		bodyMorphInterface->SetMorph(myREFR, "BreastsFantasy", "RBS2020", morphProcedural->GetMorphValueBreastsFantasy());
		bodyMorphInterface->SetMorph(myREFR, "BreastCenter", "RBS2020", morphProcedural->GetMorphValueBreastCenter());
		bodyMorphInterface->SetMorph(myREFR, "BreastCenterBig", "RBS2020", morphProcedural->GetMorphValueBreastCenterBig());
		bodyMorphInterface->SetMorph(myREFR, "BreastFlatness2", "RBS2020", morphProcedural->GetMorphValueBreastFlatness2());
		bodyMorphInterface->SetMorph(myREFR, "BreastFlatness", "RBS2020", morphProcedural->GetMorphValueBreastFlatness());
		bodyMorphInterface->SetMorph(myREFR, "BreastGravity2", "RBS2020", morphProcedural->GetMorphValueBreastGravity2());
		bodyMorphInterface->SetMorph(myREFR, "BreastHeight", "RBS2020", morphProcedural->GetMorphValueBreastHeight());
		bodyMorphInterface->SetMorph(myREFR, "BreastsTogether", "RBS2020", morphProcedural->GetMorphValueBreastsTogether());
		bodyMorphInterface->SetMorph(myREFR, "BreastTopSlope", "RBS2020", morphProcedural->GetMorphValueBreastTopSlope());
		// bodyMorphInterface->SetMorph(myREFR, "PushUp", "",
		// morphProcedural->GetMorphValuePushUp());
		bodyMorphInterface->SetMorph(myREFR, "BreastPerkiness", "RBS2020", morphProcedural->GetMorphValueBreastPerkiness());
		bodyMorphInterface->SetMorph(myREFR, "BreastWidth", "RBS2020", morphProcedural->GetMorphValueBreastWidth());
		//_MESSAGENNL("End Morphing Values,");
		bodyMorphInterface->ApplyBodyMorphs((TESObjectREFR*)myREFR, true);
		//_MESSAGENNL("Bodymorphs applied,");
		// bodyMorphInterface->UpdateModelWeight((TESObjectREFR*)myREFR, true);
		//_MESSAGENNL("Modelweight updated,");
		//_MESSAGE("Actors %s %f, %f ,%f", myActor->GetName(),
		// morphProcedural->GetMorphValueBreasts(),
		// morphProcedural->GetMorphValueBigTorso(),
		// morphProcedural->GetMorphValueForearmSize());
	}

	void Morph::MorphActorBHUNP(RE::Actor* myActor)
	{
		TESObjectREFR* myREFR = (TESObjectREFR*)myActor;
		//_MESSAGENNL("Got ObjectRefence,");
		morphProcedural->SetSeed(myActor->GetFormID());
		//_MESSAGENNL("Seed set,");
		morphProcedural->SetMusclepower(CalculateMusclepower(myActor));
		//_MESSAGENNL("Musclepower set,");;
		morphProcedural->SetMorphfactor(morphProcedural->GetMorphfactorFemale());
		//_MESSAGENNL("Morphfactor set,");
		if (myActor->GetRace()) {
			//_MESSAGENNL("Got Race,");
			if (myActor->GetRace()->GetName()) {
				//_MESSAGENNL("Got Racename,");
				std::string raceName = myActor->GetRace()->GetName();

				size_t found = raceName.find("Old");

				if (found != std::string::npos) {
					//_MESSAGENNL("Old found,");
					morphProcedural->SetGravityOffset(
						morphProcedural->GetRandomFloat(0.5, 1));
					//_MESSAGENNL("Gravity set,");
				} else {
					//_MESSAGENNL("Old not found,");
					morphProcedural->SetGravityOffset(0);
					//_MESSAGENNL("Gravity set to 0,");
				}
			}
		}

		morphProcedural->SetWeight(myActor->GetActorBase()->GetWeight());
		//_MESSAGENNL("Got weight,");
		if (myActor->GetActorBase()) {
			//_MESSAGENNL("Got Actorbase,");
			if (myActor->GetActorBase()->GetWeight() == 0) {
				//_MESSAGENNL("Weight was 0,");
				morphProcedural->SetWeight(morphProcedural->GetRandomFloat(0, 20));
				//_MESSAGENNL("Changed Weight,");
			} else {
				morphProcedural->SetWeight(myActor->GetActorBase()->GetWeight());
				//_MESSAGENNL("Set Weight,");
			}
		} else {
			morphProcedural->SetWeight(morphProcedural->GetRandomFloat(0, 100));
			//_MESSAGENNL("Set Weight Random,");
		}
		//_MESSAGENNL("Begin Morphing Values,");
		bodyMorphInterface->SetMorph(myREFR, "ForearmSize", "RBS2020", morphProcedural->GetMorphValueForearmSize());
		bodyMorphInterface->SetMorph(myREFR, "ChubbyArms", "RBS2020", morphProcedural->GetMorphValueChubbyArms());
		bodyMorphInterface->SetMorph(myREFR, "ShoulderWidth", "RBS2020", morphProcedural->GetMorphValueShoulderWidth());
		bodyMorphInterface->SetMorph(myREFR, "Arms", "RBS2020", morphProcedural->GetMorphValueArms());
		bodyMorphInterface->SetMorph(myREFR, "ShoulderSmooth", "RBS2020", morphProcedural->GetMorphValueShoulderSmooth());
		bodyMorphInterface->SetMorph(myREFR, "ShoulderTweak", "RBS2020", morphProcedural->GetMorphValueShoulderTweak());

		bodyMorphInterface->SetMorph(myREFR, "Belly", "RBS2020", morphProcedural->GetMorphValueBelly());
		bodyMorphInterface->SetMorph(myREFR, "TummyTuck", "RBS2020", morphProcedural->GetMorphValueTummyTuck());
		bodyMorphInterface->SetMorph(myREFR, "BigBelly", "RBS2020", morphProcedural->GetMorphValueBigBelly());

		bodyMorphInterface->SetMorph(myREFR, "HipBone", "RBS2020", morphProcedural->GetMorphValueHipBone());
		bodyMorphInterface->SetMorph(myREFR, "Hips", "RBS2020", morphProcedural->GetMorphValueHips());
		bodyMorphInterface->SetMorph(myREFR, "HipForward", "RBS2020", morphProcedural->GetMorphValueHipForward());
		bodyMorphInterface->SetMorph(myREFR, "HipUpperWidth", "RBS2020", morphProcedural->GetMorphValueHipUpperWidth());

		bodyMorphInterface->SetMorph(myREFR, "NippleLength", "RBS2020", morphProcedural->GetMorphValueNippleLength());
		bodyMorphInterface->SetMorph(myREFR, "NipplePerkiness", "RBS2020", morphProcedural->GetMorphValueNipplePerkiness());
		bodyMorphInterface->SetMorph(myREFR, "NipplePerkManga", "RBS2020", morphProcedural->GetMorphValueNipplePerkManga());
		bodyMorphInterface->SetMorph(myREFR, "NippleTipManga", "RBS2020", morphProcedural->GetMorphValueNippleTipManga());
		bodyMorphInterface->SetMorph(myREFR, "NippleDistance", "RBS2020", morphProcedural->GetMorphValueNippleDistance());
		bodyMorphInterface->SetMorph(myREFR, "NippleSize", "RBS2020", morphProcedural->GetMorphValueNippleSize());
		bodyMorphInterface->SetMorph(myREFR, "AreolaSize", "RBS2020", morphProcedural->GetMorphValueAreolaSize());
		bodyMorphInterface->SetMorph(myREFR, "NippleDown", "RBS2020", morphProcedural->GetMorphValueNippleDown());

		bodyMorphInterface->SetMorph(myREFR, "MuscleAbs", "RBS2020", morphProcedural->GetMorphValueMuscleAbs());
		bodyMorphInterface->SetMorph(myREFR, "MuscleArms", "RBS2020", morphProcedural->GetMorphValueMuscleArms());
		bodyMorphInterface->SetMorph(myREFR, "MuscleButt", "RBS2020", morphProcedural->GetMorphValueMuscleButt());
		bodyMorphInterface->SetMorph(myREFR, "MuscleLegs", "RBS2020", morphProcedural->GetMorphValueMuscleLegs());
		bodyMorphInterface->SetMorph(myREFR, "MusclePecs", "RBS2020", morphProcedural->GetMorphValueMusclePecs());

		bodyMorphInterface->SetMorph(myREFR, "BigButt", "RBS2020", morphProcedural->GetMorphValueBigButt());
		bodyMorphInterface->SetMorph(myREFR, "ChubbyButt", "RBS2020", morphProcedural->GetMorphValueChubbyButt());
		bodyMorphInterface->SetMorph(myREFR, "Butt", "RBS2020", morphProcedural->GetMorphValueButt());

		bodyMorphInterface->SetMorph(myREFR, "ButtClassic", "RBS2020", morphProcedural->GetMorphValueButtClassic());
		bodyMorphInterface->SetMorph(myREFR, "ButtShape2", "RBS2020", morphProcedural->GetMorphValueButtShape2());
		bodyMorphInterface->SetMorph(myREFR, "ButtCrack", "RBS2020", morphProcedural->GetMorphValueButtCrack());
		bodyMorphInterface->SetMorph(myREFR, "AppleCheeks", "RBS2020", morphProcedural->GetMorphValueAppleCheeks());
		bodyMorphInterface->SetMorph(myREFR, "RoundAss", "RBS2020", morphProcedural->GetMorphValueRoundAss());
		bodyMorphInterface->SetMorph(myREFR, "CrotchBack", "RBS2020", morphProcedural->GetMorphValueCrotchBack());
		bodyMorphInterface->SetMorph(myREFR, "Groin", "RBS2020", morphProcedural->GetMorphValueGroin());

		bodyMorphInterface->SetMorph(myREFR, "ChubbyLegs", "RBS2020", morphProcedural->GetMorphValueChubbyLegs());
		bodyMorphInterface->SetMorph(myREFR, "Legs", "RBS2020", morphProcedural->GetMorphValueLegs());
		bodyMorphInterface->SetMorph(myREFR, "Thighs", "RBS2020", morphProcedural->GetMorphValueThighs());

		bodyMorphInterface->SetMorph(myREFR, "KneeShape", "RBS2020", morphProcedural->GetMorphValueKneeShape());
		bodyMorphInterface->SetMorph(myREFR, "KneeHeight", "RBS2020", morphProcedural->GetMorphValueKneeHeight());
		bodyMorphInterface->SetMorph(myREFR, "CalfSize", "RBS2020", morphProcedural->GetMorphValueCalfSize());
		bodyMorphInterface->SetMorph(myREFR, "CalfSmooth", "RBS2020", morphProcedural->GetMorphValueCalfSmooth());
		bodyMorphInterface->SetMorph(myREFR, "LegShapeClassic", "RBS2020", morphProcedural->GetMorphValueLegShapeClassic());

		bodyMorphInterface->SetMorph(myREFR, "BigTorso", "RBS2020", morphProcedural->GetMorphValueBigTorso());
		bodyMorphInterface->SetMorph(myREFR, "ChestDepth", "RBS2020", morphProcedural->GetMorphValueChestDepth());
		bodyMorphInterface->SetMorph(myREFR, "ChestWidth", "RBS2020", morphProcedural->GetMorphValueChestWidth());
		bodyMorphInterface->SetMorph(myREFR, "ChubbyWaist", "RBS2020", morphProcedural->GetMorphValueChubbyWaist());
		bodyMorphInterface->SetMorph(myREFR, "Waist", "RBS2020", morphProcedural->GetMorphValueWaist());
		bodyMorphInterface->SetMorph(myREFR, "SternumDepth", "RBS2020", morphProcedural->GetMorphValueSternumDepth());
		bodyMorphInterface->SetMorph(myREFR, "SternumHeight", "RBS2020", morphProcedural->GetMorphValueSternumHeight());
		bodyMorphInterface->SetMorph(myREFR, "WaistHeight", "RBS2020", morphProcedural->GetMorphValueWaistHeight());
		bodyMorphInterface->SetMorph(myREFR, "WaistLine", "RBS2020", morphProcedural->GetMorphValueWaistLine());

		bodyMorphInterface->SetMorph(myREFR, "Breasts", "RBS2020", morphProcedural->GetMorphValueBreasts() * -1);
		bodyMorphInterface->SetMorph(myREFR, "BreastsNewSH", "RBS2020", morphProcedural->GetMorphValueBreastsNewSH());
		bodyMorphInterface->SetMorph(myREFR, "BreastCleavage", "RBS2020", morphProcedural->GetMorphValueBreastCleavage());
		bodyMorphInterface->SetMorph(myREFR, "BreastsFantasy", "RBS2020", morphProcedural->GetMorphValueBreastsFantasy());
		bodyMorphInterface->SetMorph(myREFR, "BreastCenter", "RBS2020", morphProcedural->GetMorphValueBreastCenter());
		bodyMorphInterface->SetMorph(myREFR, "BreastCenterBig", "RBS2020", morphProcedural->GetMorphValueBreastCenterBig());
		bodyMorphInterface->SetMorph(myREFR, "BreastFlatness2", "RBS2020", morphProcedural->GetMorphValueBreastFlatness2());
		bodyMorphInterface->SetMorph(myREFR, "BreastFlatness", "RBS2020", morphProcedural->GetMorphValueBreastFlatness());
		bodyMorphInterface->SetMorph(myREFR, "BreastGravity2", "RBS2020", morphProcedural->GetMorphValueBreastGravity2());
		bodyMorphInterface->SetMorph(myREFR, "BreastHeight", "RBS2020", morphProcedural->GetMorphValueBreastHeight());
		bodyMorphInterface->SetMorph(myREFR, "BreastsTogether", "RBS2020", morphProcedural->GetMorphValueBreastsTogether());
		bodyMorphInterface->SetMorph(myREFR, "BreastTopSlope", "RBS2020", morphProcedural->GetMorphValueBreastTopSlope());
		// bodyMorphInterface->SetMorph(myREFR, "PushUp", "", morphProcedural->GetMorphValuePushUp());
		bodyMorphInterface->SetMorph(myREFR, "BreastPerkiness", "RBS2020", morphProcedural->GetMorphValueBreastPerkiness());
		bodyMorphInterface->SetMorph(myREFR, "BreastWidth", "RBS2020", morphProcedural->GetMorphValueBreastWidth());
		//_MESSAGENNL("End Morphing Values,");
		bodyMorphInterface->ApplyBodyMorphs((TESObjectREFR*)myREFR, true);
		//_MESSAGENNL("Bodymorphs applied,");
		// bodyMorphInterface->UpdateModelWeight((TESObjectREFR*)myREFR, true);
		//_MESSAGENNL("Modelweight updated,");
		//_MESSAGE("Actors %s %f, %f ,%f", myActor->GetName(),
		// morphProcedural->GetMorphValueBreasts(),
		// morphProcedural->GetMorphValueBigTorso(),
		// morphProcedural->GetMorphValueForearmSize());
	}
}  // namespace RBS2020
