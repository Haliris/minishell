#!/bin/bash

MINISHELL_PATH="./minishell"
TEST_COMMANDS="test_commands.txt"
TEMP_DIR="./shell_comparison"

mkdir -p "$TEMP_DIR"

coproc MINISHELL { "$MINISHELL_PATH"; }
sleep 1

while IFS= read -r cmd
do
    echo "Testing command: $cmd"

    bash -c "$cmd" > "$TEMP_DIR/bash_output" 2> "$TEMP_DIR/bash_error"

    echo "$cmd" >&${MINISHELL[1]}
	echo >&${MINISHELL[1]}
	sleep 0.5

	read -r echoed_cmd <&${MINISHELL[0]}
	sleep 0.5

    read -r output <&${MINISHELL[0]}
    echo "$output" > "$TEMP_DIR/minishell_output"
    echo "Bash output:"
    cat "$TEMP_DIR/bash_output"
    echo "Minishell output:"
    cat "$TEMP_DIR/minishell_output"
    if ! diff -q "$TEMP_DIR/bash_output" "$TEMP_DIR/minishell_output" >/dev/null
    then
        echo "Difference in stdout for command: $cmd"
        echo "Diff:"
        diff "$TEMP_DIR/bash_output" "$TEMP_DIR/minishell_output"
        echo
    fi

done < "$TEST_COMMANDS"

pkill -P $MINISHELL_PID
rm -rf $TEMP_DIR

