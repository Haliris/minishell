#!/bin/bash

MINISHELL_PATH="./minishell"
TEST_COMMANDS="test_commands.txt"
TEMP_DIR="/tmp/shell_comparison"

mkdir -p "$TEMP_DIR"

coproc MINISHELL { "$MINISHELL_PATH"; }

while IFS= read -r cmd
do
    echo "Testing command: $cmd"

    bash -c "$cmd" > "$TEMP_DIR/bash_output" 2> "$TEMP_DIR/bash_error"

    echo "$cmd" >&${MINISHELL[1]}
    read -r output <&${MINISHELL[0]}
    echo "$output" > "$TEMP_DIR/minishell_output"

    if ! diff -q "$TEMP_DIR/bash_output" "$TEMP_DIR/minishell_output" >/dev/null
    then
        echo "Difference in stdout for command: $cmd"
        echo "Bash output:"
        cat "$TEMP_DIR/bash_output"
        echo "Minishell output:"
        cat "$TEMP_DIR/minishell_output"
        echo "Diff:"
        diff "$TEMP_DIR/bash_output" "$TEMP_DIR/minishell_output"
        echo
    fi

done < "$TEST_COMMANDS"

kill $COPROC_PID
rm -rf "$TEMP_DIR"
