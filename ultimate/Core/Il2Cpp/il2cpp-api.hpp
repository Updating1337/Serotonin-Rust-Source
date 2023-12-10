#pragma once

#include "../Includes/includes.hpp"

#include "il2cpp-config-api.hpp"
#include "il2cpp-class-internals.hpp"
#include "il2cpp-object-internals.hpp"

#pragma optimize( "", off )
#define DO_API( return_type, name, parameters )	extern return_type ( *name ) parameters
#pragma optimize( "", on )