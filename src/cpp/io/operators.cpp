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

#include "io/GeneratorOutputStream.h"
#include "record/Record.h"
#include "record/User.h"
#include "record/UserConnections.h"

namespace Myriad {

MyriadOutputStream& operator<<(MyriadOutputStream& out, const GraphGen::User& record)
{
	out <<
	"{\n"														<<
	"  \"id\": " 				<< record.surrogateKey()		<< ",\n"	<<
	"  \"first_name\": \""		<< record.firstName()			<< "\",\n"	<<
	"  \"last_name\": \""		<< record.lastName()			<< "\",\n"	<<
	"  \"gender\": \""			<< toString(record.gender())	<< "\",\n"	<<
	"},\n";

	return out;
}

MyriadOutputStream& operator<<(MyriadOutputStream& out, const GraphGen::UserConnections& record)
{
	out <<
														   "{\n"	<<
	"  \"id\": " 				<< record.surrogateKey()	<< ",\n" <<
	"  \"connections\": [";

	vector<ID> connections = record.connections();
	for( std::vector< ID >::iterator i = connections.begin(); i != connections.end(); ++i ) {
		out << (*i);
		if ((*i) != connections.back())
		{
			out << ",";
		}
	}

	out <<
	"]\n},\n";

	return out;
}

}  // namespace Myriad
