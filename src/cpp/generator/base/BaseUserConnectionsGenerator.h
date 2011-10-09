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

#ifndef BASEUSERCONNECTIONGENERATOR_H_
#define BASEUSERCONNECTIONGENERATOR_H_

#include "generator/RandomSetGenerator.h"
#include "hydrator/ClusteredEnumSetHydrator.h"
#include "hydrator/ClusteredSelfReferenceHydrator.h"
#include "hydrator/ConstValueHydrator.h"
#include "hydrator/MultiplicativeGroupHydrator.h"
#include "record/User.h"
#include "record/UserConnections.h"

using namespace Myriad;
using namespace Poco;

namespace GraphGen {

class BaseUserConnectionsGenerator: public RandomSetGenerator<UserConnections>
{
public:

	typedef RecordTraits<UserConnections>::HydratorChainType HydratorChainType;

	BaseUserConnectionsGenerator(const string& name, GeneratorConfig& config, NotificationCenter& notificationCenter) :
		RandomSetGenerator<UserConnections>(name, config, notificationCenter)
	{
	}


	void prepare(Stage stage, const GeneratorPool& pool)
	{
		// call generator implementation
		RandomSetGenerator<UserConnections>::prepare(stage, pool);

		if (stage.name() == "default")
		{
			registerTask(new RandomSetDefaultGeneratingTask<UserConnections> (*this));
		}
	}

	HydratorChainType hydratorChain(BaseHydratorChain::OperationMode opMode, RandomStream& random);
};

/**
 * Hydrator specialization for UserConnections.
 */
class BaseUserConnectionsHydratorChain : public HydratorChain<UserConnections>
{
public:

	typedef MultiplicativeGroupHydrator<User> UserKeyHydrator;
	typedef MultiplicativeGroupHydrator<UserConnections> UserConnectionsKeyHydrator;
	typedef ClusteredEnumSetHydrator<UserConnections, I16u> ClusterHydrator;
	typedef ConstValueHydrator<UserConnections, I32u> ConnectionsCardinalityHydrator;
	typedef ClusteredSelfReferenceHydrator<UserConnections, UserKeyHydrator, ParetoPrFunction> ConnectionsHydrator;

	BaseUserConnectionsHydratorChain(OperationMode& opMode, RandomStream& random, GeneratorConfig& config) :
		HydratorChain<UserConnections>(opMode, random),
		_hydrateUserKey(&User::surrogateKey, config.cardinality("user"), config.genIDBegin("user"), config.genIDEnd("user")),
		_hydrateUserConnectionsKey(&UserConnections::surrogateKey, config.cardinality("user_connections"), config.genIDBegin("user_connections"), config.genIDEnd("user_connections")),
		_hydrateCluster(&UserConnections::clusterID, &UserConnections::clusterInterval, static_cast<ID> (config.cardinality("user") / config.getDouble("generator.user_connections.cluster_size") + 0.5), config.cardinality("user")),
		_hydrateConnectionsCardinality(&UserConnections::connectionsCardinality, config.getInt("generator.user_connections.connections_cardinality")),
		_hydrateConnections(random, &UserConnections::addConnection, &UserConnections::connectionsCardinality, &UserConnections::clusterInterval, _hydrateUserKey, config.func<ParetoPrFunction> ("uc-connections-probability")),
		_logger(Logger::get("hydrator.user_connections"))
	{
	}

	/**
	 * Object hydrating function.
	 */
	void operator()(AutoPtr<UserConnections> recordPtr) const
	{
		ensurePosition(recordPtr->genID());

		_hydrateUserConnectionsKey(recordPtr);
		_hydrateCluster(recordPtr);
		_hydrateConnectionsCardinality(recordPtr);
		_hydrateConnections(recordPtr);
	}

protected:

	UserKeyHydrator _hydrateUserKey;
	UserConnectionsKeyHydrator _hydrateUserConnectionsKey;
	ClusterHydrator _hydrateCluster;
	ConnectionsCardinalityHydrator _hydrateConnectionsCardinality;
	ConnectionsHydrator _hydrateConnections;

	/**
	 * Logger instance.
	 */
	Logger& _logger;
};

} // namespace GraphGen

#endif /* BASEUSERCONNECTIONGENERATOR_H_ */
