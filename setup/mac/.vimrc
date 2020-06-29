set diffopt+=vertical

set background=dark
set number
set tabstop=4 softtabstop=0 noexpandtab shiftwidth=4
set autoindent
set cindent

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
