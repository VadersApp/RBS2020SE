#include "headparts.h"
#include "actors.h"
#include "re/IFormFactory.h"
#include "re/skyrim.h"
#include "skse64/GameReferences.h"
#include "skse64/PapyrusActor.h"
#include "skse64/PapyrusActorBase.h"
namespace RBS2020
{
	static std::vector<RE::BGSHeadPart*> v_hairs;
	static std::vector<BGSHeadPart*> v_hairs_skse;
	
	
	void Headparts::GetAllHairs()
	{
		auto allForms = RE::TESForm::GetAllForms();
		_MESSAGE("Got all Forms");
		auto& formIDs = *allForms.first;
		for (auto elem : formIDs) {
			if (elem.second->GetFormType() == RE::FormType::HeadPart) {
				//_MESSAGENNL("\n1,");
				RE::BGSHeadPart* headpart = RE::TESForm::LookupByID<RE::BGSHeadPart>(elem.first);
				if (headpart->type == RE::BGSHeadPart::HeadPartType::kHair) {
					v_hairs.push_back(headpart);
					v_hairs_skse.push_back((BGSHeadPart*)headpart);
				}
			}
		}
		_MESSAGE("Found Hairs %i", v_hairs.size());
	}

	void Headparts::ChangeColor()
	{
		auto haircolor = (RE::BGSColorForm*)IFormFactory::GetFactoryForType((UInt32)RE::FormType::ColorForm)->Create();
		_MESSAGE("haircolor generated");
		haircolor->color.alpha = 250;
		haircolor->color.blue = 0;
		haircolor->color.red = 20;
		haircolor->color.green = 0;
		_MESSAGE("color set to black");
		for (auto actor : Actors::GetSingleton()->GetFemales()) {
			actor->GetActorBase()->SetHairColor(haircolor);
			actor->UpdateHairColor();
		}
	}

	void Headparts::ChangeHair()
	{
		GetAllHairs();
		ChangeColor();
		// howto make new forms
		//auto NewCharacter = (RE::TESObjectARMA*)IFormFactory::GetFactoryForType((UInt32)RE::FormType::ActorCharacter)->Create();
		for (auto actor : Actors::GetSingleton()->GetFemales()) {
			Actor* test = (Actor*)actor;
			TESNPC* npc = (TESNPC*)actor->GetActorBase();

			//auto hair = actor->GetActorBase()->GetCurrentHeadPartByType(RE::BGSHeadPart::HeadPartType::kHair);
			for (int i = 0; i < papyrusActorBase::GetNumHeadParts(npc); i++) {
				auto headpart = papyrusActorBase::GetNthHeadPart(npc, i);
				if (headpart->type == BGSHeadPart::kTypeHair) {
					_MESSAGE("hair found");
					papyrusActorBase::SetNthHeadPart(npc, v_hairs_skse[0], i);
					UInt16 weight = papyrusActorBase::GetWeight(npc);
					papyrusActorBase::SetWeight(npc, 35);
					papyrusActor::QueueNiNodeUpdate(test);
				}
			}

			//RE::BGSHeadPart::Flag::kFemale
			/*
			if (hair) {
				hair->SetAltered(true);

				hair->SetFormID(hair->GetFormID() + 1, true);
				actor->GetActorBase()->ChangeHeadPart(hair); //vector of RE::BGSHeadPart* headpart (hairs)
				actor->GetActorBase()->AddChange((UInt32)RE::FormType::HeadPart);

				//auto test = actor->GetActorBase();
				//for (auto headpart : test);
				_MESSAGE("changeHeadPart");
				//_MESSAGE("UpdateModel");
			}
			*/
		}
	}
}
