/**************************************************************************
 *   Copyright (C) 2005-2020 by Oleksandr Shneyder                         *
 *                              <o.shneyder@phoca-gmbh.de>                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program.  If not, see <https://www.gnu.org/licenses/>. *
 ***************************************************************************/

#ifndef ONMAINWINDOWPRIVAT_H
#define ONMAINWINDOWPRIVAT_H

#include <QPainter>
#include <QTextStream>
#include <QToolButton>
#include <QTranslator>

#include <QApplication>
#include <QDesktopServices>
#include <QFile>
#include <QHBoxLayout>
#include <QScrollBar>
#include <QVBoxLayout>
#include "InteractionDialog.h"
#include "appdialog.h"
#include "exportdialog.h"
#include "helpdialog.h"
#include "onmainwindow.h"
#include "printprocess.h"
#include "userbutton.h"
#include "version.h"
#include "x2goclientconfig.h"
#include "x2goutils.h"

#include <QAction>
#include <QCheckBox>
#include <QComboBox>
#include <QDesktopWidget>
#include <QDir>
#include <QFileDialog>
#include <QGroupBox>
#include <QHeaderView>
#include <QInputDialog>
#include <QLabel>
#include <QLineEdit>
#include <QLocalSocket>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QProcess>
#include <QScrollArea>
#include <QShortcut>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QStatusBar>
#include <QTemporaryFile>
#include <QTextEdit>
#include <QTimer>
#include <QToolBar>
#include <QTreeView>
#include <QUrl>
#include "httpbrokerclient.h"
#include "x2gosettings.h"
#if QT_VERSION < 0x050000
#include <QPlastiqueStyle>
#endif
#include <QThread>
#include <QToolTip>
#include "clicklineedit.h"
#include "imgframe.h"

#include "brokerpassdlg.h"

#include "contest.h"
#include "sshmasterconnection.h"

#if !defined Q_OS_WIN
#include <sys/mount.h>
#ifdef Q_OS_LINUX
#include <X11/Xatom.h>
#include <X11/xpm.h>
#include <linux/fs.h>
#endif // Q_OS_LINUX
#endif // !defined Q_OS_WIN

#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <QCoreApplication>

#include <QDesktopWidget>

#define ldap_SUCCESS 0
#define ldap_INITERROR 1
#define ldap_OPTERROR 2
#define ldap_BINDERROR 3
#define ldap_SEARCHERROR 4
#define ldap_NOBASE 5

// LDAP attributes
#define SESSIONID "sn"
#define USERNAME "cn"
#define CLIENT "registeredAddress"
#define SERVER "postalAddress"
#define RES "title"
#define DISPLAY "street"
#define STATUS "st"
#define STARTTIME "telephoneNumber"
#define CREATTIME "telexNumber"
#define SUSPTIME "internationaliSDNNumber"

#define SESSIONCMD "o"
#define FIRSTUID "ou"
#define LASTUID "l"

#define SNDSUPPORT "sn"
#define NETSOUNDSYSTEM "o"
#define SNDSUPPORT "sn"
#define SNDPORT "ou"
#define STARTSNDSERVER "title"

#include <QDateTime>

#include <QMouseEvent>
#include "SVGFrame.h"
#include "configdialog.h"
#include "editconnectiondialog.h"
#include "folderbutton.h"
#include "sessionbutton.h"
#include "sessionexplorer.h"
#include "sessionmanagedialog.h"
#include "x2gologdebug.h"

#ifdef Q_OS_WIN
#include <QHostInfo>
#include "wapi.h"
#endif

#ifdef Q_OS_LINUX
#if QT_VERSION < 0x050000
#include <QX11Info>
#else
#include <QtX11Extras/QX11Info>
#endif
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#endif

#endif // ONMAINWINDOWPRIVAT_H
