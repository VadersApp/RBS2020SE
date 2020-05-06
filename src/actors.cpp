#include "actors.h"
#include "random"
#include "re/skyrim.h"
namespace RBS2020
{
	Actors::Actors()
	{
		this->prefiltered = false;
	}

	Actors* Actors::_instance = 0;
	Actors* Actors::GetSingleton()
	{
		if (!_instance)
			_instance = new Actors();
		return _instance;
	}
	auto Morph = Morph::GetSingleton();
	SInt32 Actors::PrefilterActors()
	{
		_MESSAGE("Prefiltering Actors Start");
		int counter = 0;
		auto player = RE::PlayerCharacter::GetSingleton();
		bool isCreature;
		ActorsMale.clear();
		ActorsFemale.clear();
		_MESSAGE("Vectors cleared");
		auto allForms = RE::TESForm::GetAllForms();
		_MESSAGE("Got all Forms");
		auto& formIDs = *allForms.first;
		for (auto elem : formIDs) {
			if ((int)elem.second->GetFormType() == 62) {
				RE::Actor* myActor = RE::TESForm::LookupByID<RE::Actor>(elem.first);
				if (myActor) {
					if (myActor->GetRace()) {
						if (myActor->GetActorBase()) {
							//	if (myActor->GetActorBase()->defaultOutfit) {
							if (myActor->GetActorBase()->factions.size() > 0) {
								if (myActor->GetActorBase()->factions.begin()) {
									if (myActor->GetActorBase()->factions.begin()->faction) {
										isCreature = false;
										for (auto faction : myActor->GetActorBase()->factions) {
											if (faction.faction->GetFormID() == 19) {
												isCreature = true;
											} else {
											}
										}
										if (!isCreature) {
											if (myActor->GetActorBase()->voiceType) {
												auto vt = myActor->GetActorBase()->voiceType->GetFormEditorID();
												std::string voicename = vt;
												int counter_voices = 0;
												if (voicename.find("Female") != std::string::npos) {
													counter_voices++;
												}
												if (voicename.find("Male") != std::string::npos) {
													counter_voices++;
												}
												if (counter_voices > 0) {
													if (!myActor->IsChild()) {
														if (myActor == player) {
															continue;
														}
														counter++;
														if (myActor->GetActorBase()->IsFemale()) {
															ActorsFemale.push_back(RE::TESForm::LookupByID<RE::Actor>(elem.first));

														} else {
															ActorsMale.push_back(RE::TESForm::LookupByID<RE::Actor>(elem.first));
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		prefiltered = true;
		_MESSAGE("Prefiltering End");
		return counter;
	}
	bool Actors::IsPrefiltered() { return prefiltered; }

	std::vector<RE::Actor*> Actors::GetFemales() { return ActorsFemale; }
	std::vector<RE::Actor*> Actors::GetMales() { return ActorsMale; }

	RE::FormID Actors::GetRandomFemaleFormID()
	{
		auto females = GetFemales();
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> d(0, females.size());
		int pos = d(gen);
		auto formid = females[pos]->GetFormID();
		females.erase(females.begin() + pos);
		return formid;
	}

}  // namespace RBS2020
