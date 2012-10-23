/****************************************************************************************
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
