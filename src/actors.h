#include "morph.h"
namespace RBS2020 {

	class Actors {
	private:
		static inline std::vector<RE::Actor*> ActorsFemale;
		static inline std::vector<RE::Actor*> ActorsMale;
		static inline bool prefiltered = false;

	public:
		static void PrefilterActors();
		static bool IsPrefiltered();
		static std::vector<RE::Actor*> GetFemales();
		static std::vector<RE::Actor*> GetMales();
	};
} // namespace RBS2020
