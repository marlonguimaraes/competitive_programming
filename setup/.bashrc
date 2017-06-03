alias ct="cp ~/cp/template/template.cpp ."

function cpy() {
	cat $1 | xclip -selection c
}

function cr() {
	mkdir $1
	cd $1
	ct
	mv template.cpp $1.cpp
#xdotool key ctrl+shift+t
#xdotool key ctrl+Page_Up
#xdotool key F11
	vim $1.cpp
}

function mask() {
	FILE=$1
	FILE=${FILE#.\/}
	FILE=${FILE%.cpp}
	echo $FILE
}

function cmp() {
	CPP_FILE="$(find -name '*.cpp')"
	BIN_FILE="prog"
	g++ $CPP_FILE -o $BIN_FILE -Wshadow -Wall -fsanitize=address -std=c++11
}

function gen() {
	CPP_FILE="$(find -name '*.cpp')"
	FILE="$(mask $CPP_FILE)"
	
	IN_FILE=$FILE"_in"
	ANS_FILE=$FILE"_ans"
	
	cat $IN_FILE | ./$FILE > $ANS_FILE
}

function check() {
	CPP_FILE="$(find -name '*.cpp')"
	FILE="$(mask $CPP_FILE)"

	OUT_FILE=$FILE"_out"
	ANS_FILE=$FILE"_ans"

	diff $ANS_FILE $OUT_FILE
}

function roll() {
	cmp
	gen
	check
}


mkcd () {
  mkdir "$1"
    cd "$1"
}
