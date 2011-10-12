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

#ifndef BASEUSERCONNECTIONS_H_
#define BASEUSERCONNECTIONS_H_

#include "record/Record.h"
#include "math/Interval.h"

using namespace Myriad;

namespace GraphGen {

// forward declarations
class UserConnections;
class UserConnectionsConfig;
class UserConnectionsGenerator;
class UserConnectionsHydratorChain;

class BaseUserConnections: public Record
{
public:

	BaseUserConnections() : m_connections(0)
	{
		m_connections_cardinality = 0;
	}

	void surrogateKey(const ID& v);
	const ID& surrogateKey() const;

	void clusterID(const I16u& v);
	const I16u& clusterID() const;

	void clusterInterval(const Interval<ID>& v);
	const Interval<ID>& clusterInterval() const;

	void addConnection(const ID& v);
	const vector<ID>& connections() const;

	void connectionsCardinality(const I32u& v);
	const I32u& connectionsCardinality() const;

private:

	I16u m_cluster_id;
	Interval<ID> m_cluster_interval;

	ID m_surrogate_key;
	I32u m_connections_cardinality;
	vector<ID> m_connections;
};

inline const vector<ID>& BaseUserConnections::connections() const
{
	return m_connections;
}

inline void BaseUserConnections::clusterID(const I16u& v)
{
	m_cluster_id = v;
}

inline const I16u& BaseUserConnections::clusterID() const
{
	return m_cluster_id;
}

inline void BaseUserConnections::clusterInterval(const Interval<ID>& v)
{
	m_cluster_interval = v;
}

inline void BaseUserConnections::surrogateKey(const ID& v)
{
	m_surrogate_key = v;
}

inline const ID& BaseUserConnections::surrogateKey() const
{
	return m_surrogate_key;
}

inline void BaseUserConnections::addConnection(const ID& v)
{
	m_connections.push_back(v);
}

inline const Interval<ID>& BaseUserConnections::clusterInterval() const
{
	return m_cluster_interval;
}

inline void BaseUserConnections::connectionsCardinality(const I32u& v)
{
	m_connections_cardinality = v;
	m_connections.reserve(v);
}

inline const I32u& BaseUserConnections::connectionsCardinality() const
{
	return m_connections_cardinality;
}

} // namespace GraphGen

namespace Myriad {

// record traits specialization
template<> struct RecordTraits<GraphGen::UserConnections>
{
	typedef GraphGen::UserConnectionsGenerator GeneratorType;
	typedef GraphGen::UserConnectionsHydratorChain HydratorChainType;
};

// forward declaration of operator<<
OutputCollector::StreamType& operator<<(OutputCollector::StreamType& out, const GraphGen::UserConnections& record);

} // namespace Myriad

#endif /* BASEUSERCONNECTIONS_H_ */
