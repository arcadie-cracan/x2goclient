//
// C++ Implementation: editconnectiondialog
//
// Description:
//
//
// Author: Oleksandr Shneyder <oleksandr.shneyder@treuchtlingen.de>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "editconnectiondialog.h"
#include "x2goclientconfig.h"
#include "x2gologdebug.h"

#include <QSettings>
#include <QFileDialog>
#include <QDir>
#include <QPushButton>
#include <QTabWidget>
#include <QBoxLayout>
#include <QFrame>
#include <QLineEdit>
#include <QPushButton>
#include <QGroupBox>
#include <QLabel>
#include <QSpinBox>
#include <QCheckBox>
#include <QSlider>
#include <QComboBox>
#include <QRadioButton>
#include <QButtonGroup>
#include <QTreeView>
#include <QStandardItemModel>
#include <QHeaderView>
#include "onmainwindow.h"
#include <QTextStream>

EditConnectionDialog::EditConnectionDialog(QString id, QWidget * par,int ind,Qt::WFlags f)
        : QDialog(par,f)
{
    QVBoxLayout* ml=new QVBoxLayout(this);
    fr=new QTabWidget(this);
    ml->addWidget(fr);

    QFrame* sessSet=new QFrame();
    QFrame* conSet=new QFrame();
    QFrame* otherSet=new QFrame();
    QFrame* exportDir=new QFrame();

    parent=(ONMainWindow*)par;

    bool miniMode=parent->retMiniMode();
    
    fr->addTab(sessSet,tr("&Session"));
    fr->addTab(conSet,tr("&Connection"));
    fr->addTab(otherSet,tr("&Settings"));
    fr->addTab(exportDir,tr("&Shared Folders"));

    QPushButton* ok=new QPushButton(tr("&OK"),this);
    QPushButton* cancel=new QPushButton(tr("&Cancel"),this);
    QPushButton* def=new QPushButton(tr("Defaults"),this);
    QHBoxLayout* bLay=new QHBoxLayout();

    bLay->setSpacing(5);
    bLay->addStretch();
    bLay->addWidget(ok);
    bLay->addWidget(cancel);
    bLay->addWidget(def);
    ml->addLayout(bLay);

    setSizeGripEnabled ( true );
    sessionId=id;


    setWindowIcon(QIcon(parent->iconsPath("/32x32/edit.png")));

    QVBoxLayout* sessLay=new QVBoxLayout(sessSet);
    sessName=new QLineEdit(sessSet);
    icon=new QPushButton(QString::null,sessSet);
    if(!miniMode)
    {
      icon->setIconSize(QSize(100,100));
      icon->setFixedSize(100,100);
    }
    else
    {
      icon->setIconSize(QSize(48,48));
      icon->setFixedSize(48,48);
    }
    icon->setFlat(true);

    QHBoxLayout* slay=new QHBoxLayout();
    slay->addWidget(new QLabel(tr("Session Name:"),sessSet));
    slay->addWidget(sessName);

    QHBoxLayout* ilay=new QHBoxLayout();
    ilay->addWidget(icon);
    ilay->addWidget(new QLabel(tr("<< change Icon"),sessSet));

    QGroupBox *sgb=new QGroupBox(tr("&Server"),sessSet);
    server=new QLineEdit(sgb);
    uname=new QLineEdit(sgb);
    sshPort=new QSpinBox(sgb);
    sshPort->setValue(parent->getDefaultSshPort().toInt());
    sshPort->setMinimum(1);
    sshPort->setMaximum(999999999);
    key=new QLineEdit(sgb);
    QPushButton* openKey=new QPushButton(QIcon(parent->iconsPath("/32x32/file-open.png")),
                                         QString::null,sgb);

    QVBoxLayout *sgbLay = new QVBoxLayout(sgb);
    QHBoxLayout *suLay =new QHBoxLayout();
    QVBoxLayout *slLay =new QVBoxLayout();
    QVBoxLayout *elLay =new QVBoxLayout();
    slLay->addWidget(new QLabel(tr("Host:"),sgb));
    slLay->addWidget(new QLabel(tr("Login:"),sgb));
    slLay->addWidget(new QLabel(tr("SSH Port:"),sgb));
    elLay->addWidget(server);
    elLay->addWidget(uname);
    elLay->addWidget(sshPort);
    suLay->addLayout(slLay);
    suLay->addLayout(elLay);

    QHBoxLayout *keyLay =new QHBoxLayout();
    keyLay->addWidget(new QLabel(tr("Use RSA/DSA key for ssh connection:"),sgb));
    keyLay->addWidget(key);
    keyLay->addWidget(openKey);

    sgbLay->addLayout(suLay);
    sgbLay->addLayout(keyLay);

    QGroupBox *deskSess=new QGroupBox(tr("&Desktop Session"),sessSet);
    cmd=new QLineEdit(deskSess);
    sessBox=new QComboBox(deskSess);
    sessBox->addItem("KDE");
    sessBox->addItem("GNOME");
    sessBox->addItem(tr("Custom"));
    QHBoxLayout* cmdLay=new QHBoxLayout(deskSess);
    cmdLay->addWidget(sessBox);
    cmdLay->addWidget(new QLabel(tr("Command:"),deskSess));
    cmdLay->addWidget(cmd);

    sessLay->addLayout(slay);
    sessLay->addLayout(ilay);
    if(!miniMode)
      sessLay->addSpacing(15);
    sessLay->addWidget(sgb);
    sessLay->addWidget(deskSess);
    sessLay->addStretch();



    QVBoxLayout *connLay=new QVBoxLayout(conSet);

    QGroupBox* netSpd=new QGroupBox(tr("&Connection Speed"),conSet);
    spd=new QSlider(Qt::Horizontal,netSpd);
    spd->setMinimum(0);
    spd->setMaximum(4);
    spd->setTickPosition(QSlider::TicksBelow);
    spd->setTickInterval(1);
    spd->setSingleStep(1);
    spd->setPageStep(1);

    QVBoxLayout *spdLay=new QVBoxLayout(netSpd);
    QHBoxLayout *tickLay=new QHBoxLayout();
    QHBoxLayout *slideLay=new QHBoxLayout();
    slideLay->addWidget(spd);
    QLabel* mlab= new QLabel("MODEM",netSpd);
    tickLay->addWidget(mlab);
    tickLay->addStretch();
    tickLay->addWidget(new QLabel("ISDN",netSpd));
    tickLay->addStretch();
    tickLay->addWidget(new QLabel("ADSL",netSpd));
    tickLay->addStretch();
    tickLay->addWidget(new QLabel("WAN",netSpd));
    tickLay->addStretch();
    tickLay->addWidget(new QLabel("LAN",netSpd));
    spdLay->addLayout(slideLay);
    spdLay->addLayout(tickLay);
    QFontMetrics fm(mlab->font());
    slideLay->insertSpacing(0,fm.width("MODEM")/2);
    slideLay->addSpacing(fm.width("LAN")/2);

    QGroupBox* compr=new QGroupBox(tr("C&ompression"),conSet);
    packMethode = new QComboBox(conSet);
    quali= new QSpinBox(conSet);
    quali->setRange(0,9);

    QHBoxLayout* comprLay=new QHBoxLayout(compr);
    QVBoxLayout* colLay=new QVBoxLayout();
    QVBoxLayout* cowLay=new QVBoxLayout();
    QHBoxLayout* spbl=new QHBoxLayout();
    colLay->addWidget(new QLabel(tr("Method:"),compr));
    colLay->addWidget(qualiLabel=new QLabel(tr("Image Quality:"),compr));
    cowLay->addWidget(packMethode);
    spbl->addWidget(quali);
    spbl->addStretch();
    cowLay->addLayout(spbl);
    comprLay->addLayout(colLay);
    comprLay->addLayout(cowLay);

    connLay->addWidget(netSpd);
    connLay->addWidget(compr);
    connLay->addStretch();


    QVBoxLayout* setLay=new QVBoxLayout(otherSet);

    QGroupBox *dgb=new QGroupBox(tr("&Display"),otherSet);
    QButtonGroup* radio = new QButtonGroup(dgb);

    fs=new QRadioButton(tr("Fullscreen"),dgb);
    custom=new QRadioButton(tr("Custom"),dgb);
    radio->addButton(fs);
    radio->addButton(custom);
    radio->setExclusive(true);
    width=new QSpinBox(dgb);
    height=new QSpinBox(dgb);
    QVBoxLayout *dbLay = new QVBoxLayout(dgb);
    QHBoxLayout *dgLay =new QHBoxLayout();
    QHBoxLayout *dwLay =new QHBoxLayout();

    dgLay->addWidget(fs);
    dgLay->addStretch();

    dwLay->addWidget(custom);
    dwLay->addSpacing(15);
    dwLay->addWidget(widthLabel=new QLabel(tr("Width:"),dgb));
    dwLay->addWidget(width);
    width->setRange(0,10000);
    dwLay->addWidget(heightLabel=new QLabel(tr("Height:"),dgb));
    dwLay->addWidget(height);
    height->setRange(0,10000);
    dwLay->addStretch();
    dbLay->addLayout(dgLay);
    dbLay->addLayout(dwLay);


    QGroupBox *kgb=new QGroupBox(tr("&Keyboard"),otherSet);

    kbd=new QCheckBox(tr("Keep current Keyboard Settings"),kgb);
    layout=new QLineEdit(kgb);
    type=new QLineEdit(kgb);
    QVBoxLayout *kbLay = new QVBoxLayout(kgb);

    QVBoxLayout *klLay = new QVBoxLayout();
    QVBoxLayout *kwLay = new QVBoxLayout();
    QHBoxLayout *ksLay = new QHBoxLayout();

    klLay->addWidget(layoutLabel= new QLabel(tr("Keyboard Layout:"),kgb));
    klLay->addWidget(typeLabel= new QLabel(tr("Keyboard Model:"),kgb));

    kwLay->addWidget(layout);
    kwLay->addWidget(type);

    ksLay->addLayout(klLay);
    ksLay->addLayout(kwLay);

    kbLay->addWidget(kbd);
    kbLay->addLayout(ksLay);


    QGroupBox *sbgr=new QGroupBox(tr("Sound"),otherSet);
    sound=new QCheckBox(tr("Enable Sound Support"),sbgr);
    QVBoxLayout* sLay=new QVBoxLayout(sbgr);
    sLay->addWidget(sound);
    QButtonGroup* sndsys=new QButtonGroup;
    arts=new QRadioButton("arts",sbgr);
    esd=new QRadioButton("esd",sbgr);
    sndsys->addButton(arts);
    sndsys->addButton(esd);
    sLay->addWidget(sound);
    sLay->addWidget(arts);
    sLay->addWidget(esd);

    setLay->addWidget(dgb);
    setLay->addWidget(kgb);
    setLay->addWidget(sbgr);
    setLay->addStretch();





    QGroupBox *egb=new QGroupBox(tr("&Folders"),exportDir);

    expTv=new QTreeView(egb);
    expTv->setItemsExpandable(false);
    expTv->setRootIsDecorated(false);

    model=new QStandardItemModel(0,2);
    ldir=new QLabel(egb);


    model->setHeaderData(0,Qt::Horizontal,QVariant((QString)tr("Path")));
    model->setHeaderData(1,Qt::Horizontal,QVariant((QString)tr("Automount")));
    expTv->setEditTriggers(QAbstractItemView::NoEditTriggers);



    QPushButton* openDir=new QPushButton(QIcon(parent->iconsPath("/32x32/file-open.png")),
                                         QString::null,egb);


    QPushButton* addDir=new QPushButton(tr("Add"),egb);
    QPushButton* delDir=new QPushButton(tr("Delete"),egb);


    QLabel *dirPrompt=new QLabel(tr("Path:"),egb);
    dirPrompt->setFixedSize(dirPrompt->sizeHint());
    openDir->setFixedSize(openDir->sizeHint());

    ldir->setFrameStyle(QFrame::StyledPanel|QFrame::Sunken);



    QVBoxLayout* expLay=new QVBoxLayout(exportDir);
    expLay->addWidget(egb);

    QHBoxLayout *tvLay=new QHBoxLayout(egb);

    QHBoxLayout *dirLAy=new QHBoxLayout();
    dirLAy->addWidget(dirPrompt);
    dirLAy->addWidget(ldir);
    dirLAy->addWidget(openDir);

    QVBoxLayout* leftLay=new QVBoxLayout();
    leftLay->addLayout(dirLAy);
    leftLay->addSpacing(10);
    leftLay->addWidget(expTv);

    QVBoxLayout* rightLay=new QVBoxLayout();
    rightLay->addWidget(addDir);
    rightLay->addStretch();
    rightLay->addWidget(delDir);
    rightLay->addStretch();


    tvLay->addLayout(leftLay);
    tvLay->addSpacing(10);
    tvLay->addLayout(rightLay);



    expTv->setModel((QAbstractItemModel*) model);
    QFontMetrics fm1(expTv->font());
    expTv->header()->resizeSection(1,fm1.width(tr("Automount"))+10);


    connect(sessName,SIGNAL(textChanged(const QString &)),this,
            SLOT(slot_changeCaption( const QString&)));
    connect(this,SIGNAL(accepted()),this,SLOT(slot_accepted()));
    connect(ok,SIGNAL(clicked()),this,SLOT(accept()));
    connect(cancel,SIGNAL(clicked()),this,SLOT(reject()));
    connect(def,SIGNAL(clicked()),this,SLOT(slot_default()));
    connect(icon,SIGNAL(clicked()),this,SLOT(slot_getIcon()));
    connect(openKey,SIGNAL(clicked()),this,SLOT(slot_getKey()));
    connect(openDir,SIGNAL(clicked()),this,SLOT(slot_openDir()));
    connect(addDir,SIGNAL(clicked()),this,SLOT(slot_addDir()));
    connect(delDir,SIGNAL(clicked()),this,SLOT(slot_delDir()));

    connect(custom,SIGNAL(toggled(bool)),width,SLOT(setEnabled(bool)));
    connect(custom,SIGNAL(toggled(bool)),height,SLOT(setEnabled(bool)));
    connect(custom,SIGNAL(toggled(bool)),widthLabel,SLOT(setEnabled(bool)));
    connect(custom,SIGNAL(toggled(bool)),heightLabel,SLOT(setEnabled(bool)));

    
    connect(kbd,SIGNAL(toggled(bool)),layout,SLOT(setDisabled(bool)));
    connect(kbd,SIGNAL(toggled(bool)),layoutLabel,SLOT(setDisabled(bool)));
    connect(kbd,SIGNAL(toggled(bool)),type,SLOT(setDisabled(bool)));
    connect(kbd,SIGNAL(toggled(bool)),typeLabel,SLOT(setDisabled(bool)));

    connect(packMethode,SIGNAL(activated(const QString&)),this,
            SLOT(slot_changePack( const QString&)));

    connect(sessBox,SIGNAL(activated(int)),this,
            SLOT(slot_changeCmd( int)));
    
    connect(sound,SIGNAL(toggled(bool)),arts,SLOT(setEnabled(bool)));
    connect(sound,SIGNAL(toggled(bool)),esd,SLOT(setEnabled(bool)));

    
    kbd->setChecked(true);
    custom->setChecked(true);
    ok->setDefault(true);

    readConfig();
    fr->setCurrentIndex(ind);
}


