#!/bin/bash

valgrind --leak-check=full --track-origins=yes --trace-children=yes --track-fds=yes ./minishell
