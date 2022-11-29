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



#include "olinksameenum1interfaceadapter.h"

#include <nlohmann/json.hpp>
#include "../api/agent.h"
#include "../api/json.adapter.h"

#include <QtCore>

using namespace ApiGear::ObjectLink;

using json = nlohmann::json;

OLinkSameEnum1InterfaceAdapter::OLinkSameEnum1InterfaceAdapter(AbstractSameEnum1Interface* impl, QObject *parent)
    : QObject(parent)
    , m_impl(impl)
    , m_node(nullptr)
{
    RemoteRegistry::get().addObjectSource(this);
    connect(m_impl, &AbstractSameEnum1Interface::prop1Changed, this, [=](const Enum1::Enum1Enum prop1) {
        if(m_node) {
            m_node->notifyPropertyChange("tb.same2.SameEnum1Interface/prop1", prop1);
        }
    });
    connect(m_impl, &AbstractSameEnum1Interface::sig1, this, [=](const Enum1::Enum1Enum param1) {
        if(m_node) {
            const json& args = { param1 };
            m_node->notifySignal("tb.same2.SameEnum1Interface/sig1", args);
        }
    });
}

OLinkSameEnum1InterfaceAdapter::~OLinkSameEnum1InterfaceAdapter()
{
    RemoteRegistry::get().removeObjectSource(this);
}

json OLinkSameEnum1InterfaceAdapter::captureState()
{
    return json::object({
        { "prop1", m_impl->prop1() }
    });
}

void OLinkSameEnum1InterfaceAdapter::applyState(const json& state)
{
    if(state.contains("prop1")) {
        m_impl->setProp1(state["prop1"]);
    }
}


std::string OLinkSameEnum1InterfaceAdapter::olinkObjectName() {
    return "tb.same2.SameEnum1Interface";
}

json OLinkSameEnum1InterfaceAdapter::olinkInvoke(std::string name, json args) {
    qDebug() << Q_FUNC_INFO << QString::fromStdString(name);
    std::string path = Name::pathFromName(name);
    if(path == "func1") {
        const Enum1::Enum1Enum& param1 = args.at(0);
        Enum1::Enum1Enum result = m_impl->func1(param1);
        return result;
    }
    return json();
}

void OLinkSameEnum1InterfaceAdapter::olinkSetProperty(std::string name, json value) {
    qDebug() << Q_FUNC_INFO << QString::fromStdString(name);
    std::string path = Name::pathFromName(name);
    if(path == "prop1") {
        Enum1::Enum1Enum prop1 = value.get<Enum1::Enum1Enum>();
        m_impl->setProp1(prop1);
    }    
}

void OLinkSameEnum1InterfaceAdapter::olinkLinked(std::string name, IRemoteNode *node) {
    qDebug() << Q_FUNC_INFO << QString::fromStdString(name);
    m_node = node;
}

void OLinkSameEnum1InterfaceAdapter::olinkUnlinked(std::string name)
{
    qDebug() << Q_FUNC_INFO << QString::fromStdString(name);
    m_node = nullptr;
}

json OLinkSameEnum1InterfaceAdapter::olinkCollectProperties()
{
    return captureState();
}



