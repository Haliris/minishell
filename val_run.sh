#!/bin/bash

dir=$(pwd)

valgrind --leak-check=full --track-origins=yes --trace-children=yes --track-fds=yes --show-leak-kinds=all --suppressions=$dir/readline.supp  ./minishell
