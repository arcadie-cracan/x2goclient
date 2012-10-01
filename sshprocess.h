
/***************************************************************************
 *   Copyright (C) 2005-2012 by Oleksandr Shneyder   *
 *   oleksandr.shneyder@obviously-nice.de   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef SSHPROCESS_H
#define SSHPROCESS_H

#include <libssh/libssh.h>
#include <QObject>

#ifndef Q_OS_WIN
#include <netinet/in.h>
#endif

#include "sshmasterconnection.h"


class SshProcess : public QObject
{
    Q_OBJECT
    friend class SshMasterConnection;
private:

    SshProcess(SshMasterConnection* master, int pid);
    ~SshProcess();

    void startNormal(const QString& cmd);
    void startTunnel(const QString& forwardHost, uint forwardPort, const QString& localHost,
                     uint localPort, bool reverse=false);
    void start_cp(QString src, QString dst);
    QString getSource()
    {
        return scpSource;
    }

    void tunnelLoop();

private:
    SshMasterConnection* masterCon;
    SshMasterConnection* tunnelConnection;
    int pid;
    QString forwardHost;
    QString localHost;
    QString command;
    QString scpSource;
    quint16 forwardPort;
    quint16 localPort;
    uint serverSocket;
    struct sockaddr_in address;
#ifndef  Q_OS_WIN
    socklen_t addrlen;
#else
    int addrlen;
#endif
    QString stdOutString;
    QString stdErrString;
    QString abortString;
    bool tunnel;
    bool normalExited;


private slots:
    void slotCheckNewConnection();
    void slotStdErr(SshProcess* creator, QByteArray data);
    void slotStdOut(SshProcess* creator, QByteArray data);
    void slotIOerr(SshProcess* creator,QString message, QString sshSessionErr);
    void slotChannelClosed(SshProcess* creator);
    void slotReverseTunnelOk(SshProcess* creator);
    void slotCopyOk(SshProcess* creator);
    void slotCopyErr(SshProcess* creator,QString message, QString sshSessionErr);
signals:
    void sshFinished ( bool result, QString output, int processId);
    void sshTunnelOk(int processId);
};

#endif // SSHPROCESS_H
