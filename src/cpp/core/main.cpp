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

#include "core/constants.h"
#include "core/Frontend.h"

namespace Myriad {

/**
 * Application name.
 */
const String Constant::APP_NAME = "GraphGen Parallel Data Generator (Demo)";

/**
 * Application version.
 */
const String Constant::APP_VERSION = "0.1.2";

} // Myriad namespace

// define the application main method
POCO_APP_MAIN(Myriad::Frontend)
