#!/bin/bash

projectname=$1
targetdirectory=$2

if [ -z $targetdirectory ]; then
	echo "Missing targetdirectory"
	exit 1
fi

if [ -z $projectname ]; then
	echo "Missing projectname"
	exit 1
fi

#build root
mkdir $targetdirectory$projectname
#build /assets
mkdir $targetdirectory$projectname/assets
#build /src
mkdir $targetdirectory$projectname/src
#build src/objects
mkdir $targetdirectory$projectname/src/objects
#build src/factories
mkdir $targetdirectory$projectname/src/factories
#build /logs
mkdir $targetdirectory$projectname/logs
#build /bin
mkdir $targetdirectory$projectname/bin

#build default main.cpp
cp ../src/main.cpp $targetdirectory$projectname/src/main.cpp
#build config.ini
cp defaultConfig.ini $targetdirectory$projectname/config.ini
#build makefile
cp defaultMakeFile $targetdirectory$projectname/makefile
