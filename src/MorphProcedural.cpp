#include "MorphProcedural.h"
#include "random"
namespace RBS2020
{
	MorphProcedural::MorphProcedural()
	{
		formID = 0;
		weight = 0;
		musclepower = 0;
		morphfactor = 50;
		morphfactorFemale = 100;
		morphfactorMale = 100;
		morphfactorBreasts = 100;
		morphfactorMuscles = 100;
		musclePower = 0;
		fitness = 0;
		gravityOffset = 0;
		seedOffset = 0;
	}
	MorphProcedural* MorphProcedural::_instance = 0;
	MorphProcedural* MorphProcedural::GetSingleton()
	{
		if (!_instance)
			_instance = new MorphProcedural();
		return _instance;
	}

	void MorphProcedural::SetSeedOffset(SInt32 seedOffset)
	{
		this->seedOffset = seedOffset;
	}

	SInt32 MorphProcedural::GetSeedOffset()
	{
		return seedOffset;
	}

	void MorphProcedural::SetSeed(SInt32 seed)
	{
		srand(seed + seedOffset);
	}

	float MorphProcedural::GetRandomFloat(float min, float max)
	{
		return (min + static_cast<float>(rand()) /
						  (static_cast<float>(RAND_MAX / (max - min))));
	}

	float MorphProcedural::GetRandomFloatNormalByWeight(float min, float max)
	{
		int samples = ceil(RBS2020::MorphProcedural::GetWeight() / 10);
		std::random_device rd;
		std::mt19937 gen(rd());
		// std::normal_distribution<float> d(min, max);
		std::uniform_real_distribution<float> d(min, max);
		float sample = 0;
		for (int i = 0; i < samples; ++i) {
			sample = sample + d(gen);
		}
		float ret = (sample * (morphfactor / 100)) - fitness;
		if (ret < 0)
			ret = 0;
		return (ret);
	}

	float MorphProcedural::GetRandomFloatNormalByMusclePower(float min, float max)
	{
		int samples = ceil(RBS2020::MorphProcedural::GetMusclepower() * 10);
		std::random_device rd;
		std::mt19937 gen(rd());
		// std::normal_distribution<float> d(min, max);
		std::uniform_real_distribution<float> d(min, max);
		float sample = 0;
		for (int i = 0; i < samples; ++i) {
			sample = sample + d(gen);
		}
		return (sample * ((morphfactor / 100) * (morphfactorMuscles/100)));
	}

	void MorphProcedural::SetGravityOffset(float gravityOffset)
	{
		this->gravityOffset = gravityOffset;
	}

	float MorphProcedural::GetGravityOffset()
	{
		return gravityOffset;
	}

	float MorphProcedural::GetWeight()
	{
		return weight;
	}

	float MorphProcedural::GetMusclepower()
	{
		return musclepower;
	}

	void MorphProcedural::SetMusclepower(float musclepower)
	{
		this->musclepower = musclepower;
	}

	float MorphProcedural::GetFitness()
	{
		return this->fitness;
	}

	void MorphProcedural::SetFitness(float fitness)
	{
		this->fitness = fitness;
	}

	void MorphProcedural::SetWeight(float weight)
	{
		this->weight = weight;
	}

	float MorphProcedural::GetMorphfactorMale()
	{
		if (morphfactorMale < 50)
			morphfactorMale = 50;
		return morphfactorMale;
	}

	float MorphProcedural::GetMorphfactorFemale()
	{
		if (morphfactorFemale < 50)
			morphfactorFemale = 50;
		return morphfactorFemale;
	}

	void MorphProcedural::SetMorphfactor(float morphfactor)
	{
		this->morphfactor = morphfactor;
	}

	void MorphProcedural::SetMorphfactorFemale(float morphfactor)
	{
		this->morphfactorFemale = morphfactor;
	}
	void MorphProcedural::SetMorphfactorMale(float morphfactor)
	{
		this->morphfactorMale = morphfactor;
	}

	float MorphProcedural::GetMorphfactorBreasts()
	{
		return morphfactorBreasts;
	}

	void MorphProcedural::SetMorphfactorBreasts(float morphfactorBreasts)
	{
		this->morphfactorBreasts = morphfactorBreasts;
	}

	float MorphProcedural::GetMorphfactorMuscles()
	{
		return morphfactorMuscles;
	}

	void MorphProcedural::SetMorphfactorMuscles(float morphfactorMuscles)
	{
		this->morphfactorBreasts = morphfactorMuscles;
	}

	void MorphProcedural::SetFormID(SInt32 formID)
	{
		this->formID = formID;
	}

	float MorphProcedural::GetMorphValueSamSamuel()
	{
		return GetRandomFloatNormalByWeight(0.0, 0.1);
	}

