#!/bin/sh
cp qtc_packaging/debian_harmattan debian -R
cp debian/rules-obs debian/rules -f
/opt/QtSDK/Madde/bin/mad -t harmattan_10.2011.34-1_rt1.2 dpkg-buildpackage -sa -S -uc -us -Imoc -Iobj -Ircc -Iui -I.svn -I.git -I*.deb -I*.changes -Iqtc_packaging -Ibuild -Iinstall -IMakefile -I*.pro.user -Iautoobs.sh
rm debian -R
