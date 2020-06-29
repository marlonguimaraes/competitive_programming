set diffopt+=vertical

set number

set expandtab           " enter spaces when tab is pressed
set textwidth=80       " break lines when line length increases
set tabstop=4           " use 4 spaces to represent tab
set softtabstop=4
set shiftwidth=4        " number of spaces to use for auto indent
set autoindent          " copy indent from current line when starting a new line

" make backspaces more powerfull
set backspace=indent,eol,start

set ruler				" show line and column number
syntax on               " syntax highlighting
set showcmd             " show (partial) command in status line

set pastetoggle=<F2>

" Copying files to clipboard. Requires vim-gtk.
set clipboard=unnamedplus
nmap <F3> gg"+yG

set t_Co=8

" allow mouse to work inside vim
"set mouse=a

map <C-h> <C-W>h
map <C-j> <C-W>j
map <C-k> <C-W>k
map <C-l> <C-W>l