	float MorphProcedural::GetMorphValueSamSamson()
	{
		return GetRandomFloatNormalByMusclePower(0.0, 0.1);
	}

	float MorphProcedural::GetMorphValueForearmSize()
	{
		return GetRandomFloatNormalByWeight(0.0, 0.1);
	}

	float MorphProcedural::GetMorphValueChubbyArms()
	{
		return GetRandomFloatNormalByWeight(0.0, 0.1);
	}
	float MorphProcedural::GetMorphValueShoulderWidth()
	{
		return GetRandomFloatNormalByWeight(-0.1, 0.0);
	}
	float MorphProcedural::GetMorphValueArms()
	{
		return GetRandomFloat(0.0, 1.0);
	}

	float MorphProcedural::GetMorphValueShoulderSmooth()
	{
		return GetRandomFloat(0.0, 1.0);
	}

	float MorphProcedural::GetMorphValueShoulderTweak()
	{
		return GetRandomFloat(0.0, 1.0);
	}

	float MorphProcedural::GetMorphValueBelly()
	{
		return GetRandomFloat(0.0, 1.0);
	}

	float MorphProcedural::GetMorphValueTummyTuck()
	{
		return GetRandomFloat(0.0, 1.0);
	}

	float MorphProcedural::GetMorphValueBigBelly()
	{
		return GetRandomFloatNormalByWeight(0.0, 0.1);
	}

	float MorphProcedural::GetMorphValueHipBone()
	{
		return GetRandomFloatNormalByWeight(0.0, 0.055);
	}

	float MorphProcedural::GetMorphValueHips()
	{
		return GetRandomFloatNormalByWeight(0.0, 0.055);
	}

	float MorphProcedural::GetMorphValueHipForward()
	{
		return GetRandomFloat(-0.7, 0.7);
	}

	float MorphProcedural::GetMorphValueHipUpperWidth()
	{
		return GetRandomFloat(0.0, 1.0);
	}

	float MorphProcedural::GetMorphValueNippleLength()
	{
		return GetRandomFloat(0.0, 0.3);
	}
	float MorphProcedural::GetMorphValueNipplePerkiness()
	{
		return GetRandomFloat(0.0, 1.0);
	}
	float MorphProcedural::GetMorphValueNipplePerkManga()
	{
		return GetRandomFloat(0.0, 1.0);
	}
	float MorphProcedural::GetMorphValueNippleTipManga()
	{
		return GetRandomFloat(-0.5, 0.5);
	}
	float MorphProcedural::GetMorphValueNippleDistance()
	{
		return GetRandomFloat(0.0, 1.0);
	}
	float MorphProcedural::GetMorphValueNippleSize()
	{
		return GetRandomFloat(0.0, 1.0);
	}
	float MorphProcedural::GetMorphValueAreolaSize()
	{
		return GetRandomFloat(-1.0, 1);
	}
	float MorphProcedural::GetMorphValueNippleDown()
	{
		return GetRandomFloat(0.0, 0.7);
	}

	float MorphProcedural::GetMorphValueMuscleAbs()
	{
		return GetRandomFloat(0.0, musclePower);
	}
	float MorphProcedural::GetMorphValueMuscleArms()
	{
		return GetRandomFloat(0.0, musclePower);
	}
	float MorphProcedural::GetMorphValueMuscleButt()
	{
		return GetRandomFloat(0.0, musclePower);
	}
	float MorphProcedural::GetMorphValueMuscleLegs()
	{
		return GetRandomFloat(0.0, musclePower);
	}
	float MorphProcedural::GetMorphValueMusclePecs()
	{
		return GetRandomFloat(0.0, musclePower);
	}

	float MorphProcedural::GetMorphValueBigButt()
	{
		return GetRandomFloatNormalByWeight(0.0, 0.075);
	}

	float MorphProcedural::GetMorphValueChubbyButt()
	{
		return GetRandomFloatNormalByWeight(0.0, 0.075);
	}

	float MorphProcedural::GetMorphValueButt()
	{
		return GetRandomFloatNormalByWeight(0.0, 0.075);
	}

	float MorphProcedural::GetMorphValueButtClassic()
	{
		return GetRandomFloat(0.0, 1.0);
	}

	float MorphProcedural::GetMorphValueButtShape2()
	{
		return GetRandomFloat(0.0, 1.0);
	}

	float MorphProcedural::GetMorphValueButtCrack()
	{
		return GetRandomFloat(0.0, 1.0);
	}

	float MorphProcedural::GetMorphValueAppleCheeks()
	{
		return GetRandomFloat(0.0, 1.0);
	}

	float MorphProcedural::GetMorphValueRoundAss()
	{
		return GetRandomFloat(0.0, 1.0);
	}

	float MorphProcedural::GetMorphValueCrotchBack()
	{
		return GetRandomFloat(0.0, 1.0);
	}

