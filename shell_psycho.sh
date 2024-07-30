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
echo                         "....... ...............................    ..........................',;,,,'.................'''''',,,,,,;;;;;;::::ccccclllloo
                        ............................... .......................................,;;;;:;,'...........''''''',,,,,,;;;;;:::::cccclllllooo
                        .........................   ............................................',;;;cll:,'.......'''''',,,,,,;;;;;::::ccccccllloooood
                        ...........   ........  .................................................'',,;codxdc'....'''''',,,,,,;;;;;::::cccccllllooooddd
                .................    .....      ....''..............................................';codk00o,''''''',,,,,,,;;;;;:::cccccllllloooddddd
                ............       ...        ...,;;::;;;;,,,,',,,,'''''.........................''',;codkKXXk:'''''',,,,,;;;;;::::cccccllllooooddddxx
                ............     ....       ..',;:::::::::::::::;;;,,,,,'''''....................'',:ccldkOXN0o:;,'',,,,;;;;;:::::cccclllloooooddddxxx
                ............    ......     .',;:::::::ccc:::::::::;;;,,,'''''''..................'',:odxxkO0K0xoc;',,,,;;;;;:::cccccllllloooooddddxxxk
.......        ............   ........    .';::::::::::::::::::::::;;;;,,,''''''''...............',,cdOKK0Okkkkdc,,,,,,,;;;:::cccccllllloooodddddxxxkk
.......        ...........   ........    .';:;:::::::::::::::::::::::;;,,,,,,,,'''''''...........';:cokXNX0kxkkdc;,,,,,,;;;:::ccccclllooooodddddxxxxkk
..........................   ......     ..;::;::::::::::::::::::::::::;;,,,,,,,,,,'''''..........';:cox0NNKkdxO0Od;,,,;;;;:::ccccccllloooodddddxxxxkkk
.......................  .........     ..,;:::::::ccccc::::::::::::::::;;;;;;;;,,,,'''''..........';cod0NWXkolxKXXx:,;;;;::::ccccllllooooodddddxxxkkkk
......................   ........     ..';:::::ccccccccccccc:ccccc:::c::;;;;;;;;;,,,,''''..........,:lx0NWXxlccxKNXk:;;;;:::ccccllllloooodddddxxxxkkkO
......................   ........    ...,:::cccccccccclccccc:ccccccccc::;;;;;;;;;;,,,,,'''.........',:xKNWXkoc:cxKNNk:;:::::ccccclllloooodddddxxxkkkkO
......................  .........   ...';:ccccclllllllcccccccccccccccc:::::::;;;;;;,,,,,'''.........',o0NWNOoc::lkXWNkc::::ccccclllooooodddddxxxxkkkOO
               ....... ..........  ....,:cccccllllllllllllcccccccccc::::cc:::;;;;;;;,,,,'''''........'cOXWN0dc::cd0NWNkc:::cccclllooooodddddxxxxkkkkOO
        .........................  ....,:ccclllllloolloolllccccccccc:::cccc::;;;;;;;,,,,'''''.........:xKWWKkoc:clkXNMXdc::ccccllloooooddddxxxxxkkkOOO
    ...................................,:clllllllooollllllcccccccccc::::cc:::;;;;;;;,,,,''''''........,oKWWXOdlclox0NWWKo::ccccllloooooddddxxxxkkkOOOO
 ...................................''',:cllllllooolllolllccccccccccc::::::::;;;;;;;;,,'''''''........':kNWN0koloxkOXNWXxccccccllloooooddddxxxkkkkOOO0
................. ..................''',;cllllooooooollolllccccccccccc:::c:::::;;;;;;,,''''''..........,dXWWKOxddxOKXNWWOlccccclllooooodddxxxxkkkkOOOO
...............    .................'',,;clllooooooollllllccccc:::cccc:::::::::;;;,,,,,''''''..........':ONWNKkxxdkKXNWWKoccccclllooooddddxxxxkkkkOOO0
................  ................','',;;:cllllloollllllllcccccc::cccccccc::::::;;;;,,,'''''...........';kNWNKOkkkOKNNWWXxc:ccclllooooddddxxxkkkkOOOO0
.................................',;;;;;::clllloollllooollllcccc:::ccccccccccc::::;;,,,'''''...........':kNWWXOkOO0KNWWWXxcccccllloooodddxxxxkkkkOOOO0
................... .............,;;:::::ccllloolloooooooollcccc::::cccccccccc:::::;,,,,''''..........',cONWWXkxO0KXNWWWKoccccclllooodddddxxxkkkkOOOO0
................... .............,;;:::cccllloooooodooddddolllccccc:ccccccccccc::::;;,,,''......'.....,;l0NWWXkdkKXNNWWWKdcllcllllooodddddxxxkkkkOOOO0
..................   ............,;::::ccccllloooodoooddddoooollcc::cccccllllccc:::;;,,,,''.''''.....',ckXNWMNkox0XWWWWN0dclllllllooodddddxxxkkkkOOO00
        ..........   ... .. .....,;::::cccclllloooooooodoooooooollccclccclollccc:::;;,,,,,'''''''...'';lONWWMW0dx0NWWWWKxlllclllllooodddddxxxkkkOOOO00
