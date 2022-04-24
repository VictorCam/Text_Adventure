# Text_Adventure
 A Text Adventure Game

<p><span style="font-size: xx-large;">Program 2 – CS 344</span></p>
<p>This assignment asks you to write a simple game akin to old text adventure games like Adventure:</p>
<p><a href="http://en.wikipedia.org/wiki/Colossal_Cave_Adventure" class="external" target="_blank" rel="noreferrer noopener"><span>http://en.wikipedia.org/wiki/Colossal_Cave_Adventure</span><span aria-hidden="true" class="ui-icon ui-icon-extlink ui-icon-inline" title="Links to an external site."></span><span class="screenreader-only">&nbsp;(Links to an external site.)</span></a></p>
<p>You'll write two programs that will introduce you to programming in C on UNIX based systems, and will get you familiar with reading and writing files.&nbsp;</p>
<h1>Overview</h1>
<p>This assignment is split up into two C programs (no other languages is allowed). The first program (hereafter called the "rooms program") will be contained in a file named "&lt;<em>STUDENT&nbsp;ONID USERNAME</em><em>&gt;</em>.buildrooms.c", which when compiled with the same name (minus the extension) and run&nbsp;creates a series of files that hold descriptions of the in-game rooms and how the rooms are connected.</p>
<p>The second program (hereafter called the "game") will be&nbsp;called "&lt;<em>STUDENT&nbsp;ONID USERNAME</em><em>&gt;</em>.adventure.c" and when compiled with the same name (minus the extension) and run&nbsp;provides&nbsp;an interface for playing the game using the most recently&nbsp;generated rooms.</p>
<p>In the game, the player will begin in the "starting room" and will win the game automatically upon entering the "ending room", which causes the game to exit, displaying the path&nbsp;taken by the player.</p>
<p>During the game, the player can also enter a command that returns the current time - this functionality utilizes&nbsp;mutexes and multithreading.</p>
<p>For this assignment, do not use the C99 standard: this should be done using raw C (which is C89). In the complete example and grading instructions below,&nbsp;note the absence of the -c99 compilation flag.</p>
<h1>Specifications</h1>
<p><strong>Rooms Program</strong></p>
<p>The first thing your rooms program must do is create a directory called "&lt;<em>YOUR&nbsp;STUDENT&nbsp;ONID USERNAME</em><em>&gt;</em>.rooms.<em>&lt;PROCESS ID OF ROOMS PROGRAM&gt;"</em>. Next, it must generate 7 different room files, which will contain one room per file, in the directory just created. You may use any filenames&nbsp;you want for these 7 room files, and these names should be hard-coded into your program. For example, if John Smith was writing the program, he might see this directory and filenames. Note that 19903 was the PID of the rooms program at the time it was executed, and was not hard-coded:</p>
<pre>$ ls smithj.rooms.19903<br>Crowther_room Dungeon_room PLUGH_room PLOVER_room twisty_room XYZZY_room Zork_room</pre>
<p>The elements that make up an actual room defined inside&nbsp;a room file are listed below, along with some additional specifications:</p>
<ul>
<li>A <strong>Room Name</strong>
<ul>
<li>A&nbsp;room name cannot be assigned to more than one room.</li>
<li>Each name can be at max 8 characters long, with only uppercase and lowercase letters allowed (thus, no numbers, special characters, or spaces). This restriction is not extended to the room file's filename.</li>
<li>You must hard code a list of ten different Room Names into your rooms program and have your rooms program randomly assign one of these to each room generated. Thus, for a given run of your rooms program, 7 of the 10 hard-coded room names will be used.</li>
</ul>
</li>
<li>A <strong>Room Type</strong>
<ul>
<li>The possible room type entries are: START_ROOM, END_ROOM, and MID_ROOM.</li>
<li>The assignment of which room gets which type should be randomly generated each time the rooms program is run.</li>
<li>Naturally, only one room should be assigned the START_ROOM type, and only one room should be assigned the END_ROOM type. The rest of the rooms will receive the MID_ROOM type.</li>
</ul>
</li>
<li>
<strong>Outbound connections</strong> to other rooms
<ul>
<li>There must be at least 3 outbound connections and at most 6 outbound connections from this room to other rooms.</li>
<li>The oubound connections from one room to other rooms should be assigned randomly each time the rooms program is run.</li>
<li>Outbound connections must have matching connections coming back: if room A connects to room B, then room B must have a connection back to room A. Because of all of these specs, there will always be at least one path through.</li>
<li>A room cannot have an outbound connection that points to itself.</li>
<li>A room cannot have more than one outbound connection to the same room.</li>
</ul>
</li>
</ul>
<p>Each file that stores a&nbsp;room must have exactly this format, where the … is additional outbound room connections, as randomly generated:</p>
<pre>ROOM NAME:<em> &lt;room name&gt;</em><br>CONNECTION 1: <em>&lt;room name&gt;</em><br>…<br>ROOM TYPE: <em>&lt;room type&gt;</em></pre>
<p>Here are the contents of files representing three <em>sample</em> rooms from a full set of room files (remember, you must use this same format).&nbsp;My list of room names includes the following, among others: XYZZY, PLUGH, PLOVER, twisty, Zork, Crowther, and Dungeon.</p>
<pre>ROOM NAME: XYZZY<br>CONNECTION 1: PLOVER<br>CONNECTION 2: Dungeon<br>CONNECTION 3: twisty<br>ROOM TYPE: START_ROOM<br>
ROOM NAME: twisty<br>CONNECTION 1: PLOVER<br>CONNECTION 2: XYZZY<br>CONNECTION 3: Dungeon<br>CONNECTION 4: PLUGH<br>ROOM TYPE: MID_ROOM<br>
... (Other rooms) ...<br><br>ROOM NAME: Dungeon<br>CONNECTION 1: twisty<br>CONNECTION 2: PLOVER<br>CONNECTION 3: XYZZY<br>CONNECTION 4: PLUGH<br>CONNECTION 5:&nbsp;Crowther<br>CONNECTION 6: Zork<br>ROOM TYPE: END_ROOM</pre>
<p>The ordering of the connections from a room to the other rooms, in the file, does not matter.&nbsp;Note that the randomization you do here to define the layout is not all that important: just make sure the connections between rooms, the room names themselves and which room is which type, is somewhat different each time the rooms program is run, however you want to do that. We're not evaluating your randomization procedure, though it's not acceptable to just randomize the room names yet use the same room structure every time.</p>
<p>I highly recommend building up the room graph in this manner: adding outbound connections two at a time (forwards and backwards), to randomly chosen room endpoints, until the map of all the rooms satisfies the requirements listed above. It's easy, requires no backtracking, and tends to generate sparser layouts.&nbsp;As a warning, the alternate method of choosing the number of connections <em>beforehand</em> that each room will have is <em>not recommended</em>, as it's hard to make those chosen numbers match the constraints of the map. To help do this correctly, please read the article <a class="" title="2.2 Program Outlining in Program 2" href="/courses/1738955/pages/2-dot-2-program-outlining-in-program-2" target="" data-api-endpoint="https://oregonstate.instructure.com/api/v1/courses/1738955/pages/2-dot-2-program-outlining-in-program-2" data-api-returntype="Page">2.2 Program Outlining in Program 2</a>&nbsp;and consider using the room-generating pseudo-code listed there!</p>
<p>Here is an example of the rooms program being compiled and then run. Note that it returns NO OUTPUT, unless there is an error:</p>
<pre>$ gcc -o smithj.buildrooms smithj.buildrooms.c<br>$ smithj.buildrooms<br>$</pre>
<p><strong>The Game</strong></p>
<p>Now let’s describe what should be presented to the player in the game. Once the rooms program has been run, which generates the room files, the game program can then be run. This program should present an interface to the player. Note that the room data must be read back into the program from the previously-generated room files, for use by the game. Since the rooms program may have been run multiple times before executing the game, your game should use the most recently created files: perform a <a href="https://linux.die.net/man/2/stat" class="external" target="_blank" rel="noreferrer noopener"><span><code>stat()</code> function call</span><span aria-hidden="true" class="ui-icon ui-icon-extlink ui-icon-inline" title="Links to an external site."></span><span class="screenreader-only">&nbsp;(Links to an external site.)</span></a> on rooms directories in the same directory as the game, and open the one with most recent <code>st_mtime</code> component of the returned <code>stat</code> struct.</p>
<p>This player interface should list where the player current is, and list the possible connections that can be followed. It should also then have a prompt. Here is the form that must be used:</p>
<pre>CURRENT LOCATION: XYZZY<br>POSSIBLE CONNECTIONS: PLOVER, Dungeon, twisty.<br>WHERE TO? &gt;</pre>
<p>The cursor should be placed just after the &gt; sign. Note the punctuation used: colons on the first two lines, commas on the second line, and the period on the second line. All are required.</p>
<p>When the user types in the exact name of a connection to another room (Dungeon, for example), and then hits return, your program should write a new line, and then continue running as before. For example, if I typed twisty above, here is what the output should look like:</p>
<pre>CURRENT LOCATION: XYZZY<br>POSSIBLE CONNECTIONS: PLOVER, Dungeon, twisty.<br>WHERE TO? &gt;twisty<br><br>CURRENT LOCATION: twisty<br>POSSIBLE CONNECTIONS: PLOVER, XYZZY, Dungeon, PLUGH.<br>WHERE TO? &gt;</pre>
<p>If the user types anything but a valid room name from this location (case matters!), the game should return an error line that says “HUH? I DON’T UNDERSTAND THAT ROOM. TRY AGAIN.”, and repeat the current location and prompt, as follows:</p>
<pre>CURRENT LOCATION: XYZZY<br>POSSIBLE CONNECTIONS: PLOVER, Dungeon, twisty.<br>WHERE TO? &gt;Twisty<br><br>HUH? I DON’T UNDERSTAND THAT ROOM. TRY AGAIN.<br><br>CURRENT LOCATION: XYZZY<br>POSSIBLE CONNECTIONS: PLOVER, Dungeon, twisty.<br>WHERE TO? &gt;</pre>
<p>Trying to go to an incorrect location does not increment the path history or the step count. Once the user has reached the End Room, the game should indicate that it has been reached. It should also print out the path the user has taken to get there (this path should <em>not</em> include the start room), the number of steps taken (<em>not</em> the number of rooms visited, which would be one higher because of the start room), a congratulatory message, and then exit.</p>
<p>Note the punctuation used in the complete example below: we're looking for&nbsp;the same punctuation in your program.</p>
<p>When your program exits, set the exit status code to 0, and leave the rooms directory in place, so that it can be examined.</p>
<p>If you need to use temporary files (you probably won't), place them in the directory you create, above. Do not leave any behind once your program is finished. We will not test for early termination of your program, so you don’t need to watch for those signals.</p>
<p><strong>Time Keeping</strong></p>
<p>Your game program must also be able to return the current time of day by utilizing a second thread and mutex(es). I recommend you complete all other portions of this assignment first, then add this mutex-based timekeeping component last of all. Use the classic pthread library for this simple multithreading, which will require you to use the "-lpthread" compile option switch with gcc (see below for compilation example).</p>
<p>When the player types in the command "time" at the prompt, and hits enter, a second thread must write the current time in the&nbsp;format shown below (use <a href="https://linux.die.net/man/3/strftime" class="external" target="_blank" rel="noreferrer noopener"><span>strftime()</span><span aria-hidden="true" class="ui-icon ui-icon-extlink ui-icon-inline" title="Links to an external site."></span><span class="screenreader-only">&nbsp;(Links to an external site.)</span></a> for the formatting) to a file called "currentTime.txt", which should be located in the same directory as the game (your adventure file). The main thread will then read this time value from the file and print it out to the user, with the next prompt on the next line. Additional writes to the "currentTime.txt" file should overwrite any existing contents. I recommend you keep the second thread running during the execution of the main program, and merely wake it up as needed via this "time" command. In any event, at least one mutex must be used to control execution between these two threads.</p>
<p>To help you know if you're using it right, remember these key points about mutexes:</p>
<ul>
<li>They're only useful if ...lock() is being called in multiple threads (i.e. having the only ...lock() and ...unlock() calls occur in one thread isn't using the mutex for control).</li>
<li>Mutexes allow threads to jockey for contention by having multiple locks (attempt to be) established.</li>
<li>A thread can be told to wait for another to complete&nbsp;with the ...join() function, resuming execution when the other thread finally terminates.</li>
</ul>
<p>Using the time command&nbsp;does not increment the path history or the step count. Do not delete the currentTime.txt file after your program completes - it will be examined by the grading TA.</p>
<p>Here is an example of the "time" command being run in-game:</p>
<pre>CURRENT LOCATION: XYZZY<br>POSSIBLE CONNECTIONS: PLOVER, Dungeon, twisty.<br>WHERE TO? &gt;time<br>
 1:03pm, Tuesday, September 13, 2016<br>
