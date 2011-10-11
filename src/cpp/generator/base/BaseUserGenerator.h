/*
 * Copyright 2010-2011 DIMA Research Group, TU Berlin
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
 * @author: Alexander Alexandrov <alexander.s.alexandrov@campus.tu-berlin.de>
 */

#ifndef BASEUSERGENERATOR_H_
#define BASEUSERGENERATOR_H_

#include "generator/RandomSetGenerator.h"
#include "hydrator/ConstValueHydrator.h"
#include "hydrator/ConditionalHydrator.h"
#include "hydrator/EnumSetHydrator.h"
#include "hydrator/MultiplicativeGroupHydrator.h"
#include "hydrator/RangeSetHydrator.h"
#include "math/probability/Probability.h"
#include "record/User.h"

#include <Poco/UTF8String.h>

using namespace Myriad;
using namespace Poco;

namespace GraphGen {

class UserHydratorChain;

class BaseUserGenerator: public RandomSetGenerator<User>
{
public:

	typedef RecordTraits<User>::HydratorChainType HydratorChainType;

	BaseUserGenerator(const string& name, GeneratorConfig& config, NotificationCenter& notificationCenter) :
		RandomSetGenerator<User>(name, config, notificationCenter)
	{
	}

	void prepare(Stage stage, const GeneratorPool& pool)
	{
		// call generator implementation
		RandomSetGenerator<User>::prepare(stage, pool);

		if (stage.name() == "default")
		{
			registerTask(new RandomSetDefaultGeneratingTask<User> (*this, _config));
		}
	}

	HydratorChainType hydratorChain(BaseHydratorChain::OperationMode opMode, RandomStream& random);
};

/**
 * Hydrator specialization for User.
 */
class BaseUserHydratorChain : public HydratorChain<User>
{
public:

	// hydrator type aliases
	typedef MultiplicativeGroupHydrator<User> SurrogateKeyHydrator;
	typedef EnumSetHydrator<User, Gender> GenderHydrator;
	typedef RangeSetHydrator<User, String> StringHydrator;
	typedef ConditionalHydrator<User, Gender, StringHydrator, StringHydrator> FirstNameHydrator;

	BaseUserHydratorChain(OperationMode& opMode, RandomStream& random, GeneratorConfig& config) :
		HydratorChain<User>(opMode, random),
		_hydrateSurrogateKey(&User::surrogateKey, config.cardinality("user"), config.genIDBegin("user"), config.genIDEnd("user")),
		_hydrateGender(random, &User::gender, 2),
		_hydrateMaleName(random, &User::firstName, config.maleNames(), config.func<CustomDiscreteProbability>("u-male-firstnames-probability")),
		_hydrateFemaleName(random, &User::firstName, config.femaleNames(), config.func<CustomDiscreteProbability>("u-female-firstnames-probability")),
		_hydrateFirstName(&User::gender, GraphGen::MALE, _hydrateMaleName, _hydrateFemaleName),
		_hydrateLastName(random, &User::lastName, config.lastNames(), config.func<CustomDiscreteProbability>("u-lastnames-probability")),
		_logger(Logger::get("hydrator.user"))
	{
	}

	/**
	 * Object hydrating function.
	 */
	void operator()(AutoPtr<User> recordPtr) const
	{
		ensurePosition(recordPtr->genID());

		_hydrateSurrogateKey(recordPtr);
		_hydrateGender(recordPtr);
		_hydrateFirstName(recordPtr);
		_hydrateLastName(recordPtr);
	}

protected:

	SurrogateKeyHydrator _hydrateSurrogateKey;
	GenderHydrator _hydrateGender;
	StringHydrator _hydrateMaleName;
	StringHydrator _hydrateFemaleName;
	FirstNameHydrator _hydrateFirstName;
	StringHydrator _hydrateLastName;

	/**
	 * Logger instance.
	 */
	Logger& _logger;
};

} // namespace GraphGen

#endif /* BASEUSERGENERATOR_H_ */
