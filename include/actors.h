#pragma once

#include "morph.h"
namespace RBS2020
{
	class Actors
	{
	public:
		static Actors* GetSingleton();
		
		SInt32 PrefilterActors();
		RE::FormID GetRandomFemaleFormID();
		bool IsPrefiltered();
		std::vector<RE::Actor*> GetFemales();
		std::vector<RE::Actor*> GetMales();

	private:
		 static Actors* _instance;
		Actors();
		Actors(const Actors&); 
		~Actors() {}


		std::vector<RE::Actor*> ActorsFemale;
		std::vector<RE::Actor*> ActorsMale;
		bool prefiltered = false;

		
	};
}  // namespace RBS2020