WHERE TO? &gt;</pre>
<p><strong>Complete Example</strong></p>
<p>Here is a complete example of the game being compiled and run, including the building of the rooms.&nbsp;Note the time command, incorrect spelling of a room name, the winning messages and formatting, and the return to the prompt with some examination commands following:</p>
<pre>$ gcc -o smithj.buildrooms smithj.buildrooms.c<br>$ smithj.buildrooms<br>$ gcc -o smithj.adventure smithj.adventure.c -lpthread<br>$ smithj.adventure<br>CURRENT LOCATION: XYZZY<br>POSSIBLE CONNECTIONS: PLOVER, Dungeon, twisty.<br>WHERE TO? &gt;Twisty<br><br>HUH? I DON’T UNDERSTAND THAT ROOM. TRY AGAIN.<br><br>CURRENT LOCATION: XYZZY<br>POSSIBLE CONNECTIONS: PLOVER, Dungeon, twisty.<br>WHERE TO? &gt;time<br>
 1:03pm, Tuesday, September 13, 2016<br><br>WHERE TO? &gt;twisty<br><br>CURRENT LOCATION: twisty<br>POSSIBLE CONNECTIONS: PLOVER, XYZZY, Dungeon, PLUGH.<br>WHERE TO? &gt;Dungeon<br><br>YOU HAVE FOUND THE END ROOM. CONGRATULATIONS!<br>YOU TOOK 2 STEPS. YOUR PATH TO VICTORY WAS:<br>twisty<br>Dungeon<br>$ echo $?<br>0<br>$ ls<br>currentTime.txt smithj.adventure smithj.adventure.c smithj.buildrooms<br>smithj.buildrooms.c smithj.rooms.19903<br>$ ls smithj.rooms.19903<br>Crowther_room Dungeon_room PLUGH_room PLOVER_room<br>twisty_room XYZZY_room Zork_room<br>$ cat smithj.rooms.19903/XYZZY_room<br>ROOM NAME: XYZZY<br>CONNECTION 1: PLOVER<br>CONNECTION 2: Dungeon<br>CONNECTION 3: twisty<br>ROOM TYPE: START_ROOM</pre>
