/*
 * Copyright 2013 Canonical Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef UBUNTUAPPLICATIONAPIWRAPPER_H
#define UBUNTUAPPLICATIONAPIWRAPPER_H

#include <QObject>
#include <QLocalServer>
#include <QLocalSocket>

/*
 * Class: UbuntuApplicationApiWrapper
 * The OSK-related functions in the ubuntu application api are marked as deprecated.
 * To ensure OSK works on platforms with & without (i.e. Mir), check which platform
 * we are running on: if SurfaceFlinger-based, call the deprecated API, else NOOP.
 *
 * Have added other little methods to help smooth the transition.
 */

class UbuntuApplicationApiWrapper : public QObject
{
    Q_OBJECT
public:
    UbuntuApplicationApiWrapper();

    int oskWindowRole() const;

    void reportOSKVisible(const int, const int, const int, const int);
    void reportOSKInvisible();

private Q_SLOTS:
    void onNewConnection();
    void onClientDisconnected();

private:
    // NB! Must match the definition in unity-mir. Not worth creating a shared header
    // just for that.
    struct SharedInfo {
        qint32 keyboardWidth;
        qint32 keyboardHeight;

        bool operator ==(const struct SharedInfo &other);
        void reset();
    };
    void sendInfoToClientConnection(int width, int height);
    void startLocalServer();

    bool m_runningOnMir;
    QLocalServer m_localServer;
    QLocalSocket *m_clientConnection;
    struct SharedInfo m_lastInfoShared;
};

#endif // UBUNTUAPPLICATIONAPIWRAPPER_H
