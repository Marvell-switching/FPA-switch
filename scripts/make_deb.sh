#!/bin/bash
# 1 - output directory
# 2 - lib version
# 3 - fpa release

LIB_NAME="mrvllibfpa_$2"
pushd $1 > /dev/null

if [ ! -d "$LIB_NAME/usr/lib" ]; then
        mkdir -p $LIB_NAME/usr/lib
fi
cp lib/libfpa.so $LIB_NAME/usr/lib/

if [ ! -d "$LIB_NAME/DEBIAN" ]; then
        mkdir -p $LIB_NAME/DEBIAN
        echo "package: mrvllibfpa"                          >> $LIB_NAME/DEBIAN/control
        echo "Version: $2"                                  >> $LIB_NAME/DEBIAN/control
        echo "Section: base"                                >> $LIB_NAME/DEBIAN/control
        echo "Priority: optional"                           >> $LIB_NAME/DEBIAN/control
        echo "Architecture: amd64"                          >> $LIB_NAME/DEBIAN/control
        echo "Depends:"                                     >> $LIB_NAME/DEBIAN/control
        echo "Description: Marvell FPA driver"              >> $LIB_NAME/DEBIAN/control
        echo " based on FPA v$3"                            >> $LIB_NAME/DEBIAN/control
        echo "Maintainer: Ziv Erlichson <zive@marvell.com>" >> $LIB_NAME/DEBIAN/control
fi
dpkg-deb --build $LIB_NAME/
popd > /dev/null