<h2>Hints</h2>
<ul>
<li>You’ll need to figure out how to get C to read input from the keyboard, and pause until input is received. I recommend you use the getline() function as described in the lectures. You’ll also get the chance to become proficient reading and writing files. You may use either the older open(), close(), lseek() method of manipulating files, or the STDIO standard input library methods that use fopen(), fclose(), and fseek().</li>
<li>Remember that you cannot&nbsp;copy a string with the assignment operator (=) in C! You'll need to copy strings around using a member of the strcpy() family. Don't confuse string pointers with the character data itself.</li>
<li>For the timekeeping requirement, consider the following. Perhaps the <em>main</em> thread at its beginning locks a mutex, then spawns a <em>second</em> thread whose first action is to attempt to gain control of the mutex by calling ...lock(), which blocks itself. How is the second thread started up again, when the user types "time"? By the first thread calling ...unlock(). You can keep the first thread blocked while the second thread runs by calling ...join() in the first thread. Remember to relock the mutex in the main thread when it starts running again and then re-create the second thread.</li>
<li>I HIGHY recommend that you develop this program directly on our class&nbsp;server (see our&nbsp;<a title="Home Page" href="/courses/1738955/pages/home-page" data-api-endpoint="https://oregonstate.instructure.com/api/v1/courses/1738955/pages/home-page" data-api-returntype="Page">home page</a>). Doing so will prevent you from having problems transferring the program back and forth, which can cause compatibility issues.<br><br>If you do see ^M characters all over your files, try this command:<br>
<pre>$ dos2unix bustedFile</pre>
</li>
</ul>
<h2>What to Turn&nbsp;In and When</h2>
<p>What you’ll submit is a .zip file that contains both of your correctly named programs, which compile according to the instructions given above.&nbsp;As our Syllabus says,&nbsp;please&nbsp;be aware that neither the&nbsp;Instructor nor the TA(s)&nbsp;are alerted to comments added to the text boxes in Canvas that are alongside your assignment submissions, and they may not be seen. No notifications (email or otherwise) are sent out&nbsp;when these&nbsp;comments are added, so we aren't aware that you have added content! If you need to make a meta-comment about this assignment, please include it in&nbsp;a README file&nbsp;in your .zip file, or email the person directly who will be grading it (see the&nbsp;<a title="Home Page" href="/courses/1738955/pages/home-page" data-api-endpoint="https://oregonstate.instructure.com/api/v1/courses/1738955/pages/home-page" data-api-returntype="Page">Home</a>&nbsp;page for grading responsibilities).</p>
<p>The due date given below is the last minute that this can be turned in for full credit. The "available until" date is NOT the due date, but instead closes off submissions for this assignment automatically once 48 hours past the due date has been reached, in accordance with our <a class="" title="Course Syllabus" href="/courses/1738955/assignments/syllabus#grading" target="">Syllabus Grading policies</a>.</p>
<h1>Grading</h1>
<p>Remember that if your programs&nbsp;don't compile or run on our class server, you may&nbsp;receive a zero for the grade.</p>
<p>144 points are available for meeting all of the listed specifications, while the final 16 points will be based on your style, readability, and commenting. Comment well, often, and verbosely, approximately every four or five lines or so, as appropriate: we want to see that you are telling us WHY you are doing things, in addition to telling us WHAT you are doing.</p>
<p>The TAs will use this set of instructions: <span class="ally-file-link-holder link_holder"><span class="instructure_file_holder link_holder instructure_file_link_holder ally-file-link-holder"><a class="file_preview_link" title="Program2 Grading.pdf" href="/courses/1738955/files/76095677/download?wrap=1" target="" data-api-endpoint="https://oregonstate.instructure.com/api/v1/courses/1738955/files/76095677" data-api-returntype="File" data-id="76095677" aria-expanded="true" aria-controls="preview_1" style="">Program2 Grading.pdf</a><div class="inline-block ally-enhancement ally-user-content-dropdown">
    <a href="#" role="button" tabindex="0" class="al-trigger" aria-haspopup="true">
        <span class="screenreader-only">Actions</span>
    </a>
    <ul class="al-options ui-menu ui-widget ui-widget-content ui-corner-all ui-popup ui-kyle-menu use-css-transitions-for-show-hide" id="ui-id-1" role="menu" tabindex="0" aria-hidden="true" aria-expanded="false" style="display: none; top: 5487.57px; left: 357px;" aria-activedescendant="ui-id-3"><span class="ui-menu-carat" style="left: 93px;"><span></span></span>
        <li class="ui-menu-item" role="presentation"><a href="#" class="ally_trigger_inline_preview ui-corner-all" data-preview-id="preview_1" id="ui-id-2" tabindex="-1" role="menuitem">Preview</a></li>
        <li class="ui-menu-item" role="presentation"><a href="https://canvas.oregonstate.edu/courses/1738955/files/76095677/download?download_frd=1" data-id="76095677" id="ui-id-3" class="ui-corner-all" tabindex="-1" role="menuitem">Download</a></li>
        <li class="ui-menu-item" role="presentation"><a href="#" class="ally-accessible-versions ui-corner-all" data-id="76095677" id="ui-id-4" tabindex="-1" role="menuitem">Alternative formats</a></li>
    </ul>
</div><div role="region" class="preview_container" id="preview_1" style="display: block;"><a href="#" style="font-size: 0.8em;" class="hide_file_preview_link">Minimize File Preview</a><div style="overflow: auto; resize: vertical;        border: 1px solid transparent; height: 100%;"><iframe src="/api/v1/canvadoc_session?blob=%7B%22user_id%22:10020000006205318,%22attachment_id%22:76095677,%22type%22:%22canvadoc%22%7D&amp;hmac=1f732f07c1bb8b5c70a76b2279e37cdea4e4dbb7" style="width: 100%; border: 0px none; overflow: auto; height: 99%; min-height: 800px;" allowfullscreen="1"></iframe></div></div></span></span>&nbsp;to grade your submission.</p>