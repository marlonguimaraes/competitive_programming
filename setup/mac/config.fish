# CP
function mkcd
    mkdir $argv
    cd $argv
end

alias ct "cp ~/cp/template/template.cpp ."

function cpy
	cat  "$argv[1] | xclip -selection c"
end

function cr
	mkdir  "$argv[1]"
	cd  "$argv[1]"
	ct
	mv template.cpp  "$argv[1].cpp"
	vim  "$argv[1].cpp"
end

function cmp
	set BIN_FILE "prog"
	g++  (find . -name '*.cpp') -o $BIN_FILE -Wshadow -Wall -fsanitize=address -fsanitize=undefined -std=c++17
end

function cpy
	cat (find . -name '*.cpp') | pbcopy
end