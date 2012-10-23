#!/usr/bin/python
import codecs

headerData = """/****************************************************************************************
 * Copyright (C) 2011 Lucien XU <sfietkonstantin@free.fr>                               *
 *                                                                                      *
 * This program is free software; you can redistribute it and/or modify it under        *
 * the terms of the GNU General Public License as published by the Free Software        *
 * Foundation; either version 3 of the License, or (at your option) any later           *
 * version.                                                                             *
 *                                                                                      *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY      *
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A      *
 * PARTICULAR PURPOSE. See the GNU General Public License for more details.             *
 *                                                                                      *
 * You should have received a copy of the GNU General Public License along with         *
 * this program.  If not, see <http://www.gnu.org/licenses/>.                           *
 ****************************************************************************************/

/**
 * @file countriesmodel.h
 * @short Definition of PublicTransportation::Gui::CountriesModel
 */

#ifndef PUBLICTRANSPORTATION_GUI_COUNTRIESMODEL_H
#define PUBLICTRANSPORTATION_GUI_COUNTRIESMODEL_H

#include <QtCore/QAbstractListModel>

namespace PublicTransportation
{

namespace Gui
{

class CountriesModelPrivate;

/**
 * @brief A model for countries
 *
 * This model provides a list of countries that
 * can be filtered.
 */
class CountriesModel : public QAbstractListModel
{
    Q_OBJECT
    /**
     * @short Filter
     */
    Q_PROPERTY(QString filter READ filter WRITE setFilter NOTIFY filterChanged)
    /**
     * @short Current country
     */
    Q_PROPERTY(QString currentCountry READ currentCountry NOTIFY currentCountryChanged)
    /**
     * @short Current ISO code
     */
    Q_PROPERTY(QString currentIsoCode READ currentIsoCode NOTIFY currentIsoCodeChanged)
    /**
     * @short Count
     */
    Q_PROPERTY(int count READ count NOTIFY countChanged)
public:
    /**
     * @short Model roles
     */
    enum CountriesModelRole {
        /**
         * @short Name role
         */
        NameRole = Qt::UserRole + 1,
        /**
         * @short Iso code role
         */
        IsoCodeRole
    };
    /**
     * @short Default constructor
     * @param parent parent object.
     */
    explicit CountriesModel(QObject *parent = 0);
    /**
     * @short Destructor
     */
    virtual ~CountriesModel();
    /**
     * @short Reimplementation of rowCount
     *
     * @param parent parent model index.
     * @return the number of rows in this model.
     */
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    /**
     * @short Filter
     * @return filter.
     */
    QString filter() const;
    /**
     * @short Current country
     * @return current country.
     */
    QString currentCountry() const;
    /**
     * @short Current ISO code
     * @return current ISO code.
     */
    QString currentIsoCode() const;
    /**
     * @short Count
     * @return count.
     */
    int count() const;
    /**
     * @short Reimplementation of data
     *
     * @param index model index where retrieve the data.
     * @param role role to retrieve.
     * @return retrieved data as a variant.
     */
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
public Q_SLOTS:
    /**
     * @short Set filter
     * @param filter filter to set.
     */
    void setFilter(const QString &filter);
    /**
     * @short Select a country
     * @param index index of the selected country.
     */
    void select(int index);
Q_SIGNALS:
    /**
     * @short Filter changed
     */
    void filterChanged();
    /**
     * @short Current Country changed
     */
     void currentCountryChanged();
    /**
     * @short Current ISO code changed
     */
     void currentIsoCodeChanged();
    /**
     * @short Count changed
     */
    void countChanged();
protected:
    /**
     * @short D-pointer
     */
    const QScopedPointer<CountriesModelPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(CountriesModel)

};

}

}

#endif // PUBLICTRANSPORTATION_GUI_COUNTRIESMODEL_H
"""

# Write header
headerFile = open("countriesmodel.h", 'w')
headerFile.write(headerData)
headerFile.close()

countriesSource = ""

f = codecs.open("country-list-iso.txt", 'r', "utf-8")

for line in f:
    splittedLine = line.strip().split(":")
    name = splittedLine[1]
    isoCode = splittedLine[0]
    countriesSource += "    CountriesModelItem *item" + isoCode + " = new CountriesModelItem;\n"
    countriesSource += "    item" + isoCode + "->name = QObject::tr(\"" + name + "\");\n"
    countriesSource += "    item" + isoCode + "->isoCode = \"" + isoCode + "\";\n"
    countriesSource += "    countries.append(item" + isoCode + ");\n"

