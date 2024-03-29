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

#include "connectionwidget.h"

#include <QBoxLayout>
#include <QComboBox>
#include <QDir>
#include <QFile>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QSlider>
#include <QSpinBox>
#include <QStringList>
#include <QTextStream>
#include "onmainwindow.h"
#include "x2gosettings.h"
ConnectionWidget::ConnectionWidget(QString id, ONMainWindow *mw, QWidget *parent, Qt::WindowFlags f)
    : ConfigWidget(id, mw, parent, f)
{
    QVBoxLayout *connLay = new QVBoxLayout(this);
#ifndef Q_WS_HILDON
    QGroupBox *netSpd = new QGroupBox(tr("&Connection speed"), this);
    QVBoxLayout *spdLay = new QVBoxLayout(netSpd);
#else
    QFrame *netSpd = this;
    QVBoxLayout *spdLay = new QVBoxLayout();
    spdLay->addWidget(new QLabel(tr("Connection speed:"), netSpd));
#endif
    spd = new QSlider(Qt::Horizontal, netSpd);
    spd->setMinimum(0);
    spd->setMaximum(4);
    spd->setTickPosition(QSlider::TicksBelow);
    spd->setTickInterval(1);
    spd->setSingleStep(1);
    spd->setPageStep(1);

    QHBoxLayout *tickLay = new QHBoxLayout();
    QHBoxLayout *slideLay = new QHBoxLayout();
    slideLay->addWidget(spd);
    QLabel *mlab = new QLabel("MODEM", netSpd);
    tickLay->addWidget(mlab);
    tickLay->addStretch();
    tickLay->addWidget(new QLabel("ISDN", netSpd));
    tickLay->addStretch();
    tickLay->addWidget(new QLabel("ADSL", netSpd));
    tickLay->addStretch();
    tickLay->addWidget(new QLabel("WAN", netSpd));
    tickLay->addStretch();
    tickLay->addWidget(new QLabel("LAN", netSpd));
    spdLay->addLayout(slideLay);
    spdLay->addLayout(tickLay);
    QFontMetrics fm(mlab->font());
    slideLay->insertSpacing(0, fm.horizontalAdvance("MODEM") / 2);
    slideLay->addSpacing(fm.horizontalAdvance("LAN") / 2);

#ifndef Q_WS_HILDON
    QGroupBox *compr = new QGroupBox(tr("C&ompression"), this);
    QHBoxLayout *comprLay = new QHBoxLayout(compr);
#else
    QFrame *compr = this;
    QHBoxLayout *comprLay = new QHBoxLayout();
#endif
    packMethode = new QComboBox(this);
    quali = new QSpinBox(this);
    quali->setRange(0, 9);
#ifdef Q_WS_HILDON
    quali->setFixedHeight(int(quali->sizeHint().height() * 1.5));
#endif

    QVBoxLayout *colLay = new QVBoxLayout();
    QVBoxLayout *cowLay = new QVBoxLayout();
    QHBoxLayout *spbl = new QHBoxLayout();
#ifndef Q_WS_HILDON
    colLay->addWidget(new QLabel(tr("Method:"), compr));
#else
    colLay->addWidget(new QLabel(tr("Compression method:"), compr));
#endif
    colLay->addWidget(qualiLabel = new QLabel(tr("Image quality:"), compr));
    cowLay->addWidget(packMethode);
    spbl->addWidget(quali);
    spbl->addStretch();
    cowLay->addLayout(spbl);
    comprLay->addLayout(colLay);
    comprLay->addLayout(cowLay);
#ifndef Q_WS_HILDON
    connLay->addWidget(netSpd);
    connLay->addWidget(compr);
#else
    connLay->addLayout(spdLay);
    connLay->addLayout(comprLay);
#endif
    connLay->addStretch();

    connect(packMethode,
            SIGNAL(activated(const QString &)),
            this,
            SLOT(slot_changePack(const QString &)));
    readConfig();
}

ConnectionWidget::~ConnectionWidget() {}

void ConnectionWidget::loadPackMethods()
{
    QFile file(":/txt/packs");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString pc = in.readLine();
        if (pc.indexOf("-%") != -1) {
            pc = pc.left(pc.indexOf("-%"));
            qualiList << pc;
        }
        packMethode->addItem(pc);
    }
    file.close();
}

void ConnectionWidget::slot_changePack(const QString &pc)
{
    bool ct = qualiList.contains(pc);
    quali->setEnabled(ct);
    qualiLabel->setEnabled(ct);
}

void ConnectionWidget::readConfig()
{
    loadPackMethods();
    X2goSettings st("sessions");

    spd->setValue(
        st.setting()->value(sessionId + "/speed", (QVariant) mainWindow->getDefaultLink()).toInt());
    QString mt = st.setting()
                     ->value(sessionId + "/pack", (QVariant) mainWindow->getDefaultPack())
                     .toString();

    packMethode->setCurrentIndex(packMethode->findText(mt));
    quali->setValue(
        st.setting()->value(sessionId + "/quality", mainWindow->getDefaultQuality()).toInt());
    slot_changePack(mt);
}

void ConnectionWidget::setDefaults()
{
    spd->setValue(2);
    packMethode->setCurrentIndex(packMethode->findText("16m-jpeg"));
    quali->setValue(9);
    slot_changePack("16m-jpeg");
}

void ConnectionWidget::saveSettings()
{
    X2goSettings st("sessions");
    st.setting()->setValue(sessionId + "/speed", (QVariant) spd->value());
    st.setting()->setValue(sessionId + "/pack", (QVariant) packMethode->currentText());
    st.setting()->setValue(sessionId + "/quality", (QVariant) quali->value());
    st.setting()->sync();
}
