# Override settings specified in x2goclient.pro here.
win32 {
  LIBS += -L$$PWD/../x2goclient-contrib/libssh/0.9.8-x2go1-msvc_bin/lib/ -lssh
  INCLUDEPATH += $$PWD/../x2goclient-contrib/libssh/0.9.8-x2go1-msvc_bin/include
  DEPENDPATH += $$PWD/../x2goclient-contrib/libssh/0.9.8-x2go1-msvc_bin/include
}
