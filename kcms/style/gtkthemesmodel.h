/*
 * Copyright 2020 Mikhail Zolotukhin <zomial@protonmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License or (at your option) version 3 or any later version
 * accepted by the membership of KDE e.V. (or its successor approved
 * by the membership of KDE e.V.), which shall act as a proxy
 * defined in Section 14 of version 3 of the license.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <QAbstractListModel>
#include <QMap>

class QStringList;
class QString;

class GtkThemesModel : public QAbstractListModel {
    Q_OBJECT

    Q_PROPERTY(QString selectedTheme READ selectedTheme WRITE setSelectedTheme NOTIFY selectedThemeChanged)

public:
    GtkThemesModel(QObject *parent = nullptr);

    enum Roles {
        ThemeNameRole = Qt::UserRole + 1,
        ThemePathRole
    };

    void loadGtk2();
    void loadGtk3();

    void setThemesList(const QMap<QString, QString> &themes);
    QMap<QString, QString> themesList();

    void setSelectedTheme(const QString &themeName);
    QString selectedTheme();
    Q_SIGNAL void selectedThemeChanged(const QString &themeName);

    Q_INVOKABLE bool selectedThemeRemovable();
    Q_INVOKABLE void removeSelectedTheme();
    Q_INVOKABLE int findThemeIndex(const QString &themeName);
    Q_INVOKABLE void setSelectedThemeDirty();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Roles::ThemeNameRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    void requestThemesListUpdate();

Q_SIGNALS:
    void themeRemoved();

private:
    QStringList possiblePathsToThemes();
    QString themePath(const QString &themeName);

    QString m_selectedTheme;
    QMap<QString, QString> m_themesList;
};