EditConnectionDialog::~EditConnectionDialog()
{}


void EditConnectionDialog::readConfig()
{

    loadPackMethods();
#ifndef WINDOWS
    QSettings st(QDir::homePath()+"/.x2goclient/sessions",QSettings::NativeFormat);
#else
    QSettings st("Obviously Nice","x2goclient");
    st.beginGroup("sessions");
#endif
    sessName->setText(st.value(sessionId+"/name",(QVariant)tr("New Session")).toString());
    sessIcon=st.value(sessionId+"/icon",
                      (QVariant)":icons/128x128/x2gosession.png").toString();
    icon->setIcon(QIcon(sessIcon));

    server->setText(st.value(sessionId+"/host",(QVariant)QString::null).toString());
    uname->setText(st.value(sessionId+"/user",(QVariant)QString::null).toString());
    key->setText(st.value(sessionId+"/key",(QVariant)QString::null).toString());
    sshPort->setValue(st.value(sessionId+"/sshport",
		      (QVariant)parent->getDefaultSshPort().toInt()).toInt());
    QString
    command=st.value(sessionId+"/command",(QVariant)parent->getDefaultCmd()).toString();
    if(command=="KDE")
    {
        cmd->setText("startkde");
        sessBox->setCurrentIndex(0);
        cmd->setEnabled(false);
    }
    else if(command=="GNOME")
    {
        cmd->setText("gnome-session");
        sessBox->setCurrentIndex(1);
        cmd->setEnabled(false);
    }
    else
    {
        cmd->setText(command);
        sessBox->setCurrentIndex(2);
        cmd->setEnabled(true);
    }
    if(sessName->text()==tr("New Session"))
    {
        sessName->selectAll();
        sessName->setFocus();
    }

    spd->setValue(st.value(sessionId+"/speed",(QVariant)parent->getDefaultLink()).toInt());
    QString mt=st.value(sessionId+"/pack",(QVariant)parent->getDefaultPack()).toString();


    packMethode->setCurrentIndex(packMethode->findText(mt));
    quali->setValue(st.value(sessionId+"/quality",parent->getDefaultQuality()).toInt());
    slot_changePack(mt);


    fs->setChecked(st.value(sessionId+"/fullscreen",
                            (QVariant)parent->getDefaultFullscreen()).toBool());

    custom->setChecked(! st.value(sessionId+"/fullscreen",
                                  (QVariant)parent->getDefaultFullscreen()).toBool());


    width->setValue(st.value(sessionId+"/width",(QVariant)parent->getDefaultWidth()).toInt());
    height->setValue(st.value(sessionId+"/height",(QVariant)parent->getDefaultHeight()).toInt());

    kbd->setChecked(!st.value(sessionId+"/usekbd",(QVariant)parent->getDefaultSetKbd()).toBool());
    layout->setText(st.value(sessionId+"/layout",(QVariant)parent->getDefaultLayout()).toString());
    type->setText(st.value(sessionId+"/type",(QVariant)parent->getDefaultKbdType()).toString());
    bool snd=st.value(sessionId+"/sound",(QVariant)parent->getDefaultUseSound()).toBool();
    QString sndsys=st.value(sessionId+"/soundsystem","arts").toString();
    if(sndsys=="esd")
	    esd->setChecked(true);
    else
	    arts->setChecked(true);
    sound->setChecked(snd);
    arts->setEnabled(snd);
    esd->setEnabled(snd);
    QString exportDir=st.value(sessionId+"/export",(QVariant)QString::null).toString();

    QStringList lst=exportDir.split(";",QString::SkipEmptyParts);
    for(int i=0;i<lst.size();++i)
    {
#ifndef WINDOWS    
        QStringList tails=lst[i].split(":",QString::SkipEmptyParts);
#else
        QStringList tails=lst[i].split("#",QString::SkipEmptyParts);
#endif
        QStandardItem *item;
        item= new QStandardItem(tails[0]);
        model->setItem(model->rowCount(),0,item);
        item= new QStandardItem();
        item->setCheckable(true);
	if(tails[1]=="1")
	     item->setCheckState(Qt::Checked);
        model->setItem(model->rowCount()-1,1,item);
    }
}


