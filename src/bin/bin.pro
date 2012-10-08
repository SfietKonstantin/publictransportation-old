TEMPLATE = subdirs
SUBDIRS = provider

contains(CONFIG, mobile): SUBDIRS += mobile
!contains(CONFIG, mobile): SUBDIRS += desktop
