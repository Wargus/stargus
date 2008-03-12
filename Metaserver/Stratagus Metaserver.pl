/*********************************************************
	Stratagus Metaserver Perl Implementation
		Published under the GPLv3
*********************************************************/

#!/usr/bin/perl

use strict;
use Socket;
use String::Scanf;

/* The default server port */
$DefaultPort = 12345;

/* Username List */
@Usernames = ('\0'); # FIXME: Make these linked lists

/* IP Address of logged in users */
@IPAddress = ('\0');

/* List of waiting Games */
@Games = ('\0');

/* List of game hosts name */
@HostName = ('\0');

/* The protocol */
$Protocol  = getprotobyname('tcp'); # FIXME: Is this the right protocol?

@ClientCommands = {
	1,  # Add user
	2,  # Remove User
	3,  # Log in
	4,  # Log out
	5,  # Request game list
	6,  # Join game
	7,  # Leave Game
	8,  # Create Game
	9,  # Destroy Game
	10, # Start Game
	11  # Send Message
	# FIXME: Need more commands
};

/* Main - The mainloop of the server */
sub Main {

	print("Initializing sockets...");
	socket(SOCKET, PF_INET, SOCK_STREAM, $Protocol) 
		or die "Can't open socket $!\n";

	sleep(2);
	print("Setting socket options...");
	setsockopt(SOCKET, SOL_SOCKET, SO_REUSEADDR, 1) 
		or die "Can't set socket option to SO_REUSEADDR $!\n";

	sleep(2);
	print("Binding network address to socket...");
	bind(SOCKET, pack('Sn4x8', AF_INET, $DefaultPort, "\0\0\0\0"))
		or die "Can't bind to port $DefaultPort! \n";

	listen(SOCKET, 5) 
		or die "listen: $!";

	print("Listening for connections...");
	while ($client_addr = accept(NET_SOCKET, SOCKET)) {
		print NEW_SOCKET "Smile from the server";
		close NEW_SOCKET;
	}
};

/* InitServer - Initialize the server */
sub InitServer {
	for($d = 0; d < 1000; d++)
	{
		push(@Usernames, '\0');
		push(@IPAddress, '\0');
		push(@Games, '\0');
	}
};

/* AddUser - TAdd a user to list */
sub AddUser {
	$User = $_;
	$count = 0;
	while(@Usernames[$count] != '\0')
	{
		if(@Usernames[$count] == $User)
			return 1;
		$count++;
	}
	@Usernames[$count] = $User;
	return 0;
};

/* RemoveUser - REmove user from list */
sub RemoveUser {
	$User = $_;
	$count = 0;
	while(@Usernames[$count] != NULL)
	{
		if(@Usernames[$UserNumber] == $User)
		{
			@Usernames[$count] = '\0';
			return 0;
		}
		$count++;
	}
	return 1;
};

/* LogIn - Log a user in */
sub LogIn {
	@Param = @_;
	$count = 0;
	while(@Usernames[$count] != @Param[0])
	{
		if(@Usernames[$count] == @Param[0])
		{
			@IPAddress[$count] = @Param[1];
			return 0;
		}
		$count++;
	}
	return 1;
};

/* LogOut - Log a user out */
sub LogOut {
	$User = @_;
	$count = 0;
	while(@Usernames[$count] != $User)
	{
		if(@Usernames[$count] == $User)
		{
			@IPAddress[$count] = '\0';
			return 0;
		}
		$count++;
	}
	return 1;
};

/* CreateGame - Create a game */
sub CreateGame {
	@Game = @_;
	$count = 0;
	while(@Games[$count] != '\0')
	{
		if(@Games[$count] == @Game[0])
			return 1;
		$count++;
	}
	@Games[$count] = @Game[0];
	@HostName[$count] = @Game[1];
	return 0;
};

/* ParseCommand - Identify and parse a command from client */
sub ParseCommand {
	# <.<CommandID,Param1,Param2,Param3,Param4>.>
	$command = $_;
	($commandID, $param1, $param2, $param3, $param4) = sscanf("<.<%d%,%s,%s,%s,%s>.>", $command);
	
	if($commandID == @ClientCommands[0])
	{
		if(&AddUser($param1) == 1)
			return "Error: Username taken";
		else
			return "Success: Username registered!";
	}
	else if($commandID == @ClientCommands[1])
	{
		if(&RemoveUser($param1) == 1)
			return "Error: Username doesnt exist";
		else
			return "Success: Username removed!";
	}
	else if($commandID == @ClientCommands[2])
	{
		@ParamLogin = ($param1, $param2);
		if(&LogIn(@ParamLogin) == 1)
			return "Error: Username not found";
		else
			return "Success: Logged in!";
	}
	else if($commandID == @ClientCommands[3])
	{
		if(&LogIn($param1) == 1)
			return "Error: User not logged in";
		else
			return "Success: User logged in!";
	}
	else if($commandID == @ClientCommands[4])
	{
		
	}
	else if($commandID == @ClientCommands[5])
	{
		
	}
	else if($commandID == @ClientCommands[6])
	{
		
	}
	else if($commandID == @ClientCommands[7])
	{
		
	}
	else if($commandID == @ClientCommands[8])
	{
		
	}
	else if($commandID == @ClientCommands[9])
	{
		
	}
	else if($commandID == @ClientCommands[10])
	{
		
	}
	return;
};

