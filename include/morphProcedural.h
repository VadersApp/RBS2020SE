#pragma once

namespace RBS2020
{
	class MorphProcedural
	{
	public:
		static MorphProcedural* GetSingleton();

		void SetFormID(SInt32 formID);

		float GetWeight();
		void SetWeight(float fweight);

		float GetMusclepower();
		void SetMusclepower(float musclepower);

		float GetFitness();
		void SetFitness(float musclepower);

		void SetGravityOffset(float gravityOffset);
		float GetGravityOffset();

		void SetSeed(SInt32 seed);
		void SetSeedOffset(SInt32 mySeedOffset);
		SInt32 GetSeedOffset();

		void SetMorphfactor(float fmorphfactorMale);

		float GetMorphfactorFemale();
		float GetMorphfactorMale();

		void SetMorphfactorMale(float fmorphfactorMale);
		void SetMorphfactorFemale(float fmorphfactorFeMale);

		float GetMorphfactorBreasts();
		void SetMorphfactorBreasts(float fmorphfactorBreasts);

		float GetRandomFloat(float min, float max);
		float GetRandomFloatNormalByWeight(float min, float max);
		float GetRandomFloatNormalByMusclePower(float min, float max);

		float GetMorphValueSamSamuel();
		float GetMorphValueSamSamson();
		float GetMorphValueForearmSize();
		float GetMorphValueChubbyArms();
		float GetMorphValueShoulderWidth();
		float GetMorphValueArms();
		float GetMorphValueShoulderSmooth();
		float GetMorphValueShoulderTweak();

		float GetMorphValueBelly();
		float GetMorphValueTummyTuck();
		float GetMorphValueBigBelly();
		float GetMorphValueHipBone();
		float GetMorphValueHips();
		float GetMorphValueHipForward();
		float GetMorphValueHipUpperWidth();

		float GetMorphValueNippleLength();
		float GetMorphValueNipplePerkiness();
		float GetMorphValueNipplePerkManga();
		float GetMorphValueNippleTipManga();
		float GetMorphValueNippleDistance();
		float GetMorphValueNippleSize();
		float GetMorphValueAreolaSize();
		float GetMorphValueNippleDown();

		float GetMorphValueMuscleAbs();
		float GetMorphValueMuscleArms();
		float GetMorphValueMuscleButt();
		float GetMorphValueMuscleLegs();
		float GetMorphValueMusclePecs();

		float GetMorphValueBigButt();
		float GetMorphValueChubbyButt();
		float GetMorphValueButt();
		float GetMorphValueButtClassic();
		float GetMorphValueButtShape2();
		float GetMorphValueButtCrack();
		float GetMorphValueAppleCheeks();
		float GetMorphValueRoundAss();
		float GetMorphValueCrotchBack();
		float GetMorphValueGroin();

		float GetMorphValueChubbyLegs();
		float GetMorphValueLegs();
		float GetMorphValueThighs();
		float GetMorphValueKneeShape();
		float GetMorphValueKneeHeight();
		float GetMorphValueCalfSize();
		float GetMorphValueCalfSmooth();
		float GetMorphValueLegShapeClassic();

		float GetMorphValueBigTorso();
		float GetMorphValueChestDepth();
		float GetMorphValueChestWidth();
		float GetMorphValueChubbyWaist();
		float GetMorphValueWaist();
		float GetMorphValueSternumDepth();
		float GetMorphValueSternumHeight();
		float GetMorphValueWaistHeight();
		float GetMorphValueWaistLine();

		float GetMorphValueBreasts();
		float GetMorphValueBreastsNewSH();
		float GetMorphValueBreastsFantasy();
		float GetMorphValueBreastCenter();
		float GetMorphValueBreastCenterBig();
		float GetMorphValueBreastCleavage();
		float GetMorphValueBreastFlatness2();
		float GetMorphValueBreastFlatness();
		float GetMorphValueBreastGravity2();
		float GetMorphValueBreastHeight();
		float GetMorphValueBreastsTogether();
		float GetMorphValueBreastTopSlope();
		float GetMorphValuePushUp();
		float GetMorphValueBreastPerkiness();
		float GetMorphValueBreastWidth();

	private:
		static MorphProcedural* _instance;
		MorphProcedural() {} /* verhindert, dass ein Objekt von außerhalb von N erzeugt wird. */
		// protected, wenn man von der Klasse noch erben möchte
		MorphProcedural(const MorphProcedural&); /* verhindert, dass eine weitere Instanz via
		Kopie-Konstruktor erstellt werden kann */
		~MorphProcedural() {}

		SInt32 formID = 0;
		float weight = 0;
		float musclepower = 0;
		float morphfactor = 100;
		float morphfactorFemale = 100;
		float morphfactorMale = 100;
		float morphfactorBreasts = 100;
		float musclePower = 0;
		float fitness = 0;
		float gravityOffset = 0;
		SInt32 seedOffset = 0;
	};
}  // namespace RBS2020
