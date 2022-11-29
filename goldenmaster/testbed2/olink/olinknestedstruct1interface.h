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
#pragma once

#include <QtCore>
#include <QtPromise>

#include "../api/api.h"
#include "objectlink/olink/clientnode.h"

using namespace ApiGear;
using namespace ApiGear::ObjectLink;

class OLinkNestedStruct1Interface : public AbstractNestedStruct1Interface, public IObjectSink
{
    Q_OBJECT
public:
    explicit OLinkNestedStruct1Interface(QObject *parent = nullptr);
    virtual ~OLinkNestedStruct1Interface() override;

    void applyState(const nlohmann::json& fields);
    NestedStruct1 prop1() const override;
    void setProp1(const NestedStruct1& prop1) override;
    void setProp1Local(const NestedStruct1& prop1);
    NestedStruct1 func1(const NestedStruct1& param1) override;
    QtPromise::QPromise<NestedStruct1> func1Async(const NestedStruct1& param1);
signals:
    void isReady();
public:
    virtual std::string olinkObjectName() override;
    virtual void olinkOnSignal(std::string name, nlohmann::json args) override;
    virtual void olinkOnPropertyChanged(std::string name, nlohmann::json value) override;
    virtual void olinkOnInit(std::string name, nlohmann::json props, IClientNode *node) override;
    virtual void olinkOnRelease() override;
private:
    NestedStruct1 m_prop1;
    bool m_isReady;
    IClientNode *m_node;
};