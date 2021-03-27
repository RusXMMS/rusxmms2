#! /bin/bash

TOP_DIR=`pwd | sed -e s/\\\/RusXMMS2$//`
if [ ! -d $TOP_DIR/RusXMMS2 ]; then
    PATCH_DIR=$TOP_DIR/../
    if [ ! -d $PATCH_DIR/RusXMMS2 ]; then
	exit 1
    fi
else
    PATCH_DIR=$TOP_DIR
fi

if [ ! -d $TOP_DIR/libxmms ]; then
    exit 1
fi

echo "Patching: $TOP_DIR"

cp $PATCH_DIR/RusXMMS2/source/* $TOP_DIR/libxmms/

# ID3 fixes
cat $PATCH_DIR/RusXMMS2/3rdparty/mpg123/*.patch | patch -d $TOP_DIR -p1
if [ $? -ne 0 ]; then echo -e "\n[01;31mFailed:[00m *** gentoo mpg123 patches ***"; exit 1; fi

# RusXMMS core
cat $PATCH_DIR/RusXMMS2/patches/xmms-ds-rusxmms.patch | patch -d $TOP_DIR -p1
if [ $? -ne 0 ]; then echo -e "\n[01;31mFailed:[00m *** xmms-ds-rusxmms ***"; exit 1; fi
cat $PATCH_DIR/RusXMMS2/patches/xmms-ds-rusxmms-charset.patch | patch -d $TOP_DIR -p1
if [ $? -ne 0 ]; then echo -e "\n[01;31mFailed:[00m *** xmms-ds-rusxmms-charset ***"; exit 1; fi

# RusXMMS plugins
cat $PATCH_DIR/RusXMMS2/patches/plugins/xmms-ds-mpg123.patch | patch -d $TOP_DIR -p1
if [ $? -ne 0 ]; then echo -e "\n[01;31mFailed:[00m *** xmms-ds-mpg123 ***"; exit 1; fi
cat $PATCH_DIR/RusXMMS2/patches/plugins/xmms-ds-mpg123-editor.patch | patch -d $TOP_DIR -p1
if [ $? -ne 0 ]; then echo -e "\n[01;31mFailed:[00m *** xmms-ds-mpg123-editor ***"; exit 1; fi
cat $PATCH_DIR/RusXMMS2/patches/plugins/xmms-ds-mpg123-editor-keys.patch | patch -d $TOP_DIR -p1
if [ $? -ne 0 ]; then echo -e "\n[01;31mFailed:[00m *** xmms-ds-mpg123-editor-keys ***"; exit 1; fi
cat $PATCH_DIR/RusXMMS2/patches/plugins/xmms-ds-vorbis-editor.patch | patch -d $TOP_DIR -p1
if [ $? -ne 0 ]; then echo -e "\n[01;31mFailed:[00m *** xmms-ds-vorbis-editor ***"; exit 1; fi
cat $PATCH_DIR/RusXMMS2/patches/plugins/xmms-ds-vorbis-editor-keys.patch | patch -d $TOP_DIR -p1
if [ $? -ne 0 ]; then echo -e "\n[01;31mFailed:[00m *** xmms-ds-vorbis-editor-keys ***"; exit 1; fi

# RusXMMS extra
cat $PATCH_DIR/RusXMMS2/patches/xmms-ds-playlist.patch | patch -d $TOP_DIR -p1
if [ $? -ne 0 ]; then echo -e "\n[01;31mFailed:[00m *** xmms-ds-playlist ***"; exit 1; fi
cat $PATCH_DIR/RusXMMS2/patches/xmms-ds-shade.patch | patch -d $TOP_DIR -p1
if [ $? -ne 0 ]; then echo -e "\n[01;31mFailed:[00m *** xmms-ds-shade ***"; exit 1; fi
cat $PATCH_DIR/RusXMMS2/patches/xmms-ds-textbox.patch | patch -d $TOP_DIR -p1
if [ $? -ne 0 ]; then echo -e "\n[01;31mFailed:[00m *** xmms-ds-textbox ***"; exit 1; fi