..      ....... ...  ..     .....,;;:::::ccc:cccllloooooooooooloolccllc:cloolccc:::;;,,,,''''''''..'',:oOXWMWWXkk0NWWWNOdlllclllloooooddddxxxkkkOOOO00
..................    . .   ....',;;::::;;;,'''',,,,;:ccclloollllcccllc::looolccc::;;,'''..........'',:lk0XWMWXkkKNWWNXkocllllllloooooddddxxxxkkkOOO00
..................    .       ..',;;;;:;,,'''..'......''',;:::ccc::colc:;;loocc::;,,''...............',cxOKNWMNOkKNNNXKxlcccllllllooooddddxxxxkkkOOO00
     ..............           ..,,;;;;,;;;::::;;,,,,''.....'',,;;;:lolc:,':cc:;;,'.........'''''''''..';cx0NWMN0k0XKKN0occccclllllooooddddxxxxkkkOOOO0
    ................          ..,,;;,,,;:clllllllllllc:;,,''',,,;;coooc;,.'',,'........',;;;::;;,,,'''',;cd0NMW0xkK00NOoccccclllllooooddddxxxxkkkOOOO0
   ..................         .',,;;,,;:cllooolllc:;;,,'''',;;::cloodol:,...............',,'',,''''''',;;,:oKWWKxxO0kOOoccccccllllloooodddxxxxkkkOOO00
   ...................       ..',;;;;;:cccc:;,,'.,'.......',,;cllooddol:,'...............',...........',,'':OWWXxdkOdxOo:ccccclllllooooddddxxxxkkkOOO0
   .....................     ..',;;::ccc:,'..',,','...''''';::clloooool:,'............',,,,''''''''......'':ONWNkdkOxdko:ccccccllllooooodddxxxxkkkkOOO
    .................        ..',;;::cc:::::::c::;;;,,,,,,,;:cllllooolc:;'...........'',,;;;;;,,''''....''',dXWNkdxkOxxo::ccccclllloooooddddxxxxkkkOOO
     ..............         ...',;:::cccclllllooolcc::;;;;;;:cllloooolc:;'............'',;;;;;,,'.......''',oKNN0xkO0Oxl::cccccclllooooooddddxxxkkkkOO
     ..............         ...',;;:ccccllooooooooolllllc:::ccllloooll:;;'.............'',,,,,,,''''..'''',;o0NWKkkOO0kl::ccccccllllloooooddddxxxkkkOO
     ..............          ..',,;:cclllloooddddddddoolccclloolooolll::;'..............''',,,,,,,'''''''',;o0NNOddkxkOo:::ccccccllllloooodddddxxxkkkk
.  ................          ..'',;:cclllllooddddddoolcccloooooooollllc:;'...............''',,,,,,'''''''',:dKWXxloxlckx::::cccccclllllooooddddxxxxkkk
...................        .....',;:ccllollooooooooollllodddoooooollllc:;'................'''',,,,,,,,''''';dKWKocdd:;dxc::::cccccclllllloooddddxxxxkk
...................        .....',;::cllloooodddddoooooodddoooooooollll:,'................'''''',,,,''''''';xXWOlcxxc;cdl:::::ccccccclllllooooddddxxxk
...................         ....',;;:ccllloodddddooooooddddooooooolllll:,'.................''''''''''''''.';xXNOoxOdolldc;:::::::cccccclllloooddddxxxx
...................          ....',;:ccclloooddooooooooddddooooollllllc:;,...................'''''''''....',dKWX0XO:lodd:;;:::::::ccccccllllooooddddxx
....................  ..     ....',;::ccllllooddddoooooddddooollllllolc:;,'...................'''''''....'',oKWNWWO:;:oo;;;;;::::::ccccccllllloooodddx
....................  ...........',;:::cccllooddddoooooddddoolllllloddlc:;''...................''''.......',oKWWNWO;,co:;;;;;;;;:::::::ccccllllooooddd
.....................   ..........',;::cccclooododdddooooollllllllodxdlcc:,'...........................''.',oKWWWWk;;c:,;;;;;;;;;;::::::cccclllllooodd
..................................',;::cccclloooooddddoolllllllllllooolcc:;,'.........................'''.',oKNWWWk:;;,,,,,,;;;;;;;;;:::::cccclllllooo
..................................',;::ccccclloodddooollllloolc:::cllllcc:,,'.........................','.';dKNNWNd,,,,,,,,,,,;;;;;;;;;:::::cccclllloo
..................................',;:::cccclloooddoollllooolllccccccc:::;'................'''........,,,'';dKXXNXl,,,,,,,,,,,,,,;;;;;;;;:::::ccccllll
..................................',,;::cccclllloddoolloooolllllllccc:;,,,'................'''........','.';oO0KN0:',',,',,,,,,,,,,,;;;;;;;:::::ccccll
..................................',,;::ccccllllooolllolllllllllllllc;'';c:;,................''.......','',:oxk0Kx;','','',,,,,,,,,,,,;;;;;;;::::ccccc
 .................................'',;;:cccccllllollllllllllccccclllc;',clc:;'.......................'''',:cccoOkc'''''''''''',,,,,,,,,,,;;;;;;:::::cc
 .................................'',,;::cccclllllccccccccccccccclll:,,;clcc:,,'.....................''.',::::ldl,''''''''''''''',,,,,,,,,,;;;;;::::::
 ..................................',,;;::cccclllccccccccccccllllllc:;,;;:::;,,''''..................''..,:;;;:c,''..''''''''''''''',,,,,,,,,,;;;;;:::