void EditConnectionDialog::slot_changeCaption(const QString& newName)
{
    setWindowTitle(tr("Session Preferences - ")+newName);
}


void EditConnectionDialog::loadPackMethods()
{
    QFile file(":/txt/packs");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString pc=in.readLine();
        if(pc.indexOf("-%")!=-1)
        {
            pc=pc.left(pc.indexOf("-%"));
            qualiList<<pc;
        }
        packMethode->addItem(pc);
    }
    file.close();
}


void EditConnectionDialog::slot_changePack(const QString& pc)
{
    bool ct=qualiList.contains(pc);
    quali->setEnabled(ct);
    qualiLabel->setEnabled(ct);
}


void EditConnectionDialog::slot_getIcon()
{
    QString path= QFileDialog::getOpenFileName(
                      this,
                      tr("Open Picture"),
                      QDir::homePath(),
                      tr("Pictures") +" (*.png *.xpm *.jpg)");
    if(path!=QString::null)
    {
        sessIcon=path;
        icon->setIcon(QIcon(sessIcon));
    }
}

void EditConnectionDialog::slot_getKey()
{
    QString path= QFileDialog::getOpenFileName(
                      this,
                      tr("Open Key File"),
                      QDir::homePath(),
                      tr("All Files") +" (*)");
    if(path!=QString::null)
    {
        key->setText(path);
    }
}


