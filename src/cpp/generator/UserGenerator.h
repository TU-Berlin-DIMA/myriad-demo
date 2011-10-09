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

#ifndef USERGENERATOR_H_
#define USERGENERATOR_H_

#include "generator/base/BaseUserGenerator.h"

using namespace Myriad;
using namespace Poco;

namespace GraphGen {

class UserGenerator: public BaseUserGenerator
{
public:

	UserGenerator(const string& name, GeneratorConfig& config, NotificationCenter& notificationCenter) :
		BaseUserGenerator(name, config, notificationCenter)
	{
	}
};

class UserHydratorChain : public BaseUserHydratorChain
{
public:

	UserHydratorChain(OperationMode& opMode, RandomStream& random, GeneratorConfig& config) :
		BaseUserHydratorChain(opMode, random, config)
	{
	}
};

// ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
// base method definitions (don't modify)
// ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~

inline UserHydratorChain BaseUserGenerator::hydratorChain(BaseHydratorChain::OperationMode opMode, RandomStream& random)
{
	return UserHydratorChain(opMode, random, _config);
}

} // namespace GraphGen

#endif /* USERGENERATOR_H_ */
