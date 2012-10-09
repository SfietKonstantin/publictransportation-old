/****************************************************************************************
 * Copyright (C) 2012 Lucien XU <sfietkonstantin@free.fr>                               *
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
 * @file linesmodel.cpp
 * @short Implementation of PublicTransportation::LinesModel
 */

#include "linesmodel.h"

#include "manager/abstractbackendmanager.h"

namespace PublicTransportation
{

/**
 * @internal
 * @short Private class for PublicTransportation::LinesModel
 */
class LinesModelPrivate
{
public:
    /**
     * @internal
     * @short Default constructor
     * @param q Q-pointer.
     */
    LinesModelPrivate(LinesModel *q);
    /**
     * @internal
     * @brief Slot for lines change
     * @param company company.
     */
    void slotLinesChanged(const PublicTransportation::Company &company);
    /**
     * @internal
     * @brief Update the model
     * @param lines lines to set.
     */
    void update(const QList<Line> &lines);
    /**
     * @internal
     * @brief Backend manager
     */
    AbstractBackendManager *backendManager;
    /**
     * @internal
     * @short Data
     */
    QList<Line> data;
    /**
     * @internal
     * @brief Updating
     */
    bool updating;
    /**
     * @internal
     * @brief Backend identifier
     */
    QString backendIdentifier;
    /**
     * @internal
     * @brief Company
     */
    Company company;
private:
    /**
     * @internal
     * @brief Q-pointer
     */
    LinesModel * const q_ptr;
    Q_DECLARE_PUBLIC(LinesModel)
};

LinesModelPrivate::LinesModelPrivate(LinesModel *q):
    q_ptr(q)
{
    backendManager = 0;
    updating = false;
}

void LinesModelPrivate::slotLinesChanged(const Company &company)
{
    Q_Q(LinesModel);

    AbstractBackendWrapper *backend = qobject_cast<AbstractBackendWrapper *>(q->sender());
    if (!backend) {
        return;
    }

    updating = false;
    emit q->updatingChanged();

    QObject::disconnect(backend, SIGNAL(linesChanged(PublicTransportation::Company)),
                        q, SLOT(slotLinesChanged(PublicTransportation::Company)));

    update(backend->lines(company));
}

void LinesModelPrivate::update(const QList<Line> &lines)
{
    Q_Q(LinesModel);

    q->beginRemoveRows(QModelIndex(), 0, q->rowCount() - 1);
    data.clear();
    q->endRemoveRows();


    if (lines.count() != 0) {
        q->beginInsertRows(QModelIndex(), 0, lines.count() - 1);
        data = lines;
        emit q->countChanged();
        q->endInsertRows();
    }
}

////// End of private class //////

LinesModel::LinesModel(QObject *parent):
    QAbstractListModel(parent),
    d_ptr(new LinesModelPrivate(this))
{
    // Definition of roles
    QHash <int, QByteArray> roles;
    roles.insert(NameRole, "name");
    roles.insert(DescriptionRole, "description");
    setRoleNames(roles);
}

LinesModel::~LinesModel()
{
}

void LinesModel::setBackendManager(AbstractBackendManager *backendManager)
{
    Q_D(LinesModel);
    if (d->backendManager != backendManager) {
        if (d->backendManager) {
            d->backendManager->disconnect(this);
        }

        d->backendManager = backendManager;
    }
}

int  LinesModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    Q_D(const LinesModel);
    return d->data.count();
}

bool LinesModel::isUpdating() const
{
    Q_D(const LinesModel);
    return d->updating;
}

int LinesModel::count() const
{
    return rowCount();
}

QVariant LinesModel::data(const QModelIndex &index, int role) const
{
    Q_D(const LinesModel);
    if (index.row() < 0 or index.row() >= rowCount()) {
        return QVariant();
    }
    Line line = d->data.at(index.row());

    switch(role) {
    case NameRole:
        return line.name();
        break;
    case DescriptionRole:
        return line.properties().value("description").toString();
        break;
    default:
        return QVariant();
        break;
    }
}

void LinesModel::displayLines(const QString &backendIdentifier, const Company &company)
{
    Q_D(LinesModel);
    if (!d->backendManager) {
        return;
    }

    if (!d->backendManager->contains(backendIdentifier)) {
        return;
    }

    AbstractBackendWrapper *backend = d->backendManager->backend(backendIdentifier);

    d->backendIdentifier = backendIdentifier;
    d->company = company;
    QList<Line> lines = backend->lines(company);


    if (lines.isEmpty()) {
        d->updating = true;
        emit updatingChanged();

        connect(backend, SIGNAL(linesChanged(PublicTransportation::Company)),
                this, SLOT(slotLinesChanged(PublicTransportation::Company)));

        backend->requestListLines(company);
    } else {
        d->update(lines);
    }
}

void LinesModel::requestJourneys(int index)
{
    Q_D(LinesModel);
    if (d->company.isNull()) {
        return;
    }

    if (index < 0 or index >= rowCount()) {
        return;
    }
    Line line = d->data.at(index);

    emit journeysRequested(d->backendIdentifier, d->company, line);
}

}

#include "moc_linesmodel.cpp"