sourceData1 = """/****************************************************************************************
 * Copyright (C) 2011 Lucien XU <sfietkonstantin@free.fr>                               *
 *                                                                                      *
 * This program is free software; you can redistribute it and/or modify it under        *
 * the terms of the GNU General Public License as published by the Free Software        *
 * Foundation; either version 3 of the License, or (at your option) any later           *
 * version.                                                                             *
 *                                                                                      *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY      *
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A      *
 * PARTICULAR PURPOSE. See the GNU General Public License for more details.             *
 *                                                                                      *
 * You should have received a copy of the GNU General Public License along with         *
 * this program.  If not, see <http://www.gnu.org/licenses/>.                           *
 ****************************************************************************************/

/**
 * @file countriesmodel.cpp
 * @short Implementation of PublicTransportation::Gui::CountriesModel
 */

#include "countriesmodel.h"

namespace PublicTransportation
{

namespace Gui
{

/**
 * @internal
 * @brief Private class used in PublicTransportation::Gui::CountriesModel
 */
struct CountriesModelItem
{
    /**
     * @internal
     * @short Name
     */
    QString name;
    /**
     * @internal
     * @short ISO code
     */
    QString isoCode;
};

/**
 * @internal
 * @short Private class for PublicTransportation::Gui::CountriesModel
 */
class CountriesModelPrivate
{
public:
    /**
     * @internal
     * @short Default constructor
     */
    CountriesModelPrivate();
    /**
     * @internal
     * @short Filter
     */
    QString filter;
    /**
     * @internal
     * @short Current
     */
    CountriesModelItem *current;
    /**
     * @internal
     * @short Countries
     */
    QList<CountriesModelItem *> data;
    /**
     * @internal
     * @short All
     */
    CountriesModelItem *all;
    /**
     * @internal
     * @short Countries
     */
    QList<CountriesModelItem *> countries;
};

CountriesModelPrivate::CountriesModelPrivate()
{
    all = new CountriesModelItem;
    all->name = QObject::tr("All countries");
    all->isoCode = QString();
    current = all;

"""
sourceData2 = """

    data = countries;
    data.prepend(all);
}

////// End of private class //////

CountriesModel::CountriesModel(QObject *parent):
    QAbstractListModel(parent),
    d_ptr(new CountriesModelPrivate)
{
    // Definition of roles
    QHash <int, QByteArray> roles;
    roles.insert(NameRole, "name");
    roles.insert(IsoCodeRole, "isoCode");
    setRoleNames(roles);
}

CountriesModel::~CountriesModel()
{
    Q_D(CountriesModel);
    delete d->all;
    while (!d->countries.isEmpty()) {
        delete d->countries.takeFirst();
    }
}

QString CountriesModel::currentCountry() const
{
    Q_D(const CountriesModel);
    return d->current->name;
}

QString CountriesModel::currentIsoCode() const
{
    Q_D(const CountriesModel);
    return d->current->isoCode;
}

QString CountriesModel::filter() const
{
    Q_D(const CountriesModel);
    return d->filter;
}

int  CountriesModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    Q_D(const CountriesModel);
    return d->data.count();
}

int CountriesModel::count() const
{
    return rowCount();
}

QVariant CountriesModel::data(const QModelIndex &index, int role) const
{
    Q_D(const CountriesModel);
    if (index.row() < 0 or index.row() >= rowCount()) {
        return QVariant();
    }
    CountriesModelItem *item = d->data.at(index.row());

    switch(role) {
    case NameRole:
        return item->name;
        break;
    case IsoCodeRole:
        return item->isoCode;
        break;
    default:
        return QVariant();
        break;
    }
}

void CountriesModel::setFilter(const QString &filter)
{
    Q_D(CountriesModel);
    if (d->filter != filter) {
        d->filter = filter;
        emit filterChanged();

        beginRemoveRows(QModelIndex(), 0, rowCount() - 1);
        d->data.clear();
        endRemoveRows();

        if (filter.isEmpty()) {
            d->data = d->countries;
            d->data.prepend(d->all);
        } else {
            foreach (CountriesModelItem *item, d->countries) {
                if (item->name.toLower().startsWith(filter.toLower())) {
                    d->data.append(item);
                }
            }
        }

        beginInsertRows(QModelIndex(), 0, d->data.count() - 1);
        emit countChanged();
        endInsertRows();
    }
}

void CountriesModel::select(int index)
{
    Q_D(CountriesModel);
    if (index < 0 || index >= rowCount()) {
        return;
    }

    CountriesModelItem *newItem = d->data.at(index);
    if (d->current != newItem) {
        d->current = newItem;
        emit currentCountryChanged();
        emit currentIsoCodeChanged();
    }
}

}

}
"""

# Write source
sourceFile = codecs.open("countriesmodel.cpp", 'w', "utf-8")
sourceFile.write(sourceData1)
sourceFile.write(countriesSource)
sourceFile.write(sourceData2)
sourceFile.close()







