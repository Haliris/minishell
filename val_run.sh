#!/bin/bash

dir=$(pwd)

valgrind --leak-check=full --track-origins=yes --trace-children=yes --track-fds=yes --suppressions=$dir/readline.supp  ./minishell
