" 去除自动注释
set fo-=r

" about typing
set number "show number of line
set tabstop=8 "set width of tab
set autoindent "auto indent tab
set shiftwidth=8
set softtabstop=8
set cindent "usin c/c++ auto indent
set colorcolumn=80 "set cc=80 设置行宽

"about ui
" set background=dark
set showmatch
set ruler
set linebreak
" set cursorline
"hi CursorLine cterm=NONE ctermbg=darkred ctermfg=white

"about search
set hlsearch
set ignorecase "ignore case in search
set incsearch "search intime while typing

set showcmd
set showmode

"about coding syntax
syntax enable
syntax on
set foldmethod=syntax
set foldlevelstart=99 "avoid all code is folded when open file
nnoremap <space> @=('za')<CR>

" detect file type
set nocompatible              " be iMproved, required
filetype off                  " required
"filetype on
filetype plugin on

"other
set ignorecase
set backspace=2

"about file
set nobackup
set encoding=utf-8
set fileencoding=utf-8

" change leader key
let mapleader=","


" set the runtime path to include Vundle and initialize
set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()
Plugin 'VundleVim/Vundle.vim'
Plugin 'Valloric/YouCompleteMe'
"Plugin 'Valloric/ListToggle'
"Plugin 'scrooloose/syntastic'
Plugin 'scrooloose/nerdtree'
" 这个插件可以显示文件的 Git 增删状态
Plugin 'Xuyuanp/nerdtree-git-plugin'
Plugin 'scrooloose/nerdcommenter'
call vundle#end()            " required


" setting for youcompleteme, autocomplete tools
let g:ycm_min_num_of_chars_for_completion = 1
let g:ycm_confirm_extra_conf = 0
let g:syntastic_always_populate_loc_list = 1 
let g:ycm_key_invoke_completion = "<leader>p" 
let g:ycm_autoclose_preview_window_after_insertion = 1

nnoremap <F5> :YcmForceCompileAndDiagnostics<CR>
nnoremap <leader>jc :YcmCompleter GoToDeclaration<CR>
nnoremap <leader>jd :YcmCompleter GoToDefinition<CR>
nnoremap <leader>j :YcmCompleter GoToDefinitionElseDeclaration<CR>


" file tree
" NERDTree: file tree plugin Setting
" toggle window
map <C-n> :NERDTreeToggle<CR>
" 当不带参数打开 Vim 时自动加载项目树
autocmd StdinReadPre * let s:std_in=1
autocmd VimEnter * if argc() == 0 && !exists("s:std_in") | NERDTree | endif
" 当所有文件关闭时关闭项目树窗格
autocmd bufenter * if (winnr("$") == 1 && exists("b:NERDTreeType") && b:NERDTreeType == "primary") | q | endif
" 不显示这些文件
let NERDTreeIgnore=['\.pyc$', '\~$', 'node_modules'] "ignore files in NERDTree
" 不显示项目树上额外的信息，例如帮助、提示什么的
let NERDTreeMinimalUI=1


" NERD-commenter setting
map <C-m> <leader>c<space>

" set for authorinfo.vim plugin
let g:vimrc_author='mardyu'
let g:vimrc_email='michealyxd@hotmail.com'
nnoremap <F4> :AuthorInfoDetect<CR>
