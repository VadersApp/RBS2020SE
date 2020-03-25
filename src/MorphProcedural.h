#pragma once


namespace RBS2020 {

	class MorphProcedural
	{
	private:

		static inline SInt32 formID = 0;
		static inline float weight = 0;
		static inline float musclepower = 0;
		static inline float morphfactor = 100;
		static inline float morphfactorFemale = 100;
		static inline float morphfactorMale = 100;
		static inline float morphfactorBreasts = 100;
		static inline float musclePower = 0;
		static inline float fitness = 0;
		static inline float gravityOffset = 0;
		static inline SInt32 seedOffset = 0;

	public:
		static 	void SetFormID(SInt32 formID);

		static 	float GetWeight();
		static 	void SetWeight(float fweight);

		static 	float GetMusclepower();
		static 	void SetMusclepower(float musclepower);

		static 	float GetFitness();
		static 	void SetFitness(float musclepower);

		static 	void SetGravityOffset(float gravityOffset);
		static 	float GetGravityOffset();

		static void SetSeed(SInt32 seed);
		static void SetSeedOffset(SInt32 mySeedOffset);
		static SInt32 GetSeedOffset();

		static void SetMorphfactor(float fmorphfactorMale);

		static float GetMorphfactorFemale();
		static float GetMorphfactorMale();

		static void SetMorphfactorMale(float fmorphfactorMale);
		static void SetMorphfactorFemale(float fmorphfactorFeMale);

		static float GetMorphfactorBreasts();
		static void SetMorphfactorBreasts(float fmorphfactorBreasts);

		static float GetRandomFloat(float min, float max);
		static 	float GetRandomFloatNormalByWeight(float min, float max);
		static 	float GetRandomFloatNormalByMusclePower(float min, float max);

		static float GetMorphValueSamSamuel();
		static 	float GetMorphValueSamSamson();
		static float GetMorphValueForearmSize();
		static float GetMorphValueChubbyArms();
		static float GetMorphValueShoulderWidth();
		static 	float GetMorphValueArms();
		static 	float GetMorphValueShoulderSmooth();
		static 	float GetMorphValueShoulderTweak();

		static 	float GetMorphValueBelly();
		static 	float GetMorphValueTummyTuck();
		static 	float GetMorphValueBigBelly();
		static float GetMorphValueHipBone();
		static float GetMorphValueHips();
		static float GetMorphValueHipForward();
		static 	float GetMorphValueHipUpperWidth();

		static 	float GetMorphValueNippleLength();
		static 	float GetMorphValueNipplePerkiness();
		static 	float GetMorphValueNipplePerkManga();
		static 	float GetMorphValueNippleTipManga();
		static 	float GetMorphValueNippleDistance();
		static 	float GetMorphValueNippleSize();
		static 	float GetMorphValueAreolaSize();
		static 	float GetMorphValueNippleDown();

		static 	float GetMorphValueMuscleAbs();
		static 	float GetMorphValueMuscleArms();
		static 	float GetMorphValueMuscleButt();
		static 	float GetMorphValueMuscleLegs();
		static 	float GetMorphValueMusclePecs();

		static 	float GetMorphValueBigButt();
		static 	float GetMorphValueChubbyButt();
		static 	float GetMorphValueButt();
		static 	float GetMorphValueButtClassic();
		static 	float GetMorphValueButtShape2();
		static 	float GetMorphValueButtCrack();
		static 	float GetMorphValueAppleCheeks();
		static 	float GetMorphValueRoundAss();
		static 	float GetMorphValueCrotchBack();
		static 	float GetMorphValueGroin();

		static 	float GetMorphValueChubbyLegs();
		static 	float GetMorphValueLegs();
		static 	float GetMorphValueThighs();
		static 	float GetMorphValueKneeShape();
		static 	float GetMorphValueKneeHeight();
		static 	float GetMorphValueCalfSize();
		static 		float GetMorphValueCalfSmooth();
		static 	float GetMorphValueLegShapeClassic();

		static 	float GetMorphValueBigTorso();
		static 	float GetMorphValueChestDepth();
		static 	float GetMorphValueChestWidth();
		static 	float GetMorphValueChubbyWaist();
		static 	float GetMorphValueWaist();
		static 	float GetMorphValueSternumDepth();
		static 	float GetMorphValueSternumHeight();
		static 	float GetMorphValueWaistHeight();
		static 	float GetMorphValueWaistLine();

		static 	float GetMorphValueBreasts();
		static 	float GetMorphValueBreastsNewSH();
		static 		float GetMorphValueBreastsFantasy();
		static 	float GetMorphValueBreastCenter();
		static 	float GetMorphValueBreastCenterBig();
		static 	float GetMorphValueBreastCleavage();
		static 		float GetMorphValueBreastFlatness2();
		static 	float GetMorphValueBreastFlatness();
		static 	float GetMorphValueBreastGravity2();
		static 	float GetMorphValueBreastHeight();
		static 	float GetMorphValueBreastsTogether();
		static 	float GetMorphValueBreastTopSlope();
		static 	float GetMorphValuePushUp();
		static 	float GetMorphValueBreastPerkiness();
		static 	float GetMorphValueBreastWidth();
	};
}

