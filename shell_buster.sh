#!/bin/bash

MINISHELL_PATH="./minishell"
TEST_COMMANDS="test_commands.txt"
TEMP_DIR="./shell_comparison"
FIFO_PATH="$TEMP_DIR/minishell_fifo"

mkdir -p "$TEMP_DIR"
mkfifo "$FIFO_PATH"

# Start minishell in the background, reading from the FIFO
$MINISHELL_PATH < "$FIFO_PATH" > "$TEMP_DIR/minishell_output" 2>&1 &
MINISHELL_PID=$!

echo "
  _________.__           .__  .__    __________                    .__            
 /   _____/|  |__   ____ |  | |  |   \______   \_________.__. ____ |  |__   ____  
 \_____  \ |  |  \_/ __ \|  | |  |    |     ___/  ___<   |  |/ ___\|  |  \ /  _ \ 
 /        \|   Y  \  ___/|  |_|  |__  |    |   \___ \ \___  \  \___|   Y  (  <_> )
/_______  /|___|  /\___  >____/____/  |____|  /____  >/ ____|\___  >___|  /\____/ 
        \/      \/     \/                          \/ \/         \/     \/        
"

# Function to send a command to minishell
send_command() {
    echo "$1" > "$FIFO_PATH"
    sleep 0.1
}

# Read and discard the initial prompt
send_command ""

while IFS= read -r cmd
do
    echo "Testing command: $cmd"

    # Run in Bash
    bash -c "$cmd" > "$TEMP_DIR/bash_output" 2> "$TEMP_DIR/bash_error"

    # Clear previous minishell output
    truncate -s 0 "$TEMP_DIR/minishell_output"

    # Send command to minishell
    send_command "$cmd"

    # Wait for output
    sleep 0.5

    # Process minishell output
    sed '1d;/minishell>/d' "$TEMP_DIR/minishell_output" > "$TEMP_DIR/minishell_processed"

    cat "$TEMP_DIR/minishell_processed"

    if ! diff -q "$TEMP_DIR/bash_output" "$TEMP_DIR/minishell_processed" >/dev/null
    then 
        echo "Difference in stdout for command: $cmd"
        echo "Diff:"
        diff "$TEMP_DIR/bash_output" "$TEMP_DIR/minishell_processed"
        echo 
	else
		echo "Diff ok! :)"
    fi  

done < "$TEST_COMMANDS"

# Clean up
kill $MINISHELL_PID
rm -rf "$TEMP_DIR"