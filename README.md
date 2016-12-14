Server Benchmarking
===================

## Description
This project aims to do server benchmarking for different kind of server implementations.<br>
Use apache `ab` to do load testing. Command: `ab -n 1000 -c <concurrency> -r http://server-ip:9876/`. And benchmarking result is showed with charts. For all kind of servers, `handle_request()` will `sleep` the working thread for 30 - 50 milliseconds to simulate a business server. And all server runs on `AWS EC2 Linux 3.14.35-28.38.amzn1.x86_64`, and set `net.core.somaxconn=1024`, and `listen(fd, backlog=1000)`.

## Benchmarking Parameters
 - **millisecond per request:** time cost on every http request.
 - **request per second:** http requests handled per second.

## Blocking Server With Single Thread
**Blocing Server With Single Thread:** (request) => LOOP[(accpet connection) => (read request) => (handle request) => (response) => (close connection)], this routine is done in a single thread.<br>
**Name:** [blocking_server_v1](#)
