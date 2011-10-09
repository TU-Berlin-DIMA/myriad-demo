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

#ifndef GENERATORCONFIG_H_
#define GENERATORCONFIG_H_

#include "config/AbstractGeneratorConfig.h"

namespace Myriad {

class GeneratorConfig: public AbstractGeneratorConfig
{
public:

	const vector<String>& maleNames()
	{
		return _maleNames;
	}

	const vector<String>& femaleNames()
	{
		return _femaleNames;
	}

	const vector<String>& lastNames()
	{
		return _lastNames;
	}


protected:

	void configureSets(const AutoPtr<XML::Document>& doc)
	{
		configureFunctions(doc);
		bindStringSet(doc, "u-male-firstnames", _maleNames);
		bindStringSet(doc, "u-female-firstnames", _femaleNames);
		bindStringSet(doc, "u-lastnames", _lastNames);
	}

private:

	vector<String> _maleNames;

	vector<String> _femaleNames;

	vector<String> _lastNames;

};

} // namespace Myriad

#endif /* GENERATORCONFIG_H_ */
