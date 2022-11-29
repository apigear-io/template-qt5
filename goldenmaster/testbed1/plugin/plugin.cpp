/**
NO TITLE
Copyright (C) 2020 ApiGear UG

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "plugin.h"

#include <QtQml>

#include "../api/api.h"
#include "../lib/qmlstructinterface.h"
#include "../lib/qmlstructarrayinterface.h"

void Plugin::registerTypes(const char *uri)
{
    // @uri testbed1
    // register enum

    // register structs
    qRegisterMetaType<StructBool>();
    qmlRegisterUncreatableType<StructBoolFactory>(uri, 1, 0, "StructBoolFactory", "A struct factory can not be created");
    qRegisterMetaType<StructInt>();
    qmlRegisterUncreatableType<StructIntFactory>(uri, 1, 0, "StructIntFactory", "A struct factory can not be created");
    qRegisterMetaType<StructFloat>();
    qmlRegisterUncreatableType<StructFloatFactory>(uri, 1, 0, "StructFloatFactory", "A struct factory can not be created");
    qRegisterMetaType<StructString>();
    qmlRegisterUncreatableType<StructStringFactory>(uri, 1, 0, "StructStringFactory", "A struct factory can not be created");

    // register interfaces
    qmlRegisterType<QmlStructInterface>(uri, 1, 0, "StructInterface");
    qmlRegisterType<QmlStructArrayInterface>(uri, 1, 0, "StructArrayInterface");



}