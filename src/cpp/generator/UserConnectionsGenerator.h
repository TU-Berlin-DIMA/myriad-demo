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

#ifndef USERCONNECTIONGENERATOR_H_
#define USERCONNECTIONGENERATOR_H_

#include "generator/base/BaseUserConnectionsGenerator.h"

using namespace Myriad;
using namespace Poco;

namespace GraphGen {

class UserConnectionsGenerator: public BaseUserConnectionsGenerator
{
public:

	UserConnectionsGenerator(const string& name, GeneratorConfig& config, NotificationCenter& notificationCenter) :
		BaseUserConnectionsGenerator(name, config, notificationCenter)
	{
	}
};

class UserConnectionsHydratorChain : public BaseUserConnectionsHydratorChain
{
public:

	UserConnectionsHydratorChain(OperationMode& opMode, RandomStream& random, GeneratorConfig& config) :
		BaseUserConnectionsHydratorChain(opMode, random, config)
	{
	}
};


// ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
// base method definitions (don't modify)
// ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~

inline UserConnectionsHydratorChain BaseUserConnectionsGenerator::hydratorChain(BaseHydratorChain::OperationMode opMode, RandomStream& random)
{
	return UserConnectionsHydratorChain(opMode, random, _config);
}

} // namespace GraphGen

#endif /* USERCONNECTIONGENERATOR_H_ */
