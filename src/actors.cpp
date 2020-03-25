#include "actors.h"
#include "re/skyrim.h"

namespace RBS2020 {

	void Actors::PrefilterActors() {
		_MESSAGE("Prefiltering Actors Start");

		bool isCreature;
		ActorsMale.clear();
		ActorsFemale.clear();
		_MESSAGE("Vectors cleared");
		auto allForms = RE::TESForm::GetAllForms();
		_MESSAGE("Got all Forms");
		auto& formIDs = *allForms.first;
		for (auto elem : formIDs) {
			if ((int)elem.second->GetFormType() == 62) {
				//_MESSAGENNL("\n1,");
				RE::Actor* myActor = RE::TESForm::LookupByID<RE::Actor>(elem.first);
				if (myActor) {
					//_MESSAGENNL("2,");
					if (myActor->GetRace()) {
						//_MESSAGENNL("3,");
						if (myActor->GetActorBase()) {
							//_MESSAGENNL("4,");
							//	if (myActor->GetActorBase()->defaultOutfit) {
							if (myActor->GetActorBase()->factions.size() > 0) {
								//_MESSAGENNL("5,");
								if (myActor->GetActorBase()->factions.begin()) {
									//_MESSAGENNL("6,");
									if (myActor->GetActorBase()->factions.begin()->faction) {
										//_MESSAGENNL("7,");
										isCreature = false;
										//_MESSAGENNL("8,");
										for (auto faction : myActor->GetActorBase()->factions) {
											if (faction.faction->GetFormID() == 19) {
												//_MESSAGENNL("9a,");
												isCreature = true;
											}
											else {
												//_MESSAGENNL("9b,");
											}
										}
										if (!isCreature) {
											//_MESSAGENNL("10,");
											if (myActor->GetActorBase()->voiceType) {
												//_MESSAGENNL("11,");
												auto vt =
													myActor->GetActorBase()->voiceType->GetFormEditorID();
												//_MESSAGENNL("12,");
												std::string voicename = vt;
												int counter_voices = 0;
												if (voicename.find("Female") != std::string::npos) {
													counter_voices++;
													//_MESSAGENNL("13a,");
												}
												if (voicename.find("Male") != std::string::npos) {
													//_MESSAGENNL("13b,");
													counter_voices++;
												}
												if (counter_voices > 0) {
													//_MESSAGENNL("14,");
													if (!myActor->IsChild()) {
														//_MESSAGENNL("15,");
														if (myActor->GetActorBase()->IsFemale()) {
															//_MESSAGENNL("16aa,");
															if (Morph::GetSkipUnique()) {
																//_MESSAGENNL("17aa,");
																if (!myActor->GetActorBase()->IsUnique()) {
																	//_MESSAGENNL("added");
																	ActorsFemale.push_back(
																		RE::TESForm::LookupByID<RE::Actor>(
																			elem.first));
																}
															}
															else {
																//_MESSAGENNL("added");
																ActorsFemale.push_back(
																	RE::TESForm::LookupByID<RE::Actor>(
																		elem.first));
															}
														}
														else {
															//_MESSAGENNL("16ba,");
															if (Morph::GetSkipUnique()) {
																if (!myActor->GetActorBase()->IsUnique()) {
																	//_MESSAGENNL("added");
																	ActorsMale.push_back(
																		RE::TESForm::LookupByID<RE::Actor>(
																			elem.first));
																}
															}
															else {
																//_MESSAGENNL("added");
																ActorsMale.push_back(
																	RE::TESForm::LookupByID<RE::Actor>(
																		elem.first));
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
		}
		prefiltered = true;
		_MESSAGE("Prefiltering End");
	}
	bool Actors::IsPrefiltered() { return prefiltered; }

	std::vector<RE::Actor*> Actors::GetFemales() { return ActorsFemale; }
	std::vector<RE::Actor*> Actors::GetMales() { return ActorsMale; }
} // namespace RBS2020
