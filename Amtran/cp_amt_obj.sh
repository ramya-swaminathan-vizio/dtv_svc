#!/bin/sh

DATE_STR=`date +"%Y%m%d"`
PATCH_FOLDER=~/mergeback/amtran_patch_$DATE_STR/new/apollo/custom/Vizio/Amtran

PLATFORM=MT5597_CAST_E_M
PRJ_ROOT=../../..
AMT_DIR=$PRJ_ROOT/output/Vizio_linux/$PLATFORM/rel/obj/phase2_all/custom/Vizio/Amtran



echo "# 1) Make sure FAC_CMD_REVISION has been updated in the latest revision change"
LAST_CHG=`svn info $PRJ_ROOT | grep "Last Changed Rev:"`
LAST_FAC_CHG=`svn info factory/factory.c | grep "Last Changed Rev:"`

LAST_FAC_CHG=$LAST_CHG
if [ "$LAST_CHG" != "$LAST_FAC_CHG" ] ; then
    echo "Warnning: Are you sure FAC_CMD_REVISION has been updated?"
    exit
fi

echo "The FAC_CMD_REVISION is `grep "#define FAC_CMD_REVISION" ./factory/factory.c | awk '{print $3}'`"

echo "# 2) Generate patch folder: $PATCH_FOLDER"
mkdir -p $PATCH_FOLDER

echo "# 3) Copy new .o files to current path"
pushd $AMT_DIR 1>/dev/null
ALL_OBJS=`find . -name *.o`
popd 1>/dev/null

for i in $ALL_OBJS
do
  FILE_DIR=`dirname $i`
  cp -v $AMT_DIR/$i $FILE_DIR
done

echo "# 4) cp Amtran folder to patch folder"
cp -r ./* $PATCH_FOLDER

echo "# 5) rm all *.c files"
find $PATCH_FOLDER -name *.c -exec rm {} \;
