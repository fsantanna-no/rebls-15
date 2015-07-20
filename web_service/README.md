# A crude little attempt at binding libmicrohttpd to Ceu.

The goal is something where the user can create and view entities,
which are stored (in memory) server-side.

Possibly relevant: https://github.com/komarserjio/notejam

It's not there yet.

To build and run:

    ./ake
    ./minimal_example 8888 1000

Then start a web server and navigate to localhost:8888



The "Created" organisms spawned by POST stick around,
but they don't do anything to influence the "Reporter"
organisms's reports.

Also, it's ugly.

Possibly libmicrohttpd and Ceu are somewhat stepping on one another's toes
(I think Ceu might be an excellent way to write a replacement for libhttpd).
libmicrohttpd is somewhat acting as an event-driven scheduler,
and perhaps using BSD sockets and select directly is the way to go.

Also, I'd like to fix the build so that it isn't inside this repo,
and this build complains about the lack of libmicrohttpd if it isn't
already available.