	float MorphProcedural::GetMorphValueGroin()
	{
		return GetRandomFloat(0.0, 1.0);
	}

	float MorphProcedural::GetMorphValueChubbyLegs()
	{
		return GetRandomFloatNormalByWeight(0.0, 0.1);
	}

	float MorphProcedural::GetMorphValueLegs()
	{
		return GetRandomFloatNormalByWeight(0.0, 0.1);
	}

	float MorphProcedural::GetMorphValueThighs()
	{
		return GetRandomFloatNormalByWeight(0.0, 0.1);
	}

	float MorphProcedural::GetMorphValueKneeShape()
	{
		return GetRandomFloat(0.0, 1.0);
	}

	float MorphProcedural::GetMorphValueKneeHeight()
	{
		return GetRandomFloat(0.0, 1.0);
	}

	float MorphProcedural::GetMorphValueCalfSize()
	{
		return GetRandomFloat(0.0, 1.0);
	}

	float MorphProcedural::GetMorphValueCalfSmooth()
	{
		return GetRandomFloat(0.0, 1.0);
	}

	float MorphProcedural::GetMorphValueLegShapeClassic()
	{
		return GetRandomFloat(0.0, 1.0);
	}

	float MorphProcedural::GetMorphValueBigTorso()
	{
		return GetRandomFloatNormalByWeight(0.0, 0.07);
	}

	float MorphProcedural::GetMorphValueChestDepth()
	{
		return GetRandomFloatNormalByWeight(0.0, 0.05);
	}

	float MorphProcedural::GetMorphValueChestWidth()
	{
		return GetRandomFloatNormalByWeight(0.0, 0.07);
	}

	float MorphProcedural::GetMorphValueChubbyWaist()
	{
		return GetRandomFloatNormalByWeight(0.0, 0.07);
	}

	float MorphProcedural::GetMorphValueWaist()
	{
		return GetRandomFloat(0.0, 1.0);
	}

	float MorphProcedural::GetMorphValueSternumDepth()
	{
		return GetRandomFloat(0.0, 1.0);
	}

	float MorphProcedural::GetMorphValueSternumHeight()
	{
		return GetRandomFloat(0.0, 0.4);
	}

	float MorphProcedural::GetMorphValueWaistHeight()
	{
		return GetRandomFloat(0.0, 0.5);
	}

	float MorphProcedural::GetMorphValueWaistLine()
	{
		return GetRandomFloat(-0.5, 0.5);
	}

	float MorphProcedural::GetMorphValueBreasts()
	{
		return (GetRandomFloatNormalByWeight(0.0, 0.04) + GetRandomFloat(0.0, 0.75)) * (morphfactorBreasts / 100);
	}

	float MorphProcedural::GetMorphValueBreastsNewSH()
	{
		return GetRandomFloatNormalByWeight(0.0, 0.08);
	}

	float MorphProcedural::GetMorphValueBreastCleavage()
	{
		return GetRandomFloatNormalByWeight(0.0, 0.10);
	}

	float MorphProcedural::GetMorphValueBreastsFantasy()
	{
		return GetRandomFloat(0.0, 0.4);
	}

	float MorphProcedural::GetMorphValueBreastCenter()
	{
		return GetRandomFloat(0.0, 1.0);
	}
	float MorphProcedural::GetMorphValueBreastCenterBig()
	{
		return GetRandomFloat(0.0, 1.0);
	}

	float MorphProcedural::GetMorphValueBreastFlatness2()
	{
		if (weight < 25.0) {
			return GetRandomFloat(0.0, 0.2);
		} else {
			return 0;
		}
	}

	float MorphProcedural::GetMorphValueBreastFlatness()
	{
		if (weight < 25.0) {
			return GetRandomFloat(0.0, 0.2);
		} else {
			return 0;
		}
	}

	float MorphProcedural::GetMorphValueBreastGravity2()
	{
		return (GetRandomFloatNormalByWeight(0.0, 0.07) + gravityOffset);
	}

	float MorphProcedural::GetMorphValueBreastHeight()
	{
		return GetRandomFloatNormalByWeight(0.00, 0.075);
	}

	float MorphProcedural::GetMorphValueBreastsTogether()
	{
		return GetRandomFloatNormalByWeight(0.03, 0.1);
	}

	float MorphProcedural::GetMorphValueBreastTopSlope()
	{
		return GetRandomFloat(0.0, 1.0);
	}

	float MorphProcedural::GetMorphValuePushUp()
	{
		return 0;
	}

	float MorphProcedural::GetMorphValueBreastPerkiness()
	{
		return GetRandomFloat(0.0, 1.0);
	}

	float MorphProcedural::GetMorphValueBreastWidth()
	{
		return GetRandomFloat(0.0, 1.0);
	}
}  // namespace RBS2020
