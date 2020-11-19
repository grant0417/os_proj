Hello everybody out there using Linux -

I'm doing a (free) operating system (just a hobby, won't be big and
professional like gnu) for x86\_64.  This has been brewing since may,
and is starting to get ready.  I'd like any feedback on things people
like/dislike in Linux, as my OS resembles it somewhat (same physical 
layout of the file-system (due to practical reasons) among other things).

I've currently ported bash(5.0) and gcc(10.1), and things seem to work.
This implies that I'll get something practical within a few months, and
I'd like to know what features most people would want.  Any suggestions
are welcome, but I won't promise I'll implement them :-)

                Grant (ggurvis@usf.edu)

PS.  Yes - it's free of any Linux code, and it has a multi-threaded fs.
It is NOT portable (uses x86\_64 task switching etc), and it probably never
will support anything other than AT-harddisks, as that's all I emulate :-(.