void EditConnectionDialog::slot_accepted()
{

#ifndef WINDOWS
    QSettings st(QDir::homePath()+"/.x2goclient/sessions",QSettings::NativeFormat);
#else
    QSettings st("Obviously Nice","x2goclient");
    st.beginGroup("sessions");
#endif
    st.setValue(sessionId+"/name",(QVariant)sessName->text());
    st.setValue(sessionId+"/icon",(QVariant)sessIcon);
    st.setValue(sessionId+"/host",(QVariant)server->text());
    st.setValue(sessionId+"/user",(QVariant)uname->text());
    st.setValue(sessionId+"/key",(QVariant)key->text());
    st.setValue(sessionId+"/sshport",(QVariant)sshPort->value());
    QString command;
    if(sessBox->currentIndex()!=2)
        command=sessBox->currentText();
    else
        command=cmd->text();
    if(command=="startkde")
        command="KDE";
    if(command=="gnome-session")
        command="GNOME";

    st.setValue(sessionId+"/command",(QVariant)command);
    st.setValue(sessionId+"/speed",(QVariant)spd->value());
    st.setValue(sessionId+"/pack",(QVariant)packMethode->currentText());
    st.setValue(sessionId+"/quality",(QVariant)quali->value());
    st.setValue(sessionId+"/fullscreen",(QVariant)fs->isChecked());
    st.setValue(sessionId+"/width",(QVariant)width->value());
    st.setValue(sessionId+"/height",(QVariant)height->value());
    st.setValue(sessionId+"/usekbd",(QVariant)!kbd->isChecked());
    st.setValue(sessionId+"/layout",(QVariant)layout->text());
    st.setValue(sessionId+"/type",(QVariant)type->text());
    st.setValue(sessionId+"/sound",(QVariant)sound->isChecked());
    QString sndsys=(arts->isChecked())?"arts":"esd";    
    st.setValue(sessionId+"/soundsystem",(QVariant)sndsys);


    QString exportDirs;
    for(int i=0;i<model->rowCount();++i)
    {
#ifndef WINDOWS    
        exportDirs+=model->index(i,0).data().toString()+":";
#else
        exportDirs+=model->index(i,0).data().toString()+"#";
#endif
    
        if(model->item(i,1)->checkState()==Qt::Checked)
            exportDirs+="1;";
        else
            exportDirs+="0;";
    }
    st.setValue(sessionId+"/export",(QVariant)exportDirs);
    st.sync();
}


