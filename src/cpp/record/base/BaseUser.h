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

#ifndef BASEUSER_H_
#define BASEUSER_H_

#include "record/Record.h"

using namespace Myriad;

namespace GraphGen {

// forward declarations
class User;
class UserConfig;
class UserGenerator;
class UserHydratorChain;

enum Gender
{
	MALE, FEMALE
};

// base user class
class BaseUser: public Record
{
public:

	BaseUser()
	{
	}

	void surrogateKey(const ID& v);
	const ID& surrogateKey() const;

	void firstName(const String& v);
	const String& firstName() const;

	void lastName(const String& v);
	const String& lastName() const;

	void gender(const Gender& v);
	const Gender& gender() const;

	void username(const String& v);
	const String& username() const;

private:

	ID m_surrogate_key;
	String m_first_name;
	String m_last_name;
	Gender m_gender;
	String m_username;
};

inline void BaseUser::surrogateKey(const ID& v)
{
	m_surrogate_key = v;
}

inline const ID& BaseUser::surrogateKey() const
{
	return m_surrogate_key;
}

inline void BaseUser::firstName(const String& v)
{
	m_first_name = v;
}

inline const String& BaseUser::firstName() const
{
	return m_first_name;
}

inline void BaseUser::lastName(const String& v)
{
	m_last_name = v;
}

inline const String& BaseUser::lastName() const
{
	return m_last_name;
}

inline void BaseUser::gender(const Gender& v)
{
	m_gender = v;
}

inline const Gender& BaseUser::gender() const
{
	return m_gender;
}

inline void BaseUser::username(const String& v)
{
	m_username = v;
}

inline const String& BaseUser::username() const
{
	return m_username;
}

} // namespace GraphGen


namespace Myriad {

// record traits specialization
template<> struct RecordTraits<GraphGen::User>
{
	typedef GraphGen::UserGenerator GeneratorType;
	typedef GraphGen::UserHydratorChain HydratorChainType;
};

// forward declaration of operator<<
OutputCollector::StreamType& operator<<(OutputCollector::StreamType& out, const GraphGen::User& record);

// methods for gender type
inline std::string toString(const GraphGen::Gender& t)
{
	if (t == GraphGen::MALE)
	{
		return "Male";
	}
	else
	{
		return "Female";
	}
}

template<> inline GraphGen::Gender toEnum<GraphGen::Gender> (int v)
{
	if (v == 0)
	{
		return GraphGen::MALE;
	}
	else
	{
		return GraphGen::FEMALE;
	}
}

} // namespace Myriad

#endif /* BASEUSER_H_ */
