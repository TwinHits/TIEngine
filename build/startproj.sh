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
#build /assets/textures
mkdir $targetdirectory$projectname/assets/textures
#build /assets/audio
mkdir $targetdirectory$projectname/assets/audio
#build /src
mkdir $targetdirectory$projectname/src
#build src/objects
mkdir $targetdirectory$projectname/src/objects
#build src/factories
mkdir $targetdirectory$projectname/src/factories
#build src/managers
mkdir $targetdirectory$projectname/src/managers
#build /logs
mkdir $targetdirectory$projectname/logs
#build /bin
mkdir $targetdirectory$projectname/bin
#build /bin/objs
mkdir $targetdirectory$projectname/bin/objs

#build default main.cpp
cp ../src/main.cpp $targetdirectory$projectname/src/main.cpp
#build config.ini
cp defaultConfig.ini $targetdirectory$projectname/config.ini
#build makefile
cp defaultMakeFile $targetdirectory$projectname/makefile
#build .gitignore
cp defaultGitIgnore $targetdirectory$projectname/.gitignore