void EditConnectionDialog::slot_default()
{
    switch(fr->currentIndex())
    {
    case 0:
        {
            cmd->setText("startkde");
            sessBox->setCurrentIndex(0);
            cmd->setEnabled(false);
            sessIcon=":icons/128x128/x2gosession.png";
            icon->setIcon(QIcon(sessIcon));
	    sshPort->setValue(parent->getDefaultSshPort().toInt());
        }
        break;
    case 1:
        {
            spd->setValue(2);
            packMethode->setCurrentIndex(packMethode->findText("16m-jpeg"));
            quali->setValue(9);
            slot_changePack("16m-jpeg");
        }
        break;
    case 2:
        {
            fs->setChecked(false);
            custom->setChecked(true);
            width->setValue(800);
            height->setValue(600);

            kbd->setChecked(true);
            layout->setText(tr("us"));
            type->setText(tr("pc105/us"));
            sound->setChecked(true);
        }
        break;
    }
}

void EditConnectionDialog::slot_changeCmd(int var)
{
    if(var==2)
    {
        cmd->setEnabled(true);
        cmd->selectAll();
        cmd->setFocus();
    }
    else
    {
        if(var==0)
            cmd->setText("startkde");
        else
            cmd->setText("gnome-session");
        cmd->setEnabled(false);
    }
}




void EditConnectionDialog::slot_openDir()
{
    QString path= QFileDialog::getExistingDirectory(
                      this,
                      tr("Select Folder"),
                      QDir::homePath());
    if(path!=QString::null)
    {
        ldir->setText(path);
    }
}


void EditConnectionDialog::slot_addDir()
{
    QString path=ldir->text();
    if(path.length()<1)
        return;
    for(int i=0;i<model->rowCount();++i)
        if(model->index(i,0).data().toString()==path)
            return;
    QStandardItem *item;
    item= new QStandardItem(path);
    model->setItem(model->rowCount(),0,item);
    item= new QStandardItem();
    item->setCheckable(true);
    model->setItem(model->rowCount()-1,1,item);
    ldir->setText(QString::null);
}


void EditConnectionDialog::slot_delDir()
{
    model->removeRow(expTv->currentIndex().row());
}