...................................'',,;::ccccllccccccccclllllllllllc:::;;;;;,,''....................,,..,;;,;;,''.....'.''''''''''''',,,,,,,,,;;;;;;;
....................................',,;:::cclllc:cc:::;::::::::::::;;;;,''..........................',..,;,',,'.............'''''''''''',,,,,,,,,;;;;
.....................................',,;::cclllc:::::;::::::;;;;;;;,,,''.......................''...',..',',,..................'''''''''''',,,,,,,,,;
......................................',;;:::clllc::cccccccllcccccccc:::;;,,,,''...............''....''..',,,'..'...................''''''''',,,,,,,,,
  .....................................',;;;::cclc::cccccccccccc::::;;;;;,,,,''''........................';:;.........................'''''''''''',,,,
   ....................................'',;;;::::::cc::cccccccc::;;,,,,,,''',,''........................',;l;............................''''''''''',,
   .....................................',,;;;:::::cccccc::::::::;;,,,,,,,',,,'''......................',';o;..............................'''''''''''
  .......................................',,,;;:::cccccccc::c::::::;;;::;;;;;,,'''.....................,'';l:'..................................''''''
     .....................................',,;;::::cccccccccccccclllccccc::::;;,,''...................''..,oo''...................................''''
     ................................ ....'',;;;;;;::cccccllccccclllcccc::::;;,,,''.......................'dk;.,'.....................................
     ...............................  ....''',;;;;;;;::cccclllccclcllccc::::;;,,''........................'o0o..,,....................................
     ............................      ......',,;;;;;;;:::cccccccllcc:::;;;;;,,,''........................'l0O,..::'..................................
     ..   .....................        .....'''',,,,,,;;::::::::cc:::;,,,,,,,,,,''........................,lOO:..':c:,'...............................
     .          ........              ......'''''',,,,,,;;::::;;;;;;;,'''''''''''.........................,lkk;...,cl:;,,''...........................
               ...                    ...'''''',,,,,,,,,;;;;;;;;,,,,,'''''................................,cxd,....;cc:,..''''''......................
                                      ...''''''',,,,,,;,,,,,,,,''''''''...................................':l:.....,:c:;'.........',,,,'..............
                                      ...''',,,,',,,,,;;;;,,,,,,,,,''''''..................................,;'......;cc:,'...........',;;;;;,'........
                                       ..''',,,;,,,,;;;;;;;,,,,,,,,''''''...................................... .....,::,'................';:c::;,....
                                       ..''',,;;;;;;;;;;;;;;;;;,,,,'''''''....................................  ......,;;'...................',;clll:;"

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
    sleep 0.1

    # Process minishell output
    sed '1d;/minishell>/d' "$TEMP_DIR/minishell_output" > "$TEMP_DIR/minishell_processed"

    if ! diff -q "$TEMP_DIR/bash_output" "$TEMP_DIR/minishell_processed" >/dev/null
    then 
        echo "Diff KO :( : $cmd"
        echo "Diff:"
        diff "$TEMP_DIR/bash_output" "$TEMP_DIR/minishell_processed"
        echo 
	else
		echo "Diff ok! :)"
    fi  

done < "$TEST_COMMANDS"

# Clean up
kill $MINISHELL_PID
rm -rf output.txt output2.txt output3.txt output4.txt
rm -rf "$TEMP_DIR"